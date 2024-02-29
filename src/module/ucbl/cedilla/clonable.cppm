export module ucbl.cedilla:clonable;

import :common;

export namespace cedilla
{
	template <typename T>
	struct Clonable
	{
		virtual fn	clone() const -> unique_ptr<T> = 0;
	};
}
