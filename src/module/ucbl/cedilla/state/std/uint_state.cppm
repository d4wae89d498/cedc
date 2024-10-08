export module ucbl.cedilla:state.std.uint_state;

import :common;
import :state;
import :ast.node;
import :util;
import :state.registry;

export namespace ucbl::cedilla
{
	struct UIntState final : public State
	{
		UIntState(u64 value) : State(__func__, value)
		{
		}

		fn clone() -> unique_ptr<State>
		{
			return make_unique<UIntState>(any_cast<u64>(this->value));
		}

		fn serialize() -> string
		{
			return format("{}({})", type, any_cast<u64>(this->value));
		}

		static fn deserialize(const string &s) -> unique_ptr<State>
		{
			u64 value;
			scan(s, "{}", value);
			return make_unique<UIntState>(value);
		}
	};
}

namespace ucbl::cedilla
{
	REGISTER_DESERIALIZABLE(State, UIntState);
}
