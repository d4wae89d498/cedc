#include <vector>
#include <iostream>

#include "src/Parser.hpp"

#include "src/parsers/Space.hpp"
#include "src/parsers/Raw.hpp"

#include "src/IntList.hpp"

using namespace std;

int main()
{

	IntList lst;

	lst.iter_back([](IntList *i){
		cout << i->value << endl;
	});
	cout << "-----" << endl;

	lst.add_back(new IntList(5));
	lst.add_back(new IntList(6));

	lst.iter_back([](IntList *i){
		cout << i->value << endl;
	});
	cout << "-----" << endl;

	/*auto parser = Parser("./test.txt");
	parser.rules.push_back(make_unique<Space>());
	parser.rules.push_back(make_unique<Raw>());

	parser.parse();*/

/*	parser.rules.add([&parser](const char *src){
		parser.ast.add();

		return 1;
	})

	auto ast = Ast();
	ast.rules.add([](AstNode *it)(){
		auto match = match_node(&it, [](AstNode *node){

		});
		if (!match.success)
			return ;
	})

	auto ast = parser.parse("demo.txt", ast);

	cout << ast.dump() << endl;*/

}
