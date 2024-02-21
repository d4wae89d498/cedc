#include <assert.h>

import ucbl.cedilla;

using namespace cedilla;

class IntNode : public LinkedListNode<IntNode>
{
	public:

	int x;

	IntNode()
	{

	}

	IntNode(int v)
	{
		x = v;
	}
};


fn main() -> int
{

	LinkedList<IntNode> lst;


	lst.link_front(make_unique<IntNode>(-1));
	lst.link_back(make_unique<IntNode>(21));

	lst.link_back(make_unique<IntNode>(12));
	lst.link_front(make_unique<IntNode>(-1));
	lst.link_back(make_unique<IntNode>(-12));

	lst.link_back(make_unique<IntNode>(22));
	lst.link_back(make_unique<IntNode>(-888));


	for (auto& itm : lst)
	{
		print(" value : {}\n", itm.x);
	}

	lst.del_if([](const IntNode &i){
		return i.x < 0;
	});

	assert(lst.first->x == 21);
	assert(lst.first->next->x == 12);
	assert(lst.first->next->next->x == 22);

	print ("--- LinkedList tests succeed\n");

}
