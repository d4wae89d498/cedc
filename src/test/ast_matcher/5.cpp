import ucbl.cedilla;
import std.compat;

#include "_common.hpp"

fn main() -> int
{
	auto test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast({
				Word(StateMap({{"test2", StringState("yoo2")}}))
			})
		)},
		{Word(
			StateMap({{"test21", StringState("yoo21")}}),
			Ast()
		)},
		{Word(
			StateMap(),
			Ast()
		)},
	});

	auto out = ast_matcher_interpret(R"(

		Noo
		or
		(
					NonExists as id1 [
						test = "yoo"
					] {
						Word as id1_child
					}
					or
					(
						Word as id1 [
							test = "yoo"
						] {
							Word as id1_child [ test2 = "yoo2" ]
						}
						Word as id2
						Word
						NOT Poo
					)
		)

	)", test_ast);


	assert(out["id1"][0]->type == "Word");
	assert(out["id2"][0]->type == "Word");
	assert(any_cast<string>(out["id1"][0]->states["test"]->value) == "yoo");
	assert(any_cast<string>(out["id1_child"][0]->states["test2"]->value) == "yoo2");
	assert(any_cast<string>(out["id2"][0]->states["test21"]->value) == "yoo21");


	return 0;
}
