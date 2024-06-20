module;

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include "antlr4-runtime.h"
#include "AstMatcherLexer.h"
#include "AstMatcherParser.h"
#include "AstMatcherVisitor.h"

export module ucbl.cedilla:ast_matcher_interpret;

import :common;
import :ast;
import :ast_node;
import :ast_matcher_reverse_visitor;

using namespace antlr4;

namespace cedilla {
	struct TrackingErrorListener : public antlr4::BaseErrorListener {
		bool error = false;

		virtual void syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
										const string &msg, exception_ptr e) override
		{
			println(cerr, "line {}:{} {}", line, charPositionInLine, msg);
			error = true;
		}
	};
}

export namespace cedilla {
	unordered_map<string, unique_ptr<AstNode>> ast_matcher_interpret(const string& pattern, Ast& ast) {
		cout << "Input: " << pattern << endl;

		ANTLRInputStream input(pattern);
		AstMatcherLexer lexer(&input);

		auto lexerErrorListener = TrackingErrorListener();
		lexer.removeErrorListeners();
		lexer.addErrorListener(&lexerErrorListener);

		CommonTokenStream tokens(&lexer);
		tokens.fill();

		for (auto token : tokens.getTokens()) {
			cout << "token: " << token->toString() << endl;
		}

		AstMatcherParser parser(&tokens);

		auto parserErrorListener = TrackingErrorListener();
		parser.removeErrorListeners();
		parser.addErrorListener(&parserErrorListener);

		AstMatcherParser::AstPatternDescriptionContext* tree = parser.astPatternDescription();

		if (lexerErrorListener.error || parserErrorListener.error)
		{
			throw runtime_error("astmatcher DSL syntax error.");
		}

		// Define property checkers
		unordered_map<string, InterpretReverseVisitor::PropertyChecker> checkers = {
			{"type", [](AstNode* node, const string& value) {
				return false;//node->states["type"] == value;
			}},
			{"value", [](AstNode* node, const string& value) {
				return false;//node->states["value"] == value;
			}}
		};

		InterpretReverseVisitor visitor(ast, checkers);
		visitor.visit(tree);

		unordered_map<string, unique_ptr<AstNode>> matchedNodes;
		for (const auto& [alias, node] : visitor.matches) {
			matchedNodes[alias] = node->clone();
		}

		return matchedNodes;
	}

}
