export module ucbl.cedilla_std:ast_node_state;

import ucbl.cedilla;

using namespace cedilla;

struct AstNodeState final : public State
{
   AstNodeState(unique_ptr<AstNode> value = {})
        : State(__func__, value->clone().release())
    {

    }

	~AstNodeState()
	{
		free(std::any_cast<void*>(this->value));
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

