module ucbl.cedilla;

import :common;
import :string;

namespace cedilla
{
	fn String::replace_substring_occurrences(const string& from, const string& to) -> String
	{
		String original = String(this->c_str());
		size_t start_pos = 0;
		while ((start_pos = original.find(from, start_pos)) != string::npos) {
			original.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return original;
	}

	fn String::count_substring_occurrences(const string& needle) -> u64
	{
		size_t count = 0;
		size_t pos = 0;
		while ((pos = this->find(needle, pos)) != string::npos)
		{
			count += 1;
			pos += needle.length();
		}
		return count;
	}
}
