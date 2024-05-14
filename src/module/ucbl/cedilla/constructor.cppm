export module ucbl.cedilla:constructor;

import :common;

export namespace cedilla
{
	template <typename Type, typename... Args>
	unique_ptr<Type> constructor(Args... args)
	{
		return make_unique<Type>(std::forward<Args>(args)...);
	}
}
