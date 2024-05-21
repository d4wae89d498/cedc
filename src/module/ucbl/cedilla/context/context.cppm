export module ucbl.cedilla:context;

import :common;
import :ast_node;
import :state_map;
import :ast;

export namespace cedilla
{
	/*
		Lexer return codes:
			Negative = Error
			Zero = Not a match
			Postivie = Length of matched prefix size
	*/
	using LexerOutput = pair<int, unique_ptr<AstNode>>;



	using ParserOutput = enum {
		ERROR = -1,
		SKIP = 0,
		MATCH = 1
	};

	struct Context
	{
		using Lexer = function<LexerOutput(const string src)>;
		using Parser = function<ParserOutput(Ast& ast)>;

		StateMap				state;
		Ast						ast;
		vector<Lexer>			lexers;
		vector<Parser>			parsers;

		void	lex(string src);
		void	parse(Ast& ast);
	};
};
