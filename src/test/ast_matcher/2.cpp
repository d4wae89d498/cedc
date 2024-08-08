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
		Word as id1
		{
			Word as id1_child
		}
	)", test_ast);

	assert(out.contains("id1"));
	assert(out["id1"][0]->states.contains("test"));
	assert(any_cast<string>(out["id1"][0]->states["test"]->value) == "yoo");

	assert(out.contains("id1_child"));
	assert(out["id1_child"][0]->states.contains("test2"));
	assert(any_cast<string>(out["id1_child"][0]->states["test2"]->value) == "yoo2");

}
