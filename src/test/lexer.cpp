import ucbl.cedilla;

using namespace cedilla;

struct Word : public AstNode
{
	string value;

	Word() : AstNode(__func__)
	{
	}

	fn	clone() const -> unique_ptr<AstNode>
	{
		auto out  = Word::unserialize(value);
		if (this->next)
			out->next = this->next->clone();
		return out;
	}


	fn	compile() const -> string
	{
		return format("{}", value);
	}

	static fn unserialize(const string& str) -> unique_ptr<AstNode>
	{

		auto out = make_unique<Word>();
		string my;
		scan(str, "{}", my);

		auto myany = make_unique<State>(my);

		out->data["value"] = move(myany);
		return out;
	}
};
REGISTER_CLASS(AstNode, Word);


struct Raw : public AstNode
{
	string value;

	Raw() : AstNode(__func__)
	{
	}

	fn	compile() const -> string
	{
		return format("{}", value);
	}

	fn	clone() const -> unique_ptr<AstNode>
	{
		auto out  = Raw::unserialize(value);
		if (this->next)
			out->next = this->next->clone();
		return out;
	}


	static fn unserialize(const string& str) -> unique_ptr<AstNode>
	{
		auto out = make_unique<Raw>();
		scan(str, "{}", out->value);
		return out;
	}
};
REGISTER_CLASS(AstNode, Raw);

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
		return (LexerOutput){i, Word::unserialize(src.substr(0, i))};
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
			return (LexerOutput){i, Word::unserialize(src.substr(0, i))};
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
			return (LexerOutput) {i, Word::unserialize(src.substr(0, i))};
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

			return (LexerOutput) {i, Word::unserialize(src.substr(0, i))};
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
			return (LexerOutput) {i, Word::unserialize(src.substr(0, i))};
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
			return (LexerOutput) {i, Word::unserialize(src.substr(0, i))};
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
			return (LexerOutput) {i, Word::unserialize(src.substr(0, i))};
		}
		return (LexerOutput) {0, nullptr};
	});


	// match parenthesis
	ctx.lexers.push_back([](const string src) -> LexerOutput {

		auto csrc = src.c_str();
		if ((csrc[0] == '(' || csrc[0] == '[' || csrc[0] == '{') || (csrc[0] == ')' || csrc[0] == ']' || csrc[0] == '}'))
		{
			return (LexerOutput) {1, Word::unserialize(src.substr(0, 1))};
		}
		return (LexerOutput) {0, nullptr};
	});


	// match raw fallback
	ctx.lexers.push_back([&ctx](const string src) -> LexerOutput {

		static int s_depth;

		if (s_depth)
		{
			return (LexerOutput) {0, Raw::unserialize(src.substr(0, 0))};

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
						return (LexerOutput) {i, Raw::unserialize(src.substr(0, i))};
					else
						return (LexerOutput) {0, Raw::unserialize(src.substr(0, 0))};
				}
				else if (lexer(csrc + i).matched_src_prefix_length < 0)
				{
					throw new runtime_error("Lexer error at : " + string(csrc + i));
				}
			}
			i += 1;
		}
		s_depth -= 1;
		return (LexerOutput) {i, Raw::unserialize(src.substr(0, i))};
	});


	ctx.parsers.push_back([](Ast& ast) -> ParserOutput {

		if (ast.last->compile() == string(")"))
		{
			auto it = ast.last->prev;
			while (it)
			{
				if (it->compile() == string("("))
				{
					println("FOUND!");

					auto prev = it->prev;

					ast.last = (prev->next = Word::unserialize("PARENS")).get();

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
		println("");

	}

	// test \
	dwdw\
	dwdw

	return 0;
}
