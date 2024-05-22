
// Generated from AstMatcher.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "AstMatcherListener.h"


/**
 * This class provides an empty implementation of AstMatcherListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  AstMatcherBaseListener : public AstMatcherListener {
public:

  virtual void enterPattern(AstMatcherParser::PatternContext * /*ctx*/) override { }
  virtual void exitPattern(AstMatcherParser::PatternContext * /*ctx*/) override { }

  virtual void enterAstDescription(AstMatcherParser::AstDescriptionContext * /*ctx*/) override { }
  virtual void exitAstDescription(AstMatcherParser::AstDescriptionContext * /*ctx*/) override { }

  virtual void enterCaptureStmt(AstMatcherParser::CaptureStmtContext * /*ctx*/) override { }
  virtual void exitCaptureStmt(AstMatcherParser::CaptureStmtContext * /*ctx*/) override { }

  virtual void enterSkipStmt(AstMatcherParser::SkipStmtContext * /*ctx*/) override { }
  virtual void exitSkipStmt(AstMatcherParser::SkipStmtContext * /*ctx*/) override { }

  virtual void enterAstPropertyDescription(AstMatcherParser::AstPropertyDescriptionContext * /*ctx*/) override { }
  virtual void exitAstPropertyDescription(AstMatcherParser::AstPropertyDescriptionContext * /*ctx*/) override { }

  virtual void enterFuncCall(AstMatcherParser::FuncCallContext * /*ctx*/) override { }
  virtual void exitFuncCall(AstMatcherParser::FuncCallContext * /*ctx*/) override { }

  virtual void enterMatchList(AstMatcherParser::MatchListContext * /*ctx*/) override { }
  virtual void exitMatchList(AstMatcherParser::MatchListContext * /*ctx*/) override { }

  virtual void enterMatchStmt(AstMatcherParser::MatchStmtContext * /*ctx*/) override { }
  virtual void exitMatchStmt(AstMatcherParser::MatchStmtContext * /*ctx*/) override { }

  virtual void enterNestedCapture(AstMatcherParser::NestedCaptureContext * /*ctx*/) override { }
  virtual void exitNestedCapture(AstMatcherParser::NestedCaptureContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

