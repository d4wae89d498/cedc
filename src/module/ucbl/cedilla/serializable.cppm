export module ucbl.cedilla:serializable;

import :common;

//int smallchange;

export namespace cedilla
{
	struct Serializable
	{
		virtual string	serialize() = 0;
	};
};

