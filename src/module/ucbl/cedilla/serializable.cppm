export module ucbl.cedilla:serializable;

import :common;

export namespace cedilla
{
	struct Serializable
	{
		virtual fn serialize() -> string = 0;
	};
}
