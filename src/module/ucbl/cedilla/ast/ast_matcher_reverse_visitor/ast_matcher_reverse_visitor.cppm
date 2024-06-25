module;

#include "AstMatcherVisitor.h"

export module ucbl.cedilla:ast_matcher_reverse_visitor;

import :common;
import :ast;
import :ast_node;

export namespace cedilla
{
	struct AstMatcherVisitorOutput
	{
		unordered_map<string, AstNode*> matches;
		bool success;
	};

	struct InterpretReverseVisitor : public AstMatcherVisitor
	{
		using StateChecker = function<bool(const string&, const string&)>;

		AstNode *it;
		unordered_map<string, StateChecker> StateCheckers;

		InterpretReverseVisitor(Ast& ast, unordered_map<string, StateChecker> checkers);

		fn getTypeName(antlr4::tree::ParseTree *node) -> string;

		fn visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context) -> any override;
		fn visitNodeType(AstMatcherParser::NodeTypeContext *context) -> any override;
		fn visitNodeTypeOr(AstMatcherParser::NodeTypeOrContext *context) -> any override;
		fn visitNodePropertiesDescription(AstMatcherParser::NodePropertiesDescriptionContext *context) -> any override;
		fn visitNodePropertiesDescriptionOr(AstMatcherParser::NodePropertiesDescriptionOrContext *context) -> any override;

	};
}
