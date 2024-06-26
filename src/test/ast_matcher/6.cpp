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

	auto out = ast_matcher_interpret(R"(
########################################################

		Word as id1 [ test = "yoo" ] {
			Word as id1child [ test2 = "yoo2" ]
		}

		and

		Word as id2


########################################################
	)", test_ast);

	for (auto itm : out) {
		println("- {} : {}\n\n", itm.first, itm.second->serialize());
	}

	println("out.size() == {}", out.size());


	return 1;
	assert(out["id1"]->type == "Word");
	assert(out["id1_child"]->type == "Word");

	assert(any_cast<string>(out["id1"]->states["test"]->value) == "yoo2");
	assert(any_cast<string>(out["id1_child"]->states["test2"]->value) == "yoo2");

	assert(out["id2"]->type == "Word");

}
