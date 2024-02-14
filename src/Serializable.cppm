module;

#include <string>

using namespace std;

export module Serializable;

//int smallchange;

export struct Serializable
{
	virtual string	serialize() = 0;
};
