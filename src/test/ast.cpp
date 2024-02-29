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

	auto myast = AstNodeRegistry::get().create_instance("Identifier");

	myast->next =  AstNodeRegistry::get().create_instance("Int");

	Identifier	id;
	//assert()

}
