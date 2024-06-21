module;

#include "AstMatcherVisitor.h"

module ucbl.cedilla;

import :common;
import :ast;
import :ast_node;

namespace cedilla
{
	static fn extractAndReplaceEscapedQuotes(const std::string& input) -> string
	{
		// Check if the input string starts and ends with a quote
		if (input.front() != '"' || input.back() != '"') {
			throw std::invalid_argument("Input string must start and end with a quote.");
		}

		// Extract the substring between the quotes
		std::string extracted = input.substr(1, input.length() - 2);

		// Replace escaped quotes
		std::string result;
		for (size_t i = 0; i < extracted.length(); ++i) {
			if (extracted[i] == '\\' && (i + 1 < extracted.length()) && extracted[i + 1] == '"') {
				result += '"';
				++i; // Skip the next character
			} else {
				result += extracted[i];
			}
		}

		return result;
	}

	InterpretReverseVisitor::InterpretReverseVisitor(Ast& ast, unordered_map<string, StateChecker> checkers)
		: StateCheckers(move(checkers))
	{
		it = ast.last;
		println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
		if (!it) {
			throw runtime_error("Trying to match ast with an empty string.");
		}
	}

	fn InterpretReverseVisitor::getTypeName(antlr4::tree::ParseTree *node)
		-> string
	{
		if (dynamic_cast<antlr4::tree::TerminalNode*>(node)) {
			return "TerminalNode";
		} else if (dynamic_cast<AstMatcherParser::AstPatternDescriptionContext*>(node)) {
			return "visitAstPatternDescription";
		} else if (dynamic_cast<AstMatcherParser::NodeTypeContext*>(node)) {
			return "visitNodeType";
		} else if (dynamic_cast<AstMatcherParser::NodePropertiesDescriptionContext*>(node)) {
			return "visitNodePropertiesDescription";
		} else {
			return "Unknown";
		}
	}

	fn InterpretReverseVisitor::visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context)
		-> any
	{
		println("Visiting visitAstPatternDescription in reverse order");
		AstMatcherVisitBag out = {unordered_map<string, AstNode*>(), true};

		if (!it) {
			println("{}", __LINE__);
			out.success = false;
			return out;
		}
		for (s64 i = static_cast<s64>(context->nodeTypeOr().size()) - 1; i >= 0; i -= 1) {
			auto result = visit(context->nodeTypeOr(i));
			auto resultMap = any_cast<AstMatcherVisitBag>(result);
			if (!resultMap.success) {
				out.success = false;
				return out;
			}
			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
		}
		return out;
	}

	fn InterpretReverseVisitor::visitNodeType(AstMatcherParser::NodeTypeContext *context)
		-> any
	{
		println("Visiting visitNodeType: {}", context->getText());
		AstMatcherVisitBag out = {unordered_map<string, AstNode*>(), true};

		if (!it) {
			out.success = false;
			println("{}", __LINE__);
			return out;
		}
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
			// Check for states
			println("Checking states...");
			for (size_t i = 0; i < context->nodePropertiesDescriptionOr().size(); i += 1) {
				auto result = visit(context->nodePropertiesDescriptionOr(i));
				auto resultMap = any_cast<AstMatcherVisitBag>(result);
				if (!resultMap.success) {
					out.success = false;
					return out;
				}
				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
			}
			println("{} childs", context->nodeTypeOr().size());
			if (context->nodeTypeOr().size() > 0) {
				println("Checking childs...");
				println("----");
				println("[{}], [{}], [{}]", (u64) it->childs.first.get(), (u64) it->childs.last, it->childs.serialize());
				println("----");
				if (it->childs.first)
					it = it->childs.first->last(); // TODO: check why this is needed, last pointer is not set correctly.
				else
					it = NULL;
				println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
				for (size_t i = 0; i < context->nodeTypeOr().size(); i += 1) {
					auto result = visit(context->nodeTypeOr(i));
					auto resultMap = any_cast<AstMatcherVisitBag>(result);
					if (!resultMap.success) {
						out.success = false;
						return out;
					}
					out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
				}
			}
		} else {
			out.success = false;
			it = nullptr;
			println("{}", __LINE__);
			return out;
		}
		it = prev;
		println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
		println("visitNodeType end.");

		return out;
	}

	fn InterpretReverseVisitor::visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context)
		-> any
	{
		println("Visiting visitNodePropertiesDescription: {}", context->getText());

		auto state_key = context->IDENTIFIER(0)->getText();


		AstMatcherVisitBag out = {unordered_map<string, AstNode*>(), true};

		if (!it) {
			out.success = false;
			println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
			return out;
		}
		if (!it->states.contains(state_key)) {
			println("ITM [{}] does not contains key", it->serialize());
			out.success = false;
			return out;
		}
		if (!context->EQUAL() && context->IDENTIFIER(1)) {
			// FuncCall
			auto state_key = extractAndReplaceEscapedQuotes(context->IDENTIFIER(1)->getText());

			throw runtime_error(format("{}:{} Not implemented", __FILE__, __LINE__));
		}

		else if (context->nodeType().size()) {
			// AstNode as property
			throw runtime_error(format("{}:{} Not implemented", __FILE__, __LINE__));

		}
		else {
			// Equal based match

			auto state_value = extractAndReplaceEscapedQuotes(context->STRING()->getText());
			println("key={} | value={}", state_key, state_value);
			if (it->states[state_key]->serialize() != format("StringState({})", state_value)) {
				it = nullptr;
				out.success = false;
				println("{}", __LINE__);
				return out;
			} else {
				println("---------->>> MATCH <<<----------");
				out.matches[state_key] = it;
			}
		}
		return out;
	}


	fn InterpretReverseVisitor::visitNodeTypeOr(AstMatcherParser::NodeTypeOrContext *context) -> any
	{
		println("Visiting visitNodeTypeOr: {}", context->getText());
		AstMatcherVisitBag out = {unordered_map<string, AstNode*>(), false};

		auto prev = it;

		auto result = visit(context->nodeType());
		auto resultMap = any_cast<AstMatcherVisitBag>(result);
		if (resultMap.success) {
			out.success = true;
			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
		} else if (context->nodeTypeOr()) {
			it = prev; // Reset the iterator for the alternative
			result = visit(context->nodeTypeOr());
			resultMap = any_cast<AstMatcherVisitBag>(result);
			if (resultMap.success) {
				out.success = true;
				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
			}
		}

		if (!out.success) {
			it = nullptr;
		}

		println("visitNodeTypeOr end.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodePropertiesDescriptionOr(AstMatcherParser::NodePropertiesDescriptionOrContext *context) -> any
	{
		println("Visiting visitNodePropertiesDescriptionOr: {}", context->getText());
		AstMatcherVisitBag out = {unordered_map<string, AstNode*>(), false};

		auto prev = it;

		auto result = visit(context->nodePropertiesDescription());
		auto resultMap = any_cast<AstMatcherVisitBag>(result);
		if (resultMap.success) {
			out.success = true;
			out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
		} else if (context->nodePropertiesDescriptionOr()) {
			it = prev; // Reset the iterator for the alternative
			result = visit(context->nodePropertiesDescriptionOr());
			resultMap = any_cast<AstMatcherVisitBag>(result);
			if (resultMap.success) {
				out.success = true;
				out.matches.insert(resultMap.matches.begin(), resultMap.matches.end());
			}
		}

		if (!out.success) {
			it = nullptr;
		}

		println("visitNodePropertiesDescriptionOr end.");
		return out;
	}
}
