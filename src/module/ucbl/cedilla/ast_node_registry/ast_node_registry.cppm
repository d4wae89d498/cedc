export module ucbl.cedilla:ast_node_registry;

import :common;
import :class_registry;
import :ast_node;

export namespace cedilla
{

	struct AstNodeRegistry : public ClassRegistry<AstNode>
    {
        static fn get() -> AstNodeRegistry &;

	/*	{
			static AstNodeRegistry s_instance;
			return s_instance;
		}*/
    };
}
