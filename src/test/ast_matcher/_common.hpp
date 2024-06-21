
#include <cassert>

import ucbl.cedilla;

using namespace cedilla;

struct Word final : public AstNode
{
	Word(StateMap states = StateMap(), Ast childs = Ast())
		: AstNode(__func__, move(states), move(childs))
	{
	}

    Word(Word&& other) noexcept : AstNode(__func__)
	{
        // Move constructor implementation
        // Transfer ownership of resources from 'other' to 'this'
    }

   	fn operator=(Word&& other) noexcept ->  Word&
	{
        if (this != &other) {
            // Move assignment implementation
            // Transfer ownership of resources from 'other' to 'this'
        }
        return *this;
    }


	fn	compile() -> string override
	{
		auto &mystate = this->states["value"];
		return format("{}", any_cast<string>(mystate->value));
	}

	fn clone() -> unique_ptr<AstNode> override
	{
		print("Clonning Word...\n");

		auto states = this->states.clone();

		auto out = make_unique<Word>(move(*(states.get())));//, move(*(this->childs.clone().release())));
		if (this->childs.first)
			out->childs.first = move(this->childs.first->clone());
		if (this->next)
		{
			out->next = this->next->clone();
			out->next->prev = out.get();
		}
	//	out->states = move(* (this->states.clone().release()));
	//	out->states["value"] = make_unique<StringState>(any_cast<string>(this->states["value"]->value));
		print("clonned\n");
		return out;
	}

	static fn deserialize(const string& str) -> unique_ptr<AstNode>
	{
		auto out = make_unique<Word>();
		string my;
		scan(str, "{}", my);
		out->states["value"] = make_unique<StringState>(my);
		return out;
	}
};
REGISTER_DESERIALIZABLE(AstNode, Word);
