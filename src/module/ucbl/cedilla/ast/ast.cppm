export module ucbl.cedilla:ast;

import :tree;
import :linked_list;

export namespace cedilla
{
//	using Ast = LinkedList<AstNode>;

	struct AstNode;

    struct Ast : public Tree<AstNode>
    {
    };
}
