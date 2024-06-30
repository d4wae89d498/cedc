export module ucbl.cedilla:tree;

import :linked_list;

export namespace ucbl::cedilla
{
    template <typename T>
    struct Tree : public LinkedList<T>
    {
    };
}
