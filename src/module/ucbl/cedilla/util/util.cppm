export module ucbl.cedilla:util;

import :common;

// data types
export import :_float;
export import :_int;
export import :_uint;
export import :_string;

// interfaces
export import :clonable;
export import :serializable;


export namespace cedilla
{
	/*
	 * Implementation of initializer list with move semantics
	 * https://stackoverflow.com/questions/8193102/initializer-list-and-move-semantics
	 */
	template<typename T>
	struct RrefCapture
	{
		T* ptr;
		RrefCapture(T&& x) : ptr(&x) {}
		operator T&& () const { return std::move(*ptr); } // restitute rvalue ref

	};

	template <typename T>
	fn alloc(const T data) -> T*
	{
		auto new_data = static_cast<T*>(malloc(sizeof(T)));
		if (new_data)
		{
			memcpy(new_data, &data, sizeof(T));
		}
		else
		{
			throw runtime_error("OOM error");
		}
		return new_data;
	}
}
