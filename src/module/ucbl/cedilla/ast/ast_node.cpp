module ucbl.cedilla;

import :common;

namespace cedilla
{
	AstNode::AstNode(const string &type) : type(type)
	{
	}

	// TODO: check bellow about what should be virtual
	fn AstNode::clone() -> unique_ptr<AstNode>
	{
		throw runtime_error("not implemented");
		auto out = AstNodeRegistry::get().deserialize(this->type,this->serialize());
		out->childs = move(*this->childs.clone().release());
		out->data = move(*this->data.clone().release());
		return out;
	}

	fn AstNode::serialize() -> string
	{
		throw runtime_error("not implemented");
	}

	fn AstNode::deserialize(string str) -> unique_ptr<AstNode>
	{

		throw runtime_error("not implemented");
		return 0;
	}
}


