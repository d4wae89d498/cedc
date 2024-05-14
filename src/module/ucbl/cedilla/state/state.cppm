export module ucbl.cedilla:state;

import :common;
import :serializable;
import :clonable;

export namespace cedilla
{
	struct State : public Serializable, public Clonable<State>
	{
		any		value;

		State(any value) : value(value)
		{
		}

		fn serialize() const -> string
		{
			return "";
		}

		fn clone() const -> unique_ptr<State>
		{
			return 0;
		}

	//	virtual ~State() = default;
	};
};


