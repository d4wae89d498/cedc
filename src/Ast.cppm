export module Ast;

import Std;
import Tree;
import Box;
import Serializable;
//import AstNodeRegistry;

struct AstNode : public TreeNode<AstNode>, public Serializable
{
	const string		name;
	BoxArray			data;

	virtual ~AstNode() = default;
	virtual string compile() = 0;

	AstNode(const string& name) : name(name)
	{
	}

	string	serialize()
	{
		return "{"
			"name: \"" + this->name + "\","
			"data: " + data.serialize() + ","
			"childs: " + this->childs.serialize() +
		"}";
	}

	static unique_ptr<AstNode> unserialize(string str)
	{
		unique_ptr<AstNode>	out;
	 	size_t 	index = 0;
		size_t	start;
		string name;

        // Skip leading white spaces
        while (index < str.length() && isspace(str[index])) ++index;

        if (str[index] != '{') {
            throw runtime_error("Invalid format: Expected '{'");
        }
        ++index; // Skip '{'



        // Skip to name
        while (index < str.length() && str[index] != '\"') ++index;
        ++index; // Skip '"'

        start = index;
        // Find end of name
        while (index < str.length() && str[index] != '\"') ++index;
        name = str.substr(start, index - start);
        ++index; // Skip '"'

		//out = AstNodeRegistry::createInstance(name);


        return out;
	}
};

struct Ast : public LinkedList<AstNode>
{

};

struct AstNodeRegistry : public ClassRegistry<AstNode>
{

};
