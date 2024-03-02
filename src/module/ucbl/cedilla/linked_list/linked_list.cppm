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
		fn serialize() -> string;
	};
};

