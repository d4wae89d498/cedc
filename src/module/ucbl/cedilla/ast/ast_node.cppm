export module ucbl.cedilla:ast_node;

import :common;
import :tree_node;
import :state_map;
import :clonable;
import :tree;
import :ast;

export namespace cedilla
{
 	struct AstNode : public TreeNode<Ast, AstNode>, Clonable<AstNode>
    {
        const string		type;
        StateMap			data;

		fn clone() const -> unique_ptr<AstNode>;
        virtual ~AstNode() = default;
        virtual fn compile() const -> string = 0;
        AstNode(const string &type);
        fn serialize() const -> string;
        static fn unserialize(string str) -> unique_ptr<AstNode>;
	};
}

