
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/Cong.g4 by ANTLR 4.13.2


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
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "CONCEPT", "FUNCTION", 
      "NAMESPACE", "DESCRIPTION", "GENERICIMPL", "REQUIRES", "LBRACE", "RBRACE", 
      "VARARGS", "REAL", "BOOL", "NUMBER", "STRING", "IDENTIFIER", "WHITESPACE", 
      "COMMENT", "LINE_COMMENT", "OTHER"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'('", "':'", "')'", "';'", "'&'", "'->'", "','", "'+'", "'-'", 
      "'*'", "'/'", "'%'", "'<'", "'>'", "'::'", "'concept'", "'fun'", "'namespace'", 
      "'description'", "'generic'", "'requires'", "'{'", "'}'", "'...'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "CONCEPT", 
      "FUNCTION", "NAMESPACE", "DESCRIPTION", "GENERICIMPL", "REQUIRES", 
      "LBRACE", "RBRACE", "VARARGS", "REAL", "BOOL", "NUMBER", "STRING", 
      "IDENTIFIER", "WHITESPACE", "COMMENT", "LINE_COMMENT", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,33,261,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,1,0,1,0,1,1,1,1,1,2,1,2,
  	1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,
  	1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,
  	1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,20,1,20,1,21,1,21,1,22,1,22,1,23,1,23,1,23,1,23,1,24,1,24,
  	1,24,4,24,162,8,24,11,24,12,24,163,1,24,1,24,5,24,168,8,24,10,24,12,24,
  	171,9,24,1,24,1,24,4,24,175,8,24,11,24,12,24,176,3,24,179,8,24,1,25,1,
  	25,1,25,1,25,1,25,1,25,1,25,1,25,1,25,3,25,190,8,25,1,26,1,26,5,26,194,
  	8,26,10,26,12,26,197,9,26,1,26,1,26,1,26,1,26,5,26,203,8,26,10,26,12,
  	26,206,9,26,1,26,1,26,3,26,210,8,26,1,27,1,27,5,27,214,8,27,10,27,12,
  	27,217,9,27,1,27,1,27,1,28,1,28,5,28,223,8,28,10,28,12,28,226,9,28,1,
  	29,4,29,229,8,29,11,29,12,29,230,1,29,1,29,1,30,1,30,1,30,1,30,5,30,239,
  	8,30,10,30,12,30,242,9,30,1,30,1,30,1,30,1,30,1,30,1,31,1,31,1,31,1,31,
  	5,31,253,8,31,10,31,12,31,256,9,31,1,31,1,31,1,32,1,32,1,240,0,33,1,1,
  	3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,27,14,29,
  	15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,25,51,26,
  	53,27,55,28,57,29,59,30,61,31,63,32,65,33,1,0,7,1,0,48,57,1,0,49,57,1,
  	0,34,34,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,3,0,9,10,
  	13,13,32,32,2,0,10,10,13,13,275,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,
  	7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,
  	0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,
  	0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,
  	1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,
  	0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,
  	0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,1,67,1,0,0,0,3,69,1,0,0,0,5,71,
  	1,0,0,0,7,73,1,0,0,0,9,75,1,0,0,0,11,77,1,0,0,0,13,80,1,0,0,0,15,82,1,
  	0,0,0,17,84,1,0,0,0,19,86,1,0,0,0,21,88,1,0,0,0,23,90,1,0,0,0,25,92,1,
  	0,0,0,27,94,1,0,0,0,29,96,1,0,0,0,31,99,1,0,0,0,33,107,1,0,0,0,35,111,
  	1,0,0,0,37,121,1,0,0,0,39,133,1,0,0,0,41,141,1,0,0,0,43,150,1,0,0,0,45,
  	152,1,0,0,0,47,154,1,0,0,0,49,178,1,0,0,0,51,189,1,0,0,0,53,209,1,0,0,
  	0,55,211,1,0,0,0,57,220,1,0,0,0,59,228,1,0,0,0,61,234,1,0,0,0,63,248,
  	1,0,0,0,65,259,1,0,0,0,67,68,5,40,0,0,68,2,1,0,0,0,69,70,5,58,0,0,70,
  	4,1,0,0,0,71,72,5,41,0,0,72,6,1,0,0,0,73,74,5,59,0,0,74,8,1,0,0,0,75,
  	76,5,38,0,0,76,10,1,0,0,0,77,78,5,45,0,0,78,79,5,62,0,0,79,12,1,0,0,0,
  	80,81,5,44,0,0,81,14,1,0,0,0,82,83,5,43,0,0,83,16,1,0,0,0,84,85,5,45,
  	0,0,85,18,1,0,0,0,86,87,5,42,0,0,87,20,1,0,0,0,88,89,5,47,0,0,89,22,1,
  	0,0,0,90,91,5,37,0,0,91,24,1,0,0,0,92,93,5,60,0,0,93,26,1,0,0,0,94,95,
  	5,62,0,0,95,28,1,0,0,0,96,97,5,58,0,0,97,98,5,58,0,0,98,30,1,0,0,0,99,
  	100,5,99,0,0,100,101,5,111,0,0,101,102,5,110,0,0,102,103,5,99,0,0,103,
  	104,5,101,0,0,104,105,5,112,0,0,105,106,5,116,0,0,106,32,1,0,0,0,107,
  	108,5,102,0,0,108,109,5,117,0,0,109,110,5,110,0,0,110,34,1,0,0,0,111,
  	112,5,110,0,0,112,113,5,97,0,0,113,114,5,109,0,0,114,115,5,101,0,0,115,
  	116,5,115,0,0,116,117,5,112,0,0,117,118,5,97,0,0,118,119,5,99,0,0,119,
  	120,5,101,0,0,120,36,1,0,0,0,121,122,5,100,0,0,122,123,5,101,0,0,123,
  	124,5,115,0,0,124,125,5,99,0,0,125,126,5,114,0,0,126,127,5,105,0,0,127,
  	128,5,112,0,0,128,129,5,116,0,0,129,130,5,105,0,0,130,131,5,111,0,0,131,
  	132,5,110,0,0,132,38,1,0,0,0,133,134,5,103,0,0,134,135,5,101,0,0,135,
  	136,5,110,0,0,136,137,5,101,0,0,137,138,5,114,0,0,138,139,5,105,0,0,139,
  	140,5,99,0,0,140,40,1,0,0,0,141,142,5,114,0,0,142,143,5,101,0,0,143,144,
  	5,113,0,0,144,145,5,117,0,0,145,146,5,105,0,0,146,147,5,114,0,0,147,148,
  	5,101,0,0,148,149,5,115,0,0,149,42,1,0,0,0,150,151,5,123,0,0,151,44,1,
  	0,0,0,152,153,5,125,0,0,153,46,1,0,0,0,154,155,5,46,0,0,155,156,5,46,
  	0,0,156,157,5,46,0,0,157,48,1,0,0,0,158,159,5,48,0,0,159,161,5,46,0,0,
  	160,162,7,0,0,0,161,160,1,0,0,0,162,163,1,0,0,0,163,161,1,0,0,0,163,164,
  	1,0,0,0,164,179,1,0,0,0,165,169,7,1,0,0,166,168,7,0,0,0,167,166,1,0,0,
  	0,168,171,1,0,0,0,169,167,1,0,0,0,169,170,1,0,0,0,170,172,1,0,0,0,171,
  	169,1,0,0,0,172,174,5,46,0,0,173,175,7,0,0,0,174,173,1,0,0,0,175,176,
  	1,0,0,0,176,174,1,0,0,0,176,177,1,0,0,0,177,179,1,0,0,0,178,158,1,0,0,
  	0,178,165,1,0,0,0,179,50,1,0,0,0,180,181,5,116,0,0,181,182,5,114,0,0,
  	182,183,5,117,0,0,183,190,5,101,0,0,184,185,5,102,0,0,185,186,5,97,0,
  	0,186,187,5,108,0,0,187,188,5,115,0,0,188,190,5,101,0,0,189,180,1,0,0,
  	0,189,184,1,0,0,0,190,52,1,0,0,0,191,195,7,1,0,0,192,194,7,0,0,0,193,
  	192,1,0,0,0,194,197,1,0,0,0,195,193,1,0,0,0,195,196,1,0,0,0,196,210,1,
  	0,0,0,197,195,1,0,0,0,198,210,5,48,0,0,199,200,5,45,0,0,200,204,7,1,0,
  	0,201,203,7,0,0,0,202,201,1,0,0,0,203,206,1,0,0,0,204,202,1,0,0,0,204,
  	205,1,0,0,0,205,210,1,0,0,0,206,204,1,0,0,0,207,208,5,45,0,0,208,210,
  	5,48,0,0,209,191,1,0,0,0,209,198,1,0,0,0,209,199,1,0,0,0,209,207,1,0,
  	0,0,210,54,1,0,0,0,211,215,5,34,0,0,212,214,8,2,0,0,213,212,1,0,0,0,214,
  	217,1,0,0,0,215,213,1,0,0,0,215,216,1,0,0,0,216,218,1,0,0,0,217,215,1,
  	0,0,0,218,219,5,34,0,0,219,56,1,0,0,0,220,224,7,3,0,0,221,223,7,4,0,0,
  	222,221,1,0,0,0,223,226,1,0,0,0,224,222,1,0,0,0,224,225,1,0,0,0,225,58,
  	1,0,0,0,226,224,1,0,0,0,227,229,7,5,0,0,228,227,1,0,0,0,229,230,1,0,0,
  	0,230,228,1,0,0,0,230,231,1,0,0,0,231,232,1,0,0,0,232,233,6,29,0,0,233,
  	60,1,0,0,0,234,235,5,47,0,0,235,236,5,42,0,0,236,240,1,0,0,0,237,239,
  	9,0,0,0,238,237,1,0,0,0,239,242,1,0,0,0,240,241,1,0,0,0,240,238,1,0,0,
  	0,241,243,1,0,0,0,242,240,1,0,0,0,243,244,5,42,0,0,244,245,5,47,0,0,245,
  	246,1,0,0,0,246,247,6,30,1,0,247,62,1,0,0,0,248,249,5,47,0,0,249,250,
  	5,47,0,0,250,254,1,0,0,0,251,253,8,6,0,0,252,251,1,0,0,0,253,256,1,0,
  	0,0,254,252,1,0,0,0,254,255,1,0,0,0,255,257,1,0,0,0,256,254,1,0,0,0,257,
  	258,6,31,1,0,258,64,1,0,0,0,259,260,9,0,0,0,260,66,1,0,0,0,14,0,163,169,
  	176,178,189,195,204,209,215,224,230,240,254,2,6,0,0,0,1,0
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
  return "Cong.g4";
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
