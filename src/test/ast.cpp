import ucbl.cedilla;

using namespace cedilla;

struct Identifier : public AstNode
{
	string value;

	Identifier() : AstNode(__func__)
	{
	}

	fn	compile() const -> string
	{
		return value;
	}

	static fn unserialize(const string& str) -> unique_ptr<AstNode>
	{
		//scan("{}", value);
		return nullptr;//make_unique<Int>();
	}
};
REGISTER_CLASS(AstNode, Identifier);


struct Int : public AstNode
{
	int value;

	Int() : AstNode(__func__)
	{
	}

	fn	compile() const -> string
	{
		return format("{}", value);
	}

	static fn unserialize(const string& str) -> unique_ptr<AstNode>
	{
		int value;
		//scan("{}", value);
		return nullptr;//make_unique<Int>();
	}
};
REGISTER_CLASS(AstNode, Int);

fn main() -> int
{

	auto myast = AstNodeRegistry::get().create_instance("Identifier", "salut");

	myast->next =  AstNodeRegistry::get().create_instance("Int", "4");

	Identifier	id;
	//assert()

}
