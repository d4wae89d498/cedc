module;

#include "antlr4-runtime.h"
#include "AstMatcherLexer.h"
#include "AstMatcherParser.h"
#include "AstMatcherVisitor.h"

module ucbl.cedilla;

import :common;
import :ast;
import :ast.node;
import :ast.matcher.reverse_visitor;

using namespace antlr4;

namespace ucbl::cedilla
{
	fn AstMatcherTrackingErrorListener::syntaxError(Recognizer *recognizer, Token *offendingSymbol,
									size_t line, size_t charPositionInLine, const string &msg, exception_ptr e)
		 -> void
	{
		println(cerr, "line {}:{} {}", line, charPositionInLine, msg);
		error = true;
	}

	fn ast_matcher_interpret(const string& pattern, Ast& ast) -> unordered_map<string, AstNode*>
	{
		// Lexing
		println("Input: [{}]", pattern);
		ANTLRInputStream input(pattern);
		AstMatcherLexer lexer(&input);
		auto lexerErrorListener = AstMatcherTrackingErrorListener();
		lexer.removeErrorListeners();
		lexer.addErrorListener(&lexerErrorListener);
		CommonTokenStream tokens(&lexer);
		tokens.fill();
		for (auto token : tokens.getTokens()) {
			println("token: [{}]", token->toString());
		}

		// Parsing
		AstMatcherParser parser(&tokens);
		auto parserErrorListener = AstMatcherTrackingErrorListener();
		parser.removeErrorListeners();
		parser.addErrorListener(&parserErrorListener);
		AstMatcherParser::AstPatternDescriptionContext* tree = parser.astPatternDescription();
		if (lexerErrorListener.error || parserErrorListener.error)
		{
			throw runtime_error("astmatcher DSL syntax error.");
		}

		// Define property checkers
		// TODO: implement and test some Property Checkers or expose the map.
		unordered_map<string, InterpretReverseVisitor::StateChecker> checkers = {
			{"is", [](const string& serialized_state, const string& rvalue) {
				return serialized_state == rvalue;
			}},
		};

		// Visit & match AST
		InterpretReverseVisitor visitor(ast, checkers);
		auto out = any_cast<AstMatcherVisitorOutput>(visitor.visit(tree));
		if (!out.success)
			return {};
		return out.matches;
	}
}
