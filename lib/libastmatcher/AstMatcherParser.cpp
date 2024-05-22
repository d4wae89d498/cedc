
// Generated from AstMatcher.g4 by ANTLR 4.13.1


#include "AstMatcherListener.h"
#include "AstMatcherVisitor.h"

#include "AstMatcherParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct AstMatcherParserStaticData final {
  AstMatcherParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  AstMatcherParserStaticData(const AstMatcherParserStaticData&) = delete;
  AstMatcherParserStaticData(AstMatcherParserStaticData&&) = delete;
  AstMatcherParserStaticData& operator=(const AstMatcherParserStaticData&) = delete;
  AstMatcherParserStaticData& operator=(AstMatcherParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag astmatcherParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
AstMatcherParserStaticData *astmatcherParserStaticData = nullptr;

void astmatcherParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (astmatcherParserStaticData != nullptr) {
    return;
  }
#else
  assert(astmatcherParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<AstMatcherParserStaticData>(
    std::vector<std::string>{
      "pattern", "astDescription", "captureStmt", "skipStmt", "astPropertyDescription", 
      "funcCall", "matchList", "matchStmt", "nestedCapture"
    },
    std::vector<std::string>{
      "", "'$'", "'capture'", "'skip'", "'as'", "'->'", "'('", "')'", "'['", 
      "']'", "'{'", "'}'", "'='", "','"
    },
    std::vector<std::string>{
      "", "DOLLAR", "CAPTURE", "SKIP_NODE", "AS", "ARROW", "LPAREN", "RPAREN", 
      "LBRACKET", "RBRACKET", "LBRACE", "RBRACE", "EQUAL", "COMMA", "IDENTIFIER", 
      "STRING", "WHITESPACE", "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,17,98,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,7,
  	7,7,2,8,7,8,1,0,5,0,20,8,0,10,0,12,0,23,9,0,1,0,1,0,1,1,1,1,3,1,29,8,
  	1,1,1,1,1,5,1,33,8,1,10,1,12,1,36,9,1,1,1,3,1,39,8,1,1,1,1,1,1,1,1,1,
  	3,1,45,8,1,1,2,1,2,1,2,1,2,3,2,51,8,2,1,2,1,2,3,2,55,8,2,1,3,1,3,1,3,
  	1,4,1,4,1,4,1,4,1,4,3,4,65,8,4,1,5,1,5,1,5,1,5,1,5,3,5,72,8,5,3,5,74,
  	8,5,1,5,1,5,1,6,1,6,1,6,5,6,81,8,6,10,6,12,6,84,9,6,3,6,86,8,6,1,7,1,
  	7,1,7,3,7,91,8,7,1,8,1,8,1,8,1,8,1,8,1,8,0,0,9,0,2,4,6,8,10,12,14,16,
  	0,0,102,0,21,1,0,0,0,2,28,1,0,0,0,4,46,1,0,0,0,6,56,1,0,0,0,8,64,1,0,
  	0,0,10,66,1,0,0,0,12,85,1,0,0,0,14,90,1,0,0,0,16,92,1,0,0,0,18,20,3,2,
  	1,0,19,18,1,0,0,0,20,23,1,0,0,0,21,19,1,0,0,0,21,22,1,0,0,0,22,24,1,0,
  	0,0,23,21,1,0,0,0,24,25,5,0,0,1,25,1,1,0,0,0,26,29,3,4,2,0,27,29,3,6,
  	3,0,28,26,1,0,0,0,28,27,1,0,0,0,29,38,1,0,0,0,30,34,5,8,0,0,31,33,3,8,
  	4,0,32,31,1,0,0,0,33,36,1,0,0,0,34,32,1,0,0,0,34,35,1,0,0,0,35,37,1,0,
  	0,0,36,34,1,0,0,0,37,39,5,9,0,0,38,30,1,0,0,0,38,39,1,0,0,0,39,44,1,0,
  	0,0,40,41,5,10,0,0,41,42,3,12,6,0,42,43,5,11,0,0,43,45,1,0,0,0,44,40,
  	1,0,0,0,44,45,1,0,0,0,45,3,1,0,0,0,46,47,5,2,0,0,47,50,5,14,0,0,48,49,
  	5,4,0,0,49,51,5,14,0,0,50,48,1,0,0,0,50,51,1,0,0,0,51,54,1,0,0,0,52,53,
  	5,5,0,0,53,55,5,14,0,0,54,52,1,0,0,0,54,55,1,0,0,0,55,5,1,0,0,0,56,57,
  	5,3,0,0,57,58,5,14,0,0,58,7,1,0,0,0,59,60,5,15,0,0,60,61,5,12,0,0,61,
  	65,5,15,0,0,62,63,5,15,0,0,63,65,3,10,5,0,64,59,1,0,0,0,64,62,1,0,0,0,
  	65,9,1,0,0,0,66,67,5,14,0,0,67,73,5,6,0,0,68,71,5,1,0,0,69,70,5,13,0,
  	0,70,72,5,15,0,0,71,69,1,0,0,0,71,72,1,0,0,0,72,74,1,0,0,0,73,68,1,0,
  	0,0,73,74,1,0,0,0,74,75,1,0,0,0,75,76,5,7,0,0,76,11,1,0,0,0,77,82,3,14,
  	7,0,78,79,5,13,0,0,79,81,3,14,7,0,80,78,1,0,0,0,81,84,1,0,0,0,82,80,1,
  	0,0,0,82,83,1,0,0,0,83,86,1,0,0,0,84,82,1,0,0,0,85,77,1,0,0,0,85,86,1,
  	0,0,0,86,13,1,0,0,0,87,91,3,4,2,0,88,91,3,6,3,0,89,91,3,16,8,0,90,87,
  	1,0,0,0,90,88,1,0,0,0,90,89,1,0,0,0,91,15,1,0,0,0,92,93,5,14,0,0,93,94,
  	5,10,0,0,94,95,3,12,6,0,95,96,5,11,0,0,96,17,1,0,0,0,13,21,28,34,38,44,
  	50,54,64,71,73,82,85,90
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  astmatcherParserStaticData = staticData.release();
}

}

AstMatcherParser::AstMatcherParser(TokenStream *input) : AstMatcherParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

AstMatcherParser::AstMatcherParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  AstMatcherParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *astmatcherParserStaticData->atn, astmatcherParserStaticData->decisionToDFA, astmatcherParserStaticData->sharedContextCache, options);
}

AstMatcherParser::~AstMatcherParser() {
  delete _interpreter;
}

const atn::ATN& AstMatcherParser::getATN() const {
  return *astmatcherParserStaticData->atn;
}

std::string AstMatcherParser::getGrammarFileName() const {
  return "AstMatcher.g4";
}

const std::vector<std::string>& AstMatcherParser::getRuleNames() const {
  return astmatcherParserStaticData->ruleNames;
}

const dfa::Vocabulary& AstMatcherParser::getVocabulary() const {
  return astmatcherParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView AstMatcherParser::getSerializedATN() const {
  return astmatcherParserStaticData->serializedATN;
}


//----------------- PatternContext ------------------------------------------------------------------

AstMatcherParser::PatternContext::PatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AstMatcherParser::PatternContext::EOF() {
  return getToken(AstMatcherParser::EOF, 0);
}

std::vector<AstMatcherParser::AstDescriptionContext *> AstMatcherParser::PatternContext::astDescription() {
  return getRuleContexts<AstMatcherParser::AstDescriptionContext>();
}

AstMatcherParser::AstDescriptionContext* AstMatcherParser::PatternContext::astDescription(size_t i) {
  return getRuleContext<AstMatcherParser::AstDescriptionContext>(i);
}


size_t AstMatcherParser::PatternContext::getRuleIndex() const {
  return AstMatcherParser::RulePattern;
}

void AstMatcherParser::PatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPattern(this);
}

void AstMatcherParser::PatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPattern(this);
}


std::any AstMatcherParser::PatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitPattern(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::PatternContext* AstMatcherParser::pattern() {
  PatternContext *_localctx = _tracker.createInstance<PatternContext>(_ctx, getState());
  enterRule(_localctx, 0, AstMatcherParser::RulePattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(21);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == AstMatcherParser::CAPTURE

    || _la == AstMatcherParser::SKIP_NODE) {
      setState(18);
      astDescription();
      setState(23);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(24);
    match(AstMatcherParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AstDescriptionContext ------------------------------------------------------------------

AstMatcherParser::AstDescriptionContext::AstDescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AstMatcherParser::CaptureStmtContext* AstMatcherParser::AstDescriptionContext::captureStmt() {
  return getRuleContext<AstMatcherParser::CaptureStmtContext>(0);
}

AstMatcherParser::SkipStmtContext* AstMatcherParser::AstDescriptionContext::skipStmt() {
  return getRuleContext<AstMatcherParser::SkipStmtContext>(0);
}

tree::TerminalNode* AstMatcherParser::AstDescriptionContext::LBRACKET() {
  return getToken(AstMatcherParser::LBRACKET, 0);
}

tree::TerminalNode* AstMatcherParser::AstDescriptionContext::RBRACKET() {
  return getToken(AstMatcherParser::RBRACKET, 0);
}

tree::TerminalNode* AstMatcherParser::AstDescriptionContext::LBRACE() {
  return getToken(AstMatcherParser::LBRACE, 0);
}

AstMatcherParser::MatchListContext* AstMatcherParser::AstDescriptionContext::matchList() {
  return getRuleContext<AstMatcherParser::MatchListContext>(0);
}

tree::TerminalNode* AstMatcherParser::AstDescriptionContext::RBRACE() {
  return getToken(AstMatcherParser::RBRACE, 0);
}

std::vector<AstMatcherParser::AstPropertyDescriptionContext *> AstMatcherParser::AstDescriptionContext::astPropertyDescription() {
  return getRuleContexts<AstMatcherParser::AstPropertyDescriptionContext>();
}

AstMatcherParser::AstPropertyDescriptionContext* AstMatcherParser::AstDescriptionContext::astPropertyDescription(size_t i) {
  return getRuleContext<AstMatcherParser::AstPropertyDescriptionContext>(i);
}


size_t AstMatcherParser::AstDescriptionContext::getRuleIndex() const {
  return AstMatcherParser::RuleAstDescription;
}

void AstMatcherParser::AstDescriptionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAstDescription(this);
}

void AstMatcherParser::AstDescriptionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAstDescription(this);
}


std::any AstMatcherParser::AstDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitAstDescription(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::AstDescriptionContext* AstMatcherParser::astDescription() {
  AstDescriptionContext *_localctx = _tracker.createInstance<AstDescriptionContext>(_ctx, getState());
  enterRule(_localctx, 2, AstMatcherParser::RuleAstDescription);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(28);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AstMatcherParser::CAPTURE: {
        setState(26);
        captureStmt();
        break;
      }

      case AstMatcherParser::SKIP_NODE: {
        setState(27);
        skipStmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(38);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AstMatcherParser::LBRACKET) {
      setState(30);
      match(AstMatcherParser::LBRACKET);
      setState(34);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == AstMatcherParser::STRING) {
        setState(31);
        astPropertyDescription();
        setState(36);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(37);
      match(AstMatcherParser::RBRACKET);
    }
    setState(44);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AstMatcherParser::LBRACE) {
      setState(40);
      match(AstMatcherParser::LBRACE);
      setState(41);
      matchList();
      setState(42);
      match(AstMatcherParser::RBRACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CaptureStmtContext ------------------------------------------------------------------

AstMatcherParser::CaptureStmtContext::CaptureStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AstMatcherParser::CaptureStmtContext::CAPTURE() {
  return getToken(AstMatcherParser::CAPTURE, 0);
}

std::vector<tree::TerminalNode *> AstMatcherParser::CaptureStmtContext::IDENTIFIER() {
  return getTokens(AstMatcherParser::IDENTIFIER);
}

tree::TerminalNode* AstMatcherParser::CaptureStmtContext::IDENTIFIER(size_t i) {
  return getToken(AstMatcherParser::IDENTIFIER, i);
}

tree::TerminalNode* AstMatcherParser::CaptureStmtContext::AS() {
  return getToken(AstMatcherParser::AS, 0);
}

tree::TerminalNode* AstMatcherParser::CaptureStmtContext::ARROW() {
  return getToken(AstMatcherParser::ARROW, 0);
}


size_t AstMatcherParser::CaptureStmtContext::getRuleIndex() const {
  return AstMatcherParser::RuleCaptureStmt;
}

void AstMatcherParser::CaptureStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCaptureStmt(this);
}

void AstMatcherParser::CaptureStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCaptureStmt(this);
}


std::any AstMatcherParser::CaptureStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitCaptureStmt(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::CaptureStmtContext* AstMatcherParser::captureStmt() {
  CaptureStmtContext *_localctx = _tracker.createInstance<CaptureStmtContext>(_ctx, getState());
  enterRule(_localctx, 4, AstMatcherParser::RuleCaptureStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(46);
    match(AstMatcherParser::CAPTURE);
    setState(47);
    match(AstMatcherParser::IDENTIFIER);
    setState(50);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AstMatcherParser::AS) {
      setState(48);
      match(AstMatcherParser::AS);
      setState(49);
      match(AstMatcherParser::IDENTIFIER);
    }
    setState(54);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AstMatcherParser::ARROW) {
      setState(52);
      match(AstMatcherParser::ARROW);
      setState(53);
      match(AstMatcherParser::IDENTIFIER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SkipStmtContext ------------------------------------------------------------------

AstMatcherParser::SkipStmtContext::SkipStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AstMatcherParser::SkipStmtContext::SKIP_NODE() {
  return getToken(AstMatcherParser::SKIP_NODE, 0);
}

tree::TerminalNode* AstMatcherParser::SkipStmtContext::IDENTIFIER() {
  return getToken(AstMatcherParser::IDENTIFIER, 0);
}


size_t AstMatcherParser::SkipStmtContext::getRuleIndex() const {
  return AstMatcherParser::RuleSkipStmt;
}

void AstMatcherParser::SkipStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSkipStmt(this);
}

void AstMatcherParser::SkipStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSkipStmt(this);
}


std::any AstMatcherParser::SkipStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitSkipStmt(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::SkipStmtContext* AstMatcherParser::skipStmt() {
  SkipStmtContext *_localctx = _tracker.createInstance<SkipStmtContext>(_ctx, getState());
  enterRule(_localctx, 6, AstMatcherParser::RuleSkipStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(AstMatcherParser::SKIP_NODE);
    setState(57);
    match(AstMatcherParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AstPropertyDescriptionContext ------------------------------------------------------------------

AstMatcherParser::AstPropertyDescriptionContext::AstPropertyDescriptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> AstMatcherParser::AstPropertyDescriptionContext::STRING() {
  return getTokens(AstMatcherParser::STRING);
}

tree::TerminalNode* AstMatcherParser::AstPropertyDescriptionContext::STRING(size_t i) {
  return getToken(AstMatcherParser::STRING, i);
}

tree::TerminalNode* AstMatcherParser::AstPropertyDescriptionContext::EQUAL() {
  return getToken(AstMatcherParser::EQUAL, 0);
}

AstMatcherParser::FuncCallContext* AstMatcherParser::AstPropertyDescriptionContext::funcCall() {
  return getRuleContext<AstMatcherParser::FuncCallContext>(0);
}


size_t AstMatcherParser::AstPropertyDescriptionContext::getRuleIndex() const {
  return AstMatcherParser::RuleAstPropertyDescription;
}

void AstMatcherParser::AstPropertyDescriptionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAstPropertyDescription(this);
}

void AstMatcherParser::AstPropertyDescriptionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAstPropertyDescription(this);
}


std::any AstMatcherParser::AstPropertyDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitAstPropertyDescription(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::AstPropertyDescriptionContext* AstMatcherParser::astPropertyDescription() {
  AstPropertyDescriptionContext *_localctx = _tracker.createInstance<AstPropertyDescriptionContext>(_ctx, getState());
  enterRule(_localctx, 8, AstMatcherParser::RuleAstPropertyDescription);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(64);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(59);
      match(AstMatcherParser::STRING);
      setState(60);
      match(AstMatcherParser::EQUAL);
      setState(61);
      match(AstMatcherParser::STRING);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(62);
      match(AstMatcherParser::STRING);
      setState(63);
      funcCall();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncCallContext ------------------------------------------------------------------

AstMatcherParser::FuncCallContext::FuncCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AstMatcherParser::FuncCallContext::IDENTIFIER() {
  return getToken(AstMatcherParser::IDENTIFIER, 0);
}

tree::TerminalNode* AstMatcherParser::FuncCallContext::LPAREN() {
  return getToken(AstMatcherParser::LPAREN, 0);
}

tree::TerminalNode* AstMatcherParser::FuncCallContext::RPAREN() {
  return getToken(AstMatcherParser::RPAREN, 0);
}

tree::TerminalNode* AstMatcherParser::FuncCallContext::DOLLAR() {
  return getToken(AstMatcherParser::DOLLAR, 0);
}

tree::TerminalNode* AstMatcherParser::FuncCallContext::COMMA() {
  return getToken(AstMatcherParser::COMMA, 0);
}

tree::TerminalNode* AstMatcherParser::FuncCallContext::STRING() {
  return getToken(AstMatcherParser::STRING, 0);
}


size_t AstMatcherParser::FuncCallContext::getRuleIndex() const {
  return AstMatcherParser::RuleFuncCall;
}

void AstMatcherParser::FuncCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFuncCall(this);
}

void AstMatcherParser::FuncCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFuncCall(this);
}


std::any AstMatcherParser::FuncCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitFuncCall(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::FuncCallContext* AstMatcherParser::funcCall() {
  FuncCallContext *_localctx = _tracker.createInstance<FuncCallContext>(_ctx, getState());
  enterRule(_localctx, 10, AstMatcherParser::RuleFuncCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66);
    match(AstMatcherParser::IDENTIFIER);
    setState(67);
    match(AstMatcherParser::LPAREN);
    setState(73);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == AstMatcherParser::DOLLAR) {
      setState(68);
      match(AstMatcherParser::DOLLAR);
      setState(71);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == AstMatcherParser::COMMA) {
        setState(69);
        match(AstMatcherParser::COMMA);
        setState(70);
        match(AstMatcherParser::STRING);
      }
    }
    setState(75);
    match(AstMatcherParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchListContext ------------------------------------------------------------------

AstMatcherParser::MatchListContext::MatchListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<AstMatcherParser::MatchStmtContext *> AstMatcherParser::MatchListContext::matchStmt() {
  return getRuleContexts<AstMatcherParser::MatchStmtContext>();
}

AstMatcherParser::MatchStmtContext* AstMatcherParser::MatchListContext::matchStmt(size_t i) {
  return getRuleContext<AstMatcherParser::MatchStmtContext>(i);
}

std::vector<tree::TerminalNode *> AstMatcherParser::MatchListContext::COMMA() {
  return getTokens(AstMatcherParser::COMMA);
}

tree::TerminalNode* AstMatcherParser::MatchListContext::COMMA(size_t i) {
  return getToken(AstMatcherParser::COMMA, i);
}


size_t AstMatcherParser::MatchListContext::getRuleIndex() const {
  return AstMatcherParser::RuleMatchList;
}

void AstMatcherParser::MatchListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMatchList(this);
}

void AstMatcherParser::MatchListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMatchList(this);
}


std::any AstMatcherParser::MatchListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitMatchList(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::MatchListContext* AstMatcherParser::matchList() {
  MatchListContext *_localctx = _tracker.createInstance<MatchListContext>(_ctx, getState());
  enterRule(_localctx, 12, AstMatcherParser::RuleMatchList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 16396) != 0)) {
      setState(77);
      matchStmt();
      setState(82);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == AstMatcherParser::COMMA) {
        setState(78);
        match(AstMatcherParser::COMMA);
        setState(79);
        matchStmt();
        setState(84);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchStmtContext ------------------------------------------------------------------

AstMatcherParser::MatchStmtContext::MatchStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

AstMatcherParser::CaptureStmtContext* AstMatcherParser::MatchStmtContext::captureStmt() {
  return getRuleContext<AstMatcherParser::CaptureStmtContext>(0);
}

AstMatcherParser::SkipStmtContext* AstMatcherParser::MatchStmtContext::skipStmt() {
  return getRuleContext<AstMatcherParser::SkipStmtContext>(0);
}

AstMatcherParser::NestedCaptureContext* AstMatcherParser::MatchStmtContext::nestedCapture() {
  return getRuleContext<AstMatcherParser::NestedCaptureContext>(0);
}


size_t AstMatcherParser::MatchStmtContext::getRuleIndex() const {
  return AstMatcherParser::RuleMatchStmt;
}

void AstMatcherParser::MatchStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMatchStmt(this);
}

void AstMatcherParser::MatchStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMatchStmt(this);
}


std::any AstMatcherParser::MatchStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitMatchStmt(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::MatchStmtContext* AstMatcherParser::matchStmt() {
  MatchStmtContext *_localctx = _tracker.createInstance<MatchStmtContext>(_ctx, getState());
  enterRule(_localctx, 14, AstMatcherParser::RuleMatchStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(90);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case AstMatcherParser::CAPTURE: {
        enterOuterAlt(_localctx, 1);
        setState(87);
        captureStmt();
        break;
      }

      case AstMatcherParser::SKIP_NODE: {
        enterOuterAlt(_localctx, 2);
        setState(88);
        skipStmt();
        break;
      }

      case AstMatcherParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 3);
        setState(89);
        nestedCapture();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NestedCaptureContext ------------------------------------------------------------------

AstMatcherParser::NestedCaptureContext::NestedCaptureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* AstMatcherParser::NestedCaptureContext::IDENTIFIER() {
  return getToken(AstMatcherParser::IDENTIFIER, 0);
}

tree::TerminalNode* AstMatcherParser::NestedCaptureContext::LBRACE() {
  return getToken(AstMatcherParser::LBRACE, 0);
}

AstMatcherParser::MatchListContext* AstMatcherParser::NestedCaptureContext::matchList() {
  return getRuleContext<AstMatcherParser::MatchListContext>(0);
}

tree::TerminalNode* AstMatcherParser::NestedCaptureContext::RBRACE() {
  return getToken(AstMatcherParser::RBRACE, 0);
}


size_t AstMatcherParser::NestedCaptureContext::getRuleIndex() const {
  return AstMatcherParser::RuleNestedCapture;
}

void AstMatcherParser::NestedCaptureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNestedCapture(this);
}

void AstMatcherParser::NestedCaptureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<AstMatcherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNestedCapture(this);
}


std::any AstMatcherParser::NestedCaptureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<AstMatcherVisitor*>(visitor))
    return parserVisitor->visitNestedCapture(this);
  else
    return visitor->visitChildren(this);
}

AstMatcherParser::NestedCaptureContext* AstMatcherParser::nestedCapture() {
  NestedCaptureContext *_localctx = _tracker.createInstance<NestedCaptureContext>(_ctx, getState());
  enterRule(_localctx, 16, AstMatcherParser::RuleNestedCapture);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(92);
    match(AstMatcherParser::IDENTIFIER);
    setState(93);
    match(AstMatcherParser::LBRACE);
    setState(94);
    matchList();
    setState(95);
    match(AstMatcherParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void AstMatcherParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  astmatcherParserInitialize();
#else
  ::antlr4::internal::call_once(astmatcherParserOnceFlag, astmatcherParserInitialize);
#endif
}
