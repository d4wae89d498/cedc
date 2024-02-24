import ucbl.cedilla;

using namespace cedilla;

struct Identifier : public AstNode
{
	Identifier() : AstNode(__func__)
	{

	}

	fn compile() -> string
	{
		return "";
	}
};
REGISTER_CLASS(AstNode, Identifier);


fn main() -> int
{
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
