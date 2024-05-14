export module ucbl.cedilla:state_array;

import :state;
import :common;
import :serializable;
import :clonable;

export namespace cedilla
{
	struct StateArray final
		:
		vector<unique_ptr<State>>,
		public Serializable,
		public Clonable<StateArray>
	{
		fn clone() const -> unique_ptr<StateArray>;
		fn serialize() const -> string;
		virtual ~StateArray() = default;
	};
}
