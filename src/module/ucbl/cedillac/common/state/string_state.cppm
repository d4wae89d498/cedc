export module ucbl.cedillac:string_state;

import ucbl.cedilla;

using namespace cedilla;

struct StringState final : public State
{
	StringState(string value) : State(__func__, value)
	{
	}

	fn clone() -> unique_ptr<State> override
	{
		return make_unique<StringState>(any_cast<string>(this->value));
	}

	fn serialize() -> string override
	{
		return this->type + "(\"" + String(any_cast<string>(this->value))
			.replace_substring_occurrences("\"", "\\\"")
			+ "\")";
	}

	static fn deserialize(const string &str) -> unique_ptr<State>
	{
		return make_unique<StringState>(str);
	}
};
REGISTER_DESERIALIZABLE(State, StringState);
