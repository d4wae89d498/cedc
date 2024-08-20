import ucbl.cedilla;
import std.compat;

#include "_common.hpp"

fn main() -> int
{
	auto test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast({
				Word(StateMap({{"test2", StringState("yoo2")}})),
				Word(StateMap({{"test3", StringState("yoo3")}}),
					 Ast({
						 Word(StateMap({{"test4", StringState("yoo4")}})),
						 Word(StateMap({{"test5", StringState("yoo5")}}))
					 })
				),
				Word(StateMap({{"test6", StringState("yoo6")}}))
			})
		)}
	});

	auto out = ast_matcher_interpret(R"(
		Word as id1 [
			test = "yoo"
		] {
			Word as id1_child1 [test2 = "yoo2"]
			or
			Word as id1_child2 [test3 = "yoo3"] {
				Word as id1_child2_grandchild1 [test4 = "yoo4"]
				or
				Word as id1_child2_grandchild2 [test5 = "yoo5"]
			}
			Word as id1_child3 [test6 = "yoo6"]
		}
	)", test_ast);

	assert(out.contains("id1"));
	assert(any_cast<string>(out["id1"][0]->states["test"]->value) == "yoo");

	assert(!out.contains("id1_child1"));

	assert(out.contains("id1_child2"));
	assert(any_cast<string>(out["id1_child2"][0]->states["test3"]->value) == "yoo3");

	assert(!out.contains("id1_child2_grandchild1"));

	assert(out.contains("id1_child2_grandchild2"));
	assert(any_cast<string>(out["id1_child2_grandchild2"][0]->states["test5"]->value) == "yoo5");

	assert(out.contains("id1_child3"));
	assert(any_cast<string>(out["id1_child3"][0]->states["test6"]->value) == "yoo6");

	return 0;
}
