export module ucbl.cedilla:scan;

import :common;

// basic impl of https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p1729r0.html
export namespace cedilla
{
	template<typename... Args>
	fn scan(const string& input, const string& format, Args&... args) -> bool
	{
		string regex_format = regex_replace(format, regex("\\{\\}"), "(.*)");
		regex r(regex_format);
		smatch match;
		if (regex_search(input, match, r) && match.size() == sizeof...(Args) + 1)
		{
			istringstream iss;
			size_t index = 0;
			((iss.clear(), iss.str(match[++index]), iss >> args), ...);
			return true;
		}
		return false;
	}
}
