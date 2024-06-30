export module ucbl.cedilla:util.interface.clonable;

import :common;

export namespace ucbl::cedilla {
	template <typename T>
	struct Clonable
	{
		virtual fn	clone() -> unique_ptr<T> = 0;
	};
}
