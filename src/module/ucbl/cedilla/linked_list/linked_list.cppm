export module ucbl.cedilla:linked_list;

import :common;

export namespace cedilla
{
	template <typename T>
	struct LinkedList
	{
		unique_ptr<T>	first = nullptr;
		T 				*last = nullptr;

		struct Iterator
		{
			T* current;

			explicit Iterator(T* node);
			fn operator*() const -> T&;
			fn operator->() -> T*;
			fn operator++() -> Iterator&;
			fn operator!=(const Iterator& other) const -> bool;
		};

		fn begin() -> Iterator;
		fn end() -> Iterator;
		fn link_before(T* node, unique_ptr<T> new_node) -> void;
		fn link_after(T* node, unique_ptr<T> new_node) -> void;
		fn link_back(unique_ptr<T> node) -> void;
		fn link_front(unique_ptr<T> node) -> void;
		fn del_one(T* node) -> void;
		fn del_all(function<bool(const T&)> predicate) -> void;
		fn replace_one(T* old_node, unique_ptr<T> new_node) -> void;
		fn size() -> u64;
	};

	template<typename T>
	LinkedList<T>::Iterator::Iterator(T* node) : current(node)
	{
	}

	template<typename T>
	fn LinkedList<T>::Iterator::operator*() const -> T&
	{
		return *current;
	}

	template<typename T>
	fn LinkedList<T>::Iterator::operator->() -> T*
	{
		return current;
	}

	template<typename T>
	fn LinkedList<T>::Iterator::operator++() -> Iterator&
	{
		current = current->next.get();
		return *this;
	}

	template<typename T>
	fn LinkedList<T>::Iterator::operator!=(const Iterator& other) const -> bool
	{
		return current != other.current;
	}

	template<typename T>
	fn LinkedList<T>::begin() -> Iterator
	{
		return Iterator(first.get());
	}

	template<typename T>
	fn LinkedList<T>::end() -> Iterator {
		return Iterator(nullptr);
	}

	template <typename T>
	fn LinkedList<T>::link_before(T* node, unique_ptr<T> new_node) -> void
	{
		if (!node || !new_node)
			return;
		const auto new_node_last = new_node->last();
		if (!node->prev)
		{
			new_node_last->next = move(first);
			new_node_last->next->prev = new_node_last;
			first = move(new_node);
		}
		else
		{
			const auto old_prev = node->prev;
			new_node_last->next = unique_ptr<T>(node);
			new_node_last->next->prev = new_node_last;
			new_node->prev = old_prev;

			old_prev->next.release();
			old_prev->next = move(new_node);
		}
	}

	template <typename T>
	fn LinkedList<T>::link_after(T* node, unique_ptr<T> new_node) -> void
	{
		if (!node->next)
		{
			node->next = move(new_node);
			node->next->prev = node;
			last = node->next.get();
		}
		else
		{
			new_node->next = move(node->next);
			new_node->prev = node;
			node->next = move(new_node);
			node->next->next->prev = node->next.get();
		}
	}

	template <typename T>
	fn LinkedList<T>::link_back(unique_ptr<T> node) -> void
	{
		if (!first)
		{
			first = move(node);
			last = first.get();
		}
		else
		{
			last->next = move(node);
			last->next->prev = last;
			last = last->next.get();
		}
	}

	template <typename T>
	fn LinkedList<T>::link_front(unique_ptr<T> node) -> void
	{
		if (first)
		{
			node->next = move(first);
			node->next->prev = node.get();
			first = move(node);
		}
		else
		{
			first = move(node);
			last = first.get();
		}
	}

	template <typename T>
	fn LinkedList<T>::del_one(T* node) -> void
	{
		if (node->next)
			node->next->prev = node->prev;
		else
			last = node->prev;
		if (node->prev)
			node->prev->next = move(node->next);
		else
			first = move(node->next);
	}

	template <typename T>
	fn LinkedList<T>::del_all(function<bool(const T&)> predicate) -> void
	{
		T* current = first.get();
		T* prev = nullptr;

		while (current)
		{
			T* next = current->next.get();
			if (predicate(*current))
				del_one(current);
			current = next;
		}
	}

	template <typename T>
	fn LinkedList<T>::replace_one(T* old_node, unique_ptr<T> new_node) -> void
	{
		if (old_node->prev)
			old_node->prev->next = move(new_node);
		else
			first = move(new_node);
		if (old_node->next)
		{
			first->next->prev = first.get();
			first->prev = old_node->prev;
		}
		if (old_node == last)
			last = first.get();
	}

	template <typename T>
	fn LinkedList<T>::size() -> u64
	{
		u64	size = 0;
		T* current = first.get();
		while (current)
		{
			size += 1;
			current = current->next.get();
		}
		return size;
	}
}
