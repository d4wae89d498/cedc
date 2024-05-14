module ucbl.cedilla;

import :common;

namespace cedilla
{

	AstNode::AstNode(const string &type) : type(type)
	{
	}

	fn AstNode::serialize() -> string
	{
		return "{"
				"name: \""
				+ this->type
				+ "\","
	//				"data: " + data.serialize() + ","
				"childs: "
			+ this->childs.serialize() +
		"}";
	}
/*
	// todo: this should call Registry::create_instance under the hood

	fn AstNode::unserialize(string str) -> unique_ptr<AstNode>
	{
		unique_ptr<AstNode> out;
		size_t index = 0;
		size_t start;
		string name;

		print("calling astNode::unserialize()... {}\n", str);

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
	};*/
}


