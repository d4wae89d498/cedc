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
				if (result.matched_src_prefix_length > longest_match.matched_src_prefix_length)
				{
					longest_match.matched_src_prefix_length = result.matched_src_prefix_length;
					if (result.nodes)
						longest_match.nodes = move(result.nodes);
					else
						longest_match.nodes = 0;
				}
				else if (result.matched_src_prefix_length < 0)
				{
					throw runtime_error("Lexer runtime error at : " + string(csrc + i));
				}
			}

			if (longest_match.matched_src_prefix_length)
			{
				i += longest_match.matched_src_prefix_length;
				if (longest_match.nodes)
				{
					this->ast.link_back(move(longest_match.nodes));
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

