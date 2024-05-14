module ucbl.cedilla;

import :common;

namespace cedilla
{
	fn AstNodeRegistry::get() -> AstNodeRegistry &
	{
		static AstNodeRegistry s_instance;
		return s_instance;
	};
}
