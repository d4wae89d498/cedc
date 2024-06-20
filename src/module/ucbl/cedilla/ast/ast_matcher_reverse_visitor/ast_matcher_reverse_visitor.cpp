module;

#include "AstMatcherVisitor.h"

module ucbl.cedilla;

import :common;
import :ast;
import :ast_node;

namespace cedilla
{
	static string extractAndReplaceEscapedQuotes(const std::string& input)
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

		if (!it) {
			println("{}", __LINE__);
			match = false;
			return nullptr;
		}
		for (s64 i = static_cast<s64>(context->nodeType().size()) - 1; i >= 0; i -= 1) {
			visit(context->nodeType(i));
		}
		return nullptr;
	}

	fn InterpretReverseVisitor::visitNodeType(AstMatcherParser::NodeTypeContext *context)
			-> any
	{
		println("Visiting visitNodeType: {}", context->getText());

		if (!it) {
			match = false;
			println("{}", __LINE__);
			return nullptr;
		}
		auto expectedType = context->IDENTIFIER(0)->getText();
		string alias;
		if (context->AS()) {
			alias = context->IDENTIFIER(1)->getText();
		}
		auto prev = it->prev;
		if (it->type == expectedType) {
			if (!alias.empty()) {
				matches[alias] = it;
			}
			// Check for states
			println("Checking states...");
			for (s64 i = 0; i < context->nodePropertiesDescription().size(); i += 1) {
				visit(context->nodePropertiesDescription(i));
			}
			println("{} childs", context->nodeType().size());
			if (context->nodeType().size()) {
				println("Checking childs...");
				println("----");
				println("[{}], [{}], [{}]", (u64) it->childs.first.get(), (u64) it->childs.last, it->childs.serialize());
				println("----");
				if (it->childs.first)
					it = it->childs.first->last(); // TODO: check why this is needed, last pointer is not set correctly.
				else
					it = NULL;
				println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
				for (s64 i = static_cast<s64>(context->nodeType().size()) - 1; i >= 0; i -= 1) {
					visit(context->nodeType(i));
				}
			}
		} else {
			match = false;
			it = nullptr;
			println("{}", __LINE__);
		}
		it = prev;
		println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
		println("visitNodeType end.");
		return nullptr;
	}

	fn InterpretReverseVisitor::visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context)
			-> any
	{
		println("Visiting visitNodePropertiesDescription: {}", context->getText());
		auto state_key = extractAndReplaceEscapedQuotes(context->STRING(0)->getText());
		auto state_value = extractAndReplaceEscapedQuotes(context->STRING(1)->getText());
		println("key={} | value={}", state_key, state_value);


		if (!it) {
			println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
			return nullptr;
		}
		if (!it->states.contains(state_key)) {
			println("ITM [{}] does not contains key", it->serialize());
			return false;
		}
		// TODO: check if its a funccall
		if (!context->EQUAL()) {

		} else {

			if (it->states[state_key]->serialize() != format("StringState({})", state_value)) {
				it = nullptr;
				match = false;
				println("{}", __LINE__);
				return nullptr;
			} else {
				println("---------->>> MATCH <<<----------");
			}
		}
		return nullptr;
	}
}
