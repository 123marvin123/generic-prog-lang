
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
      "NAMESPACE", "DESCRIPTION", "GENERICIMPL", "REQUIRES", "TIME", "SPACE", 
      "LBRACE", "RBRACE", "VARARGS", "REAL", "BOOL", "NUMBER", "STRING", 
      "IDENTIFIER", "WHITESPACE", "COMMENT", "LINE_COMMENT", "OTHER"
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
      "'description'", "'generic'", "'requires'", "'time'", "'space'", "'{'", 
      "'}'", "'...'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "CONCEPT", 
      "FUNCTION", "NAMESPACE", "DESCRIPTION", "GENERICIMPL", "REQUIRES", 
      "TIME", "SPACE", "LBRACE", "RBRACE", "VARARGS", "REAL", "BOOL", "NUMBER", 
      "STRING", "IDENTIFIER", "WHITESPACE", "COMMENT", "LINE_COMMENT", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,35,276,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,1,0,
  	1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,4,1,4,1,5,1,5,1,5,1,6,1,6,1,7,1,7,1,8,1,
  	8,1,9,1,9,1,10,1,10,1,11,1,11,1,12,1,12,1,13,1,13,1,14,1,14,1,14,1,15,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,18,1,18,1,18,1,18,1,18,1,18,1,18,
  	1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,20,
  	1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,21,1,21,1,21,1,21,1,21,1,22,
  	1,22,1,22,1,22,1,22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,1,25,1,25,1,26,
  	1,26,1,26,4,26,177,8,26,11,26,12,26,178,1,26,1,26,5,26,183,8,26,10,26,
  	12,26,186,9,26,1,26,1,26,4,26,190,8,26,11,26,12,26,191,3,26,194,8,26,
  	1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,1,27,3,27,205,8,27,1,28,1,28,
  	5,28,209,8,28,10,28,12,28,212,9,28,1,28,1,28,1,28,1,28,5,28,218,8,28,
  	10,28,12,28,221,9,28,1,28,1,28,3,28,225,8,28,1,29,1,29,5,29,229,8,29,
  	10,29,12,29,232,9,29,1,29,1,29,1,30,1,30,5,30,238,8,30,10,30,12,30,241,
  	9,30,1,31,4,31,244,8,31,11,31,12,31,245,1,31,1,31,1,32,1,32,1,32,1,32,
  	5,32,254,8,32,10,32,12,32,257,9,32,1,32,1,32,1,32,1,32,1,32,1,33,1,33,
  	1,33,1,33,5,33,268,8,33,10,33,12,33,271,9,33,1,33,1,33,1,34,1,34,1,255,
  	0,35,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,9,19,10,21,11,23,12,25,13,
  	27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,21,43,22,45,23,47,24,49,
  	25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,65,33,67,34,69,35,1,0,7,
  	1,0,48,57,1,0,49,57,1,0,34,34,3,0,65,90,95,95,97,122,4,0,48,57,65,90,
  	95,95,97,122,3,0,9,10,13,13,32,32,2,0,10,10,13,13,290,0,1,1,0,0,0,0,3,
  	1,0,0,0,0,5,1,0,0,0,0,7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,
  	0,15,1,0,0,0,0,17,1,0,0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,
  	1,0,0,0,0,27,1,0,0,0,0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,
  	0,0,0,37,1,0,0,0,0,39,1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,
  	0,47,1,0,0,0,0,49,1,0,0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,
  	1,0,0,0,0,59,1,0,0,0,0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,
  	0,0,0,69,1,0,0,0,1,71,1,0,0,0,3,73,1,0,0,0,5,75,1,0,0,0,7,77,1,0,0,0,
  	9,79,1,0,0,0,11,81,1,0,0,0,13,84,1,0,0,0,15,86,1,0,0,0,17,88,1,0,0,0,
  	19,90,1,0,0,0,21,92,1,0,0,0,23,94,1,0,0,0,25,96,1,0,0,0,27,98,1,0,0,0,
  	29,100,1,0,0,0,31,103,1,0,0,0,33,111,1,0,0,0,35,115,1,0,0,0,37,125,1,
  	0,0,0,39,137,1,0,0,0,41,145,1,0,0,0,43,154,1,0,0,0,45,159,1,0,0,0,47,
  	165,1,0,0,0,49,167,1,0,0,0,51,169,1,0,0,0,53,193,1,0,0,0,55,204,1,0,0,
  	0,57,224,1,0,0,0,59,226,1,0,0,0,61,235,1,0,0,0,63,243,1,0,0,0,65,249,
  	1,0,0,0,67,263,1,0,0,0,69,274,1,0,0,0,71,72,5,40,0,0,72,2,1,0,0,0,73,
  	74,5,58,0,0,74,4,1,0,0,0,75,76,5,41,0,0,76,6,1,0,0,0,77,78,5,59,0,0,78,
  	8,1,0,0,0,79,80,5,38,0,0,80,10,1,0,0,0,81,82,5,45,0,0,82,83,5,62,0,0,
  	83,12,1,0,0,0,84,85,5,44,0,0,85,14,1,0,0,0,86,87,5,43,0,0,87,16,1,0,0,
  	0,88,89,5,45,0,0,89,18,1,0,0,0,90,91,5,42,0,0,91,20,1,0,0,0,92,93,5,47,
  	0,0,93,22,1,0,0,0,94,95,5,37,0,0,95,24,1,0,0,0,96,97,5,60,0,0,97,26,1,
  	0,0,0,98,99,5,62,0,0,99,28,1,0,0,0,100,101,5,58,0,0,101,102,5,58,0,0,
  	102,30,1,0,0,0,103,104,5,99,0,0,104,105,5,111,0,0,105,106,5,110,0,0,106,
  	107,5,99,0,0,107,108,5,101,0,0,108,109,5,112,0,0,109,110,5,116,0,0,110,
  	32,1,0,0,0,111,112,5,102,0,0,112,113,5,117,0,0,113,114,5,110,0,0,114,
  	34,1,0,0,0,115,116,5,110,0,0,116,117,5,97,0,0,117,118,5,109,0,0,118,119,
  	5,101,0,0,119,120,5,115,0,0,120,121,5,112,0,0,121,122,5,97,0,0,122,123,
  	5,99,0,0,123,124,5,101,0,0,124,36,1,0,0,0,125,126,5,100,0,0,126,127,5,
  	101,0,0,127,128,5,115,0,0,128,129,5,99,0,0,129,130,5,114,0,0,130,131,
  	5,105,0,0,131,132,5,112,0,0,132,133,5,116,0,0,133,134,5,105,0,0,134,135,
  	5,111,0,0,135,136,5,110,0,0,136,38,1,0,0,0,137,138,5,103,0,0,138,139,
  	5,101,0,0,139,140,5,110,0,0,140,141,5,101,0,0,141,142,5,114,0,0,142,143,
  	5,105,0,0,143,144,5,99,0,0,144,40,1,0,0,0,145,146,5,114,0,0,146,147,5,
  	101,0,0,147,148,5,113,0,0,148,149,5,117,0,0,149,150,5,105,0,0,150,151,
  	5,114,0,0,151,152,5,101,0,0,152,153,5,115,0,0,153,42,1,0,0,0,154,155,
  	5,116,0,0,155,156,5,105,0,0,156,157,5,109,0,0,157,158,5,101,0,0,158,44,
  	1,0,0,0,159,160,5,115,0,0,160,161,5,112,0,0,161,162,5,97,0,0,162,163,
  	5,99,0,0,163,164,5,101,0,0,164,46,1,0,0,0,165,166,5,123,0,0,166,48,1,
  	0,0,0,167,168,5,125,0,0,168,50,1,0,0,0,169,170,5,46,0,0,170,171,5,46,
  	0,0,171,172,5,46,0,0,172,52,1,0,0,0,173,174,5,48,0,0,174,176,5,46,0,0,
  	175,177,7,0,0,0,176,175,1,0,0,0,177,178,1,0,0,0,178,176,1,0,0,0,178,179,
  	1,0,0,0,179,194,1,0,0,0,180,184,7,1,0,0,181,183,7,0,0,0,182,181,1,0,0,
  	0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,187,1,0,0,0,186,
  	184,1,0,0,0,187,189,5,46,0,0,188,190,7,0,0,0,189,188,1,0,0,0,190,191,
  	1,0,0,0,191,189,1,0,0,0,191,192,1,0,0,0,192,194,1,0,0,0,193,173,1,0,0,
  	0,193,180,1,0,0,0,194,54,1,0,0,0,195,196,5,116,0,0,196,197,5,114,0,0,
  	197,198,5,117,0,0,198,205,5,101,0,0,199,200,5,102,0,0,200,201,5,97,0,
  	0,201,202,5,108,0,0,202,203,5,115,0,0,203,205,5,101,0,0,204,195,1,0,0,
  	0,204,199,1,0,0,0,205,56,1,0,0,0,206,210,7,1,0,0,207,209,7,0,0,0,208,
  	207,1,0,0,0,209,212,1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,225,1,
  	0,0,0,212,210,1,0,0,0,213,225,5,48,0,0,214,215,5,45,0,0,215,219,7,1,0,
  	0,216,218,7,0,0,0,217,216,1,0,0,0,218,221,1,0,0,0,219,217,1,0,0,0,219,
  	220,1,0,0,0,220,225,1,0,0,0,221,219,1,0,0,0,222,223,5,45,0,0,223,225,
  	5,48,0,0,224,206,1,0,0,0,224,213,1,0,0,0,224,214,1,0,0,0,224,222,1,0,
  	0,0,225,58,1,0,0,0,226,230,5,34,0,0,227,229,8,2,0,0,228,227,1,0,0,0,229,
  	232,1,0,0,0,230,228,1,0,0,0,230,231,1,0,0,0,231,233,1,0,0,0,232,230,1,
  	0,0,0,233,234,5,34,0,0,234,60,1,0,0,0,235,239,7,3,0,0,236,238,7,4,0,0,
  	237,236,1,0,0,0,238,241,1,0,0,0,239,237,1,0,0,0,239,240,1,0,0,0,240,62,
  	1,0,0,0,241,239,1,0,0,0,242,244,7,5,0,0,243,242,1,0,0,0,244,245,1,0,0,
  	0,245,243,1,0,0,0,245,246,1,0,0,0,246,247,1,0,0,0,247,248,6,31,0,0,248,
  	64,1,0,0,0,249,250,5,47,0,0,250,251,5,42,0,0,251,255,1,0,0,0,252,254,
  	9,0,0,0,253,252,1,0,0,0,254,257,1,0,0,0,255,256,1,0,0,0,255,253,1,0,0,
  	0,256,258,1,0,0,0,257,255,1,0,0,0,258,259,5,42,0,0,259,260,5,47,0,0,260,
  	261,1,0,0,0,261,262,6,32,1,0,262,66,1,0,0,0,263,264,5,47,0,0,264,265,
  	5,47,0,0,265,269,1,0,0,0,266,268,8,6,0,0,267,266,1,0,0,0,268,271,1,0,
  	0,0,269,267,1,0,0,0,269,270,1,0,0,0,270,272,1,0,0,0,271,269,1,0,0,0,272,
  	273,6,33,1,0,273,68,1,0,0,0,274,275,9,0,0,0,275,70,1,0,0,0,14,0,178,184,
  	191,193,204,210,219,224,230,239,245,255,269,2,6,0,0,0,1,0
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
