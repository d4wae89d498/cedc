
// Generated from AstMatcher.g4 by ANTLR 4.13.1


#include "ASTNodeMatcherLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct ASTNodeMatcherLexerStaticData final {
  ASTNodeMatcherLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ASTNodeMatcherLexerStaticData(const ASTNodeMatcherLexerStaticData&) = delete;
  ASTNodeMatcherLexerStaticData(ASTNodeMatcherLexerStaticData&&) = delete;
  ASTNodeMatcherLexerStaticData& operator=(const ASTNodeMatcherLexerStaticData&) = delete;
  ASTNodeMatcherLexerStaticData& operator=(ASTNodeMatcherLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag astnodematcherlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
ASTNodeMatcherLexerStaticData *astnodematcherlexerLexerStaticData = nullptr;

void astnodematcherlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (astnodematcherlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(astnodematcherlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ASTNodeMatcherLexerStaticData>(
    std::vector<std::string>{
      "DOLLAR", "AS", "LPARENTHESE", "RPARENTHESE", "LBRACKET", "RBRACKET", 
      "LBRACE", "RBRACE", "EQUAL", "COMMA", "IDENTIFIER", "STRING", "ESC", 
      "COMMENT", "WHITESPACE"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'$'", "'as'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'='", 
      "','"
    },
    std::vector<std::string>{
      "", "DOLLAR", "AS", "LPARENTHESE", "RPARENTHESE", "LBRACKET", "RBRACKET", 
      "LBRACE", "RBRACE", "EQUAL", "COMMA", "IDENTIFIER", "STRING", "COMMENT", 
      "WHITESPACE"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,14,88,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,1,0,1,0,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,6,1,6,1,7,
  	1,7,1,8,1,8,1,9,1,9,1,10,1,10,5,10,55,8,10,10,10,12,10,58,9,10,1,11,1,
  	11,1,11,5,11,63,8,11,10,11,12,11,66,9,11,1,11,1,11,1,12,1,12,1,12,1,13,
  	1,13,5,13,75,8,13,10,13,12,13,78,9,13,1,13,1,13,1,14,4,14,83,8,14,11,
  	14,12,14,84,1,14,1,14,0,0,15,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,
  	19,10,21,11,23,12,25,0,27,13,29,14,1,0,5,3,0,65,90,95,95,97,122,4,0,48,
  	57,65,90,95,95,97,122,2,0,34,34,92,92,2,0,10,10,13,13,3,0,9,10,13,13,
  	32,32,91,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,
  	0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,
  	1,0,0,0,0,23,1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,1,31,1,0,0,0,3,33,1,0,
  	0,0,5,36,1,0,0,0,7,38,1,0,0,0,9,40,1,0,0,0,11,42,1,0,0,0,13,44,1,0,0,
  	0,15,46,1,0,0,0,17,48,1,0,0,0,19,50,1,0,0,0,21,52,1,0,0,0,23,59,1,0,0,
  	0,25,69,1,0,0,0,27,72,1,0,0,0,29,82,1,0,0,0,31,32,5,36,0,0,32,2,1,0,0,
  	0,33,34,5,97,0,0,34,35,5,115,0,0,35,4,1,0,0,0,36,37,5,40,0,0,37,6,1,0,
  	0,0,38,39,5,41,0,0,39,8,1,0,0,0,40,41,5,91,0,0,41,10,1,0,0,0,42,43,5,
  	93,0,0,43,12,1,0,0,0,44,45,5,123,0,0,45,14,1,0,0,0,46,47,5,125,0,0,47,
  	16,1,0,0,0,48,49,5,61,0,0,49,18,1,0,0,0,50,51,5,44,0,0,51,20,1,0,0,0,
  	52,56,7,0,0,0,53,55,7,1,0,0,54,53,1,0,0,0,55,58,1,0,0,0,56,54,1,0,0,0,
  	56,57,1,0,0,0,57,22,1,0,0,0,58,56,1,0,0,0,59,64,5,34,0,0,60,63,3,25,12,
  	0,61,63,8,2,0,0,62,60,1,0,0,0,62,61,1,0,0,0,63,66,1,0,0,0,64,62,1,0,0,
  	0,64,65,1,0,0,0,65,67,1,0,0,0,66,64,1,0,0,0,67,68,5,34,0,0,68,24,1,0,
  	0,0,69,70,5,92,0,0,70,71,9,0,0,0,71,26,1,0,0,0,72,76,5,35,0,0,73,75,8,
  	3,0,0,74,73,1,0,0,0,75,78,1,0,0,0,76,74,1,0,0,0,76,77,1,0,0,0,77,79,1,
  	0,0,0,78,76,1,0,0,0,79,80,6,13,0,0,80,28,1,0,0,0,81,83,7,4,0,0,82,81,
  	1,0,0,0,83,84,1,0,0,0,84,82,1,0,0,0,84,85,1,0,0,0,85,86,1,0,0,0,86,87,
  	6,14,0,0,87,30,1,0,0,0,6,0,56,62,64,76,84,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  astnodematcherlexerLexerStaticData = staticData.release();
}

}

ASTNodeMatcherLexer::ASTNodeMatcherLexer(CharStream *input) : Lexer(input) {
  ASTNodeMatcherLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *astnodematcherlexerLexerStaticData->atn, astnodematcherlexerLexerStaticData->decisionToDFA, astnodematcherlexerLexerStaticData->sharedContextCache);
}

ASTNodeMatcherLexer::~ASTNodeMatcherLexer() {
  delete _interpreter;
}

std::string ASTNodeMatcherLexer::getGrammarFileName() const {
  return "AstMatcher.g4";
}

const std::vector<std::string>& ASTNodeMatcherLexer::getRuleNames() const {
  return astnodematcherlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& ASTNodeMatcherLexer::getChannelNames() const {
  return astnodematcherlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& ASTNodeMatcherLexer::getModeNames() const {
  return astnodematcherlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& ASTNodeMatcherLexer::getVocabulary() const {
  return astnodematcherlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ASTNodeMatcherLexer::getSerializedATN() const {
  return astnodematcherlexerLexerStaticData->serializedATN;
}

const atn::ATN& ASTNodeMatcherLexer::getATN() const {
  return *astnodematcherlexerLexerStaticData->atn;
}




void ASTNodeMatcherLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  astnodematcherlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(astnodematcherlexerLexerOnceFlag, astnodematcherlexerLexerInitialize);
#endif
}
