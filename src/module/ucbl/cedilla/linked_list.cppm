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
			new_node->next = move(node->prev ? node->prev->next : first);
			new_node->prev = node->prev;
			if (node->prev)
				node->prev->next = move(new_node);
			else
				first = move(new_node);
			node->prev = new_node.get();
			if (!node->next)
				last = node;
		}

		fn replace_node(T* old_node, unique_ptr<T> new_node)
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

		fn delete_node(T* node)
		{
			if (node->prev)
				node->prev->next = move(node->next);
			else
				first = move(node->next);

			if (node->next)
				node->next->prev = node->prev;
			else
				last = node->prev;
		}

		fn link_back(unique_ptr<T> node)
		{
			if (!first)
			{
				first = move(node);
				this->last = first.get();
			}
			else
			{
				this->last->next = move(node);
				this->last->next->prev = this->last;
				this->last = this->last->next.get();
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

		fn del_if(function<bool(const T&)> predicate)
		{
			T* current = first.get();
			T* prev = nullptr;

			while (current != nullptr)
			{
				if (predicate(*current))
				{
					if (prev)
					{
						prev->next = move(current->next);
						if (prev->next)
							prev->next->prev = prev;
						else
							last = prev;
					}
					else
					{
						first = move(current->next);
						if (first)
							first->prev = nullptr;
						else
							last = nullptr;
					}
					current = (prev) ? prev->next.get() : first.get();
				}
				else
				{
					prev = current;
					current = current->next.get();
				}
			}
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


