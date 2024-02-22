export module ucbl.cedilla:box;

import :common;

export namespace cedilla {
	struct Box // : public Serializable
	{
		any		value;

		virtual ~Box() = default;
	};

	struct BoxArray : unordered_map<string, unique_ptr<Box>>
	{
		fn serialize() -> string
		{
			return "[]";
		}
	};
};


