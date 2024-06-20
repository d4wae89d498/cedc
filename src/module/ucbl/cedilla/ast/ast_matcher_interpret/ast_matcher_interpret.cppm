module;

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

export namespace cedilla
{
	struct AstMatcherTrackingErrorListener : public antlr4::BaseErrorListener
	{
		bool error = false;

		virtual fn syntaxError(Recognizer *recognizer, Token *offendingSymbol, size_t line, size_t charPositionInLine,
										const string &msg, exception_ptr e) -> void override;
	};

	fn ast_matcher_interpret(const string& pattern, Ast& ast) -> unordered_map<string, AstNode*>;
}
