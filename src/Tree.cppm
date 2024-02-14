module;

import LinkedList;

export module Tree;

export
template <typename T>
struct TreeNode : public LinkedListNode<T>
{
	LinkedList<T>	childs;
};

export
template <typename T>
struct Tree : public LinkedList<T>
{
};

