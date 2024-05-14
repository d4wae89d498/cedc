export module ucbl.cedilla:tree;

import :linked_list;

export namespace cedilla
{
    template <typename T>
    struct Tree : public LinkedList<T>
    {
    };
}
