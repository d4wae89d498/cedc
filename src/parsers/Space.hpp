#pragma once

#include "../Parser.hpp"

using namespace std;

class Space : public ParsingRule
{
	public:

	Space() : ParsingRule(__func__)
	{
	}

	size_t	f(const string s)
	{
		size_t i = 0;

		//while (isspace(s[0]))
		//	;
		return 0;
	}
};
