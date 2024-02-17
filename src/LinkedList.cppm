module;

import Serializable;



#include <string>
#include <memory>




using namespace  std;

export module LinkedList;

export template <typename T>
struct LinkedListNode
{
	unique_ptr<T>	next;
	T				*prev;
};

export template <typename T>
struct LinkedList  : public Serializable
{
	unique_ptr<T>	first;
	T 				*last;

	string serialize()
	{
		return string("");
	}
};
