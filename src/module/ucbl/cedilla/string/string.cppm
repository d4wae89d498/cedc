export module ucbl.cedilla:string;

import :common;

export namespace cedilla
{
	struct String : public string
	{
		fn replace_substring_occurrences(const string& from, const string& to) -> String;

		fn count_substring_occurrences(const string& needle) -> u64;

		template<typename T>
		fn cast(T& value) -> bool
		{
			auto str = this;
			if constexpr (is_same_v<T, string>)
			{
				value = str;
				return true;
			}
			else if constexpr (is_same_v<T, float> || is_same_v<T, double>)
			{ // TODO : wait std c++ from_chars to support float and double.
			// or check for errono bellow as errno is currently not visible with LIBCXX PCM modules
				char* end;
				if constexpr (is_same_v<T, float>)
					value = strtof(str->c_str(), &end);
				else if constexpr (is_same_v<T, double>)
					value = strtod(str->c_str(), &end);
				return end == str->c_str() + str->size();
			}
			else
			{
				auto [ptr, ec] = from_chars(str->data(), str->data() + str->size(), value);
				return ec == errc();
			}
			// todo handle operator >> for generic class but  LIBCXX PCM modules currently crash with it
		}
	};
}
