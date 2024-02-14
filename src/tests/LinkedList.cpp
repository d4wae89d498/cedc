import Std;

class IntNode : public Node<IntNode>
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


int main()
{

	LinkedList<IntNode> lst;


	lst.add_front(make_unique<IntNode>(-1));
	lst.add_back(make_unique<IntNode>(21));

	lst.add_back(make_unique<IntNode>(12));
	lst.add_front(make_unique<IntNode>(-1));
	lst.add_back(make_unique<IntNode>(-12));

	lst.add_back(make_unique<IntNode>(22));
	lst.add_back(make_unique<IntNode>(-888));

/*
	lst.iter_back([](IntNode *i){
		return ;
		cout << "this: " << i << endl;
		cout << "*value:" << i->x << endl;
		cout << "next:" << i->next << endl;
		cout << "prev:" << i->prev << endl;
		cout << "--" << endl;
	});
*/

	lst.del_if([](IntNode *i){
		return i->x < 0;
	});

	assert(lst.first->x == 21);
	assert(lst.first->next->x == 12);
	assert(lst.first->next->next->x == 22);
/*
	cout << "after del: " << endl;


	lst.iter_back([](IntNode *i){
		cout << "this: " << i << endl;
		cout << "*value:" << i->x << endl;
		cout << "next:" << i->next << endl;
		cout << "prev:" << i->prev << endl;
		cout << "--" << endl;
	});
*/
	//assert()

}
