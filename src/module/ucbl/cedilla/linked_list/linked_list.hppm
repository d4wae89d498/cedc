export module ucbl.cedilla:linked_list;

import :common;

export namespace cedilla
{
	template <typename T>
	struct LinkedList
	{
		unique_ptr<T>	first = nullptr;
		T 				*last = nullptr;

		fn link_before(T* node, unique_ptr<T> new_node)
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

		fn link_after(T* node, unique_ptr<T> new_node)
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

		fn link_back(unique_ptr<T> node)
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

		fn link_front(unique_ptr<T> node)
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

		fn del_one(T* node)
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

		fn del_all(function<bool(const T&)> predicate)
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

		fn replace_one(T* old_node, unique_ptr<T> new_node)
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

		fn serialize() -> string
		{
			return string("");
		}

		struct Iterator
		{
			T* current;

			Iterator(T* node) : current(node)
			{

			}

			fn operator*() const -> T&
			{
				return *current;
			}

			fn operator->() -> T*
			{
				return current;
			}

			fn operator++()	-> Iterator&
			{
				current = current->next.get();
				return *this;
			}

			fn operator!=(const Iterator& other) const -> bool
			{
				return current != other.current;
			}
		};

		fn begin() -> Iterator
		{
			return Iterator(first.get());
		}

		fn end() -> Iterator
		{
			return Iterator(nullptr);
		}
	};

	template <typename T>
	struct LinkedListNode
	{
		unique_ptr<T>	next = nullptr;
		T				*prev = nullptr;

		fn last()
		{
			T* last = static_cast<T*>(this);
			while (last->next)
				last = last->next.get();
			return last;
		}
	};
};


