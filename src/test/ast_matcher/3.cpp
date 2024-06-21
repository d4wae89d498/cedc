#include "_common.hpp"

fn main() -> int
{

	auto test_ast = Ast({
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

	auto out = ast_matcher_interpret(R"(
########################################################

				# Test child matching with properties
				Word as id1 [
					test = "yoo"
#	Todo: implement these syntax:
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
					Word as id1_child [test2 = "yoo2"]
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
}
