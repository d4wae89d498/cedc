module;

#include "AstMatcherVisitor.h"

export module ucbl.cedilla:ast.matcher.reverse_visitor;

import :common;
import :ast;
import :ast.node;

export namespace ucbl::cedilla
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
		fn visitNodeTypeSequence(AstMatcherParser::NodeTypeSequenceContext *context) -> any override;
		fn visitNodeProperty(AstMatcherParser::NodePropertyContext *context) -> any override;
		fn visitNodePropertySequence(AstMatcherParser::NodePropertySequenceContext *context) -> any override;
		fn visitNodePropertyElement(AstMatcherParser::NodePropertyElementContext *context) -> any override;
		fn visitNodeTypeElement(AstMatcherParser::NodeTypeElementContext *context) -> any override;

	};
}
