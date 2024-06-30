export module ucbl.cedilla:ast.node;

import :common;
import :util;
import :tree.node;
import :state.map;
import :tree;
import :ast;

export namespace ucbl::cedilla
{
 	struct AstNode : public TreeNode<Ast, AstNode>, public Clonable<AstNode>, public Serializable
    {
        const string		type;
        StateMap			states;

        AstNode(const string type, StateMap states = StateMap(), Ast childs = Ast());
		fn clone() -> unique_ptr<AstNode> override;
        fn serialize() -> string override;
        virtual ~AstNode() = default;
        virtual fn compile() -> string = 0;
        static fn deserialize(string str) -> unique_ptr<AstNode>;
	};
}

