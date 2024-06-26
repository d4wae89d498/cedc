export module ucbl.cedilla:int_state;

import :common;
import :state;
import :ast_node;
import :util;
import :state_registry;

export namespace cedilla
{
	struct IntState final : public State
	{
		IntState(s64 value) : State(__func__, value)
		{
		}

		fn clone() -> unique_ptr<State>
		{
			return make_unique<IntState>(any_cast<s64>(this->value));
		}

		fn serialize() -> string
		{
			return format("{}({})", type, any_cast<s64>(this->value));
		}

		static fn deserialize(const string &s) -> unique_ptr<State>
		{
			s64 value;
			scan(s, "{}", value);
			return make_unique<IntState>(value);
		}
	};
}

namespace cedilla
{
	REGISTER_DESERIALIZABLE(State, IntState);
}