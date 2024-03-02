export module ucbl.cedilla:scan;

import :common;

// basic impl of https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1729r0.html
export namespace cedilla
{
	/*
	* Count number of needle in haystack
	*/
	fn count_substring_occurrences(const string& haystack, const string& needle) -> u64
	{
		size_t count = 0;
		size_t pos = 0;
		while ((pos = haystack.find(needle, pos)) != string::npos)
		{
			count += 1;
			pos += needle.length();
		}
		return count;
	}

	/*
	* Assign string str to T value and returns true if success
	*/
	template<typename T>
	fn string_to(const string &str, T& value) -> bool
	{
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
				value = strtof(str.c_str(), &end);
			else if constexpr (is_same_v<T, double>)
				value = strtod(str.c_str(), &end);
			return end == str.c_str() + str.size();
		}
		else
		{
			auto [ptr, ec] = from_chars(str.data(), str.data() + str.size(), value);
			return ec == errc();
		}
		// todo handle operator >> for generic class but  LIBCXX PCM modules currently crash with it
	}

	/*
	* Scan with 1 arg
	*/
	template<typename T>
	fn scan(const string& str, const string& format, T& value) -> bool
	{
		const char *s = str.c_str();
		const char *f = format.c_str();

		if (count_substring_occurrences(format, "{}") > 1)
			throw runtime_error("More {} placeholders than arguments in scan function");

		while (*s)
			if (!strncmp(f, "{}", 2))
			{
				string match = "";
				f += 2;
				while (*s && *s != *f)
					match += *s++;
				if (!string_to(match, value))
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
	*/
	template<typename T, typename ... Args>
	fn scan(const string& str, const string& format, T& value, Args&... args) -> bool
	{
		const char *s = str.c_str();
		const char *f = format.c_str();

		if (count_substring_occurrences(format, "{}") > sizeof...(Args) + 1)
			throw runtime_error("More {} placeholders than arguments in scan function");
		if (count_substring_occurrences(format, "{}") < sizeof...(Args) + 1)
			throw runtime_error("More arguments tahn placeholders {} in scan function");

		while (1)
			if (!strncmp(f, "{}", 2))
			{
				string match = "";
				f += 2;
				while (*s && *s != *f)
					match += *s++;
				if (!string_to(match, value))
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
