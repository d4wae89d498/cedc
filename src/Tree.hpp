#pragma once
#include <vector>
#include <any>
#include "./LinkedList.hpp"

using namespace std;

template <typename T>
class Tree : public LinkedList < T >
{
	T	*childs;
};
