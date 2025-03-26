
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
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "CONCEPT", "FUNCTION", "NAMESPACE", "DESCRIPTION", 
      "GENERICIMPL", "REQUIRES", "FAMILY", "LBRACE", "RBRACE", "VARARGS", 
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
      "", "'('", "','", "')'", "':'", "';'", "'&'", "'->'", "'+'", "'-'", 
      "'*'", "'/'", "'%'", "'<'", "'>'", "'String'", "'Number'", "'Real'", 
      "'Bool'", "'Void'", "'::'", "'concept'", "'fun'", "'namespace'", "'description'", 
      "'generic'", "'requires'", "'family'", "'{'", "'}'", "'...'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "CONCEPT", "FUNCTION", "NAMESPACE", "DESCRIPTION", 
      "GENERICIMPL", "REQUIRES", "FAMILY", "LBRACE", "RBRACE", "VARARGS", 
      "REAL", "BOOL", "NUMBER", "STRING", "IDENTIFIER", "WHITESPACE", "COMMENT", 
      "LINE_COMMENT", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,39,309,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,
  	7,35,2,36,7,36,2,37,7,37,2,38,7,38,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,1,
  	4,1,4,1,5,1,5,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,9,1,9,1,10,1,10,1,11,1,11,
  	1,12,1,12,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,
  	1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,17,1,17,
  	1,18,1,18,1,18,1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,1,20,1,21,1,21,1,21,1,21,1,22,1,22,1,22,1,22,1,22,1,22,1,22,1,22,
  	1,22,1,22,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,1,23,
  	1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,25,1,25,
  	1,25,1,25,1,25,1,26,1,26,1,26,1,26,1,26,1,26,1,26,1,27,1,27,1,28,1,28,
  	1,29,1,29,1,29,1,29,1,30,1,30,1,30,4,30,210,8,30,11,30,12,30,211,1,30,
  	1,30,5,30,216,8,30,10,30,12,30,219,9,30,1,30,1,30,4,30,223,8,30,11,30,
  	12,30,224,3,30,227,8,30,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,1,31,
  	3,31,238,8,31,1,32,1,32,5,32,242,8,32,10,32,12,32,245,9,32,1,32,1,32,
  	1,32,1,32,5,32,251,8,32,10,32,12,32,254,9,32,1,32,1,32,3,32,258,8,32,
  	1,33,1,33,5,33,262,8,33,10,33,12,33,265,9,33,1,33,1,33,1,34,1,34,5,34,
  	271,8,34,10,34,12,34,274,9,34,1,35,4,35,277,8,35,11,35,12,35,278,1,35,
  	1,35,1,36,1,36,1,36,1,36,5,36,287,8,36,10,36,12,36,290,9,36,1,36,1,36,
  	1,36,1,36,1,36,1,37,1,37,1,37,1,37,5,37,301,8,37,10,37,12,37,304,9,37,
  	1,37,1,37,1,38,1,38,1,288,0,39,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,8,17,
  	9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,20,41,
  	21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,63,32,
  	65,33,67,34,69,35,71,36,73,37,75,38,77,39,1,0,7,1,0,48,57,1,0,49,57,1,
  	0,34,34,3,0,65,90,95,95,97,122,4,0,48,57,65,90,95,95,97,122,3,0,9,10,
  	13,13,32,32,2,0,10,10,13,13,323,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,
  	7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,
  	0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,
  	0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,
  	1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,
  	0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,
  	0,61,1,0,0,0,0,63,1,0,0,0,0,65,1,0,0,0,0,67,1,0,0,0,0,69,1,0,0,0,0,71,
  	1,0,0,0,0,73,1,0,0,0,0,75,1,0,0,0,0,77,1,0,0,0,1,79,1,0,0,0,3,81,1,0,
  	0,0,5,83,1,0,0,0,7,85,1,0,0,0,9,87,1,0,0,0,11,89,1,0,0,0,13,91,1,0,0,
  	0,15,94,1,0,0,0,17,96,1,0,0,0,19,98,1,0,0,0,21,100,1,0,0,0,23,102,1,0,
  	0,0,25,104,1,0,0,0,27,106,1,0,0,0,29,108,1,0,0,0,31,115,1,0,0,0,33,122,
  	1,0,0,0,35,127,1,0,0,0,37,132,1,0,0,0,39,137,1,0,0,0,41,140,1,0,0,0,43,
  	148,1,0,0,0,45,152,1,0,0,0,47,162,1,0,0,0,49,174,1,0,0,0,51,182,1,0,0,
  	0,53,191,1,0,0,0,55,198,1,0,0,0,57,200,1,0,0,0,59,202,1,0,0,0,61,226,
  	1,0,0,0,63,237,1,0,0,0,65,257,1,0,0,0,67,259,1,0,0,0,69,268,1,0,0,0,71,
  	276,1,0,0,0,73,282,1,0,0,0,75,296,1,0,0,0,77,307,1,0,0,0,79,80,5,40,0,
  	0,80,2,1,0,0,0,81,82,5,44,0,0,82,4,1,0,0,0,83,84,5,41,0,0,84,6,1,0,0,
  	0,85,86,5,58,0,0,86,8,1,0,0,0,87,88,5,59,0,0,88,10,1,0,0,0,89,90,5,38,
  	0,0,90,12,1,0,0,0,91,92,5,45,0,0,92,93,5,62,0,0,93,14,1,0,0,0,94,95,5,
  	43,0,0,95,16,1,0,0,0,96,97,5,45,0,0,97,18,1,0,0,0,98,99,5,42,0,0,99,20,
  	1,0,0,0,100,101,5,47,0,0,101,22,1,0,0,0,102,103,5,37,0,0,103,24,1,0,0,
  	0,104,105,5,60,0,0,105,26,1,0,0,0,106,107,5,62,0,0,107,28,1,0,0,0,108,
  	109,5,83,0,0,109,110,5,116,0,0,110,111,5,114,0,0,111,112,5,105,0,0,112,
  	113,5,110,0,0,113,114,5,103,0,0,114,30,1,0,0,0,115,116,5,78,0,0,116,117,
  	5,117,0,0,117,118,5,109,0,0,118,119,5,98,0,0,119,120,5,101,0,0,120,121,
  	5,114,0,0,121,32,1,0,0,0,122,123,5,82,0,0,123,124,5,101,0,0,124,125,5,
  	97,0,0,125,126,5,108,0,0,126,34,1,0,0,0,127,128,5,66,0,0,128,129,5,111,
  	0,0,129,130,5,111,0,0,130,131,5,108,0,0,131,36,1,0,0,0,132,133,5,86,0,
  	0,133,134,5,111,0,0,134,135,5,105,0,0,135,136,5,100,0,0,136,38,1,0,0,
  	0,137,138,5,58,0,0,138,139,5,58,0,0,139,40,1,0,0,0,140,141,5,99,0,0,141,
  	142,5,111,0,0,142,143,5,110,0,0,143,144,5,99,0,0,144,145,5,101,0,0,145,
  	146,5,112,0,0,146,147,5,116,0,0,147,42,1,0,0,0,148,149,5,102,0,0,149,
  	150,5,117,0,0,150,151,5,110,0,0,151,44,1,0,0,0,152,153,5,110,0,0,153,
  	154,5,97,0,0,154,155,5,109,0,0,155,156,5,101,0,0,156,157,5,115,0,0,157,
  	158,5,112,0,0,158,159,5,97,0,0,159,160,5,99,0,0,160,161,5,101,0,0,161,
  	46,1,0,0,0,162,163,5,100,0,0,163,164,5,101,0,0,164,165,5,115,0,0,165,
  	166,5,99,0,0,166,167,5,114,0,0,167,168,5,105,0,0,168,169,5,112,0,0,169,
  	170,5,116,0,0,170,171,5,105,0,0,171,172,5,111,0,0,172,173,5,110,0,0,173,
  	48,1,0,0,0,174,175,5,103,0,0,175,176,5,101,0,0,176,177,5,110,0,0,177,
  	178,5,101,0,0,178,179,5,114,0,0,179,180,5,105,0,0,180,181,5,99,0,0,181,
  	50,1,0,0,0,182,183,5,114,0,0,183,184,5,101,0,0,184,185,5,113,0,0,185,
  	186,5,117,0,0,186,187,5,105,0,0,187,188,5,114,0,0,188,189,5,101,0,0,189,
  	190,5,115,0,0,190,52,1,0,0,0,191,192,5,102,0,0,192,193,5,97,0,0,193,194,
  	5,109,0,0,194,195,5,105,0,0,195,196,5,108,0,0,196,197,5,121,0,0,197,54,
  	1,0,0,0,198,199,5,123,0,0,199,56,1,0,0,0,200,201,5,125,0,0,201,58,1,0,
  	0,0,202,203,5,46,0,0,203,204,5,46,0,0,204,205,5,46,0,0,205,60,1,0,0,0,
  	206,207,5,48,0,0,207,209,5,46,0,0,208,210,7,0,0,0,209,208,1,0,0,0,210,
  	211,1,0,0,0,211,209,1,0,0,0,211,212,1,0,0,0,212,227,1,0,0,0,213,217,7,
  	1,0,0,214,216,7,0,0,0,215,214,1,0,0,0,216,219,1,0,0,0,217,215,1,0,0,0,
  	217,218,1,0,0,0,218,220,1,0,0,0,219,217,1,0,0,0,220,222,5,46,0,0,221,
  	223,7,0,0,0,222,221,1,0,0,0,223,224,1,0,0,0,224,222,1,0,0,0,224,225,1,
  	0,0,0,225,227,1,0,0,0,226,206,1,0,0,0,226,213,1,0,0,0,227,62,1,0,0,0,
  	228,229,5,116,0,0,229,230,5,114,0,0,230,231,5,117,0,0,231,238,5,101,0,
  	0,232,233,5,102,0,0,233,234,5,97,0,0,234,235,5,108,0,0,235,236,5,115,
  	0,0,236,238,5,101,0,0,237,228,1,0,0,0,237,232,1,0,0,0,238,64,1,0,0,0,
  	239,243,7,1,0,0,240,242,7,0,0,0,241,240,1,0,0,0,242,245,1,0,0,0,243,241,
  	1,0,0,0,243,244,1,0,0,0,244,258,1,0,0,0,245,243,1,0,0,0,246,258,5,48,
  	0,0,247,248,5,45,0,0,248,252,7,1,0,0,249,251,7,0,0,0,250,249,1,0,0,0,
  	251,254,1,0,0,0,252,250,1,0,0,0,252,253,1,0,0,0,253,258,1,0,0,0,254,252,
  	1,0,0,0,255,256,5,45,0,0,256,258,5,48,0,0,257,239,1,0,0,0,257,246,1,0,
  	0,0,257,247,1,0,0,0,257,255,1,0,0,0,258,66,1,0,0,0,259,263,5,34,0,0,260,
  	262,8,2,0,0,261,260,1,0,0,0,262,265,1,0,0,0,263,261,1,0,0,0,263,264,1,
  	0,0,0,264,266,1,0,0,0,265,263,1,0,0,0,266,267,5,34,0,0,267,68,1,0,0,0,
  	268,272,7,3,0,0,269,271,7,4,0,0,270,269,1,0,0,0,271,274,1,0,0,0,272,270,
  	1,0,0,0,272,273,1,0,0,0,273,70,1,0,0,0,274,272,1,0,0,0,275,277,7,5,0,
  	0,276,275,1,0,0,0,277,278,1,0,0,0,278,276,1,0,0,0,278,279,1,0,0,0,279,
  	280,1,0,0,0,280,281,6,35,0,0,281,72,1,0,0,0,282,283,5,47,0,0,283,284,
  	5,42,0,0,284,288,1,0,0,0,285,287,9,0,0,0,286,285,1,0,0,0,287,290,1,0,
  	0,0,288,289,1,0,0,0,288,286,1,0,0,0,289,291,1,0,0,0,290,288,1,0,0,0,291,
  	292,5,42,0,0,292,293,5,47,0,0,293,294,1,0,0,0,294,295,6,36,1,0,295,74,
  	1,0,0,0,296,297,5,47,0,0,297,298,5,47,0,0,298,302,1,0,0,0,299,301,8,6,
  	0,0,300,299,1,0,0,0,301,304,1,0,0,0,302,300,1,0,0,0,302,303,1,0,0,0,303,
  	305,1,0,0,0,304,302,1,0,0,0,305,306,6,37,1,0,306,76,1,0,0,0,307,308,9,
  	0,0,0,308,78,1,0,0,0,14,0,211,217,224,226,237,243,252,257,263,272,278,
  	288,302,2,6,0,0,0,1,0
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
