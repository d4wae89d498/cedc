#include <assert.h>

import ucbl.cedilla;

using namespace cedilla;

class IntNode final : public LinkedListNode<IntNode>
{
	public:

	int x;

	IntNode(int v)
	{
		x = v;
	}

	fn dump(int depth = 0) -> void
	{
		printf("%*s{\n", depth * 4, "");
		printf("%*svalue : %i\n", depth * 4 + 4, "", this->x);
		printf("%*snext : %i\n", depth * 4 + 4, "",  this->next.get());
		printf("%*sprev : %i\n", depth * 4 + 4, "", this->prev);
		printf("%*s}\n", depth * 4 , "");
	}
};


struct SInt final : public State
{
	SInt(int value) : State(value)
	{
	}

	fn clone() const -> unique_ptr<State>
	{
		return make_unique<SInt>(any_cast<int>(this->value));
	}

	fn serialize() const -> string
	{
		return format("CSInt({})", any_cast<int>(this->value));
	}

	static fn unserialize(const string& str) -> unique_ptr<State>
	{
		return make_unique<SInt>(19);
	}
};
REGISTER_CLASS(State, SInt, int);

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

	print("Serialized: {}\n", lst.serialize());

	auto pomme = SInt(4);


	auto pomme2 = pomme.clone();

	print("new value: {}\n",any_cast<int>(pomme2->value));

	IntNode *tmp;
	for (auto& itm : lst)
		itm.dump();
	print("----\n");
	for (auto& itm : lst)
		if (itm.x == -888)
			tmp = &itm;
	tmp->x = 775;
	lst.link_before(tmp, make_unique<IntNode>(444));
	lst.del_all([](const IntNode &i){
		return i.x < 0;
	});
	for (auto& itm : lst)
		itm.dump();

	assert(lst.first->x == 21);
	assert(lst.first->next->x == 12);
	assert(lst.first->next->next->x == 22);
	assert(lst.last->prev->x == 444);
	assert(lst.first->prev == nullptr);
	assert(lst.last->next == nullptr);

	print ("--- LinkedList tests succeed\n");
}
