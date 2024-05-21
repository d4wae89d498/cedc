module ucbl.cedilla;

import :common;
import :ast;
import :ast_node;

namespace cedilla
{
    Ast::Ast(initializer_list<RrefCapture<unique_ptr<AstNode>>> init)
	{
		for (auto &&elem : init)
		{
			this->link_back(move(elem));
		}
	}

	Ast::Ast(initializer_list<RrefCapture<AstNode>> init)
	{
		print("Ast::init ...");
		for (auto &&elem : init)
		{
			print("type {}\n", elem.ptr->type);
			this->link_back(elem.ptr->clone());
			print("linked\n");
		}
		print("Ast::init end\n");
	}

	fn	Ast::clone() -> unique_ptr<Ast>
	{
		auto out = make_unique<Ast>();
		out->first = this->first->clone();
		out->last = out->first->last();
		return out;
	}

	fn Ast::serialize() -> string
	{
		string out = "Ast(";
		auto it = this->begin();
		if (it != this->end())
			while (true)
			{
				out += it->serialize();
				++it;
				if (it != this->end())
					out += ",";
				else
					break ;
			}
		out += ")";
		return out;
	}

	/*
		# AST NODE MATCHER DSL

		#we can capture? capture* and skip? skip* also
		#? means optional *means repeat until

		# a node contains properties and childs. A property may be a string or an ast node.
		# Childs are ast.

		capture Type [

			"prop1" = "str"					// prop cant be matched or skipped, but can be compared like this
			"prop2" islower($)
			"prop3" contains($, "needle"),	// prop will be passed a second argument to containing

			 "prop4" {
				#assume ast here. we can use capture and amtch here.
			}] {childs}
		skip Type


		capture Type				# By default match Type name as matched key
		capture Identifier	as id1	# we may specify a new name
		capture Parenthesis
		capture Braces
		-> Func

		capture Raw[value=async]	# Use [] for data match
		capture Func["Braces"={		# Use {} for child match
			skip Braces				# First braces are function arguments
			{
				capture Expr {
					capture Raw[value=await]
					capture Call
				}
			}
		}]

		matches["Call"]["type"]






	*/
	fn match(const string fmt)
	{

	}
}

/*
Word(
	{"value": StringState("PARENS")},
	Ast(
		Word(
			{"value": StringState("(")},
			Ast()
		),
	)
)

*/
