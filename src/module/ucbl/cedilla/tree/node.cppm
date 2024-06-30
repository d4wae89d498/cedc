export module ucbl.cedilla:tree.node;

import :tree;
import :linked_list.node;

export namespace ucbl::cedilla
{
	template <typename T, typename U>
    struct TreeNode : public LinkedListNode<U>
    {
	 	T childs;
	};
}
