export module ucbl.cedilla:ast;

import :common;
import :class_registry;
import :tree;

export namespace cedilla
{
	struct AstNode;

	struct AstNodeRegistry : public ClassRegistry<AstNode>
	{
		static fn get() -> AstNodeRegistry&
		{
			static AstNodeRegistry s_instance;
			return s_instance;
		}
	};

	struct AstNode: public TreeNode<AstNode>
	{
		const string		name;
		//BoxArray			data;

		AstNode(const string& name) : name(name)
		{
		}

		fn serialize() -> string
		{
			return "{"
				"name: \"" + this->name + "\","
		//		"data: " + data.serialize() + ","
				"childs: " + this->childs.serialize() +
			"}";
		}

		static fn unserialize(string str)
		{
			unique_ptr<AstNode>	out;
			size_t 	index = 0;
			size_t	start;
			string name;

			// Skip leading white spaces
			while (index < str.length() && isspace(str[index]))
				index += 1;

			if (str[index] != '{')
			{
				throw runtime_error("Invalid format: Expected '{'");
			}
			index += 1;



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

		virtual fn compile() -> string = 0;

		//static unique_ptr<AstNode> unserialize(string str);
	};
};

