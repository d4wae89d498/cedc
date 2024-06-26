export module ucbl.cedilla:state.map;

import :common;
import :util;
import :state;

export namespace ucbl::cedilla
{
	struct StateMap final
		:
		public unordered_map<string, unique_ptr<State>>,
		public Serializable,
		public Clonable<StateMap>
	{
        using BaseType = unordered_map<string, unique_ptr<State>>;
        using BaseType::unordered_map;

        StateMap(StateMap&& other) noexcept : BaseType(std::move(other)) {}
        StateMap(initializer_list<pair<const string, RrefCapture<unique_ptr<State>>>> init);
        StateMap(initializer_list<pair<const string, RrefCapture<State>>> init);


    	//StateMap(const StateMap&) = delete;
        //fn operator=(const StateMap&) -> StateMap& = delete;

		fn clone() -> unique_ptr<StateMap> override;
		fn serialize() -> string override;
	};
}
