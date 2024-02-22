export module ucbl.cedilla:ast;

import :common;
import :class_registry;
import :tree;

export namespace cedilla
{
    struct AstNode;

    struct AstNodeRegistry : public ClassRegistry<AstNode>
    {
        static fn get()->AstNodeRegistry &
        {
            static AstNodeRegistry s_instance;
            return s_instance;
        }
    };

    struct AstNode : public TreeNode<AstNode>
    {
        const string name;
        // BoxArray			data;
        virtual ~AstNode() = default;
        virtual fn compile()->string = 0;

        AstNode(const string &name) : name(name)
        {
        }

        fn serialize()->string
        {
            return "{"
                   "name: \"" +
                   this->name + "\","
                                //		"data: " + data.serialize() + ","
                                "childs: " +
                   this->childs.serialize() +
                   "}";
        }

        static fn unserialize(string str)
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
        }
    };
}
