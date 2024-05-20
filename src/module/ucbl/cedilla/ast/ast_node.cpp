module ucbl.cedilla;

import :common;

namespace cedilla
{
	AstNode::AstNode(const string type, StateMap states, Ast childs) : type(type), states(move(states))
	{
	//	this->states = move(states);
		this->childs = move(childs);
	}

	fn AstNode::clone() -> unique_ptr<AstNode>
	{
		return AstNodeRegistry::get().deserialize(this->type,this->serialize());
	}

	fn AstNode::serialize() -> string
	{
		//throw runtime_error("err23");
		return this->type + "(" + this->states.serialize() + ", " + this->childs.serialize() + ")";
	}

	fn AstNode::deserialize(string str) -> unique_ptr<AstNode>
	{
		throw runtime_error("AstNode::deserialize(string) not implemented");
		return 0;
	}
}


