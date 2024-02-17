import LinkedList;
import Ast;
//import Std;

import std;


//#include <iostream>

using namespace std;

struct Identifier : public AstNode
{
	Identifier() : AstNode(__func__)
	{

	}

	string compile()
	{
		return "";
	}
};
REGISTER_CLASS(AstNode, Identifier);


int main()
{
	print("hello");
	//cout << AstNodeRegistry::get().createInstance("Identifier") << endl;

	//printf("... hello\n");
	unique_ptr<int> p;
/*
	cout << "" << endl;

	string a;

	unique_ptr<string> pp;
*/
//	Serializable::serialize();
}
