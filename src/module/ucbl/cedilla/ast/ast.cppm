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
			return "[]";
		}

		fn	clone() const -> unique_ptr<Ast>
		{
			return 0;
		}
    };
}
