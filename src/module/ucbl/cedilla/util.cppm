export module ucbl.cedilla:util;

import :common;

// data types
export import :util.data_type._float;
export import :util.data_type._int;
export import :util.data_type._uint;
export import :util.data_type._string;

// interfaces
export import :util.interface.clonable;
export import :util.interface.serializable;


export namespace ucbl::cedilla
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

	fn extractAndReplaceEscapedQuotes(const string& input) -> string
	{
		if (input.front() != '"' || input.back() != '"') {
			throw invalid_argument("Input string must start and end with a quote.");
		}
		auto extracted = input.substr(1, input.length() - 2);
		auto result = string("");
		for (u64 i = 0; i < extracted.length(); i += 1) {
			if (extracted[i] == '\\' && (i + 1 < extracted.length()) && extracted[i + 1] == '"') {
				result += '"';
				i += 1;
			} else {
				result += extracted[i];
			}
		}
		return result;
	}
}
