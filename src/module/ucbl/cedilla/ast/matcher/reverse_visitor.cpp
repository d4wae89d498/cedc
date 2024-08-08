module;

#include "AstMatcherVisitor.h"
#define AST_MATCHER_FAILURE(N, MSG, ...) \
	{\
		DEBUG_LOG("ASTMatcher dit not succeed, reason -> [" MSG "] trying to continue...", ##__VA_ARGS__);\
		N.success = false;\
		return N;\
	}

module ucbl.cedilla;

import :common;
import :util;
import :ast;
import :ast.node;

namespace ucbl::cedilla
{
	fn merge_ast_matches(AstMatch& mainMap, const AstMatch& auxMap) -> void {
		for (const auto& [key, vec] : auxMap) {
			// If the key exists in mainMap, append to the vector
			if (mainMap.find(key) != mainMap.end()) {
				mainMap[key].insert(mainMap[key].end(), vec.begin(), vec.end());
			} else {
				// If the key doesn't exist, create a new vector
				mainMap[key] = vec;
			}
		}
	}


	InterpretReverseVisitor::InterpretReverseVisitor(Ast& ast, unordered_map<string, StateChecker> checkers)
		: StateCheckers(move(checkers))
	{
		it = ast.last; // Start from the end of the AST
		if (!it) {
			throw runtime_error("Trying to match an empty ast with an ast matcher pattern.");
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

	fn InterpretReverseVisitor::visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitAstPatternDescription in reverse order");
		auto out = AstMatcherVisitorOutput();
		if (!it)
			AST_MATCHER_FAILURE(out, "Empty ast tree.");
		out = any_cast<AstMatcherVisitorOutput>(visit(context->astRoot));
		if (!out.success)
			AST_MATCHER_FAILURE(out, "The AST tree definitely does not match the pattern.");
		DEBUG_LOG("visitAstPatternDescription ended properly.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodeType(AstMatcherParser::NodeTypeContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitNodeType: {}", context->getText());
		auto out = AstMatcherVisitorOutput();
		if (!it)
			AST_MATCHER_FAILURE(out, "End of tree reached.");
		auto expectedType = context->ANY() ? it->type : context->IDENTIFIER(0)->getText();
		string alias;
		if (context->AS()) {
			alias = context->IDENTIFIER(1)->getText();
		}
		auto it_bkp = it->prev;
		if (it->type == expectedType) {
			if (!alias.empty()) {
				out.matches[alias] = {it};
			}

			DEBUG_LOG("Checking states...");
			if (context->nodePropertySequence()) {
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence()));
				if (!result.success) {
					AST_MATCHER_FAILURE(out, "Node properties sequence does not match.");
				}
				merge_ast_matches(out.matches, result.matches);
			}

			DEBUG_LOG("Checking childs...");
			if (context->nodeTypeSequence()) {
				auto child_it = it->childs.first->last();
				it = child_it;
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()));
				it = it_bkp;  // Reset iterator after processing child nodes
				if (!result.success) {
					AST_MATCHER_FAILURE(out, "Node child sequence does not match.");
				}
				merge_ast_matches(out.matches, result.matches);
			}
		} else {
			AST_MATCHER_FAILURE(out, "Wrong node type, expected '{}' got '{}'.", expectedType, it->type);
		}

		it = it_bkp;  // Ensure iterator is reset
		DEBUG_LOG("AstNode matched.");
		DEBUG_LOG("visitNodeType ended properly.");

		return out;
	}

	fn InterpretReverseVisitor::visitNodeProperty(AstMatcherParser::NodePropertyContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitNodeProperty: {}", context->getText());

		auto state_key = context->IDENTIFIER(0)->getText();

		auto out = (AstMatcherVisitorOutput){true, AstMatch()};

		if (!it)
			AST_MATCHER_FAILURE(out, "End of tree reached.");

		if (!it->states.contains(state_key)) {
			AST_MATCHER_FAILURE(out, "Node '{}' does not contain property '{}'.", it->serialize(), state_key);
		}
		if (!context->EQUAL() && context->IDENTIFIER(1)) {
			// FuncCall
			auto state_key = extractAndReplaceEscapedQuotes(context->IDENTIFIER(1)->getText());
			NOT_IMPLEMENTED_LOG("FuncCall in node property");
		} else if (context->nodeTypeSequence()) {
			NOT_IMPLEMENTED_LOG("AstNode as node property");
		} else {
			// TODO: also support string instead of identifier
			auto state_value = extractAndReplaceEscapedQuotes(context->STRING(0)->getText());
			if (it->states[state_key]->serialize() != format("StringState({})", state_value)) {
				AST_MATCHER_FAILURE(
					out,
					"Node property '{}' mismatch, expected value '{}' but got value '{}'.",
					state_key,
					format("StringState({})", state_value),
					it->states[state_key]->serialize()
				);
			} else {
				DEBUG_LOG("Property match.");
			}
		}
		DEBUG_LOG("visitNodeProperty ended properly.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodeTypeSequence(AstMatcherParser::NodeTypeSequenceContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitNodeTypeSequence: {}", context->getText());
		auto out = AstMatcherVisitorOutput();
		auto it_bkp = it;  // Store current iterator position
		if (context->elem) {
			// Single nodeTypeElement
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->elem));
			if (!result.success) {
				it = it_bkp;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out, "Node failed in a single node sequence.");
			}
			merge_ast_matches(out.matches, result.matches);
			DEBUG_LOG("Single node sequence matched.");
		} else if (context->nodeTypeSequence().size() > 1) {
			// Handle recursive nodeTypeSequence
			if (context->isor) {
				// Handle OR logic by trying each side separately
				DEBUG_LOG("Handling OR operation in NodeTypeSequence");

				auto result1 = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(1)));

				it = it_bkp;  // Reset iterator for the second alternative

				auto result2 = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(0)));

				if (result1.success) {
					merge_ast_matches(out.matches, result1.matches);
					out.success = true;
				} else if (result2.success) {
					merge_ast_matches(out.matches, result2.matches);
					out.success = true;
				} else {
					it = it_bkp;  // Reset iterator if neither alternative matched
					AST_MATCHER_FAILURE(out, "Neither alternative matched using the OR operator in the node pattern sequence.");
				}
				DEBUG_LOG("Sequence matched using the OR operator.");
			} else {
				// Handle consecutive elements
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(1)));

				if (!result.success) {
					it = it_bkp;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out, "Node failed in a node sequence.");
				}

				merge_ast_matches(out.matches, result.matches);

				// Move to the next element in the sequence
				it = it->prev;
				result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(0)));

				if (!result.success) {
					it = it_bkp;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out, "Node failed in a node sequence.");
				}
				DEBUG_LOG("Sequence matched.");
				merge_ast_matches(out.matches, result.matches);

			}
		}
		it = it_bkp;  // Reset iterator to original position after sequence processing
		DEBUG_LOG("visitNodeTypeSequence ended properly.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodePropertySequence(AstMatcherParser::NodePropertySequenceContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitNodePropertySequence: {}", context->getText());
		auto out = AstMatcherVisitorOutput();

		auto it_bkp = it;  // Store current iterator position

		if (context->elem) {
			// Single nodePropertyElement
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->elem));

			if (!result.success) {
				it = it_bkp;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out, "Single property Node Property Sequence failed.");
			}
			merge_ast_matches(out.matches, result.matches);

		} else if (context->nodePropertySequence().size() > 1) {
			// Handle recursive nodePropertySequence
			if (context->isor) {
				// Handle OR logic by trying each side separately
				DEBUG_LOG("Handling OR operation in Node Property Sequence");

				auto result1 = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(0)));

				it = it_bkp;  // Reset iterator for the second alternative

				auto result2 = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(1)));

				if (result1.success) {
					merge_ast_matches(out.matches, result1.matches);

					out.success = true;
				} else if (result2.success) {
					merge_ast_matches(out.matches, result2.matches);
					out.success = true;
				} else {
					it = it_bkp;  // Reset iterator if neither alternative matched
					AST_MATCHER_FAILURE(out, "Node property sequence failed using the OR operator.");
				}
			} else {
				// Handle consecutive elements
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(0)));

				if (!result.success) {
					it = it_bkp;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out, "Node property sequence failed.");
				}

				merge_ast_matches(out.matches, result.matches);


				// Move to the next element in the sequence
				auto next_iteration = it->prev;
				it = next_iteration;
				result = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(1)));

				if (!result.success) {
					it = it_bkp;  // Reset iterator if match fails
					AST_MATCHER_FAILURE(out, "Node property sequence failed.");
				}

				merge_ast_matches(out.matches, result.matches);
			}
		}

		it = it_bkp;  // Reset iterator to original position after sequence processing

		DEBUG_LOG("visitNodePropertySequence ended properly.");
		return out;
	}


	fn InterpretReverseVisitor::visitNodePropertyElement(AstMatcherParser::NodePropertyElementContext *context)
		-> any
	{
		println("Visiting visitNodePropertyElement: {}", context->getText());
		auto out = AstMatcherVisitorOutput();

		auto it_bkp = it;  // Store current iterator position

		if (context->NOT()) {
			auto not_out = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertyElement()));
			not_out.success = !not_out.success;
			it = it_bkp;  // Reset iterator after NOT operation
			return not_out;
		}

		if (context->nodeProperty()) {
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeProperty()));
			if (!result.success) {
				it = it_bkp;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out, "Node property does not match.");
			}

			out.matches.insert(result.matches.begin(), result.matches.end());
		} else if (context->nodePropertySequence()) {

			// Handle consecutive elements
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence()));

			if (!result.success) {
				it = it_bkp;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out, "Node property sequence does not match.");
			}

			merge_ast_matches(out.matches, result.matches);
		}

		println("visitNodePropertyElement end.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodeTypeElement(AstMatcherParser::NodeTypeElementContext *context) -> any
	{
		DEBUG_LOG("Visiting visitNodeTypeElement: {}", context->getText());
		auto out = AstMatcherVisitorOutput();
		auto it_bkp = it;  // Store current iterator position

		if (context->NOT()) {
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeElement()));
			out.success = !out.success;
		//	it = it_bkp;  // Reset iterator after NOT operation (not needed for properties?)
		} else if (context->nodeTypeSequence()) {
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()));
			if (!out.success) {
				it = it_bkp;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out, "Node seuquence does not match.");
			}
		} else if (context->PLUS()) {
			if (!it)
				AST_MATCHER_FAILURE(out, "Node one or more ('+' symbol) was not respected.");
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeElement()));
			if (!out.success) {
				it = it_bkp;  // Reset iterator if match fails // TODO: is that needed ?
				AST_MATCHER_FAILURE(out, "Node one or more ('+' symbol) was not respected.");
			}
			while (it)
			{
				it_bkp = it;
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeElement()));
				if (!result.success) {
					it = it_bkp;
					break;
				}
				merge_ast_matches(out.matches, result.matches);
			}
		} else if (context->STAR()) {
			while (it)
			{
				it_bkp = it;
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeElement()));
				if (!result.success) {
					it = it_bkp;
					break;
				}
				merge_ast_matches(out.matches, result.matches);
			}
		} else if (context->QUESTION_MARK()) {
			it_bkp = it;
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeElement()));
			if (out.success) {
				it = it->prev;
			} else {
				it = it_bkp;
			}
		} else if (context->node) {
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->node));
			if (!result.success) {
				it = it_bkp;  // Reset iterator if match fails
				AST_MATCHER_FAILURE(out, "Node does not match the pattern.");
			}
			merge_ast_matches(out.matches, result.matches);
		} else {
			NOT_IMPLEMENTED_LOG("Unknow logic pattern");
		}
		DEBUG_LOG("visitNodeTypeElement ended properly.");
		return out;
	}

}
