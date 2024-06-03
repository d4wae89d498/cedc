
// Generated from AstMatcher.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  ASTNodeMatcherLexer : public antlr4::Lexer {
public:
  enum {
    DOLLAR = 1, AS = 2, LPARENTHESE = 3, RPARENTHESE = 4, LBRACKET = 5, 
    RBRACKET = 6, LBRACE = 7, RBRACE = 8, EQUAL = 9, COMMA = 10, IDENTIFIER = 11, 
    STRING = 12, COMMENT = 13, WHITESPACE = 14
  };

  explicit ASTNodeMatcherLexer(antlr4::CharStream *input);

  ~ASTNodeMatcherLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

