module;

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include "antlr4-runtime.h"
#include "AstMatcherLexer.h"
#include "AstMatcherParser.h"
#include "AstMatcherVisitor.h"

export module ucbl.astmatcher:interpret;

import :interpret_reverse_visitor;
import ucbl.cedilla;

using namespace std;
using namespace antlr4;

export namespace astmatcher {
	unordered_map<string, unique_ptr<cedilla::AstNode>> interpret(const string& pattern, cedilla::Ast& ast) {
		cout << "Input: " << pattern << endl;

		ANTLRInputStream input(pattern);
		AstMatcherLexer lexer(&input);
		CommonTokenStream tokens(&lexer);
		tokens.fill();

		for (auto token : tokens.getTokens()) {
			cout << "token: " << token->toString() << endl;
		}

		AstMatcherParser parser(&tokens);
		AstMatcherParser::AstPatternDescriptionContext* tree = parser.astPatternDescription();

		// Define property checkers
		std::unordered_map<std::string, InterpretReverseVisitor::PropertyChecker> checkers = {
			{"type", [](cedilla::AstNode* node, const std::string& value) {
				return false;//node->states["type"] == value;
			}},
			{"value", [](cedilla::AstNode* node, const std::string& value) {
				return false;//node->states["value"] == value;
			}}
		};

		InterpretReverseVisitor visitor(ast, checkers);
		visitor.visit(tree);

		unordered_map<string, unique_ptr<cedilla::AstNode>> matchedNodes;
		for (const auto& [alias, node] : visitor.matches) {
			matchedNodes[alias] = node->clone();
		}

		return matchedNodes;
	}

}
