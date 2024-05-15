module ucbl.cedilla;

import :common;
import :ast;
import :ast_node;

namespace cedilla
{
	fn	Ast::clone() -> unique_ptr<Ast>
	{
		auto out = make_unique<Ast>();
		out->first = this->first->clone();
		out->last = out->first->last();
		return out;
	}

	fn Ast::serialize() -> string
	{
		throw runtime_error("not implemented");
	}
}
