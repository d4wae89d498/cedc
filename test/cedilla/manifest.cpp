export module ucbl.cedillac:manifest;

import ucbl.cedilla;

using namespace cedilla;

extern "C"
{

	fn on_attach(cedilla::Context &ctx)
	{
		ctx.parsers.push_back([](Ast &tree) -> ParserOutput {

			// match function return values ?
			AstNode *ptr;

			// todo: use libastmatch instead
			if (tree.match("skip:O_PAR capture:* skip:C_PAR"))
			{

			}
		});
	}

	fn on_detach(cedilla::Context &ctx)
	{

	}
}

