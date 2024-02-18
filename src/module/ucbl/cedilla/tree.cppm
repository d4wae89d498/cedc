export module ucbl.cedilla:tree;

import :linked_list;

export namespace cedilla {

	template <typename T>
	struct TreeNode : public LinkedListNode<T>
	{
		LinkedList<T>	childs;
	};

	template <typename T>
	struct Tree : public LinkedList<T>
	{
	};

	fn f()
	{
		return 21;
	}
}
