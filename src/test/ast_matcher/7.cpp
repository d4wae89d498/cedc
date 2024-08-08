import ucbl.cedilla;
import std.compat;

#include "_common.hpp"

fn main() -> int
{
	auto test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo3")}}),
			Ast({
				Word(StateMap({{"test2", StringState("yoo2")}}))
			})
		)},
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast()
		)},
	});

	return 0;

	auto out = ast_matcher_interpret(R"(
		Word?
		Word+
		Word*
		Word?
	)", test_ast);

	return 0;

	//assert(out["id1"]->type == "Word");

}
