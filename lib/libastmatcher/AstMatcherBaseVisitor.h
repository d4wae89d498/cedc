
// Generated from AstMatcher.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "AstMatcherVisitor.h"


/**
 * This class provides an empty implementation of AstMatcherVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  AstMatcherBaseVisitor : public AstMatcherVisitor {
public:

  virtual std::any visitPattern(AstMatcherParser::PatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAstDescription(AstMatcherParser::AstDescriptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCaptureStmt(AstMatcherParser::CaptureStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSkipStmt(AstMatcherParser::SkipStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAstPropertyDescription(AstMatcherParser::AstPropertyDescriptionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncCall(AstMatcherParser::FuncCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchList(AstMatcherParser::MatchListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchStmt(AstMatcherParser::MatchStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNestedCapture(AstMatcherParser::NestedCaptureContext *ctx) override {
    return visitChildren(ctx);
  }


};

