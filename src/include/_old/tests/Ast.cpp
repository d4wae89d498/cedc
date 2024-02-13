#include <vector>
#include <iostream>
#include <stdlib.h>

#include "./../src/LinkedList.hpp"
#include "./../src/Tree.hpp"
#include "./../src/Ast.hpp"

using namespace std;

struct Identifier : public AstNode
{
	string value;

	Identifier() : AstNode(__func__)
	{
	}

	string	compile()
	{
		return value;
	}
};
//REGISTER_CLASS(AstNode, Identifier);


int main()
{


	Identifier	id;
	//assert()

}
