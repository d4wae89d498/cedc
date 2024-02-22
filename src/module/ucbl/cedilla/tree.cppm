export module ucbl.cedilla:tree;

import :linked_list;

export namespace cedilla
{
    template <typename T>
    struct TreeNode : public LinkedListNode<T>
    {
        LinkedList<T> childs;
        //	dadw
    };

    fn f() -> int;
}
 // namespace cedilla

/*
A  <- cursor

  ...
   |
   +-- Child1 <- cursor

  ...
   |
   +-- Child1 <- cursor
   +-- Child2 <- cursor

 A B <- cursor

 A B C <- cursor

 A B C
   |
   +-- Child1
   +-- Child2


=> pas besoin de parent ?

*/
