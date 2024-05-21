export module ucbl.cedillac:identifier;

import ucbl.cedilla;

import :string_state;

using namespace cedilla;

struct Lexer
{

};


struct Identifier : public AstNode
{
	Identifier(StateMap states = StateMap()) : AstNode(__func__, move(states))
	{

	}

	fn compile() -> string
	{
		return "";
	}

	static fn lex(const string src) -> LexerOutput
	{

		auto csrc = src.c_str();

		if (csrc[0] == '_' || isalpha(csrc[0]))
		{
			int i = 1;
			while (csrc[i] == '_' || isalnum(csrc[i]))
				i += 1;
			return (LexerOutput){
				i,
				make_unique<Identifier>(
					StateMap({{"test", StringState::deserialize("yoo")}})
				)
			};
		}
		return (LexerOutput) {0, nullptr};
	};

};

// REGISTER_LEXER()
