module ucbl.cedilla;

import :common;

namespace cedilla
{
	fn Context::lex(string src) -> void
	{
		auto csrc = src.c_str();
		unsigned int i = 0;

		while (csrc[i])
		{
			LexerOutput longest_match { 0, nullptr };

			for (const auto& lexer : this->lexers)
			{
				auto result = lexer(csrc + i);
				if (result.first > longest_match.first)
				{
					longest_match.first = result.first;
					longest_match.second = result.second ? move(result.second) : nullptr;
				}
				else if (result.first < 0)
				{
					throw runtime_error("Lexer runtime error at: " + string(csrc + i));
				}
			}

			if (longest_match.first)
			{
				i += longest_match.first;
				if (longest_match.second)
				{
					this->ast.link_back(move(longest_match.second));
					this->parse(this->ast);
				}
				continue;
			}

			if (csrc[i])
			{
				throw runtime_error("Lexer unknown syntax at: " + string(csrc + i));
			}
		}
	}

	fn Context::parse(Ast& ast) -> void
	{
		while (true)
		{
			auto parsed = false;

			for (const auto& parser : this->parsers)
			{
				auto result = parser(ast);
				if (result > 0)
				{
					parsed = true;
					break;
				}
				else if (result < 0)
				{
					throw runtime_error("Parser runtime error.");
				}
			}

			if (!parsed)
			{
				break;
			}
		}
	}
}

