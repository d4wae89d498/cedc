module;

#include "AstMatcherVisitor.h"
#define AST_MATCHER_FAILURE(N, MSG, ...) \
	{\
		DEBUG_LOG("ASTMatcher dit not succeed, reason -> [" MSG "] trying to continue...", ##__VA_ARGS__);\
		N.success = false;\
		return N;\
	}

#define BACKUP_ITERATOR(BACKUP, ITERATOR)   auto BACKUP = ITERATOR;
#define RESTORE_ITERATOR(ITERATOR, BACKUP)  ITERATOR = BACKUP;
#define ADVANCE_ITERATOR(ITERATOR)    		ITERATOR = ITERATOR ->prev;

module ucbl.cedilla;

import :common;
import :util;
import :ast;
import :ast.node;

namespace ucbl::cedilla
{

	/*\
	 *
	 *		U T I L S
	 *
	\*/

	fn merge_ast_matches(AstMatch& mainMap, const AstMatch& auxMap) -> void {
		for (const auto& [key, vec] : auxMap) {
			// If the key exists in mainMap, append to the vector
			if (mainMap.find(key) != mainMap.end()) {
				mainMap[key].insert(mainMap[key].end(), vec.begin(), vec.end());
			} else {
				// If the key doesn't exist, create a new vector
				mainMap[key] = vec;
			}
		}
	}

	fn InterpretReverseVisitor::getTypeName(antlr4::tree::ParseTree *node) -> string
	{
		if (dynamic_cast<antlr4::tree::TerminalNode*>(node)) {
			return "TerminalNode";
		} else if (dynamic_cast<AstMatcherParser::AstPatternDescriptionContext*>(node)) {
			return "visitAstPatternDescription";
		} else if (dynamic_cast<AstMatcherParser::NodeTypeContext*>(node)) {
			return "visitNodeType";
		} else if (dynamic_cast<AstMatcherParser::NodePropertyContext*>(node)) {
			return "visitNodeProperty";
		} else if (dynamic_cast<AstMatcherParser::NodeTypeSequenceContext*>(node)) {
			return "visitNodeTypeSequence";
		} else if (dynamic_cast<AstMatcherParser::NodePropertySequenceContext*>(node)) {
			return "visitNodePropertySequence";
		} else {
			return "Unknown";
		}
	}

	/*\
	 *
	 *		C O N S T R U C T O R S
	 *
	\*/

	InterpretReverseVisitor::InterpretReverseVisitor(Ast& ast, unordered_map<string, StateChecker> checkers)
		: StateCheckers(move(checkers))
	{
		it = ast.last; // Start from the end of the AST
		if (!it) {
			throw runtime_error("Trying to match an empty ast with an ast matcher pattern.");
		}
	}

	/*\
	 *
	 *		R O O T
	 *
	\*/

	fn InterpretReverseVisitor::visitAstPatternDescription(AstMatcherParser::AstPatternDescriptionContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitAstPatternDescription in reverse order");
		auto out = AstMatcherVisitorOutput();
		if (!it)
			AST_MATCHER_FAILURE(out, "Empty ast tree.");
		out = any_cast<AstMatcherVisitorOutput>(visit(context->astRoot));
		if (!out.success)
			AST_MATCHER_FAILURE(out, "The AST tree definitely does not match the pattern.");
		DEBUG_LOG("visitAstPatternDescription ended properly.");
		return out;
	}


	/*\
	 *
	 *		N O D E    P R O P E R T I E S    F E A T U R E S
	 *
	\*/

	fn InterpretReverseVisitor::visitNodeProperty(AstMatcherParser::NodePropertyContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitNodeProperty: {}", context->getText());
		auto state_key = context->IDENTIFIER(0)->getText();
		auto out = (AstMatcherVisitorOutput){true, AstMatch()};
		if (!it)
			AST_MATCHER_FAILURE(out, "End of tree reached.");
		if (!it->states.contains(state_key)) {
			AST_MATCHER_FAILURE(out, "Node '{}' does not contain property '{}'.", it->serialize(), state_key);
		}
		if (!context->EQUAL() && context->IDENTIFIER(1)) {
			// FuncCall
			auto state_key = extractAndReplaceEscapedQuotes(context->IDENTIFIER(1)->getText());
			NOT_IMPLEMENTED_LOG("FuncCall in node property");
		} else if (context->nodeTypeSequence()) {
			NOT_IMPLEMENTED_LOG("AstNode as node property");
		} else {
			// TODO: also support string instead of identifier
			auto state_value = extractAndReplaceEscapedQuotes(context->STRING(0)->getText());
			if (it->states[state_key]->serialize() != format("StringState({})", state_value)) {
				AST_MATCHER_FAILURE(
					out,
					"Node property '{}' mismatch, expected value '{}' but got value '{}'.",
					state_key,
					format("StringState({})", state_value),
					it->states[state_key]->serialize()
				);
			} else {
				DEBUG_LOG("Property match.");
			}
		}
		DEBUG_LOG("visitNodeProperty ended properly.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodePropertySequence(AstMatcherParser::NodePropertySequenceContext *context)
		-> any
	{
		println("Visiting visitNodePropertyElement: {}", context->getText());
		auto out = AstMatcherVisitorOutput();

		// NOT should not advance iterator ? or should ? harder if should => need to count all the tree...
		if (context->NOT()) {
			if (context->nodePropertySequence().size() != 1) {
				NOT_IMPLEMENTED_LOG("Unknow logic pattern");
			}
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence()[0]));
			out.success = !out.success;
		} else if (context->nodeProperty()) {
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeProperty()));
			if (!out.success) {
				AST_MATCHER_FAILURE(out, "Node property does not match.");
			}
		} /*else if (context->nodePropertySequence().size() == 1) {
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence()[0]));
			if (!out.success) {
				AST_MATCHER_FAILURE(out, "Node property sequence does not match.");
			}
		} else if (context->elem) {
			// Single nodePropertyElement
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->elem));
			if (!result.success) {
				AST_MATCHER_FAILURE(out, "Single property Node Property Sequence failed.");
			}
			merge_ast_matches(out.matches, result.matches);
		}*/ else if (context->nodePropertySequence().size() > 1) {
			// Handle recursive nodePropertySequence
			if (context->isor) {
				// Handle OR logic by trying each side separately
				DEBUG_LOG("Handling OR operation in Node Property Sequence");
				auto result1 = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(0)));
				if (result1.success) {
					merge_ast_matches(out.matches, result1.matches);
					out.success = true;
				} else {
					auto result2 = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(1)));
					if (result2.success) {
						merge_ast_matches(out.matches, result2.matches);
						out.success = true;
					} else {
						AST_MATCHER_FAILURE(out, "Node property sequence failed using the OR operator.");
					}
				}
			} else {
				// Handle consecutive elements
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(0)));
				if (!result.success) {
					AST_MATCHER_FAILURE(out, "Node property sequence failed.");
				}
				merge_ast_matches(out.matches, result.matches);
				result = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence(1)));
				if (!result.success) {
					AST_MATCHER_FAILURE(out, "Node property sequence failed.");
				}
				merge_ast_matches(out.matches, result.matches);
			}
		} /* else if (context->nodePropertySequence().size() == 1) {

		} */ else {
			NOT_IMPLEMENTED_LOG("Unknow logic pattern");
		}

		println("visitNodePropertyElement end.");
		return out;
	}


	/*\
	 *
	 *		N O D E    T Y P E    F E A T U R E S
	 *
	\*/

	fn InterpretReverseVisitor::visitNodeType(AstMatcherParser::NodeTypeContext *context)
		-> any
	{
		DEBUG_LOG("Visiting visitNodeType: {}", context->getText());
		auto out = AstMatcherVisitorOutput();
		if (!it)
			AST_MATCHER_FAILURE(out, "End of tree reached.");
		auto expectedType = context->ANY() ? it->type : context->IDENTIFIER(0)->getText();
		string alias;
		if (context->AS()) {
			alias = context->IDENTIFIER(1)->getText();
		}
		if (it->type == expectedType) {
			if (!alias.empty()) {
				out.matches[alias] = {it};
			}
			DEBUG_LOG("Checking states...");
			if (context->nodePropertySequence()) {
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodePropertySequence()));
				if (!result.success) {
					AST_MATCHER_FAILURE(out, "Node properties sequence does not match.");
				}
				merge_ast_matches(out.matches, result.matches);
			}
			DEBUG_LOG("Checking childs...");
			if (context->nodeTypeSequence()) {
				BACKUP_ITERATOR(current_node, it);
				RESTORE_ITERATOR(it, it->childs.first->last());
				BACKUP_ITERATOR(node_childs, it);
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()));
				RESTORE_ITERATOR(it, current_node);
				if (!result.success) {
					AST_MATCHER_FAILURE(out, "Node child sequence does not match.");
				}/* else {
					DEBUG_LOG("ADV ---------- 1");
					//ADVANCE_ITERATOR(it);
				}*/
				merge_ast_matches(out.matches, result.matches);
			}
		} else {
			AST_MATCHER_FAILURE(out, "Wrong node type, expected '{}' got '{}'.", expectedType, it->type);
		}
		DEBUG_LOG("AstNode matched.");
		DEBUG_LOG("visitNodeType ended properly.");
		return out;
	}

	fn InterpretReverseVisitor::visitNodeTypeSequence(AstMatcherParser::NodeTypeSequenceContext *context) -> any
	{
		DEBUG_LOG("Visiting visitNodeTypeElement: {}", context->getText());
		auto out = AstMatcherVisitorOutput();

		if (context->NOT()) {
			if (context->nodeTypeSequence().size() != 1) {
				NOT_IMPLEMENTED_LOG("Unknow logic pattern");
			}
			// TODO: comment avance l'iterator ici ? si debut sequence vrai, reste fausse etc..
			// -----> devrait avancer de la taille de la sequence.
			// Implementer la logique avec une pile et des modification dqns le code.
			// ou penser a une autre logique....
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()[0]));
			out.success = !out.success;
		} /*else if (context->nodeTypeSequence().size() == 1) {
			BACKUP_ITERATOR(it_bkp, it);
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()[0]));
			if (!out.success) {
				RESTORE_ITERATOR(it, it_bkp);
				AST_MATCHER_FAILURE(out, "Node seuquence does not match.");
			}
		}*/ else if (context->PLUS()) {
			if (context->nodeTypeSequence().size() != 1) {
				NOT_IMPLEMENTED_LOG("Unknow logic pattern");
			}
			BACKUP_ITERATOR(it_bkp, it);
			if (!it)
				AST_MATCHER_FAILURE(out, "Node one or more ('+' symbol) was not respected.");
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()[0]));
			if (!out.success) {
				RESTORE_ITERATOR(it, it_bkp);
				AST_MATCHER_FAILURE(out, "Node one or more ('+' symbol) was not respected.");
			}
			while (it)
			{
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()[0]));
				if (!result.success) {
					break;
				}
				merge_ast_matches(out.matches, result.matches);
			}
		} else if (context->STAR()) {
			if (context->nodeTypeSequence().size() != 1) {
				NOT_IMPLEMENTED_LOG("Unknow logic pattern");
			}
			while (it)
			{
				auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()[0]));
				if (!result.success) {
					break;
				}
				merge_ast_matches(out.matches, result.matches);
			}
		} else if (context->QUESTION_MARK()) {
			if (context->nodeTypeSequence().size() != 1) {
				NOT_IMPLEMENTED_LOG("Unknow logic pattern");
			}
			BACKUP_ITERATOR(it_bkp, it);
			out = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence()[0]));
			if (out.success) {
				DEBUG_LOG("QUESTION_MARK SUCCESS");
			} else {
				RESTORE_ITERATOR(it, it_bkp);
				DEBUG_LOG("QUESTION_MARK FAILURE");
				out.success = true;
			}
		} else if (context->node) {
			BACKUP_ITERATOR(it_bkp, it);
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->node));
			if (!result.success) {
				RESTORE_ITERATOR(it, it_bkp);
				AST_MATCHER_FAILURE(out, "Node does not match the pattern.");
			}
			ADVANCE_ITERATOR(it);
			merge_ast_matches(out.matches, result.matches);
		} /*else if (context->elem) {
			// Single nodeTypeElement
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->elem));
			if (!result.success) {
				AST_MATCHER_FAILURE(out, "Node failed in a single node sequence.");
			}
			merge_ast_matches(out.matches, result.matches);
			DEBUG_LOG("Single node sequence matched.");
		}*/ else if (context->nodeTypeSequence().size() > 1) {
			// Handle recursive nodeTypeSequence
			if (context->isor) {
				// Handle OR logic by trying each side separately
				DEBUG_LOG("Handling OR operation in NodeTypeSequence");
				BACKUP_ITERATOR(it_bkp, it);
				auto result1 = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(1)));
				if (result1.success) {
					merge_ast_matches(out.matches, result1.matches);
					out.success = true;
				} else {
					RESTORE_ITERATOR(it, it_bkp);
					auto result2 = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(0)));
					if (result2.success) {
						merge_ast_matches(out.matches, result2.matches);
						out.success = true;
					} else {
						RESTORE_ITERATOR(it, it_bkp);
						AST_MATCHER_FAILURE(out, "Neither alternative matched using the OR operator in the node pattern sequence.");
					}
				}
				DEBUG_LOG("Sequence matched using the OR operator.");
			} else {
				// Handle consecutive elements
				BACKUP_ITERATOR(it_bkp, it);
				auto result1 = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(1)));
				if (!result1.success) {
					RESTORE_ITERATOR(it, it_bkp);
					AST_MATCHER_FAILURE(out, "Node failed in a node sequence.");
				}
				auto result2 = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(0)));
				if (!result2.success) {
					RESTORE_ITERATOR(it, it_bkp);
					AST_MATCHER_FAILURE(out, "Node failed in a node sequence.");
				}
				DEBUG_LOG("Sequence matched.");
				merge_ast_matches(out.matches, result1.matches);
				merge_ast_matches(out.matches, result2.matches);
			}
		} else if (context->nodeTypeSequence().size() == 1) {
			BACKUP_ITERATOR(it_bkp, it);
			auto result = any_cast<AstMatcherVisitorOutput>(visit(context->nodeTypeSequence(0)));
			if (!result.success) {
				RESTORE_ITERATOR(it, it_bkp);
				AST_MATCHER_FAILURE(out, "Node does not match the pattern.");
			}
			merge_ast_matches(out.matches, result.matches);
		} else {
		//	DEBUG_LOG("context->nodeTypeSequence().size() = {}", 	context->nodeTypeSequence().size());
		//	DEBUG_LOG("context->isor = {}",							context->isor ? 1 : 0);

			NOT_IMPLEMENTED_LOG("Unknow logic pattern");
		}
		DEBUG_LOG("visitNodeTypeElement ended properly.");
		return out;
	}

}
