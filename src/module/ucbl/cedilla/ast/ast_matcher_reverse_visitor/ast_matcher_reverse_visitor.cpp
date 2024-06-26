module;

#include "AstMatcherVisitor.h"
#define AST_MATCHER_FAILURE(N) \
	{\
		println("ASTMatcher failure. Exit point: {}:{} ({}) ", __FILE__, __LINE__, __func__);\
		N.success = false;\
		return N;\
	}

module ucbl.cedilla;

import :common;
import :ast;
import :ast_node;

namespace cedilla
{
	static fn extractAndReplaceEscapedQuotes(const string& input) -> string
	{
		if (input.front() != '"' || input.back() != '"') {
			throw invalid_argument("Input string must start and end with a quote.");
		}
		auto extracted = input.substr(1, input.length() - 2);
		auto result = string("");
		for (u64 i = 0; i < extracted.length(); i += 1) {
			if (extracted[i] == '\\' && (i + 1 < extracted.length()) && extracted[i + 1] == '"') {
				result += '"';
				i += 1;
			} else {
				result += extracted[i];
			}
		}
		return result;
	}

	InterpretReverseVisitor::InterpretReverseVisitor(Ast& ast, unordered_map<string, StateChecker> checkers)
		: StateCheckers(move(checkers))
	{
		it = ast.last; // Start from the end of the AST
		if (!it) {
			throw runtime_error("Trying to match ast with an empty string.");
		}
	}

	fn InterpretReverseVisitor::getTypeName(antlr4::tree::ParseTree *node) -> string
	{
		if (dynamic_cast<antlr4::tree::TerminalNode*>(node)) {
			return "TerminalNode";
		} else if (dynamic_cast<AstMatcherParser::AstPatternDescriptionContext*>(node)) {
			return "visitAstPatternDescription";
		} else if (dynamic_cast<AstMatcherParser::NodeTypeContext*>(node)) {
			return "visitNodeType";
		} else if (dynamic_cast<AstMatcherParser::NodePropertyContext*>(node)) {
			return "visitNodeProperty";
		} else if (dynamic_cast<AstMatcherParser::NodeTypeSequenceContext*>(node)) {
			return "visitNodeTypeSequence";
		} else if (dynamic_cast<AstMatcherParser::NodePropertySequenceContext*>(node)) {
			return "visitNodePropertySequence";
		} else {
			return "Unknown";
		}
	}

	fn InterpretReverseVisitor::visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context) -> any
	{
		println("Visiting visitAstPatternDescription in reverse order");
		AstMatcherVisitorOutput out = {unordered_map<string, AstNode*>(), true};

		if (!it)
			AST_MATCHER_FAILURE(out)

		auto result = visit(context->astRoot);
		auto resultMap = any_cast<AstMatcherVisitorOutput>(result);
		if (!resultMap.success)
			AST_MATCHER_FAILURE(out)

		out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());

		return out;
	}

	fn InterpretReverseVisitor::visitNodeType(AstMatcherParser::NodeTypeContext *context) -> any
	{
		println("Visiting visitNodeType: {}", context->getText());
		AstMatcherVisitorOutput out = {unordered_map<string, AstNode*>(), true};

		if (!it)
			AST_MATCHER_FAILURE(out)

		auto expectedType = context->IDENTIFIER(0)->getText();
		string alias;
		if (context->AS()) {
			alias = context->IDENTIFIER(1)->getText();
		}
		auto prev = it->prev;
		if (it->type == expectedType) {
			if (!alias.empty()) {
				out.matches[alias] = it;
			}

			println("Checking states...");
			if (context->nodePropertySequence()) {
				auto result = visit(context->nodePropertySequence());
				auto resultMap = any_cast<AstMatcherVisitorOutput>(result);
				if (!resultMap.success) {
					out.success = false;
					return out;
				}
				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
			}

			println("Checking childs...");
			if (context->nodeTypeSequence()) {
				auto child_it = it->childs.first->last();
				it = child_it;
				auto result = visit(context->nodeTypeSequence());
				auto resultMap = any_cast<AstMatcherVisitorOutput>(result);
				it = prev;  // Reset iterator after processing child nodes
				if (!resultMap.success) {
					out.success = false;
					return out;
				}
				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
			}
		} else {
			println("EXPECTED NODE TYPE: {} GOT {}", expectedType, it->type);
			AST_MATCHER_FAILURE(out)
		}

		it = prev;  // Ensure iterator is reset
		println("visitNodeType end.");

		return out;
	}

	fn InterpretReverseVisitor::visitNodeProperty(AstMatcherParser::NodePropertyContext *context) -> any
	{
		println("Visiting visitNodeProperty: {}", context->getText());

		auto state_key = context->IDENTIFIER(0)->getText();

		auto out = (AstMatcherVisitorOutput){unordered_map<string, AstNode*>(), true};

		if (!it)
			AST_MATCHER_FAILURE(out)

		if (!it->states.contains(state_key)) {
			println("ITM [{}] does not contain key", it->serialize());
			out.success = false;
			return out;
		}
		if (!context->EQUAL() && context->IDENTIFIER(1)) {
			// FuncCall
			auto state_key = extractAndReplaceEscapedQuotes(context->IDENTIFIER(1)->getText());
			throw runtime_error(format("{}:{} Not implemented", __FILE__, __LINE__));
		} else if (context->nodeTypeSequence()) {
			// AstNode as property
			throw runtime_error(format("{}:{} Not implemented", __FILE__, __LINE__));
		} else {
			// TODO: also support string instead of identifier
			auto state_value = extractAndReplaceEscapedQuotes(context->STRING(0)->getText());
			if (it->states[state_key]->serialize() != format("StringState({})", state_value)) {
				AST_MATCHER_FAILURE(out)
			} else {
				println("property match\n");
				out.matches[state_key] = it;
			}
		}
		return out;
	}

	fn InterpretReverseVisitor::visitNodeTypeSequence(AstMatcherParser::NodeTypeSequenceContext *context)
	-> any
	{
		println("Visiting visitNodeTypeSequence: {}", context->getText());
		AstMatcherVisitorOutput out = {unordered_map<string, AstNode*>(), true};

		auto prev = it;  // Store current iterator position

		if (context->elem) {
			// Single nodeTypeElement
			auto result = visit(context->elem);
			auto resultMap = any_cast<AstMatcherVisitorOutput>(result);

			if (!resultMap.success) {
				it = prev;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out)
			}

			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());

		} else if (context->nodeTypeSequence().size() > 1) {
			// Handle recursive nodeTypeSequence
			if (context->isor) {
				// Handle OR logic by trying each side separately
				println("Handling OR operation in NodeTypeSequence");

				auto result1 = visit(context->nodeTypeSequence(1));
				auto resultMap1 = any_cast<AstMatcherVisitorOutput>(result1);

				it = prev;  // Reset iterator for the second alternative

				auto result2 = visit(context->nodeTypeSequence(0));
				auto resultMap2 = any_cast<AstMatcherVisitorOutput>(result2);

				if (resultMap1.success) {
					out.matches.insert(resultMap1.matches.begin(), resultMap1.matches.end());
					out.success = true;
				} else if (resultMap2.success) {
					out.matches.insert(resultMap2.matches.begin(), resultMap2.matches.end());
					out.success = true;
				} else {
					it = prev;  // Reset iterator if neither alternative matched
					AST_MATCHER_FAILURE(out)
				}
			} else {
				// Handle consecutive elements
				auto result = visit(context->nodeTypeSequence(1));
				auto resultMap = any_cast<AstMatcherVisitorOutput>(result);

				if (!resultMap.success) {
					it = prev;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out)
				}

				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());

				// Move to the next element in the sequence
				auto next_iteration = it->prev;
				it = next_iteration;
				result = visit(context->nodeTypeSequence(0));
				resultMap = any_cast<AstMatcherVisitorOutput>(result);

				if (!resultMap.success) {
					it = prev;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out)
				}

				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
			}
		}

		it = prev;  // Reset iterator to original position after sequence processing

		println("visitNodeTypeSequence end.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodePropertySequence(AstMatcherParser::NodePropertySequenceContext *context)
		-> any
	{
		println("Visiting visitNodePropertySequence: {}", context->getText());
		AstMatcherVisitorOutput out = {unordered_map<string, AstNode*>(), true};

		auto prev = it;  // Store current iterator position

		if (context->elem) {
			// Single nodePropertyElement
			auto result = visit(context->elem);
			auto resultMap = any_cast<AstMatcherVisitorOutput>(result);

			if (!resultMap.success) {
				it = prev;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out)
			}

			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());

		} else if (context->nodePropertySequence().size() > 1) {
			// Handle recursive nodePropertySequence
			if (context->isor) {
				// Handle OR logic by trying each side separately
				println("Handling OR operation in NodePropertySequence");

				auto result1 = visit(context->nodePropertySequence(0));
				auto resultMap1 = any_cast<AstMatcherVisitorOutput>(result1);

				it = prev;  // Reset iterator for the second alternative

				auto result2 = visit(context->nodePropertySequence(1));
				auto resultMap2 = any_cast<AstMatcherVisitorOutput>(result2);

				if (resultMap1.success) {
					out.matches.insert(resultMap1.matches.begin(), resultMap1.matches.end());
					out.success = true;
				} else if (resultMap2.success) {
					out.matches.insert(resultMap2.matches.begin(), resultMap2.matches.end());
					out.success = true;
				} else {
					it = prev;  // Reset iterator if neither alternative matched
					AST_MATCHER_FAILURE(out)
				}
			} else {
				// Handle consecutive elements
				auto result = visit(context->nodePropertySequence(0));
				auto resultMap = any_cast<AstMatcherVisitorOutput>(result);

				if (!resultMap.success) {
					it = prev;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out)
				}

				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());

				// Move to the next element in the sequence
				auto next_iteration = it->prev;
				it = next_iteration;
				result = visit(context->nodePropertySequence(1));
				resultMap = any_cast<AstMatcherVisitorOutput>(result);

				if (!resultMap.success) {
					it = prev;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out)
				}

				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
			}
		}

		it = prev;  // Reset iterator to original position after sequence processing

		println("visitNodePropertySequence end.");
		return out;
	}


	fn InterpretReverseVisitor::visitNodePropertyElement(AstMatcherParser::NodePropertyElementContext *context)
		-> any
	{
		println("Visiting visitNodePropertyElement: {}", context->getText());
		AstMatcherVisitorOutput out = {unordered_map<string, AstNode*>(), true};

		auto prev = it;  // Store current iterator position

		if (context->NOT()) {
			auto not_out = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertyElement()));
			not_out.success = !not_out.success;
			it = prev;  // Reset iterator after NOT operation
			return not_out;
		}

		if (context->nodeProperty()) {
			auto result = visit(context->nodeProperty());
			auto resultMap = any_cast<AstMatcherVisitorOutput>(result);
			if (!resultMap.success) {
				it = prev;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out)
			}

			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
		} else if (context->nodePropertySequence()) {

			// Handle consecutive elements
			auto result = visit(context->nodePropertySequence());
			auto resultMap = any_cast<AstMatcherVisitorOutput>(result);

			if (!resultMap.success) {
				it = prev;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out)
			}

			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());



		}

		println("visitNodePropertyElement end.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodeTypeElement(AstMatcherParser::NodeTypeElementContext *context) -> any
	{
		println("Visiting visitNodeTypeElement: {}", context->getText());
		AstMatcherVisitorOutput out = {unordered_map<string, AstNode*>(), true};

		auto prev = it;  // Store current iterator position

		if (context->NOT()) {
			auto not_out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeElement()));
			not_out.success = !not_out.success;
		//	it = prev;  // Reset iterator after NOT operation (not needed for properties?)
			return not_out;
		}

		if (context->nodeType()) {
			auto result = visit(context->nodeType());
			auto resultMap = any_cast<AstMatcherVisitorOutput>(result);
			if (!resultMap.success) {
				it = prev;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out)
			}

			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
		} else if (context->nodeTypeSequence()) {
			auto result = visit(context->nodeTypeSequence());
			auto resultMap = any_cast<AstMatcherVisitorOutput>(result);
			if (!resultMap.success) {
				it = prev;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out)
			}

			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
		}

		println("visitNodeTypeElement end.");
		return out;
	}

}
