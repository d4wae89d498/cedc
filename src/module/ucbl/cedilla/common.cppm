export module ucbl.cedilla:common;

export import std;
export import std.compat;

export namespace cedilla
{
	using namespace std;

	template <typename T>
	struct Clonable
	{
		virtual fn	clone() -> unique_ptr<T> = 0;
	};

	struct Serializable
	{
		virtual fn serialize() -> string = 0;
	};

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
};
