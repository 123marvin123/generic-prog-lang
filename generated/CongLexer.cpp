
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongLexer.g4 by ANTLR 4.13.2


#include "CongLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct CongLexerStaticData final {
  CongLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CongLexerStaticData(const CongLexerStaticData&) = delete;
  CongLexerStaticData(CongLexerStaticData&&) = delete;
  CongLexerStaticData& operator=(const CongLexerStaticData&) = delete;
  CongLexerStaticData& operator=(CongLexerStaticData&&) = delete;

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

::antlr4::internal::OnceFlag conglexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CongLexerStaticData> conglexerLexerStaticData = nullptr;

void conglexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (conglexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(conglexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CongLexerStaticData>(
    std::vector<std::string>{
      "CONCEPT", "FUNCTION", "NAMESPACE", "LET", "DESCRIPTION", "GENERICIMPL", 
      "REQUIRES", "TIME", "SPACE", "LANG", "LBRACE", "RBRACE", "VARARGS", 
      "LPAREN", "RPAREN", "COLON", "SEMI", "AMP", "ARROW", "COMMA", "ASSIGN", 
      "PLUS", "MINUS", "MUL", "DIV", "MOD", "LT", "GT", "DOUBLE_COLON", 
      "REAL", "BOOL", "NUMBER", "STRING", "IDENTIFIER", "WHITESPACE", "COMMENT", 
      "LINE_COMMENT", "OTHER"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'concept'", "'fun'", "'namespace'", "'let'", "'description'", 
      "'generic'", "'requires'", "'time'", "'space'", "'lang'", "'{'", "'}'", 
      "'...'", "'('", "')'", "':'", "';'", "'&'", "'->'", "','", "'='", 
      "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'::'"
    },
    std::vector<std::string>{
      "", "CONCEPT", "FUNCTION", "NAMESPACE", "LET", "DESCRIPTION", "GENERICIMPL", 
      "REQUIRES", "TIME", "SPACE", "LANG", "LBRACE", "RBRACE", "VARARGS", 
      "LPAREN", "RPAREN", "COLON", "SEMI", "AMP", "ARROW", "COMMA", "ASSIGN", 
      "PLUS", "MINUS", "MUL", "DIV", "MOD", "LT", "GT", "DOUBLE_COLON", 
      "REAL", "BOOL", "NUMBER", "STRING", "IDENTIFIER", "WHITESPACE", "COMMENT", 
      "LINE_COMMENT", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,38,293,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,
  	1,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,1,
  	4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,12,1,12,
  	1,13,1,13,1,14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,18,1,18,1,18,1,19,
  	1,19,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,1,26,
  	1,26,1,27,1,27,1,28,1,28,1,28,1,29,1,29,1,29,4,29,194,8,29,11,29,12,29,
  	195,1,29,1,29,5,29,200,8,29,10,29,12,29,203,9,29,1,29,1,29,4,29,207,8,
  	29,11,29,12,29,208,3,29,211,8,29,1,30,1,30,1,30,1,30,1,30,1,30,1,30,1,
  	30,1,30,3,30,222,8,30,1,31,1,31,5,31,226,8,31,10,31,12,31,229,9,31,1,
  	31,1,31,1,31,1,31,5,31,235,8,31,10,31,12,31,238,9,31,1,31,1,31,3,31,242,
  	8,31,1,32,1,32,5,32,246,8,32,10,32,12,32,249,9,32,1,32,1,32,1,33,1,33,
  	5,33,255,8,33,10,33,12,33,258,9,33,1,34,4,34,261,8,34,11,34,12,34,262,
  	1,34,1,34,1,35,1,35,1,35,1,35,5,35,271,8,35,10,35,12,35,274,9,35,1,35,
  	1,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,5,36,285,8,36,10,36,12,36,288,
  	9,36,1,36,1,36,1,37,1,37,1,272,0,38,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,
  	8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,
  	20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,
  	63,32,65,33,67,34,69,35,71,36,73,37,75,38,1,0,7,1,0,48,57,1,0,49,57,1,
  	0,34,34,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,3,0,9,10,
  	13,13,32,32,2,0,10,10,13,13,307,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,
  	7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,
  	0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,
  	0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,
  	1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,
  	0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,
  	0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,
  	1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,1,77,1,0,0,0,3,85,1,0,0,0,5,89,1,0,
  	0,0,7,99,1,0,0,0,9,103,1,0,0,0,11,115,1,0,0,0,13,123,1,0,0,0,15,132,1,
  	0,0,0,17,137,1,0,0,0,19,143,1,0,0,0,21,148,1,0,0,0,23,150,1,0,0,0,25,
  	152,1,0,0,0,27,156,1,0,0,0,29,158,1,0,0,0,31,160,1,0,0,0,33,162,1,0,0,
  	0,35,164,1,0,0,0,37,166,1,0,0,0,39,169,1,0,0,0,41,171,1,0,0,0,43,173,
  	1,0,0,0,45,175,1,0,0,0,47,177,1,0,0,0,49,179,1,0,0,0,51,181,1,0,0,0,53,
  	183,1,0,0,0,55,185,1,0,0,0,57,187,1,0,0,0,59,210,1,0,0,0,61,221,1,0,0,
  	0,63,241,1,0,0,0,65,243,1,0,0,0,67,252,1,0,0,0,69,260,1,0,0,0,71,266,
  	1,0,0,0,73,280,1,0,0,0,75,291,1,0,0,0,77,78,5,99,0,0,78,79,5,111,0,0,
  	79,80,5,110,0,0,80,81,5,99,0,0,81,82,5,101,0,0,82,83,5,112,0,0,83,84,
  	5,116,0,0,84,2,1,0,0,0,85,86,5,102,0,0,86,87,5,117,0,0,87,88,5,110,0,
  	0,88,4,1,0,0,0,89,90,5,110,0,0,90,91,5,97,0,0,91,92,5,109,0,0,92,93,5,
  	101,0,0,93,94,5,115,0,0,94,95,5,112,0,0,95,96,5,97,0,0,96,97,5,99,0,0,
  	97,98,5,101,0,0,98,6,1,0,0,0,99,100,5,108,0,0,100,101,5,101,0,0,101,102,
  	5,116,0,0,102,8,1,0,0,0,103,104,5,100,0,0,104,105,5,101,0,0,105,106,5,
  	115,0,0,106,107,5,99,0,0,107,108,5,114,0,0,108,109,5,105,0,0,109,110,
  	5,112,0,0,110,111,5,116,0,0,111,112,5,105,0,0,112,113,5,111,0,0,113,114,
  	5,110,0,0,114,10,1,0,0,0,115,116,5,103,0,0,116,117,5,101,0,0,117,118,
  	5,110,0,0,118,119,5,101,0,0,119,120,5,114,0,0,120,121,5,105,0,0,121,122,
  	5,99,0,0,122,12,1,0,0,0,123,124,5,114,0,0,124,125,5,101,0,0,125,126,5,
  	113,0,0,126,127,5,117,0,0,127,128,5,105,0,0,128,129,5,114,0,0,129,130,
  	5,101,0,0,130,131,5,115,0,0,131,14,1,0,0,0,132,133,5,116,0,0,133,134,
  	5,105,0,0,134,135,5,109,0,0,135,136,5,101,0,0,136,16,1,0,0,0,137,138,
  	5,115,0,0,138,139,5,112,0,0,139,140,5,97,0,0,140,141,5,99,0,0,141,142,
  	5,101,0,0,142,18,1,0,0,0,143,144,5,108,0,0,144,145,5,97,0,0,145,146,5,
  	110,0,0,146,147,5,103,0,0,147,20,1,0,0,0,148,149,5,123,0,0,149,22,1,0,
  	0,0,150,151,5,125,0,0,151,24,1,0,0,0,152,153,5,46,0,0,153,154,5,46,0,
  	0,154,155,5,46,0,0,155,26,1,0,0,0,156,157,5,40,0,0,157,28,1,0,0,0,158,
  	159,5,41,0,0,159,30,1,0,0,0,160,161,5,58,0,0,161,32,1,0,0,0,162,163,5,
  	59,0,0,163,34,1,0,0,0,164,165,5,38,0,0,165,36,1,0,0,0,166,167,5,45,0,
  	0,167,168,5,62,0,0,168,38,1,0,0,0,169,170,5,44,0,0,170,40,1,0,0,0,171,
  	172,5,61,0,0,172,42,1,0,0,0,173,174,5,43,0,0,174,44,1,0,0,0,175,176,5,
  	45,0,0,176,46,1,0,0,0,177,178,5,42,0,0,178,48,1,0,0,0,179,180,5,47,0,
  	0,180,50,1,0,0,0,181,182,5,37,0,0,182,52,1,0,0,0,183,184,5,60,0,0,184,
  	54,1,0,0,0,185,186,5,62,0,0,186,56,1,0,0,0,187,188,5,58,0,0,188,189,5,
  	58,0,0,189,58,1,0,0,0,190,191,5,48,0,0,191,193,5,46,0,0,192,194,7,0,0,
  	0,193,192,1,0,0,0,194,195,1,0,0,0,195,193,1,0,0,0,195,196,1,0,0,0,196,
  	211,1,0,0,0,197,201,7,1,0,0,198,200,7,0,0,0,199,198,1,0,0,0,200,203,1,
  	0,0,0,201,199,1,0,0,0,201,202,1,0,0,0,202,204,1,0,0,0,203,201,1,0,0,0,
  	204,206,5,46,0,0,205,207,7,0,0,0,206,205,1,0,0,0,207,208,1,0,0,0,208,
  	206,1,0,0,0,208,209,1,0,0,0,209,211,1,0,0,0,210,190,1,0,0,0,210,197,1,
  	0,0,0,211,60,1,0,0,0,212,213,5,116,0,0,213,214,5,114,0,0,214,215,5,117,
  	0,0,215,222,5,101,0,0,216,217,5,102,0,0,217,218,5,97,0,0,218,219,5,108,
  	0,0,219,220,5,115,0,0,220,222,5,101,0,0,221,212,1,0,0,0,221,216,1,0,0,
  	0,222,62,1,0,0,0,223,227,7,1,0,0,224,226,7,0,0,0,225,224,1,0,0,0,226,
  	229,1,0,0,0,227,225,1,0,0,0,227,228,1,0,0,0,228,242,1,0,0,0,229,227,1,
  	0,0,0,230,242,5,48,0,0,231,232,5,45,0,0,232,236,7,1,0,0,233,235,7,0,0,
  	0,234,233,1,0,0,0,235,238,1,0,0,0,236,234,1,0,0,0,236,237,1,0,0,0,237,
  	242,1,0,0,0,238,236,1,0,0,0,239,240,5,45,0,0,240,242,5,48,0,0,241,223,
  	1,0,0,0,241,230,1,0,0,0,241,231,1,0,0,0,241,239,1,0,0,0,242,64,1,0,0,
  	0,243,247,5,34,0,0,244,246,8,2,0,0,245,244,1,0,0,0,246,249,1,0,0,0,247,
  	245,1,0,0,0,247,248,1,0,0,0,248,250,1,0,0,0,249,247,1,0,0,0,250,251,5,
  	34,0,0,251,66,1,0,0,0,252,256,7,3,0,0,253,255,7,4,0,0,254,253,1,0,0,0,
  	255,258,1,0,0,0,256,254,1,0,0,0,256,257,1,0,0,0,257,68,1,0,0,0,258,256,
  	1,0,0,0,259,261,7,5,0,0,260,259,1,0,0,0,261,262,1,0,0,0,262,260,1,0,0,
  	0,262,263,1,0,0,0,263,264,1,0,0,0,264,265,6,34,0,0,265,70,1,0,0,0,266,
  	267,5,47,0,0,267,268,5,42,0,0,268,272,1,0,0,0,269,271,9,0,0,0,270,269,
  	1,0,0,0,271,274,1,0,0,0,272,273,1,0,0,0,272,270,1,0,0,0,273,275,1,0,0,
  	0,274,272,1,0,0,0,275,276,5,42,0,0,276,277,5,47,0,0,277,278,1,0,0,0,278,
  	279,6,35,1,0,279,72,1,0,0,0,280,281,5,47,0,0,281,282,5,47,0,0,282,286,
  	1,0,0,0,283,285,8,6,0,0,284,283,1,0,0,0,285,288,1,0,0,0,286,284,1,0,0,
  	0,286,287,1,0,0,0,287,289,1,0,0,0,288,286,1,0,0,0,289,290,6,36,1,0,290,
  	74,1,0,0,0,291,292,9,0,0,0,292,76,1,0,0,0,14,0,195,201,208,210,221,227,
  	236,241,247,256,262,272,286,2,6,0,0,0,1,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  conglexerLexerStaticData = std::move(staticData);
}

}

CongLexer::CongLexer(CharStream *input) : Lexer(input) {
  CongLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *conglexerLexerStaticData->atn, conglexerLexerStaticData->decisionToDFA, conglexerLexerStaticData->sharedContextCache);
}

CongLexer::~CongLexer() {
  delete _interpreter;
}

std::string CongLexer::getGrammarFileName() const {
  return "CongLexer.g4";
}

const std::vector<std::string>& CongLexer::getRuleNames() const {
  return conglexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& CongLexer::getChannelNames() const {
  return conglexerLexerStaticData->channelNames;
}

const std::vector<std::string>& CongLexer::getModeNames() const {
  return conglexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& CongLexer::getVocabulary() const {
  return conglexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CongLexer::getSerializedATN() const {
  return conglexerLexerStaticData->serializedATN;
}

const atn::ATN& CongLexer::getATN() const {
  return *conglexerLexerStaticData->atn;
}




void CongLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  conglexerLexerInitialize();
#else
  ::antlr4::internal::call_once(conglexerLexerOnceFlag, conglexerLexerInitialize);
#endif
}
