
#include <cassert>

import ucbl.cedilla;

using namespace cedilla;

struct Word final : public AstNode
{
	Word(StateMap states = StateMap(), Ast childs = Ast())
		: AstNode(__func__, move(states), move(childs))
	{
	}

    Word(Word&& other) noexcept : AstNode(__func__)
	{
        // Move constructor implementation
        // Transfer ownership of resources from 'other' to 'this'
    }

   	fn operator=(Word&& other) noexcept ->  Word&
	{
        if (this != &other) {
            // Move assignment implementation
            // Transfer ownership of resources from 'other' to 'this'
        }
        return *this;
    }


	fn	compile() -> string override
	{
		auto &mystate = this->states["value"];
		return format("{}", any_cast<string>(mystate->value));
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		print("Clonning Word...\n");

		auto states = this->states.clone();

		auto out = make_unique<Word>(move(*(states.get())));//, move(*(this->childs.clone().release())));
		if (this->childs.first)
			out->childs.first = move(this->childs.first->clone());
		if (this->next)
		{
			out->next = this->next->clone();
			out->next->prev = out.get();
		}
	//	out->states = move(* (this->states.clone().release()));
	//	out->states["value"] = make_unique<StringState>(any_cast<string>(this->states["value"]->value));
		print("clonned\n");
		return out;
	}

	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		auto out = make_unique<Word>();
		string my;
		scan(str, "{}", my);
		out->states["value"] = make_unique<StringState>(my);
		return out;
	}
};
REGISTER_DESERIALIZABLE(AstNode, Word);

fn main() -> int
{
	auto test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast({
					{Word(
					StateMap(),
					Ast()
					)},
			})
		)},
	});

	auto out = ast_matcher_interpret(R"(
########################################################

				# Simple test case
				Word as id1


########################################################
	)", test_ast);

	assert(out.contains("id1"));
	assert(any_cast<string>(out["id1"]->states["test"]->value) == "yoo");



//////////////////////////////////////////////////////////



	test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast({
					{Word(
						StateMap({{"test2", StringState("yoo2")}}),
						Ast()
					)},
			})
		)},
	});

	out = ast_matcher_interpret(R"(
########################################################

				# Test child matching
				Word as id1
				{
					Word as id1_child
				}



########################################################
	)", test_ast);

	println("-----");
	println("{}", test_ast.serialize());
	println("-----");

			test_ast.first->childs.last = test_ast.last->childs.first->last();

	println("------");
	println("first: {}", (s64)test_ast.first.get());
	println("last: {}", (s64)test_ast.last);

	println("[0]first: {}", (s64)test_ast.first->childs.first.get());
	println("[0]last: {}", (s64)test_ast.first->childs.last);
	println("------");

	assert(out.contains("id1"));
	assert(out["id1"]->states.contains("test"));
	assert(any_cast<string>(out["id1"]->states["test"]->value) == "yoo");


	assert(out.contains("id1_child"));
	assert(out["id1_child"]->states.contains("test2"));
	assert(any_cast<string>(out["id1_child"]->states["test2"]->value) == "yoo2");


//////////////////////////////////////////////////////////



	test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast({
					{Word(
						StateMap({{"test2", StringState("yoo2")}}),
						Ast()
					)},
			})
		)},
	});

	out = ast_matcher_interpret(R"(
########################################################

				# Test child matching with properties
				Word as id1 [
					"test" = "yoo"
#					test2 {
#						Word as ...
#					}
#					test3 is_in("blue, red, orange")
#
#					(test3 == "blue")
#					|
#					(test3 == "red")
#					|
#					(test3 == "orange")
				]
				{
					Word as id1_child ["test2" = "yoo2"]
				}



########################################################
	)", test_ast);

	println("-----");
	println("{}", test_ast.serialize());
	println("-----");

			test_ast.first->childs.last = test_ast.last->childs.first->last();

	println("------");
	println("first: {}", (s64)test_ast.first.get());
	println("last: {}", (s64)test_ast.last);

	println("[0]first: {}", (s64)test_ast.first->childs.first.get());
	println("[0]last: {}", (s64)test_ast.first->childs.last);
	println("------");

	assert(out.size() != 0);
	assert(out.contains("id1"));
	assert(out["id1"]->states.contains("test"));
	assert(any_cast<string>(out["id1"]->states["test"]->value) == "yoo");


	assert(out.contains("id1_child"));
	assert(out["id1_child"]->states.contains("test2"));
	assert(any_cast<string>(out["id1_child"]->states["test2"]->value) == "yoo2");

//////////////////////////////////////////////////////////
	test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast({
					{Word(
						StateMap({{"test2", StringState("yoo2")}}),
						Ast()
					)},
			})
		)},
	});

	out = ast_matcher_interpret(R"(
########################################################

				# Test child matching
				NonExists as id1
				{
					Word as id1_child
				}



########################################################
	)", test_ast);

	assert(out.size() == 0);





}
