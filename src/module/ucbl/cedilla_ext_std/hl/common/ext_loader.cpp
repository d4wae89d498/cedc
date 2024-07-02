module ucbl.cedilla_ext_std;

import :common;

namespace ucbl::cedilla
{
	fn ext_extract_path(const string src) -> pair<string, u64>
	{
		u64 pos = 0;
		// Skip optional spaces
		while (pos < src.length() && isspace(src[pos])) {
			pos += 1;
		}

		if (pos < src.length()) {
			if (src[pos] == '"') {
			 	// Path enclosed in quotes
				size_t endPos = pos + 1;
				while (endPos < src.length()) {
					if (src[endPos] == '"' && src[endPos - 1] != '\\') {
						break;
					}
					endPos += 1;
				}
				if (endPos != string::npos && endPos < src.length() && src[endPos] == '"') {					string path = extractAndReplaceEscapedQuotes(src.substr(pos, endPos - pos + 1));
					return { path, static_cast<u64>(endPos + 1) };
				}
			} else {
				// Path not enclosed in quotes, capture until end of line or next space
				size_t endPos = src.find(' ', pos);
				if (endPos == string::npos) {
					endPos = src.length();
				}
				string path = src.substr(pos, endPos - pos);
				return { path, static_cast<u64>(endPos) };
			}
		}

		return { "", 0 };
	}

	/*

		format is :

		cedilla_ext_load "./path/to/ext"

		cedilla_ext_load path/to/ext


	*/




	fn ext_loader(const string& src) -> LexerOutput
	{
		size_t prefix_len = src.find("cedilla_ext_load");
		if (prefix_len != 0)
			return { 0, nullptr };
		auto [path, matched_len] = ext_extract_path(src.substr(prefix_len));
		matched_len += prefix_len;
		// TODO: proceed....
		return { matched_len, nullptr };
	}

	fn ext_unloader(const string& src) -> LexerOutput
	{
		size_t prefix_len = src.find("cedilla_ext_unload");
		if (prefix_len != 0)
			return { 0, nullptr };
		auto [path, matched_len] = ext_extract_path(src.substr(prefix_len));
		matched_len += prefix_len;
		// TODO: proceed....
		return { matched_len, nullptr };
	}
}

