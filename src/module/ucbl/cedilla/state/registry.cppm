export module ucbl.cedilla:state.registry;

import :common;
import :class_registry;

export namespace ucbl::cedilla
{
	struct State;

	struct StateRegistry : public ClassRegistry<State>
    {
        static fn get() -> StateRegistry &;
    };
}
