
// Generated from AstMatcher.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"
#include "AstMatcherParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by AstMatcherParser.
 */
class  AstMatcherVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by AstMatcherParser.
   */
    virtual std::any visitPattern(AstMatcherParser::PatternContext *context) = 0;

    virtual std::any visitAstDescription(AstMatcherParser::AstDescriptionContext *context) = 0;

    virtual std::any visitCaptureStmt(AstMatcherParser::CaptureStmtContext *context) = 0;

    virtual std::any visitSkipStmt(AstMatcherParser::SkipStmtContext *context) = 0;

    virtual std::any visitAstPropertyDescription(AstMatcherParser::AstPropertyDescriptionContext *context) = 0;

    virtual std::any visitFuncCall(AstMatcherParser::FuncCallContext *context) = 0;

    virtual std::any visitMatchList(AstMatcherParser::MatchListContext *context) = 0;

    virtual std::any visitMatchStmt(AstMatcherParser::MatchStmtContext *context) = 0;

    virtual std::any visitNestedCapture(AstMatcherParser::NestedCaptureContext *context) = 0;


};

