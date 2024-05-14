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

		// todo : remove that from state, shall be in child impls
		fn serialize() const -> string
		{
			throw runtime_error("not implemented");
			return "";
		}

		fn clone() const -> unique_ptr<State>
		{
			throw runtime_error("not implemented");
			return 0;
		}
	};
};


