module;

#include "AstMatcherVisitor.h"

export module ucbl.astmatcher:interpret_reverse_visitor;

export namespace astmatcher
{
	class InterpretReverseVisitor : public AstMatcherVisitor {
	public:

		std::string getTypeName(antlr4::tree::ParseTree *node) {
			if (dynamic_cast<antlr4::tree::TerminalNode*>(node)) {
				return "TerminalNode";
			} else if (dynamic_cast<AstMatcherParser::AstDescriptionContext*>(node)) {
				return "AstDescriptionContext";
			} else if (dynamic_cast<AstMatcherParser::CaptureStmtContext*>(node)) {
				return "CaptureStmtContext";
			} else if (dynamic_cast<AstMatcherParser::SkipStmtContext*>(node)) {
				return "SkipStmtContext";
			} else if (dynamic_cast<AstMatcherParser::AstPropertyDescriptionContext*>(node)) {
				return "AstPropertyDescriptionContext";
			} else if (dynamic_cast<AstMatcherParser::FuncCallContext*>(node)) {
				return "FuncCallContext";
			} else if (dynamic_cast<AstMatcherParser::MatchListContext*>(node)) {
				return "MatchListContext";
			} else if (dynamic_cast<AstMatcherParser::MatchStmtContext*>(node)) {
				return "MatchStmtContext";
			} else if (dynamic_cast<AstMatcherParser::NestedCaptureContext*>(node)) {
				return "NestedCaptureContext";
			} else {
				return "Unknown";
			}
		}

		std::any visitPattern(AstMatcherParser::PatternContext *context) override {
			std::cout << "Visiting Pattern in reverse order" << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				if (context->children[i]->getText() == std::string("<EOF>"))
					continue;
				std::cout << "Visiting child ..." << getTypeName(context->children[i]) << " " << context->children[i]->getText() << std::endl;
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitAstDescription(AstMatcherParser::AstDescriptionContext *context) override {
			std::cout << "Visiting AstDescription in reverse order" << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitCaptureStmt(AstMatcherParser::CaptureStmtContext *context) override {
			std::cout << "Visiting CaptureStmt: " << context->getText() << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitSkipStmt(AstMatcherParser::SkipStmtContext *context) override {
			std::cout << "Visiting SkipStmt: " << context->getText() << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitAstPropertyDescription(AstMatcherParser::AstPropertyDescriptionContext *context) override {
			std::cout << "Visiting AstPropertyDescription: " << context->getText() << std::endl;
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

		std::any visitMatchList(AstMatcherParser::MatchListContext *context) override {
			std::cout << "Visiting MatchList in reverse order" << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitMatchStmt(AstMatcherParser::MatchStmtContext *context) override {
			std::cout << "Visiting MatchStmt: " << context->getText() << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}

		std::any visitNestedCapture(AstMatcherParser::NestedCaptureContext *context) override {
			std::cout << "Visiting NestedCapture: " << context->getText() << std::endl;
			for (int i = context->children.size() - 1; i >= 0; --i) {
				visit(context->children[i]);
			}
			return nullptr;
		}
	};
}
