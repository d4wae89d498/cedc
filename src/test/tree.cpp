#include <assert.h>

import ucbl.cedilla;

using namespace cedilla;

class IntTreeNode : public TreeNode<IntTreeNode>
{
	public:

	int x;

	IntTreeNode()
	{

	}

	IntTreeNode(int v)
	{
		x = v;
	}

	fn dump(int depth = 0) -> void
	{
		printf("%*s{\n", depth * 4, "");
		printf("%*svalue : %i\n", depth * 4 + 4, "", this->x);
		printf("%*schilds : {", depth * 4 + 4, "");
		if (this->childs.first)
		{
			for (auto& itm : this->childs)
			{
				print("\n");
				itm.dump(depth + 2);
			};
			printf("%*s}\n", depth * 4 + 4, "");
		}
		else
		{
			printf("}\n", "");
		}

		printf("%*s}\n", depth * 4 , "");
	}
};


fn main() -> int
{

	LinkedList<IntTreeNode> lst;


	lst.link_front(make_unique<IntTreeNode>(-1));
	lst.link_back(make_unique<IntTreeNode>(21));

	lst.link_back(make_unique<IntTreeNode>(12));
	lst.link_front(make_unique<IntTreeNode>(-1));
	lst.link_back(make_unique<IntTreeNode>(-12));

	lst.link_back(make_unique<IntTreeNode>(22));
	lst.link_back(make_unique<IntTreeNode>(-888));


	lst.first->next->next->childs.link_back(make_unique<IntTreeNode>(42));


	lst.del_if([](const IntTreeNode &i){
		return i.x < 0;
	});

	for (auto& itm : lst)
	{
		itm.dump();
	}



	assert(lst.first->x == 21);
	assert(lst.first->childs.first->x == 42);
	assert(lst.first->next->x == 12);
	assert(lst.first->next->next->x == 22);

	print ("--- Tree tests succeed\n");

};
