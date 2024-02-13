#pragma once
#include <vector>
#include <any>
#include <unordered_map>
#include <string>

#include "./Tree.hpp"
#include "./Box.hpp"
#include "./Serializable.hpp"
//#include "./AstNodeRegistry.hpp"

using namespace std;

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
