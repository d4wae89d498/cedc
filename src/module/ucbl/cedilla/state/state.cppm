export module ucbl.cedilla:state;

import :common;
import :state_registry;

export namespace cedilla
{
	struct State : public Serializable, public Clonable<State>
	{
		const string 	type;
		any				value;

		State(const string type, any value) : type(type), value(value)
		{
		}

		fn clone() -> unique_ptr<State> override
		{
			return StateRegistry::get().deserialize(this->type, this->serialize());
		}

		virtual ~State() = default;
	};
};


