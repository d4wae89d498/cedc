export module ucbl.cedilla:state_map;

import :state;
import :common;
import :serializable;
import :clonable;

export namespace cedilla
{
	struct StateMap
		:
		unordered_map<string, unique_ptr<StateMap>>,
		public Serializable,
		public Clonable<StateMap>
	{
		fn clone() const -> unique_ptr<StateMap>;
		fn serialize() const -> string;
	};
}
