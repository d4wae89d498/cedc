export module ucbl.cedilla:ast;

import :common;
import :tree;
import :linked_list;
import :serializable;
import :clonable;

export namespace cedilla
{
	struct AstNode;

    struct Ast final : public Tree<AstNode>, public Serializable, public Clonable<Ast>
    {
		fn	serialize() const -> string
		{
			throw runtime_error("not implemented");
			return "[]";
		}

		fn	clone() const -> unique_ptr<Ast>
		{
			throw runtime_error("not implemented");
			return 0;
		}
    };
}
