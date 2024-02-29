export module ucbl.cedilla:state_registry;

import :common;
import :class_registry;
import :state;

export namespace cedilla
{

	struct StateRegistry : public ClassRegistry<State>
    {
        static fn get() -> StateRegistry &;

	/*	{
			static AstNodeRegistry s_instance;
			return s_instance;
		}*/
    };
}
