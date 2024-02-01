#pragma once

#include "../Parser.hpp"
#include "../Ast.hpp"

using namespace std;

class Raw : public ParsingRule
{
	public:

	Raw() : ParsingRule(__func__)
	{
	}

	size_t	f(const string s)
	{
		size_t i = 0;
		if (!s.length())
			return 0;

		//while (isspace(s[0]))
		//	;
		return 0;
	}
};
