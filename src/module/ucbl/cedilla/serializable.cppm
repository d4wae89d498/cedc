export module ucbl.cedilla:serializable;

import :common;

export namespace cedilla
{
	template <typename T>
	struct Serializable
	{
		fn	serialize() -> string;
	};
}
