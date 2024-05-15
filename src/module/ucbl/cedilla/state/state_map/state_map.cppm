export module ucbl.cedilla:state_map;

import :state;
import :common;
import :serializable;
import :clonable;

export namespace cedilla
{
	struct StateMap final
		:
		unordered_map<string, unique_ptr<State>>,
		public Serializable,
		public Clonable<StateMap>
	{
		fn clone() -> unique_ptr<StateMap> override;
		fn serialize() -> string override;
	};
}
