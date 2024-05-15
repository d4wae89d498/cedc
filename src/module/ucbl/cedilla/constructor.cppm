export module ucbl.cedilla:constructor;

import :common;

export namespace cedilla
{
	template <typename TYPE, typename... ARGS>
	fn constructor(ARGS... args) -> unique_ptr<TYPE>
	{
		return make_unique<TYPE>(std::forward<ARGS>(args)...);
	}
}
