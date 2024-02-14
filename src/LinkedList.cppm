export module LinkedList;

import Std;
import Serializable;

export
void sayHello()
{
//	printf("hello\n");
}

export
template <typename T>
struct Node
{
	unique_ptr<T>	next;
	T				*prev;
};

export
template <typename T>
struct LinkedList : public Serializable
{
	unique_ptr<T>	first;
	T 				last;

	string serialize()
	{

	}
};
