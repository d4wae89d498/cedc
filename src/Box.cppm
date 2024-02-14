export module Box;

import Std;
import Serializable;

struct Box : public Serializable
{
	any		value;

	virtual ~Box() = default;
};

struct BoxArray : unordered_map<string, unique_ptr<Box>>, public Serializable
{
	string serialize()
	{
		return "[]";
	}
};
