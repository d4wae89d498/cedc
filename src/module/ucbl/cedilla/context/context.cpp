module ucbl.cedilla;

import :common;

namespace cedilla
{
	fn Context::lex(string src) -> void
	{
		auto csrc = src.c_str();
		unsigned i = 0;

		while (csrc[i])
		{
			// Keep longest match only

			println("i={}\n", i);
			auto longest_match = LexerOutput { 0, nullptr };

			for (auto& lexer : this->lexers)
			{
				auto result = lexer(csrc + i);
				if (result.first > longest_match.first)
				{
					longest_match.first = result.first;
					if (result.second)
						longest_match.second = move(result.second);
					else
						longest_match.second = 0;
				}
				else if (result.first < 0)
				{
					throw runtime_error("Lexer runtime error at : " + string(csrc + i));
				}
			}

			if (longest_match.first)
			{
				i += longest_match.first;
				if (longest_match.second)
				{
					this->ast.link_back(move(longest_match.second));
					// todo: apply parser rules

					this->parse(this->ast);


				}

				continue ;
			}

			if (csrc[i])
					throw runtime_error("Lexer unknown syntax at : " + string(csrc + i));
		}
	}

	fn Context::parse(Ast& ast) -> void
	{
		redo:
		for (auto& parser : this->parsers)
		{
			auto result = parser(ast);
			if (result > 0)
			{
				// iter until lastt
				// TODO: finish me
				goto redo;
			}
			else if (result < 0)
			{
				throw new runtime_error("Parser runtime error.");
			}
		}
	}
}

