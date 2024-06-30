export module ucbl.cedilla:state.array;

import :state;
import :util;
import :common;

export namespace ucbl::cedilla
{
	struct StateArray final
		:
		vector<unique_ptr<State>>,
		public Serializable,
		public Clonable<StateArray>
	{
 		using BaseType = vector<unique_ptr<State>>;
        using BaseType::vector;

        StateArray(StateArray&& other) noexcept : BaseType(std::move(other)) {}
        StateArray(initializer_list<RrefCapture<unique_ptr<State>>> init);

        StateArray(const StateArray&) = delete;
        fn operator=(const StateArray&) -> StateArray& = delete;

		fn clone() -> unique_ptr<StateArray> override;
		fn serialize() -> string override;
		virtual ~StateArray() = default;
	};
}
