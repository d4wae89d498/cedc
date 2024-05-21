
// Generated from AstMatcher.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "AstMatcherParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by AstMatcherParser.
 */
class  AstMatcherListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterAstDescription(AstMatcherParser::AstDescriptionContext *ctx) = 0;
  virtual void exitAstDescription(AstMatcherParser::AstDescriptionContext *ctx) = 0;

  virtual void enterCaptureStmt(AstMatcherParser::CaptureStmtContext *ctx) = 0;
  virtual void exitCaptureStmt(AstMatcherParser::CaptureStmtContext *ctx) = 0;

  virtual void enterSkipStmt(AstMatcherParser::SkipStmtContext *ctx) = 0;
  virtual void exitSkipStmt(AstMatcherParser::SkipStmtContext *ctx) = 0;

  virtual void enterAstPropertyDescription(AstMatcherParser::AstPropertyDescriptionContext *ctx) = 0;
  virtual void exitAstPropertyDescription(AstMatcherParser::AstPropertyDescriptionContext *ctx) = 0;

  virtual void enterFuncCall(AstMatcherParser::FuncCallContext *ctx) = 0;
  virtual void exitFuncCall(AstMatcherParser::FuncCallContext *ctx) = 0;

  virtual void enterMatchList(AstMatcherParser::MatchListContext *ctx) = 0;
  virtual void exitMatchList(AstMatcherParser::MatchListContext *ctx) = 0;

  virtual void enterMatchStmt(AstMatcherParser::MatchStmtContext *ctx) = 0;
  virtual void exitMatchStmt(AstMatcherParser::MatchStmtContext *ctx) = 0;

  virtual void enterNestedCapture(AstMatcherParser::NestedCaptureContext *ctx) = 0;
  virtual void exitNestedCapture(AstMatcherParser::NestedCaptureContext *ctx) = 0;


};

