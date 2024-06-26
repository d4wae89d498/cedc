#include "_common.hpp"

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
		Word as id1
	)", test_ast);

	assert(out.contains("id1"));
	assert(any_cast<string>(out["id1"]->states["test"]->value) == "yoo");

}
