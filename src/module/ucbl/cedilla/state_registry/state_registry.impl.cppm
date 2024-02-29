export module ucbl.cedilla:state_registry.impl;
export import :state_registry;

import :common;
import :class_registry.impl;

namespace cedilla
{
	fn StateRegistry::get() -> StateRegistry &
	{
		static StateRegistry s_instance;
		return s_instance;
    };
}
