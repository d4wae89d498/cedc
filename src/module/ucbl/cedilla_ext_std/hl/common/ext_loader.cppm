export module ucbl.cedilla_ext_std:hl.common.ext_loader;

import :common;

export namespace ucbl::cedilla
{
	/*

		format is :

		cedilla_ext_load "./path/to/ext"

		cedilla_ext_load path/to/ext


	*/
	fn ext_extract_path(const string src) -> pair<string, u64>;
	//
	fn ext_loader(const string& src) -> LexerOutput;
	fn ext_unloader(const string& src) -> LexerOutput;
}

