module;

#include "AstMatcherVisitor.h"

export module ucbl.astmatcher:interpret_reverse_visitor;

import ucbl.cedilla;

export namespace astmatcher
{
	class InterpretReverseVisitor : public AstMatcherVisitor {
	public:

		cedilla::Ast&	ast;

		InterpretReverseVisitor(cedilla::Ast& ast)
			: ast(ast) {}

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
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context) override {
			std::cout << "Visiting visitNodePropertiesDescription: " << context->getText() << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}
		std::any visitFuncCall(AstMatcherParser::FuncCallContext *context) override {
			std::cout << "Visiting FuncCall: " << context->getText() << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}
	};
}
