export module ucbl.cedilla:ast_node_state;

import :common;
import :state;
import :ast_node;
import :string;
import :state_registry;

namespace cedilla
{
	// 'any' cant store unique_ptr, so we have to use manual memory management here
	struct AstNodeState final : public State
	{
		AstNodeState(unique_ptr<AstNode> value = {})
			: State(__func__, value->clone().release())
		{
			if (!value)
			{
				throw invalid_argument("value cannot be null");
			}
		}

		// TODO: implement copy and move constructors

		~AstNodeState()
		{
			delete any_cast<AstNode*>(this->value);
		}

		fn clone() -> unique_ptr<State> override
		{
			return make_unique<AstNodeState>(any_cast<AstNode*>(this->value)->clone());
		}

		fn serialize() -> string override
		{
			auto node = any_cast<AstNode*>(this->value);
			return format("{}({})", type, node->serialize());
		}

		static fn deserialize(const string &s) -> unique_ptr<State>
		{
			return make_unique<AstNodeState>(AstNode::deserialize(s));
		}
	};
	REGISTER_DESERIALIZABLE(State, AstNodeState);
}
