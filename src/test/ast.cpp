#include "assert.h"

import ucbl.cedilla;
import std.compat;

using namespace ucbl::cedilla;
using namespace std;

struct Identifier final : public AstNode
{
	string value;

	Identifier(string b = "") : AstNode(__func__)
	{
		this->value = b;
	}

	fn	compile() -> string override
	{
		throw runtime_error("Identifier::compile() not implemented");
		return format("{}", "");
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		throw runtime_error("Identifier::clone() not implemented");
		return 0;
	}

	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		print("unserializing...\n");
		//scan("{}", value);

		auto pp = Identifier::deserialize("const string &str");

  auto gg2 = std::make_unique<int>(42);  // Create a unique_ptr<int>




		auto gg = make_unique<int>(42);

		auto out = make_unique<Identifier>();
		out->states["test"] = make_unique<StringState>(StringState("test"));
		out->states["test2"] = make_unique<AstNodeState>(AstNodeState(move(out)));

	//	out->value = str;
		return out;
	}
};
REGISTER_DESERIALIZABLE(AstNode, Identifier);


struct IntNode final : public AstNode
{
	int value;

	IntNode(int b = 42) : AstNode(__func__)
	{
		this->value = b;
	}

	fn	compile() -> string override
	{
		throw runtime_error("Int::compile() not implemented");
		return format("{}", value);
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		throw runtime_error("Int::clone() not implemented");
		return 0;
	}

	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		print("unserializing...");
		auto out = make_unique<IntNode>();
		scan(str, "{}", out->value);
		return out;
	}
};
//REGISTER_DESERIALIZABLE(AstNode, IntNode);

fn main() -> int
{
	return 0;

	auto myast = AstNodeRegistry::get().deserialize("Identifier", "salut");


	print("myast: {}\n", (void*)myast.get());


	return 0;
	myast->next =  AstNodeRegistry::get().deserialize("IntNode", "4");

	print("ptr is : {}", (void*)myast->next.get());

	Identifier	id;

	IntNode* tmp = (IntNode*)myast->next.get();

	assert(tmp->value == 4);

	StateMap test;

	print("tests succeed\n");
}
