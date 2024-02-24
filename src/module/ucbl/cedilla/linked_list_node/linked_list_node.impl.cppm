export module ucbl.cedilla:linked_list_node.impl;
export import :linked_list_node;

import :common;

namespace cedilla
{
	template <typename T>
	fn LinkedListNode<T>::last() -> T*
	{
		T* last = static_cast<T*>(this);
		while (last->next)
			last = last->next.get();
		return last;
	}
}
