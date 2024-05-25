export module ucbl.cedillac:c_var;

// todo: add or (|) in g4 file.

namespace cedillac
{
	struct VarDecl : AstNode
	{

	}

	fn c_var_decl(ctx)
	{
		ctx.add_parser(()[]{
			unordered_map<string, unique_ptr<AstNode>> result =
			astmatcher("

				Program | Block {
					capture Identifier as Type;

					vv: # to avoid repetitions, use variables to store rules ?  store all rules in one files ? ==> probably the best idea
						capture Identifier as Name;
						(
							skip	Symbol [\"value\" = \"=\"];
							capture Expr;
						)?;
					(
						skip	Symbol [\"value\" = \",\"];
						vv;
					)*;

					skip	Symbol [\"value\" = \";\"];
				};

			");
			if (!parent || parent is block && )

			if (is_std_type(result["Type"].states["value"])
				|| is_user_type(ctx, result["Type"].states["value"])
			)
			{
				ctx.ast.pop(result.length);
				for (auto name : result["Name"])
				{
					ctx.ast.link_back(make_unique<VarDecl>(
						{"type", StringState(result["Type"].states["value"])}
						{"name", StringState(result["Name"].states["value"])}
					));
				}
			}
		})
	}

	fn c_var_use(ctx)
	{
		ctx.add_parser(()[]{
			unordered_map<string, unique_ptr<AstNode>> result =
			astmatcher("


				rule:
				(
					skip? Any exept Identifier {
						rule;
					}*;
					capture VarDecl as var_decl;

					capture Identifier as var_ref [
								\"value\" in($, var_decl)
							] -> VarRef[\"name\"=var_decl.name];
				)*;

				// no

			");
			if (!parent || parent is block && )

			if (is_std_type(result["Type"].states["value"])
				|| is_user_type(ctx, result["Type"].states["value"])
			)
			{
				ctx.ast.pop(result.length);
				for (auto name : result["Name"])
				{
					ctx.ast.link_back(make_unique<VarDecl>(
						{"type", StringState(result["Type"].states["value"])}
						{"name", StringState(result["Name"].states["value"])}
					));
				}
			}
		})
	}


	fn c_parenthesis(ctx)
	{
		ctx.add_parser(()[]{
			unordered_map<string, unique_ptr<AstNode>> result =
			astmatcher("

				(
					skip LPARENS as var_decl;

					capture?* Any except ( LPARENS[]{} | ... ) as Content;

					skip RPARENS as var_decl;

				) -> Parenthesis {
					Content;
				}


				// yes
			");
			if (!parent || parent is block && )

			if (is_std_type(result["Type"].states["value"])
				|| is_user_type(ctx, result["Type"].states["value"])
			)
			{
				ctx.ast.pop(result.length);
				for (auto name : result["Name"])
				{
					ctx.ast.link_back(make_unique<VarDecl>(
						{"type", StringState(result["Type"].states["value"])}
						{"name", StringState(result["Name"].states["value"])}
					));
				}
			}
		})
	}
}
