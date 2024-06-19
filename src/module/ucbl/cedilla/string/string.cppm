export module ucbl.cedilla:string;

import :common;

export namespace cedilla
{
	struct String : public string
	{
		fn replace_substring_occurrences(const string& from, const string& to) -> String;

		fn count_substring_occurrences(const string& needle) const -> u64;

		template<typename T>
		fn assign_to(T& value) const -> bool
		{
			auto str = this;
			if constexpr (is_same_v<T, string>)
			{
				value = *str;
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

		template <typename T>
		operator T() const {
			T value;
			auto r = this->assign_to<T>(value);
			if (!r) {
				throw invalid_argument("Conversion failed");
			}
			return value;
		}

		template<typename T>
		fn scan(const string& format, T& value)
		{
			return scan(this->c_str(), format, &value);
		}
	};

	/*
	* Scan with 1 arg
	*/
	template<typename T>
	fn scan(const string& str, const string& format, T& value) -> bool
	{
		const char *s = str.c_str();
		const char *f = format.c_str();

		if (String(format).count_substring_occurrences("{}") > 1)
			throw runtime_error("More {} placeholders than arguments in scan function");

		while (*s)
			if (!strncmp(f, "{}", 2))
			{
				string match = "";
				f += 2;
				while (*s && *s != *f)
					match += *s++;
				if (!String(match).assign_to(value))
					return false;
			}
			else if (*s == *f && *s)
			{
				s += 1;
				f += 1;
			}
			else
				return false;
		return true;
	}

	/*
	* Scan with reccursive templates args
	* (basic impl of https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1729r0.html)
	*/
	template<typename T, typename ... ARGS>
	fn scan(const string& str, const string& format, T& value, ARGS&... args) -> bool
	{
		const char *s = str.c_str();
		const char *f = format.c_str();

		auto format_string = String(format);

		if (format_string.count_substring_occurrences("{}") > sizeof...(ARGS) + 1)
			throw runtime_error("More {} placeholders than arguments in scan function");
		if (format_string.count_substring_occurrences("{}") < sizeof...(ARGS) + 1)
			throw runtime_error("More arguments tahn placeholders {} in scan function");

		while (1)
			if (!strncmp(f, "{}", 2))
			{
				string match = "";
				f += 2;
				while (*s && *s != *f)
					match += *s++;
				if (!String(match).assign_to(value))
					return false;
				return scan(s, f, args...);
			}
			else if (*s == *f && *s)
			{
				s += 1;
				f += 1;
			}
			else
				return false;
	}
}
