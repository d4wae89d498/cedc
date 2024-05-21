module ucbl.cedilla;

import :common;
import :ast;
import :ast_node;
import :rref_capture;

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

		?	may be empty
		*	until
		capture Type [
			"prop" is "str",
			"prop" is lower,
			"prop" is containing("needle"),

			 or prop { assume ast and match and }] {childs}
		skip Type


		capture Type
		capture Identifier
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
