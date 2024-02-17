module;

import std;
import Serializable;

using namespace std;

export module Box;

export struct Box // : public Serializable
{
	any		value;

	virtual ~Box() = default;
};

export struct BoxArray : unordered_map<string, unique_ptr<Box>>, public Serializable
{
	string serialize()
	{
		return "[]";
	}
};
