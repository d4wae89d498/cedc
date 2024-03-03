module ucbl.cedilla;

import :common;

namespace cedilla
{

	AstNode::AstNode(const string &name) : name(name)
	{
	}

	fn AstNode::serialize() -> string
	{
		return "{"
				"name: \""
				+ this->name
				+ "\","
	//				"data: " + data.serialize() + ","
				"childs: "
			+ this->childs.serialize() +
		"}";
	}
}

/*
fn AstNode::unserialize(string str) -> unique_ptr<AstNode>
{
	unique_ptr<AstNode> out;
	size_t index = 0;
	size_t start;
	string name;

	while (index < str.length() && isspace(str[index]))
		index += 1;

	if (str[index] != '{')
	{
		throw runtime_error("Invalid format: Expected '{'");
	}
	index += 1;

	while (index < str.length() && str[index] != '\"')
		index += 1;
	index += 1;

	start = index;
	while (index < str.length() && str[index] != '\"')
		index += 1;
	name = str.substr(start, index - start);
	index += 1;
	return out;
};
*/
/*
fn AstNodeRegistry::get() -> AstNodeRegistry &
{
	static AstNodeRegistry s_instance;
	return s_instance;
};*/
