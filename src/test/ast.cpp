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
//REGISTER_CLASS(AstNode, Identifier);


struct Int : public AstNode
{
	int value;

	Int() : AstNode(__func__)
	{
	}

	string	compile()
	{
		return format("{}", value);
	}
};
//REGISTER_CLASS(AstNode, Int);

fn main() -> int
{

	auto myast = AstNodeRegistry::get().create_instance("Identifier", "salut");

	myast->next =  AstNodeRegistry::get().create_instance("Int", "4");

	Identifier	id;
	//assert()

}
