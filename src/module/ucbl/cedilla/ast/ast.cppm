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
		fn	clone() -> unique_ptr<Ast> override;
		fn	serialize() -> string override;
    };
}
