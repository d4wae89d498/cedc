export module ucbl.cedilla:ast_node;

import :common;
import :class_registry;
import :tree_node;

export namespace cedilla
{
    struct AstNode : public TreeNode<AstNode>
    {
        const string name;
        // BoxArray			data;

        virtual ~AstNode() = default;
        virtual fn compile() -> string = 0;
        explicit AstNode(const string &name);
        fn serialize() -> string;
        static fn unserialize(string str) -> unique_ptr<AstNode>;
	};

/*
	struct AstNodeRegistry : public ClassRegistry<AstNode>
    {
        static fn get() -> AstNodeRegistry &;
    };*/
}
