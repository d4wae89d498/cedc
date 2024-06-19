export module ucbl.cedilla:float_state;

import :common;
import :state;
import :ast_node;
import :util;
import :state_registry;

export namespace cedilla
{
	struct FloatState final : public State
	{
		FloatState(double value) : State(__func__, value)
		{
		}

		fn clone() -> unique_ptr<State>
		{
			return make_unique<FloatState>(any_cast<double>(this->value));
		}

		fn serialize() -> string
		{
			return format("{}({})", type, any_cast<double>(this->value));
		}

		static fn deserialize(const string &s) -> unique_ptr<State>
		{
			double value;
			scan(s, "{}", value);
			return make_unique<FloatState>(value);
		}
	};
}

namespace cedilla
{
	REGISTER_DESERIALIZABLE(State, FloatState);
}
