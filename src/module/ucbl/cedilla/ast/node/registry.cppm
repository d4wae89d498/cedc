export module ucbl.cedilla:ast.node.registry;

import :common;
import :class_registry;
import :ast.node;

export namespace ucbl::cedilla
{

	struct AstNodeRegistry final : public ClassRegistry<AstNode>
    {
        static fn get() -> AstNodeRegistry &;
    };
}
