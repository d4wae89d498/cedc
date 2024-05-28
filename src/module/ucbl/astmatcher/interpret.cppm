module;

#include "AstMatcherLexer.h"
#include "AstMatcherParser.h"

export module ucbl.astmatcher:interpret;

import ucbl.cedilla;
import :interpret_reverse_visitor;

using namespace cedilla;

export namespace astmatcher
{
	/*
	 *		interpret(TXT(skip dawdw; capture dwda;), Ast) -> map <str, node>
	 *
	 */
	fn interpret(const string pattern, Ast &Ast) -> unordered_map<string, unique_ptr<AstNode>>
	{
		println("Input: {}", pattern);
		cedilla::cout << "Input: " << pattern << cedilla::endl;

		antlr4::ANTLRInputStream input(pattern.c_str());

	//	TODO:: fix these lines

		AstMatcherLexer lexer(&input);


		antlr4::CommonTokenStream tokens(&lexer);

		tokens.fill();
		for (auto token : tokens.getTokens()) {
			println("token: {}", token->toString());
		}
		AstMatcherParser parser(&tokens);
		AstMatcherParser::PatternContext* tree = parser.pattern();
		InterpretReverseVisitor visitor;
		visitor.visit(tree);



		return unordered_map<string, unique_ptr<AstNode>>{};
	}

}
