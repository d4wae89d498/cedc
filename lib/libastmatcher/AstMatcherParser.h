
// Generated from AstMatcher.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  AstMatcherParser : public antlr4::Parser {
public:
  enum {
    DOLLAR = 1, CAPTURE = 2, SKIP = 3, AS = 4, ARROW = 5, LPAREN = 6, RPAREN = 7, 
    LBRACKET = 8, RBRACKET = 9, LBRACE = 10, RBRACE = 11, EQUAL = 12, COMMA = 13, 
    IDENTIFIER = 14, STRING = 15, WHITESPACE = 16
  };

  enum {
    RuleAstDescription = 0, RuleCaptureStmt = 1, RuleSkipStmt = 2, RuleAstPropertyDescription = 3, 
    RuleFuncCall = 4, RuleMatchList = 5, RuleMatchStmt = 6, RuleNestedCapture = 7
  };

  explicit AstMatcherParser(antlr4::TokenStream *input);

  AstMatcherParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~AstMatcherParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class AstDescriptionContext;
  class CaptureStmtContext;
  class SkipStmtContext;
  class AstPropertyDescriptionContext;
  class FuncCallContext;
  class MatchListContext;
  class MatchStmtContext;
  class NestedCaptureContext; 

  class  AstDescriptionContext : public antlr4::ParserRuleContext {
  public:
    AstDescriptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CaptureStmtContext *captureStmt();
    SkipStmtContext *skipStmt();
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *LBRACE();
    MatchListContext *matchList();
    antlr4::tree::TerminalNode *RBRACE();
    std::vector<AstPropertyDescriptionContext *> astPropertyDescription();
    AstPropertyDescriptionContext* astPropertyDescription(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AstDescriptionContext* astDescription();

  class  CaptureStmtContext : public antlr4::ParserRuleContext {
  public:
    CaptureStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CAPTURE();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *ARROW();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CaptureStmtContext* captureStmt();

  class  SkipStmtContext : public antlr4::ParserRuleContext {
  public:
    SkipStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SKIP();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SkipStmtContext* skipStmt();

  class  AstPropertyDescriptionContext : public antlr4::ParserRuleContext {
  public:
    AstPropertyDescriptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    FuncCallContext *funcCall();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AstPropertyDescriptionContext* astPropertyDescription();

  class  FuncCallContext : public antlr4::ParserRuleContext {
  public:
    FuncCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *DOLLAR();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FuncCallContext* funcCall();

  class  MatchListContext : public antlr4::ParserRuleContext {
  public:
    MatchListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MatchStmtContext *> matchStmt();
    MatchStmtContext* matchStmt(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchListContext* matchList();

  class  MatchStmtContext : public antlr4::ParserRuleContext {
  public:
    MatchStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CaptureStmtContext *captureStmt();
    SkipStmtContext *skipStmt();
    NestedCaptureContext *nestedCapture();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchStmtContext* matchStmt();

  class  NestedCaptureContext : public antlr4::ParserRuleContext {
  public:
    NestedCaptureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *LBRACE();
    MatchListContext *matchList();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NestedCaptureContext* nestedCapture();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

