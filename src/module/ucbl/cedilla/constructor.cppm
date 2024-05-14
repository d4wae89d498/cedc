export module ucbl.cedilla:constructor;

import :common;

export namespace cedilla
{
	template <typename TYPE, typename... ARGS>
	unique_ptr<TYPE> constructor(ARGS... args)
	{
		return make_unique<TYPE>(std::forward<ARGS>(args)...);
	}
}
