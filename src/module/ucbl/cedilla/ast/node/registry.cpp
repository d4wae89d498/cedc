module ucbl.cedilla;

import :common;

namespace ucbl::cedilla
{
	fn AstNodeRegistry::get() -> AstNodeRegistry &
	{
		static AstNodeRegistry s_instance;
		return s_instance;
	};
}
