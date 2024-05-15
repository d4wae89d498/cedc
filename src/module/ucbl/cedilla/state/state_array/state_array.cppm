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
		fn clone() -> unique_ptr<StateArray> override;
		fn serialize() -> string override;
		virtual ~StateArray() = default;
	};
}
