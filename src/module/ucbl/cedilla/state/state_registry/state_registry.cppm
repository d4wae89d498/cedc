export module ucbl.cedilla:state_registry;

import :common;
import :class_registry;

export namespace cedilla
{
	struct State;

	struct StateRegistry : public ClassRegistry<State>
    {
        static fn get() -> StateRegistry &;
    };
}
