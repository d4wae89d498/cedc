module;

#include "AstMatcherVisitor.h"
#include <iostream>
#include <stdexcept>
#include <any>
#include <unordered_map>
#include <functional>

export module ucbl.astmatcher:interpret_reverse_visitor;

import ucbl.cedilla;

using namespace std;

export namespace astmatcher
{
	class InterpretReverseVisitor : public AstMatcherVisitor {
	public:
		using PropertyChecker = function<bool(cedilla::AstNode*, const string&)>;

		cedilla::AstNode *it;
		unordered_map<string, cedilla::AstNode*> matches;
		unordered_map<string, PropertyChecker> propertyCheckers;

		InterpretReverseVisitor(cedilla::Ast& ast, unordered_map<string, PropertyChecker> checkers)
			: propertyCheckers(move(checkers))
		{
			it = ast.first.get();
			if (!it)
				throw runtime_error("Trying to analyse an empty file.");
		}

		string getTypeName(antlr4::tree::ParseTree *node) {
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
			string expectedType = context->IDENTIFIER(0)->getText();
			string alias;
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
			string key = context->STRING(0)->getText();
			string value = context->STRING(1)->getText();
			auto checkerIt = propertyCheckers.find(key);
			if (checkerIt != propertyCheckers.end()) {
				return checkerIt->second(node, value);
			}
			return false;
		}

		any visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context) override {
			cout << "Visiting visitAstPatternDescription in reverse order" << endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				if (context->children[i]->getText() == string("<EOF>"))
					continue;
				cout << "Visiting child ..." << getTypeName(context->children[i]) << " " << context->children[i]->getText() << endl;
				visit(context->children[i]);
			}
			return nullptr;
		}

		any visitNodeTypeList(AstMatcherParser::NodeTypeListContext *context) override {
			cout << "Visiting visitNodeTypeList in reverse order" << endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		any visitNodeType(AstMatcherParser::NodeTypeContext *context) override {
			cout << "Visiting visitNodeType: " << context->getText() << endl;
			matchNode(context);
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		any visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context) override {
			cout << "Visiting visitNodePropertiesDescription: " << context->getText() << endl;
			if (!checkProperties(it, context)) {
				it = nullptr; // Skip this node
			}
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		any visitFuncCall(AstMatcherParser::FuncCallContext *context) override {
			cout << "Visiting FuncCall: " << context->getText() << endl;
			// Function call matching logic goes here
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}
	};
}
