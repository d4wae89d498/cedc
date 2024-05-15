#include "assert.h"

import ucbl.cedilla;

using namespace cedilla;

struct StringState final : public State
{
	StringState(string str) : State(__func__, str)
	{

	}

	fn serialize() -> string
	{
		return "";
	}

	fn clone() -> unique_ptr<State>
	{
		return 0;
	}
};

struct AstNodeState final : public State
{
	AstNodeState(unique_ptr<AstNode> node) : State(__func__, node.release())
	{

	}

	fn serialize() -> string
	{
		return "";
	}

	fn clone() -> unique_ptr<State>
	{
		auto ptr = any_cast<AstNode*>(value);
		return make_unique<AstNodeState>(ptr->clone());
	}

	~AstNodeState()
	{
		auto ptr = any_cast<AstNode*>(value);
		delete ptr;
	}

};

struct Identifier final : public AstNode
{
	string value;

	Identifier(string b = "") : AstNode(__func__)
	{
		this->value = b;
	}

	fn	compile() -> string override
	{
		throw runtime_error("not implemented");
		return format("{}", "");
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		throw runtime_error("not implemented");
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
		out->data["test"] = make_unique<StringState>(StringState("test"));
		out->data["test2"] = make_unique<AstNodeState>(AstNodeState(move(out)));

	//	out->value = str;
		return out;
	}
};
REGISTER_DESERIALIZABLE(AstNode, Identifier);


struct Int final : public AstNode
{
	int value;

	Int(int b = 42) : AstNode(__func__)
	{
		this->value = b;
	}

	fn	compile() -> string override
	{
		throw runtime_error("not implemented");
		return format("{}", value);
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		throw runtime_error("not implemented");
		return 0;
	}

	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		print("unserializing...");
		auto out = make_unique<Int>();
		scan(str, "{}", out->value);
		return out;
	}
};
REGISTER_DESERIALIZABLE(AstNode, Int);

fn main() -> int
{
	auto myast = AstNodeRegistry::get().deserialize("Identifier", "salut");


	print("myast: {}\n", (void*)myast.get());

	myast->next =  AstNodeRegistry::get().deserialize("Int", "4");

	print("ptr is : {}", (void*)myast->next.get());

	Identifier	id;

	Int* tmp = (Int*)myast->next.get();

	assert(tmp->value == 4);

	StateMap test;

	print("tests succeed\n");
}
