module;

#include "AstMatcherVisitor.h"

export module ucbl.cedilla:ast_matcher_reverse_visitor;

import :common;
import :ast;
import :ast_node;

export namespace cedilla
{
	struct InterpretReverseVisitor : public AstMatcherVisitor
	{
		using StateChecker = function<bool(const string&, const string&)>;

		AstNode *it;
		unordered_map<string, AstNode*> matches;
		unordered_map<string, StateChecker> StateCheckers;
		bool match = true;

		InterpretReverseVisitor(Ast& ast, unordered_map<string, StateChecker> checkers);
		fn getTypeName(antlr4::tree::ParseTree *node) -> string;
		fn visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context) -> any override;
		fn visitNodeType(AstMatcherParser::NodeTypeContext *context) -> any override;
		fn visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context) -> any override;
	};
}
