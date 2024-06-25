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
			StateMap(),
			Ast()
		)},
	});

	auto out = ast_matcher_interpret(R"(
########################################################

				# False
(
				NonExists as id1 [
					test = "yoo"

				] {
					Word as id1_child
				}

				or

				# True

				(
					Word as id1 [
						(unknow = "nothin" or test = "yoo" )
					] {
						Word as id1_child [test2 = "yoo2"]

					}

					# True
					Word as id2
				)
	) or Nothin


########################################################
	)", test_ast);

	for (auto itm : out) {
		println("- {} : {}\n\n", itm.first, itm.second->serialize());
	}

	println("out.size() == {}", out.size());

	assert(out["id1"]->type == "Word");
	assert(out["id2"]->type == "Word");

}
