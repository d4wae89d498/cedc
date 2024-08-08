module;

#include "antlr4-runtime.h"
#include "AstMatcherLexer.h"
#include "AstMatcherParser.h"
#include "AstMatcherVisitor.h"

export module ucbl.cedilla:ast.matcher.interpret;

import :common;
import :ast;
import :ast.node;
import :ast.matcher.reverse_visitor;

using namespace antlr4;

export namespace ucbl::cedilla
{
	struct AstMatcherTrackingErrorListener : public antlr4::BaseErrorListener
	{
		bool error = false;

		virtual fn syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
										const string &msg, exception_ptr e) -> void override;
	};

	fn ast_matcher_interpret(const string& pattern, Ast& ast) -> AstMatch;
}
