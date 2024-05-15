import ucbl.cedilla;

using namespace cedilla;

struct StringState final : public State
{
	StringState(string value) : State(__func__, value)
	{
	}

	fn clone() -> unique_ptr<State> override
	{
		return make_unique<StringState>(any_cast<string>(this->value));
	}

	fn serialize() -> string override
	{
		return any_cast<string>(this->value);
	}

	static fn deserialize(const string &str) -> unique_ptr<State>
	{
		return make_unique<StringState>(str);
	}
};
REGISTER_DESERIALIZABLE(State, StringState);

struct Word final : public AstNode
{
	Word() : AstNode(__func__)
	{
	}

	fn	compile() -> string override
	{
		auto &mystate = this->data["value"];
		return format("{}", any_cast<string>(mystate->value));
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		throw runtime_error("not implemented");
		auto out = make_unique<Word>();
		out->data["value"] = make_unique<StringState>(any_cast<string>(this->data["value"]->value));
		return out;
	}

	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		auto out = make_unique<Word>();
		string my;
		scan(str, "{}", my);
		out->data["value"] = make_unique<StringState>(my);
		return out;
	}
};
REGISTER_DESERIALIZABLE(AstNode, Word);


struct Raw final : public AstNode
{
	string value;

	Raw(string pp = "") : AstNode(__func__)
	{
	}

	fn	compile() -> string
	{
		return format("{}", value);
	}

	fn	clone() -> unique_ptr<AstNode>
	{
		auto out  = Raw::deserialize(value);
		if (this->next)
			out->next = this->next->clone();
		return out;
	}


	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		auto out = make_unique<Raw>();
		scan(str, "{}", out->value);
		return out;
	}
};
REGISTER_DESERIALIZABLE(AstNode, Raw)

fn main() -> int
{
	print("begin...\n");

	Context ctx;

	// match a space
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();

		int i = 0;

		// we got a space
		while (isspace(csrc[i]))
		{
			i += 1;
		}
		return (LexerOutput){i, Word::deserialize(src.substr(0, i))};
	});

	// match a word
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();

		// we got a word
		if (csrc[0] == '_' || isalpha(csrc[0]))
		{
			int i = 1;
			while (csrc[i] == '_' || isalnum(csrc[i]))
				i += 1;
			return (LexerOutput){i, Word::deserialize(src.substr(0, i))};
		}
		return (LexerOutput) {0, nullptr};
	});


	// skip single line comments
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();
		if (csrc[0] == '/' && csrc[1] == '/')
		{
			int i = 2;
			while (csrc[i])
			{
				if (csrc[i - 1] != '\\' && csrc[i] == '\n')
				{
					i += 1;
					break ;
				}
				i += 1;
			}
			return (LexerOutput) {i, Word::deserialize(src.substr(0, i))};
		}
		return (LexerOutput) {0, nullptr};
	});


	// skip multi line comments
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();
		if (csrc[0] == '/' && csrc[1] == '*')
		{
			println("found begin");

			int i = 2;
			bool found = false;
			while (csrc[i])
			{
				if (csrc[i] == '*' && csrc[i + 1] == '/')
				{
					found = true;
					i += 2;
					break ;
				}
				i += 1;
			}

			if (!found)
			{
					println("not found");
					return (LexerOutput) {-1, nullptr};
			}
			println("ok {}", i);

			return (LexerOutput) {i, Word::deserialize(src.substr(0, i))};
		}
		return (LexerOutput) {0, nullptr};
	});

	// skip simple quote strings
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();
		if (csrc[0] == '\'')
		{
			int i = 1;
			while (csrc[i])
			{
				if (csrc[i - 1] != '\\' && csrc[i] == '\'')
				{
					i += 1;
					break ;
				}
				i += 1;
			}
			return (LexerOutput) {i, Word::deserialize(src.substr(0, i))};
		}
		return (LexerOutput) {0, nullptr};
	});

	// skip double quote strings
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();
		if (csrc[0] == '\"')
		{
			int i = 1;
			while (csrc[i])
			{
				if (csrc[i - 1] != '\\' && csrc[i] == '\"')
				{
					i += 1;
					break ;
				}
				i += 1;
			}
			return (LexerOutput) {i, Word::deserialize(src.substr(0, i))};
		}
		return (LexerOutput) {0, nullptr};
	});

	// match digits
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();
		if (isdigit(csrc[0]) || csrc[0] == '.')
		{
			int i = 1;
			bool has_digit = false;
			while (isdigit(csrc[i]))
			{
				i += 1;
				has_digit = true;
			}
			if (csrc[i] == '.')
			{
				i += 1;
			}
			while (isdigit(csrc[i]))
			{
				has_digit = true;
				i += 1;
			}
			if (!has_digit)
				return (LexerOutput) {0, nullptr};
			return (LexerOutput) {i, Word::deserialize(src.substr(0, i))};
		}
		return (LexerOutput) {0, nullptr};
	});


	// match parenthesis
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();
		if ((csrc[0] == '(' || csrc[0] == '[' || csrc[0] == '{') || (csrc[0] == ')' || csrc[0] == ']' || csrc[0] == '}'))
		{
			return (LexerOutput) {1, Word::deserialize(src.substr(0, 1))};
		}
		return (LexerOutput) {0, nullptr};
	});


	// match raw fallback
	ctx.lexers.push_back([&ctx](const string src) -> LexerOutput {

		static int s_depth;

		if (s_depth)
		{
			return (LexerOutput) {0, Raw::deserialize(src.substr(0, 0))};

		}
		s_depth += 1;

		auto csrc = src.c_str();

		int i = 0;
		while (csrc[i])
		{
			for (auto &lexer : ctx.lexers)
			{
				if (lexer(csrc + i).matched_src_prefix_length > 0)
				{
					s_depth -= 1;
					if (i)
						return (LexerOutput) {i, Raw::deserialize(src.substr(0, i))};
					else
						return (LexerOutput) {0, Raw::deserialize(src.substr(0, 0))};
				}
				else if (lexer(csrc + i).matched_src_prefix_length < 0)
				{
					throw new runtime_error("Lexer error at : " + string(csrc + i));
				}
			}
			i += 1;
		}
		s_depth -= 1;
		return (LexerOutput) {i, Raw::deserialize(src.substr(0, i))};
	});


	ctx.parsers.push_back([](Ast& ast) -> ParserOutput {

		if (ast.last->compile() == string(")"))
		{
			print("--------\n");
			auto it = ast.last->prev;
			while (it)
			{
				if (it->compile() == string("("))
				{
					println("FOUND!");

					auto prev = it->prev;

					ast.last = (prev->next = Word::deserialize("PARENS")).get();

					auto new_childs = it->clone();
				//	ast.last->childs.link_front(move(new_childs));

					prev->next->prev = prev;

				//	it->prev->next->prev = it->prev;

				//	ast.last = it->prev->next.get();

					//ast.replace_one(it, );
					return MATCH;
				}
				it = it->prev;
			}
		}
		return SKIP;

	});

	ctx.lex(
		"hel      lo  "
			 "// this is a comment\\n dd\n"
			 "test"
			 "/*pomme*/"
			 "test"
			 "'test'"
			 "\"test\""
			 "(5.98) "
			 "§fesfesfe$éééé"

		);



	for (auto &item : ctx.ast)
	{
		println("item->type: [{}]", item.type);
		println("item->value: [{}]", item.compile());
		println("item->childs: [{}]", item.childs.size());
		println("");

	}

	// test \
	dwdw\
	dwdw

	return 0;
}
