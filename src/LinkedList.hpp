#pragma once
#include <vector>
#include <any>

using namespace std;

template <typename T>
class LinkedList
{
public:
    T   	*next = nullptr;
    T   	*prev = nullptr;
	bool	init = false;

	void iter_back_until(const function<bool(T*)>& callback)
    {
		if (!init)
			return ;
        T* current = (T*)this;
        while (current) {
            if (callback(current))
				break ;
            current = current->next;
        }
    }

	void iter_back(const function<void(T*)>& callback)
    {
		if (!init)
			return ;
        T* current = (T*)this;
        while (current) {
            callback(current);
            current = current->next;
        }
    }

    void add_back(T* value)
    {
		if (!init)
		{
			value->init = true;
			memcpy(this, value, sizeof(T));
		//	*this = *value;
			return;
		}
		this->iter_back_until([&](T *n){
			if (!n->next)
			{
				n->next = value;
				value->prev = n;
				return true;
			}
			return false;
		});
    }

    void add_front(T *value)
    {
		if (init)
		{
			value->next = this;
			this->prev = value;
		}
		value->init = true;
		*this = *value;
    }

    void del_one(T *value)
    {
		// TODO ...
    }

    T clone()
    {
        T newList;
		// TODO ...
        return newList;
    }


};
