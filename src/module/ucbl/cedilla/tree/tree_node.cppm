export module ucbl.cedilla:tree_node;

import :tree;
import :linked_list_node;

export namespace cedilla
{
	template <typename T, typename U>
    struct TreeNode : public LinkedListNode<U>
    {
	 	T childs;
	};
}
