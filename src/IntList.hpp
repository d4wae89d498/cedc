#include "./LinkedList.hpp"

class IntList : public LinkedList<IntList>
{
	public:

	int	value;

	IntList(int	value = 0)
	{
		this->value = value;
	}
};
