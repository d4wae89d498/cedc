import ucbl.cedilla;

using namespace cedilla;

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
REGISTER_CLASS(AstNode, Identifier);


fn main() -> int
{


	Identifier	id;
	//assert()

}
