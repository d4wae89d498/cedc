module;

#include "AstMatcherVisitor.h"

export module ucbl.cedilla:ast_matcher_reverse_visitor;

import :common;
import :ast;
import :ast_node;

export namespace cedilla
{
	struct InterpretReverseVisitor : public AstMatcherVisitor
	{
		using PropertyChecker = function<bool(AstNode*, const string&)>;

		AstNode *it;
		unordered_map<string, AstNode*> matches;
		unordered_map<string, PropertyChecker> propertyCheckers;
		bool match = true;

		InterpretReverseVisitor(Ast& ast, unordered_map<string, PropertyChecker> checkers)
			: propertyCheckers(move(checkers))
		{
			it = ast.last;
			println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
			if (!it) {
				throw runtime_error("Trying to match ast with an empty string.");
			}
		}

		fn getTypeName(antlr4::tree::ParseTree *node) -> string
		{
			if (dynamic_cast<antlr4::tree::TerminalNode*>(node)) {
				return "TerminalNode";
			} else if (dynamic_cast<AstMatcherParser::AstPatternDescriptionContext*>(node)) {
				return "visitAstPatternDescription";
			} else if (dynamic_cast<AstMatcherParser::NodeTypeContext*>(node)) {
				return "visitNodeType";
			} else if (dynamic_cast<AstMatcherParser::NodePropertiesDescriptionContext*>(node)) {
				return "visitNodePropertiesDescription";
			} else if (dynamic_cast<AstMatcherParser::FuncCallContext*>(node)) {
				return "visitFuncCall";
			} else {
				return "Unknown";
			}
		}

		fn checkProperties(AstNode* node, AstMatcherParser::NodePropertiesDescriptionContext* context) -> bool
		{
			auto key = context->STRING(0)->getText();
			auto value = context->STRING(1)->getText();
			auto checkerIt = propertyCheckers.find(key);
			if (checkerIt != propertyCheckers.end()) {
				return checkerIt->second(node, value);
			}
			return false;
		}

		fn visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context) -> any override
		{
			println("Visiting visitAstPatternDescription in reverse order");

			if (!it) {
				println("{}", __LINE__);
				match = false;
				return nullptr;
			}
			for (s64 i = static_cast<s64>(context->children.size()) - 1; i >= 0; i -= 1) {
				if (context->children[i]->getText() == string("<EOF>")) {
					continue;
				}
				visit(context->children[i]);
			}
			return nullptr;
		}

		fn visitNodeType(AstMatcherParser::NodeTypeContext *context) -> any override
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
				if (context->children.size()) {
					println("----");
					println("[{}], [{}], [{}]", (u64) it->childs.first.get(), (u64) it->childs.last, it->childs.serialize());
					println("----");
					if (it->childs.first)
						it = it->childs.first->last(); // TODO: check why this is needed, last pointer is not set correctly.
					else
						it = NULL;
					println("it {} = [{}]", __LINE__, it ? it->serialize() : "NULL");
					for (s64 i = static_cast<s64>(context->children.size()) - 1; i >= 0; i -= 1) {
						visit(context->children[i]);
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

		fn visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context) -> any override
		{
			println("Visiting visitNodePropertiesDescription: {}", context->getText());

			if (!it) {
				return nullptr;
			}
			if (!checkProperties(it, context)) {
				it = nullptr;
				match = false;
				println("{}", __LINE__);
				return nullptr;
			}
			for (s64 i = static_cast<s64>(context->children.size()) - 1; i >= 0; i -= 1) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		fn visitFuncCall(AstMatcherParser::FuncCallContext *context) -> any override
		{
			println("Visiting FuncCall: {}", context->getText());

			// TODO: check that
			if (!it) {
				return nullptr;
			}
			for (s64 i = static_cast<s64>(context->children.size()) - 1; i >= 0; i -= 1) {
				visit(context->children[i]);
			}
			return nullptr;
		}
	};
}
