#include "assert.h"

import ucbl.cedilla;
import ucbl.cedilla_ext_std;
import std.compat;

using namespace ucbl::cedilla;
using namespace std;

fn test_ext_loader(const string& src) -> pair<string, int>
{
	const string needle = "cedilla_ext_load";
	if (src.find(needle) != 0)
		return { "", 0 };
	auto needle_len = needle.length();
	auto [path, matched_size] =  ext_extract_path(src.substr(needle_len));
	if (!matched_size)
		return { "", 0 };
	matched_size += needle_len;
	return {path, matched_size};
}

fn test_ext_unloader(const string& src) -> pair<string, int>
{
	const string needle = "cedilla_ext_unload";
	if (src.find(needle) != 0)
		return { "", 0 };
	auto needle_len = needle.length();
	auto [path, matched_size] =  ext_extract_path(src.substr(needle_len));
	if (!matched_size)
		return { "", 0 };
	matched_size += needle_len;
	return {path, matched_size};
}

fn main() -> int
{
	{
		string input = R"(cedilla_ext_load   ./path/to/A.so)";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(cedilla_ext_load path/to/ext)";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(cedilla_ext_unload path/to/ext)";
		auto [path, matched_len] = test_ext_unloader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(cedilla_ext_load "./path/to/with\"escaped\"quotes")";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(cedilla_ext_load"./path/without/space")";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(cedilla_ext_loadpath/to/no/space)";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(some_other_command path/to/ignore)";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == 0);
	}
	{
		string input = R"( cedilla_ext_something_else path/to/ignore)";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == 0);
	}
	{
		string input = R"(cedilla_ext_load"unmatched quote)";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == 0);
	}
	{
		string input = R"(cedilla_ext_load )";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == 0);
	}
	{
		string input = R"(cedilla_ext_load "")";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(cedilla_ext_unload "")";
		auto [path, matched_len] =test_ext_unloader(input);
		assert(matched_len == input.length());
	}
	{
		string input = R"(cedilla_ext_load "load")";
		auto [path, matched_len] = test_ext_loader(input);
		assert(matched_len == input.length());
	}
    println("All tests passed.");
}
