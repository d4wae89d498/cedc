import ucbl.cedilla;
import std.compat;

#include "_common.hpp"

fn main() -> int
{
	auto test_ast = Ast({
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast()
		)},
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast()
		)},
		{Word(
			StateMap({{"test", StringState("yoo")}}),
			Ast()
		)},
		{Word(
			StateMap({{"test2", StringState("yoo")}}),
			Ast()
		)},
		{Word(
			StateMap({{"test23", StringState("yoo")}}),
			Ast()
		)}
	});

	auto out = ast_matcher_interpret(R"(
		Word  as m2 [test = "yoo"]+
		Word as m3 [test2 = "yoo"]*
		Word
		IDontCare?
	)", test_ast);



	assert(out.contains("m2"));

	DEBUG_LOG("{}", out["m2"].size());
	assert(out["m2"].size() == 3);


	assert(out.contains("m3"));
	assert(out["m3"].size() == 1);


	return 0;
}
