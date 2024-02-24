export module ucbl.cedilla:ast_node_registry.impl;
export import :ast_node_registry;

import :common;
import :class_registry.impl;

namespace cedilla
{
	fn AstNodeRegistry::get() -> AstNodeRegistry &
	{
		static AstNodeRegistry s_instance;
		return s_instance;
    };
}
