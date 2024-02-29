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

		virtual ~State() = default;
	};
};


