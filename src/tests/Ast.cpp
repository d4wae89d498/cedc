

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
