export module ucbl.cedilla_std:string_state;

import ucbl.cedilla;

using namespace cedilla;

struct StringState final : public State
{
	StringState(string value) : State(__func__, value)
	{
	}

	fn clone() -> unique_ptr<State>
	{
		return make_unique<StringState>(any_cast<string>(this->value));
	}

	fn serialize() -> string
	{
		return format("{}({})", type, any_cast<string>(this->value));
	}

	static fn deserialize(const string &s) -> unique_ptr<State>
	{
		string value;
		scan(s, "{}", value);
		return make_unique<StringState>(value);
	}
};
REGISTER_DESERIALIZABLE(State, StringState);
