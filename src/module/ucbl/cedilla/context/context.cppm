export module ucbl.cedilla:context;

import :common;
import :ast_node;
import :state_map;
import :ast;

export namespace cedilla
{

	struct LexerOutput
	{
		/*
			Lexer return codes:
				Negative = Error
				Zero = Not a match
				Postivie = Length of matched prefix size
		*/
		int 					matched_src_prefix_length;
		unique_ptr<AstNode>		nodes;
	};

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
