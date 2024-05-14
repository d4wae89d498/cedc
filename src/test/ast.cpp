#include "assert.h"

import ucbl.cedilla;

using namespace cedilla;

struct Identifier : public AstNode
{
	//string value;

	Identifier() : AstNode(__func__)
	{
	}

	fn	compile() const -> string
	{
		return format("{}", "");
	}

	fn clone() const -> unique_ptr<AstNode>
	{
		return 0;
	}

	static fn unserialize(const string& str) -> unique_ptr<AstNode>
	{
		print("unserializing...\n");
		//scan("{}", value);

		auto pp = Identifier::unserialize("const string &str");

  auto gg2 = std::make_unique<int>(42);  // Create a unique_ptr<int>




		auto gg = make_unique<int>(42);

		auto out = make_unique<Identifier>();
		out->data["test"] = make_unique<State>("test");
		out->data["test2"] = make_unique<State>(&out);

	//	out->value = str;
		return out;
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

	fn clone() const -> unique_ptr<AstNode>
	{
		return 0;
	}

	static fn unserialize(const string& str) -> unique_ptr<AstNode>
	{
		print("unserializing...");
		auto out = make_unique<Int>();
		scan(str, "{}", out->value);
		return out;
	}
};
REGISTER_CLASS(AstNode, Int);

fn main() -> int
{

	auto myast = AstNodeRegistry::get().create_instance("Identifier", "salut");

	print("myast: {}\n", (void*)myast.get());

	myast->next =  AstNodeRegistry::get().create_instance("Int", "4");

	print("ptr is : {}", (void*)myast->next.get());

	Identifier	id;

	Int* tmp = (Int*)myast->next.get();

	assert(tmp->value == 4);

	StateMap test;

	print("tests succeed\n");
}
