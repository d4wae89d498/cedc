//import Tree;
module;

import Serializable;
import Box;
import LinkedList;
import Tree;
import ClassRegistry;

#include <string>
#include <memory>

using namespace std;

export module Ast;


export
struct AstNode;

export
struct AstNodeRegistry : public ClassRegistry<AstNode>
{
    static AstNodeRegistry& get() {
        static AstNodeRegistry instance;
        return instance;
    }
};

export
struct AstNode: public TreeNode<AstNode>, public Serializable
{
	const string		name;
	//BoxArray			data;

	AstNode(const string& name) : name(name)
	{
	}

	string serialize()
	{
		return "{"
			"name: \"" + this->name + "\","
	//		"data: " + data.serialize() + ","
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

		//out = astNodeRegistry.createInstance(name);


        return out;
	}

	virtual ~AstNode() = default;
	virtual string compile() = 0;
	//static unique_ptr<AstNode> unserialize(string str);
};


