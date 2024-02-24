export module ucbl.cedilla:tree;

import :common;
import :linked_list;

export namespace cedilla
{
    template <typename T>
    struct TreeNode : public LinkedListNode<T>
    {
        LinkedList<T> childs;
    };
}
