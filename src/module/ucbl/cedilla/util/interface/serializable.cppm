export module ucbl.cedilla:util.interface.serializable;

import :common;

export namespace ucbl::cedilla {
	struct Serializable
	{
		virtual fn serialize() -> string = 0;
	};
}
