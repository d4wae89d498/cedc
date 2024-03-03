
import ucbl.cedilla;

using namespace cedilla;

struct IntNode :  public LinkedListNode<IntNode>
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

fn main() -> int
{

	IntNode n(4);

	LinkedList<IntNode>	lst;

	//lst.link_front(make_unique<IntNode>(-1));


	println("id: {}",n.x);

    string key;
    int value;
	float v;
	int rest;
	float d = -1;

	if (scan("23.2549 end","{} end", d))
		println("OK VAL {}", d);

	if (scan("test =", "{} =", key))
		println("key: [{}]", key);

    if (scan("test = 12 0.26", "{} = {} {}", key, value, d))
		println("key: [{}]", key);
	else
		println("pasok");
	println("k: {}", value);
	println("d: {}", d);
    return 0;
}
