module ucbl.cedilla;

import :common;

namespace ucbl::cedilla
{
	fn StateRegistry::get() -> StateRegistry &
	{
		static StateRegistry s_instance;
		return s_instance;
	};
}
