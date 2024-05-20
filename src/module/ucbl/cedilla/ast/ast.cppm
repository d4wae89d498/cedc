export module ucbl.cedilla:ast;

import :common;
import :tree;
import :linked_list;
import :serializable;
import :clonable;
import :rref_capture;

export namespace cedilla
{
	struct AstNode;

    struct Ast final : public Tree<AstNode>, public Serializable, public Clonable<Ast>
    {
		using BaseType = vector<unique_ptr<AstNode>>;
       // using BaseType::vector;
        Ast(initializer_list<RrefCapture<unique_ptr<AstNode>>> init = {});
		Ast(initializer_list<RrefCapture<AstNode>> init);

	//    Ast(const Ast&) = delete;
    //    fn operator=(const Ast&) -> Ast& = delete;


		fn	clone() -> unique_ptr<Ast> override;
		fn	serialize() -> string override;
    };
}
