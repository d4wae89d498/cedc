#include <cassert>

import ucbl.cedilla;
import ucbl.astmatcher;

using namespace cedilla;

struct Word final : public AstNode
{
	Word(StateMap states = StateMap(), Ast childs = Ast())
		: AstNode(__func__, move(states), move(childs))
	{
	}

    Word(Word&& other) noexcept : AstNode(__func__)
	{
        // Move constructor implementation
        // Transfer ownership of resources from 'other' to 'this'
    }

   	fn operator=(Word&& other) noexcept ->  Word&
	{
        if (this != &other) {
            // Move assignment implementation
            // Transfer ownership of resources from 'other' to 'this'
        }
        return *this;
    }


	fn	compile() -> string override
	{
		auto &mystate = this->states["value"];
		return format("{}", any_cast<string>(mystate->value));
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		print("Clonning Word...\n");

		auto states = this->states.clone();

		auto out = make_unique<Word>(move(*(states.get())));//, move(*(this->childs.clone().release())));
		if (this->childs.first)
			out->childs.first = move(this->childs.first->clone());
		if (this->next)
		{
			out->next = this->next->clone();
			out->next->prev = out.get();
		}
	//	out->states = move(* (this->states.clone().release()));
	//	out->states["value"] = make_unique<StringState>(any_cast<string>(this->states["value"]->value));
		print("clonned\n");
		return out;
	}

	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		auto out = make_unique<Word>();
		string my;
		scan(str, "{}", my);
		out->states["value"] = make_unique<StringState>(my);
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

/*
fn ftest(initializer_list<pair<const string, unique_ptr<State>>> init)
{
	auto test21 = StateMap();
	for (auto &&itm : init)
	{
	//	test21.emplace(itm.first, move(itm.second));
		 test21.emplace(std::piecewise_construct,
                       std::forward_as_tuple(itm.first),
                       std::forward_as_tuple(std::move(itm.second)));
	}
}
*/
fn main() -> int
{
	print("begin...\n");

	auto test = String("yoo pomme yoo");

	int i;

	auto my = String("42").assign_to<int>(i);
	if (!my) {
		print("conversion error for {}", i);
		exit(1);
	}
	assert(i == 42);

	i = String("43");
	assert(i == 43);
	println("i={}", i);

	println("my: {}", test.replace_substring_occurrences("yoo", "hello").c_str());

	Context ctx;

	auto ii = make_unique<int>(42);


	auto p = StringState::deserialize("yoo");


	/*ftest({
		{string("test"), StringState::deserialize("yoo")}
	});
*/
	auto gg = StateMap({{"test", StringState("yoo")}});

	auto test33 = Ast({
		{Word(
		StateMap({{"test", StringState("yoo")}}),
		Ast({
				{Word(
				StateMap(),
				Ast()
				)},
			})
		)},
	});

	if (test33.first)
		print("type is ... {}\n", test33.first->type);

	astmatcher::interpret("\
								\
			Identifier; 		\n\
			Identifier; 		\n\
			PARENS;				\n\
								\
		", test33);

	println("end..");

	return 0;

	//println("{}", gg["test"]->serialize());
	//println("{}",test33.first->type);


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
				if (lexer(csrc + i).first > 0)
				{
					s_depth -= 1;
					if (i)
						return (LexerOutput) {i, Raw::deserialize(src.substr(0, i))};
					else
						return (LexerOutput) {0, Raw::deserialize(src.substr(0, 0))};
				}
				else if (lexer(csrc + i).first  < 0)
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
					auto prev = it->prev;

					auto new_childs = it->clone();

					// we remove first and last elements (opening and closing parenthesis)
					new_childs = move(new_childs->next);
					new_childs->last()->prev->next = nullptr;


					ast.last = (prev->next = Word::deserialize("PARENS")).get();
					ast.last->childs.link_front(move(new_childs));
					prev->next->prev = prev;
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
			 "\"tes\\\"t\""
			 "(5.98) "
			 "§fesfesfe$éééé \""

		);



	for (auto &item : ctx.ast)
	{
		println("{}", item.serialize());
	}

/*
	astmatcher::interpret("		\
								\
		skip Identifier 		\n\
		skip Identifier 		\n\
		capture PARENS 			\n\
								\
	", ctx.ast);*/

	// test \
	dwdw\
	dwdw

	return 0;
}
