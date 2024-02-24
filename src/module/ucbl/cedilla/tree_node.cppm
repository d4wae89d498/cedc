export module ucbl.cedilla:tree_node;

import :linked_list;
import :linked_list_node;

export namespace cedilla
{
    template <typename T>
    struct TreeNode : public LinkedListNode<T>
    {
        LinkedList<T> childs;
    };
}
