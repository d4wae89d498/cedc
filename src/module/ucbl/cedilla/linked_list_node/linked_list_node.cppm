export module ucbl.cedilla:linked_list_node;

import :common;

export
namespace cedilla
{
	template <typename T>
	struct LinkedListNode
	{
		unique_ptr<T>	next = nullptr;
		T				*prev = nullptr;

		fn last() -> T*;
	};

	template <typename T>
	fn LinkedListNode<T>::last() -> T*
	{
		T* last = static_cast<T*>(this);
		while (last->next)
			last = last->next.get();
		return last;
	}
}


