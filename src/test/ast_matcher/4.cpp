import ucbl.cedilla;
import std.compat;

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
		NonExists as id1
		{
			Word as id1_child
		}
		|
		Word as id1
	)", test_ast);

	assert(out.size() == 1);
	assert(out["id1"][0]->type == "Word");

}
