module;

#include "AstMatcherVisitor.h"
#include <iostream>
#include <stdexcept>
#include <any>
#include <unordered_map>
#include <functional>

export module ucbl.astmatcher:interpret_reverse_visitor;

import ucbl.cedilla;

export namespace astmatcher
{
	class InterpretReverseVisitor : public AstMatcherVisitor {
	public:
		using PropertyChecker = std::function<bool(cedilla::AstNode*, const std::string&)>;

		cedilla::AstNode *it;
		std::unordered_map<std::string, cedilla::AstNode*> matches;
		std::unordered_map<std::string, PropertyChecker> propertyCheckers;

		InterpretReverseVisitor(cedilla::Ast& ast, std::unordered_map<std::string, PropertyChecker> checkers)
			: propertyCheckers(std::move(checkers))
		{
			it = ast.first.get();
			if (!it)
				throw std::runtime_error("Trying to analyse an empty file.");
		}

		std::string getTypeName(antlr4::tree::ParseTree *node) {
			if (dynamic_cast<antlr4::tree::TerminalNode*>(node)) {
				return "TerminalNode";
			} else if (dynamic_cast<AstMatcherParser::AstPatternDescriptionContext*>(node)) {
				return "visitAstPatternDescription";
			} else if (dynamic_cast<AstMatcherParser::NodeTypeListContext*>(node)) {
				return "visitNodeTypeList";
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

		void matchNode(AstMatcherParser::NodeTypeContext *context) {
			std::string expectedType = context->IDENTIFIER(0)->getText();
			std::string alias;
			if (context->AS()) {
				alias = context->IDENTIFIER(1)->getText();
			}

			if (it && it->type == expectedType) {
				if (!alias.empty()) {
					matches[alias] = it;
				}
				it = it->next.get();
			}
		}

		bool checkProperties(cedilla::AstNode* node, AstMatcherParser::NodePropertiesDescriptionContext* context) {
			std::string key = context->STRING(0)->getText();
			std::string value = context->STRING(1)->getText();
			auto checkerIt = propertyCheckers.find(key);
			if (checkerIt != propertyCheckers.end()) {
				return checkerIt->second(node, value);
			}
			return false;
		}

		std::any visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context) override {
			std::cout << "Visiting visitAstPatternDescription in reverse order" << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				if (context->children[i]->getText() == std::string("<EOF>"))
					continue;
				std::cout << "Visiting child ..." << getTypeName(context->children[i]) << " " << context->children[i]->getText() << std::endl;
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitNodeTypeList(AstMatcherParser::NodeTypeListContext *context) override {
			std::cout << "Visiting visitNodeTypeList in reverse order" << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitNodeType(AstMatcherParser::NodeTypeContext *context) override {
			std::cout << "Visiting visitNodeType: " << context->getText() << std::endl;
			matchNode(context);
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context) override {
			std::cout << "Visiting visitNodePropertiesDescription: " << context->getText() << std::endl;
			if (!checkProperties(it, context)) {
				it = nullptr; // Skip this node
			}
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitFuncCall(AstMatcherParser::FuncCallContext *context) override {
			std::cout << "Visiting FuncCall: " << context->getText() << std::endl;
			// Function call matching logic goes here
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}
	};
}
