/*-----------------------------------------------------*/
//
//	CedC
//
/*-----------------------------------------------------*/

//#include <stdio.h>
//#include <memory>

//using namespace std;

/*-----------------------------------------------------*/

export module LinkedList;

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

};

export
template <typename T>
struct LinkedList : public Serializable
{
//	unique_ptr<T>	first;
	T 				last;
};
