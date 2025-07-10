
#include "CongLexer.h"


// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/CongParser.g4 by ANTLR 4.13.2


#include "CongParserVisitor.h"

#include "CongParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CongParserStaticData final {
  CongParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CongParserStaticData(const CongParserStaticData&) = delete;
  CongParserStaticData(CongParserStaticData&&) = delete;
  CongParserStaticData& operator=(const CongParserStaticData&) = delete;
  CongParserStaticData& operator=(CongParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag congparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CongParserStaticData> congparserParserStaticData = nullptr;

void congparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (congparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(congparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CongParserStaticData>(
    std::vector<std::string>{
      "translationUnit", "stmnt", "conceptDefinitionStmnt", "conceptDefinitionBases", 
      "namespaceStmnt", "functionStmnt", "functionBody", "functionBodyStmnt", 
      "rawTextContent", "element", "parameterList", "genericImplDetail", 
      "requirementDetail", "requirementDetails", "genericImplDetails", "parameter", 
      "expression", "expressionBlock", "placeholderOrQualifiedId", "placeholder", 
      "qualifiedIdentifier", "literal"
    },
    std::vector<std::string>{
      "", "'concept'", "'fun'", "'namespace'", "'let'", "'name'", "'description'", 
      "'generic'", "'requires'", "'time'", "'space'", "'lang'", "'quote'", 
      "'eval'", "'{'", "'}'", "'('", "')'", "':'", "'\\u003F'", "';'", "'&'", 
      "'->'", "','", "'='", "'=='", "'!='", "'+'", "'-'", "'*'", "'/'", 
      "'%'", "'^'", "'<'", "'<='", "'>'", "'>='", "'::'", "", "'_d'"
    },
    std::vector<std::string>{
      "", "CONCEPT", "FUNCTION", "NAMESPACE", "LET", "NAME", "DESCRIPTION", 
      "GENERICIMPL", "REQUIRES", "TIME", "SPACE", "LANG", "QUOTE", "EVAL", 
      "LBRACE", "RBRACE", "LPAREN", "RPAREN", "COLON", "QUESTION_MARK", 
      "SEMI", "AMP", "ARROW", "COMMA", "ASSIGN", "EQUAL", "NOT_EQUAL", "PLUS", 
      "MINUS", "MUL", "DIV", "MOD", "POW", "LT", "LESS_EQUAL", "GT", "GREATER_EQUAL", 
      "DOUBLE_COLON", "OPEN_BINDING", "DYNAMIC_ANNOTATOR", "REAL", "BOOL", 
      "INTEGER", "STRING", "IDENTIFIER", "WHITESPACE", "COMMENT", "LINE_COMMENT", 
      "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,48,327,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,1,0,5,0,46,8,0,10,0,12,0,49,9,0,1,0,1,0,1,1,1,1,1,1,3,1,56,8,1,1,2,
  	1,2,1,2,1,2,1,2,1,2,1,2,3,2,65,8,2,1,2,3,2,68,8,2,1,2,1,2,1,3,1,3,1,3,
  	1,3,5,3,76,8,3,10,3,12,3,79,9,3,1,4,1,4,1,4,1,4,5,4,85,8,4,10,4,12,4,
  	88,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,5,6,101,8,6,10,6,12,
  	6,104,9,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,3,7,124,8,7,1,7,1,7,3,7,128,8,7,1,7,1,7,1,7,1,7,3,7,134,8,
  	7,1,8,5,8,137,8,8,10,8,12,8,140,9,8,1,9,1,9,1,9,1,9,1,9,3,9,147,8,9,1,
  	10,1,10,1,10,1,10,5,10,153,8,10,10,10,12,10,156,9,10,3,10,158,8,10,1,
  	10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,3,11,176,8,11,1,12,1,12,1,12,1,12,1,12,1,12,3,12,184,8,12,1,13,
  	1,13,1,13,1,13,5,13,190,8,13,10,13,12,13,193,9,13,3,13,195,8,13,1,13,
  	1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,5,14,207,8,14,10,14,12,14,
  	210,9,14,3,14,212,8,14,1,14,1,14,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,5,16,245,8,16,10,16,12,16,248,9,
  	16,3,16,250,8,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,3,16,264,8,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,5,16,278,8,16,10,16,12,16,281,9,16,1,17,1,17,1,17,5,17,286,
  	8,17,10,17,12,17,289,9,17,1,17,1,17,1,18,1,18,3,18,295,8,18,1,19,1,19,
  	1,19,1,19,1,20,3,20,302,8,20,1,20,1,20,1,20,5,20,307,8,20,10,20,12,20,
  	310,9,20,1,21,1,21,3,21,314,8,21,1,21,1,21,3,21,318,8,21,1,21,1,21,1,
  	21,3,21,323,8,21,3,21,325,8,21,1,21,0,1,32,22,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,0,3,1,0,14,15,1,0,27,32,2,0,25,26,
  	33,36,350,0,47,1,0,0,0,2,55,1,0,0,0,4,57,1,0,0,0,6,71,1,0,0,0,8,80,1,
  	0,0,0,10,91,1,0,0,0,12,98,1,0,0,0,14,133,1,0,0,0,16,138,1,0,0,0,18,146,
  	1,0,0,0,20,148,1,0,0,0,22,175,1,0,0,0,24,183,1,0,0,0,26,185,1,0,0,0,28,
  	198,1,0,0,0,30,215,1,0,0,0,32,263,1,0,0,0,34,287,1,0,0,0,36,294,1,0,0,
  	0,38,296,1,0,0,0,40,301,1,0,0,0,42,324,1,0,0,0,44,46,3,2,1,0,45,44,1,
  	0,0,0,46,49,1,0,0,0,47,45,1,0,0,0,47,48,1,0,0,0,48,50,1,0,0,0,49,47,1,
  	0,0,0,50,51,5,0,0,1,51,1,1,0,0,0,52,56,3,4,2,0,53,56,3,8,4,0,54,56,3,
  	10,5,0,55,52,1,0,0,0,55,53,1,0,0,0,55,54,1,0,0,0,56,3,1,0,0,0,57,58,5,
  	1,0,0,58,64,5,44,0,0,59,60,5,16,0,0,60,61,5,6,0,0,61,62,5,18,0,0,62,63,
  	5,43,0,0,63,65,5,17,0,0,64,59,1,0,0,0,64,65,1,0,0,0,65,67,1,0,0,0,66,
  	68,3,6,3,0,67,66,1,0,0,0,67,68,1,0,0,0,68,69,1,0,0,0,69,70,5,20,0,0,70,
  	5,1,0,0,0,71,72,5,18,0,0,72,77,3,40,20,0,73,74,5,21,0,0,74,76,3,40,20,
  	0,75,73,1,0,0,0,76,79,1,0,0,0,77,75,1,0,0,0,77,78,1,0,0,0,78,7,1,0,0,
  	0,79,77,1,0,0,0,80,81,5,3,0,0,81,82,5,44,0,0,82,86,5,14,0,0,83,85,3,2,
  	1,0,84,83,1,0,0,0,85,88,1,0,0,0,86,84,1,0,0,0,86,87,1,0,0,0,87,89,1,0,
  	0,0,88,86,1,0,0,0,89,90,5,15,0,0,90,9,1,0,0,0,91,92,5,2,0,0,92,93,5,44,
  	0,0,93,94,3,20,10,0,94,95,5,22,0,0,95,96,3,40,20,0,96,97,3,12,6,0,97,
  	11,1,0,0,0,98,102,5,14,0,0,99,101,3,14,7,0,100,99,1,0,0,0,101,104,1,0,
  	0,0,102,100,1,0,0,0,102,103,1,0,0,0,103,105,1,0,0,0,104,102,1,0,0,0,105,
  	106,5,15,0,0,106,13,1,0,0,0,107,108,5,6,0,0,108,109,5,14,0,0,109,110,
  	3,42,21,0,110,111,5,15,0,0,111,134,1,0,0,0,112,113,5,7,0,0,113,123,3,
  	28,14,0,114,115,4,7,0,1,115,116,5,14,0,0,116,117,3,16,8,0,117,118,5,15,
  	0,0,118,124,1,0,0,0,119,120,5,14,0,0,120,121,3,32,16,0,121,122,5,15,0,
  	0,122,124,1,0,0,0,123,114,1,0,0,0,123,119,1,0,0,0,124,134,1,0,0,0,125,
  	127,5,8,0,0,126,128,3,26,13,0,127,126,1,0,0,0,127,128,1,0,0,0,128,129,
  	1,0,0,0,129,130,5,14,0,0,130,131,3,32,16,0,131,132,5,15,0,0,132,134,1,
  	0,0,0,133,107,1,0,0,0,133,112,1,0,0,0,133,125,1,0,0,0,134,15,1,0,0,0,
  	135,137,3,18,9,0,136,135,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,138,
  	139,1,0,0,0,139,17,1,0,0,0,140,138,1,0,0,0,141,142,5,14,0,0,142,143,3,
  	16,8,0,143,144,5,15,0,0,144,147,1,0,0,0,145,147,8,0,0,0,146,141,1,0,0,
  	0,146,145,1,0,0,0,147,19,1,0,0,0,148,157,5,16,0,0,149,154,3,30,15,0,150,
  	151,5,23,0,0,151,153,3,30,15,0,152,150,1,0,0,0,153,156,1,0,0,0,154,152,
  	1,0,0,0,154,155,1,0,0,0,155,158,1,0,0,0,156,154,1,0,0,0,157,149,1,0,0,
  	0,157,158,1,0,0,0,158,159,1,0,0,0,159,160,5,17,0,0,160,21,1,0,0,0,161,
  	162,5,9,0,0,162,163,5,18,0,0,163,164,3,32,16,0,164,165,6,11,-1,0,165,
  	176,1,0,0,0,166,167,5,10,0,0,167,168,5,18,0,0,168,169,3,32,16,0,169,170,
  	6,11,-1,0,170,176,1,0,0,0,171,172,5,11,0,0,172,173,5,18,0,0,173,174,5,
  	43,0,0,174,176,6,11,-1,0,175,161,1,0,0,0,175,166,1,0,0,0,175,171,1,0,
  	0,0,176,23,1,0,0,0,177,178,5,5,0,0,178,179,5,18,0,0,179,184,5,43,0,0,
  	180,181,5,6,0,0,181,182,5,18,0,0,182,184,5,43,0,0,183,177,1,0,0,0,183,
  	180,1,0,0,0,184,25,1,0,0,0,185,194,5,16,0,0,186,191,3,24,12,0,187,188,
  	5,23,0,0,188,190,3,24,12,0,189,187,1,0,0,0,190,193,1,0,0,0,191,189,1,
  	0,0,0,191,192,1,0,0,0,192,195,1,0,0,0,193,191,1,0,0,0,194,186,1,0,0,0,
  	194,195,1,0,0,0,195,196,1,0,0,0,196,197,5,17,0,0,197,27,1,0,0,0,198,199,
  	6,14,-1,0,199,211,5,16,0,0,200,201,3,22,11,0,201,208,6,14,-1,0,202,203,
  	5,23,0,0,203,204,3,22,11,0,204,205,6,14,-1,0,205,207,1,0,0,0,206,202,
  	1,0,0,0,207,210,1,0,0,0,208,206,1,0,0,0,208,209,1,0,0,0,209,212,1,0,0,
  	0,210,208,1,0,0,0,211,200,1,0,0,0,211,212,1,0,0,0,212,213,1,0,0,0,213,
  	214,5,17,0,0,214,29,1,0,0,0,215,216,5,44,0,0,216,217,5,18,0,0,217,218,
  	3,36,18,0,218,31,1,0,0,0,219,220,6,16,-1,0,220,221,5,16,0,0,221,222,3,
  	32,16,0,222,223,5,17,0,0,223,264,1,0,0,0,224,264,3,42,21,0,225,226,5,
  	12,0,0,226,227,5,16,0,0,227,228,3,32,16,0,228,229,5,17,0,0,229,264,1,
  	0,0,0,230,231,5,13,0,0,231,232,5,16,0,0,232,233,3,32,16,0,233,234,5,17,
  	0,0,234,264,1,0,0,0,235,236,5,8,0,0,236,237,5,16,0,0,237,238,5,43,0,0,
  	238,264,5,17,0,0,239,240,3,40,20,0,240,249,5,16,0,0,241,246,3,32,16,0,
  	242,243,5,23,0,0,243,245,3,32,16,0,244,242,1,0,0,0,245,248,1,0,0,0,246,
  	244,1,0,0,0,246,247,1,0,0,0,247,250,1,0,0,0,248,246,1,0,0,0,249,241,1,
  	0,0,0,249,250,1,0,0,0,250,251,1,0,0,0,251,252,5,17,0,0,252,264,1,0,0,
  	0,253,264,3,40,20,0,254,255,5,4,0,0,255,256,5,44,0,0,256,257,5,24,0,0,
  	257,258,3,32,16,0,258,259,5,14,0,0,259,260,3,34,17,0,260,261,5,15,0,0,
  	261,264,1,0,0,0,262,264,5,38,0,0,263,219,1,0,0,0,263,224,1,0,0,0,263,
  	225,1,0,0,0,263,230,1,0,0,0,263,235,1,0,0,0,263,239,1,0,0,0,263,253,1,
  	0,0,0,263,254,1,0,0,0,263,262,1,0,0,0,264,279,1,0,0,0,265,266,10,11,0,
  	0,266,267,7,1,0,0,267,278,3,32,16,12,268,269,10,10,0,0,269,270,7,2,0,
  	0,270,278,3,32,16,11,271,272,10,8,0,0,272,273,5,19,0,0,273,274,3,32,16,
  	0,274,275,5,18,0,0,275,276,3,32,16,9,276,278,1,0,0,0,277,265,1,0,0,0,
  	277,268,1,0,0,0,277,271,1,0,0,0,278,281,1,0,0,0,279,277,1,0,0,0,279,280,
  	1,0,0,0,280,33,1,0,0,0,281,279,1,0,0,0,282,283,3,32,16,0,283,284,5,20,
  	0,0,284,286,1,0,0,0,285,282,1,0,0,0,286,289,1,0,0,0,287,285,1,0,0,0,287,
  	288,1,0,0,0,288,290,1,0,0,0,289,287,1,0,0,0,290,291,3,32,16,0,291,35,
  	1,0,0,0,292,295,3,40,20,0,293,295,3,38,19,0,294,292,1,0,0,0,294,293,1,
  	0,0,0,295,37,1,0,0,0,296,297,5,33,0,0,297,298,5,44,0,0,298,299,5,35,0,
  	0,299,39,1,0,0,0,300,302,5,37,0,0,301,300,1,0,0,0,301,302,1,0,0,0,302,
  	303,1,0,0,0,303,308,5,44,0,0,304,305,5,37,0,0,305,307,5,44,0,0,306,304,
  	1,0,0,0,307,310,1,0,0,0,308,306,1,0,0,0,308,309,1,0,0,0,309,41,1,0,0,
  	0,310,308,1,0,0,0,311,313,5,40,0,0,312,314,5,39,0,0,313,312,1,0,0,0,313,
  	314,1,0,0,0,314,325,1,0,0,0,315,317,5,42,0,0,316,318,5,39,0,0,317,316,
  	1,0,0,0,317,318,1,0,0,0,318,325,1,0,0,0,319,325,5,43,0,0,320,322,5,41,
  	0,0,321,323,5,39,0,0,322,321,1,0,0,0,322,323,1,0,0,0,323,325,1,0,0,0,
  	324,311,1,0,0,0,324,315,1,0,0,0,324,319,1,0,0,0,324,320,1,0,0,0,325,43,
  	1,0,0,0,33,47,55,64,67,77,86,102,123,127,133,138,146,154,157,175,183,
  	191,194,208,211,246,249,263,277,279,287,294,301,308,313,317,322,324
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  congparserParserStaticData = std::move(staticData);
}

}

CongParser::CongParser(TokenStream *input) : CongParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CongParser::CongParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CongParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *congparserParserStaticData->atn, congparserParserStaticData->decisionToDFA, congparserParserStaticData->sharedContextCache, options);
}

CongParser::~CongParser() {
  delete _interpreter;
}

const atn::ATN& CongParser::getATN() const {
  return *congparserParserStaticData->atn;
}

std::string CongParser::getGrammarFileName() const {
  return "CongParser.g4";
}

const std::vector<std::string>& CongParser::getRuleNames() const {
  return congparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& CongParser::getVocabulary() const {
  return congparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CongParser::getSerializedATN() const {
  return congparserParserStaticData->serializedATN;
}


//----------------- TranslationUnitContext ------------------------------------------------------------------

CongParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::TranslationUnitContext::EOF() {
  return getToken(CongParser::EOF, 0);
}

std::vector<CongParser::StmntContext *> CongParser::TranslationUnitContext::stmnt() {
  return getRuleContexts<CongParser::StmntContext>();
}

CongParser::StmntContext* CongParser::TranslationUnitContext::stmnt(size_t i) {
  return getRuleContext<CongParser::StmntContext>(i);
}


size_t CongParser::TranslationUnitContext::getRuleIndex() const {
  return CongParser::RuleTranslationUnit;
}


std::any CongParser::TranslationUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitTranslationUnit(this);
  else
    return visitor->visitChildren(this);
}

CongParser::TranslationUnitContext* CongParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, CongParser::RuleTranslationUnit);
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
    setState(47);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 14) != 0)) {
      setState(44);
      stmnt();
      setState(49);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(50);
    match(CongParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmntContext ------------------------------------------------------------------

CongParser::StmntContext::StmntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CongParser::ConceptDefinitionStmntContext* CongParser::StmntContext::conceptDefinitionStmnt() {
  return getRuleContext<CongParser::ConceptDefinitionStmntContext>(0);
}

CongParser::NamespaceStmntContext* CongParser::StmntContext::namespaceStmnt() {
  return getRuleContext<CongParser::NamespaceStmntContext>(0);
}

CongParser::FunctionStmntContext* CongParser::StmntContext::functionStmnt() {
  return getRuleContext<CongParser::FunctionStmntContext>(0);
}


size_t CongParser::StmntContext::getRuleIndex() const {
  return CongParser::RuleStmnt;
}


std::any CongParser::StmntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitStmnt(this);
  else
    return visitor->visitChildren(this);
}

CongParser::StmntContext* CongParser::stmnt() {
  StmntContext *_localctx = _tracker.createInstance<StmntContext>(_ctx, getState());
  enterRule(_localctx, 2, CongParser::RuleStmnt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(55);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::CONCEPT: {
        enterOuterAlt(_localctx, 1);
        setState(52);
        conceptDefinitionStmnt();
        break;
      }

      case CongParser::NAMESPACE: {
        enterOuterAlt(_localctx, 2);
        setState(53);
        namespaceStmnt();
        break;
      }

      case CongParser::FUNCTION: {
        enterOuterAlt(_localctx, 3);
        setState(54);
        functionStmnt();
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

//----------------- ConceptDefinitionStmntContext ------------------------------------------------------------------

CongParser::ConceptDefinitionStmntContext::ConceptDefinitionStmntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::CONCEPT() {
  return getToken(CongParser::CONCEPT, 0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::SEMI() {
  return getToken(CongParser::SEMI, 0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::DESCRIPTION() {
  return getToken(CongParser::DESCRIPTION, 0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::COLON() {
  return getToken(CongParser::COLON, 0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

CongParser::ConceptDefinitionBasesContext* CongParser::ConceptDefinitionStmntContext::conceptDefinitionBases() {
  return getRuleContext<CongParser::ConceptDefinitionBasesContext>(0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::STRING() {
  return getToken(CongParser::STRING, 0);
}


size_t CongParser::ConceptDefinitionStmntContext::getRuleIndex() const {
  return CongParser::RuleConceptDefinitionStmnt;
}


std::any CongParser::ConceptDefinitionStmntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitConceptDefinitionStmnt(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ConceptDefinitionStmntContext* CongParser::conceptDefinitionStmnt() {
  ConceptDefinitionStmntContext *_localctx = _tracker.createInstance<ConceptDefinitionStmntContext>(_ctx, getState());
  enterRule(_localctx, 4, CongParser::RuleConceptDefinitionStmnt);
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
    setState(57);
    match(CongParser::CONCEPT);
    setState(58);
    antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(64);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::LPAREN) {
      setState(59);
      match(CongParser::LPAREN);
      setState(60);
      match(CongParser::DESCRIPTION);
      setState(61);
      match(CongParser::COLON);
      setState(62);
      antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->desc = match(CongParser::STRING);
      setState(63);
      match(CongParser::RPAREN);
    }
    setState(67);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::COLON) {
      setState(66);
      conceptDefinitionBases();
    }
    setState(69);
    match(CongParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConceptDefinitionBasesContext ------------------------------------------------------------------

CongParser::ConceptDefinitionBasesContext::ConceptDefinitionBasesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::ConceptDefinitionBasesContext::COLON() {
  return getToken(CongParser::COLON, 0);
}

std::vector<CongParser::QualifiedIdentifierContext *> CongParser::ConceptDefinitionBasesContext::qualifiedIdentifier() {
  return getRuleContexts<CongParser::QualifiedIdentifierContext>();
}

CongParser::QualifiedIdentifierContext* CongParser::ConceptDefinitionBasesContext::qualifiedIdentifier(size_t i) {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(i);
}

std::vector<tree::TerminalNode *> CongParser::ConceptDefinitionBasesContext::AMP() {
  return getTokens(CongParser::AMP);
}

tree::TerminalNode* CongParser::ConceptDefinitionBasesContext::AMP(size_t i) {
  return getToken(CongParser::AMP, i);
}


size_t CongParser::ConceptDefinitionBasesContext::getRuleIndex() const {
  return CongParser::RuleConceptDefinitionBases;
}


std::any CongParser::ConceptDefinitionBasesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitConceptDefinitionBases(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ConceptDefinitionBasesContext* CongParser::conceptDefinitionBases() {
  ConceptDefinitionBasesContext *_localctx = _tracker.createInstance<ConceptDefinitionBasesContext>(_ctx, getState());
  enterRule(_localctx, 6, CongParser::RuleConceptDefinitionBases);
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
    setState(71);
    match(CongParser::COLON);
    setState(72);
    qualifiedIdentifier();
    setState(77);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::AMP) {
      setState(73);
      match(CongParser::AMP);
      setState(74);
      qualifiedIdentifier();
      setState(79);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespaceStmntContext ------------------------------------------------------------------

CongParser::NamespaceStmntContext::NamespaceStmntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::NamespaceStmntContext::NAMESPACE() {
  return getToken(CongParser::NAMESPACE, 0);
}

tree::TerminalNode* CongParser::NamespaceStmntContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

tree::TerminalNode* CongParser::NamespaceStmntContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

tree::TerminalNode* CongParser::NamespaceStmntContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

std::vector<CongParser::StmntContext *> CongParser::NamespaceStmntContext::stmnt() {
  return getRuleContexts<CongParser::StmntContext>();
}

CongParser::StmntContext* CongParser::NamespaceStmntContext::stmnt(size_t i) {
  return getRuleContext<CongParser::StmntContext>(i);
}


size_t CongParser::NamespaceStmntContext::getRuleIndex() const {
  return CongParser::RuleNamespaceStmnt;
}


std::any CongParser::NamespaceStmntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitNamespaceStmnt(this);
  else
    return visitor->visitChildren(this);
}

CongParser::NamespaceStmntContext* CongParser::namespaceStmnt() {
  NamespaceStmntContext *_localctx = _tracker.createInstance<NamespaceStmntContext>(_ctx, getState());
  enterRule(_localctx, 8, CongParser::RuleNamespaceStmnt);
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
    setState(80);
    match(CongParser::NAMESPACE);
    setState(81);
    antlrcpp::downCast<NamespaceStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(82);
    match(CongParser::LBRACE);
    setState(86);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 14) != 0)) {
      setState(83);
      stmnt();
      setState(88);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(89);
    match(CongParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionStmntContext ------------------------------------------------------------------

CongParser::FunctionStmntContext::FunctionStmntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::FunctionStmntContext::FUNCTION() {
  return getToken(CongParser::FUNCTION, 0);
}

CongParser::ParameterListContext* CongParser::FunctionStmntContext::parameterList() {
  return getRuleContext<CongParser::ParameterListContext>(0);
}

tree::TerminalNode* CongParser::FunctionStmntContext::ARROW() {
  return getToken(CongParser::ARROW, 0);
}

CongParser::FunctionBodyContext* CongParser::FunctionStmntContext::functionBody() {
  return getRuleContext<CongParser::FunctionBodyContext>(0);
}

tree::TerminalNode* CongParser::FunctionStmntContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

CongParser::QualifiedIdentifierContext* CongParser::FunctionStmntContext::qualifiedIdentifier() {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(0);
}


size_t CongParser::FunctionStmntContext::getRuleIndex() const {
  return CongParser::RuleFunctionStmnt;
}


std::any CongParser::FunctionStmntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitFunctionStmnt(this);
  else
    return visitor->visitChildren(this);
}

CongParser::FunctionStmntContext* CongParser::functionStmnt() {
  FunctionStmntContext *_localctx = _tracker.createInstance<FunctionStmntContext>(_ctx, getState());
  enterRule(_localctx, 10, CongParser::RuleFunctionStmnt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(91);
    match(CongParser::FUNCTION);
    setState(92);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(93);
    parameterList();
    setState(94);
    match(CongParser::ARROW);
    setState(95);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->type = qualifiedIdentifier();
    setState(96);
    functionBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionBodyContext ------------------------------------------------------------------

CongParser::FunctionBodyContext::FunctionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::FunctionBodyContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

tree::TerminalNode* CongParser::FunctionBodyContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

std::vector<CongParser::FunctionBodyStmntContext *> CongParser::FunctionBodyContext::functionBodyStmnt() {
  return getRuleContexts<CongParser::FunctionBodyStmntContext>();
}

CongParser::FunctionBodyStmntContext* CongParser::FunctionBodyContext::functionBodyStmnt(size_t i) {
  return getRuleContext<CongParser::FunctionBodyStmntContext>(i);
}


size_t CongParser::FunctionBodyContext::getRuleIndex() const {
  return CongParser::RuleFunctionBody;
}


std::any CongParser::FunctionBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitFunctionBody(this);
  else
    return visitor->visitChildren(this);
}

CongParser::FunctionBodyContext* CongParser::functionBody() {
  FunctionBodyContext *_localctx = _tracker.createInstance<FunctionBodyContext>(_ctx, getState());
  enterRule(_localctx, 12, CongParser::RuleFunctionBody);
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
    setState(98);
    match(CongParser::LBRACE);
    setState(102);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 448) != 0)) {
      setState(99);
      functionBodyStmnt();
      setState(104);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(105);
    match(CongParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionBodyStmntContext ------------------------------------------------------------------

CongParser::FunctionBodyStmntContext::FunctionBodyStmntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CongParser::FunctionBodyStmntContext::getRuleIndex() const {
  return CongParser::RuleFunctionBodyStmnt;
}

void CongParser::FunctionBodyStmntContext::copyFrom(FunctionBodyStmntContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FunctionGenericImplContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::FunctionGenericImplContext::GENERICIMPL() {
  return getToken(CongParser::GENERICIMPL, 0);
}

tree::TerminalNode* CongParser::FunctionGenericImplContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

tree::TerminalNode* CongParser::FunctionGenericImplContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

CongParser::GenericImplDetailsContext* CongParser::FunctionGenericImplContext::genericImplDetails() {
  return getRuleContext<CongParser::GenericImplDetailsContext>(0);
}

CongParser::RawTextContentContext* CongParser::FunctionGenericImplContext::rawTextContent() {
  return getRuleContext<CongParser::RawTextContentContext>(0);
}

CongParser::ExpressionContext* CongParser::FunctionGenericImplContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

CongParser::FunctionGenericImplContext::FunctionGenericImplContext(FunctionBodyStmntContext *ctx) { copyFrom(ctx); }


std::any CongParser::FunctionGenericImplContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitFunctionGenericImpl(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionExpRequiresContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::FunctionExpRequiresContext::REQUIRES() {
  return getToken(CongParser::REQUIRES, 0);
}

tree::TerminalNode* CongParser::FunctionExpRequiresContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

CongParser::ExpressionContext* CongParser::FunctionExpRequiresContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

tree::TerminalNode* CongParser::FunctionExpRequiresContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

CongParser::RequirementDetailsContext* CongParser::FunctionExpRequiresContext::requirementDetails() {
  return getRuleContext<CongParser::RequirementDetailsContext>(0);
}

CongParser::FunctionExpRequiresContext::FunctionExpRequiresContext(FunctionBodyStmntContext *ctx) { copyFrom(ctx); }


std::any CongParser::FunctionExpRequiresContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitFunctionExpRequires(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionDescriptionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::FunctionDescriptionContext::DESCRIPTION() {
  return getToken(CongParser::DESCRIPTION, 0);
}

tree::TerminalNode* CongParser::FunctionDescriptionContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

CongParser::LiteralContext* CongParser::FunctionDescriptionContext::literal() {
  return getRuleContext<CongParser::LiteralContext>(0);
}

tree::TerminalNode* CongParser::FunctionDescriptionContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

CongParser::FunctionDescriptionContext::FunctionDescriptionContext(FunctionBodyStmntContext *ctx) { copyFrom(ctx); }


std::any CongParser::FunctionDescriptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDescription(this);
  else
    return visitor->visitChildren(this);
}
CongParser::FunctionBodyStmntContext* CongParser::functionBodyStmnt() {
  FunctionBodyStmntContext *_localctx = _tracker.createInstance<FunctionBodyStmntContext>(_ctx, getState());
  enterRule(_localctx, 14, CongParser::RuleFunctionBodyStmnt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(133);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::DESCRIPTION: {
        _localctx = _tracker.createInstance<CongParser::FunctionDescriptionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(107);
        match(CongParser::DESCRIPTION);
        setState(108);
        match(CongParser::LBRACE);
        setState(109);
        literal();
        setState(110);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::GENERICIMPL: {
        _localctx = _tracker.createInstance<CongParser::FunctionGenericImplContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(112);
        match(CongParser::GENERICIMPL);

        setState(113);
        antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->g = genericImplDetails();
        setState(123);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          setState(114);

          if (!( antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->g->hasLangArg )) throw FailedPredicateException(this, " $g.hasLangArg ");
          setState(115);
          match(CongParser::LBRACE);
          setState(116);
          antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->body_native = rawTextContent();
          setState(117);
          match(CongParser::RBRACE);
          break;
        }

        case 2: {
          setState(119);
          match(CongParser::LBRACE);
          setState(120);
          antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->body_expr = expression(0);
          setState(121);
          match(CongParser::RBRACE);
          break;
        }

        default:
          break;
        }
        break;
      }

      case CongParser::REQUIRES: {
        _localctx = _tracker.createInstance<CongParser::FunctionExpRequiresContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(125);
        match(CongParser::REQUIRES);
        setState(127);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CongParser::LPAREN) {
          setState(126);
          antlrcpp::downCast<FunctionExpRequiresContext *>(_localctx)->details = requirementDetails();
        }
        setState(129);
        match(CongParser::LBRACE);
        setState(130);
        expression(0);
        setState(131);
        match(CongParser::RBRACE);
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

//----------------- RawTextContentContext ------------------------------------------------------------------

CongParser::RawTextContentContext::RawTextContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CongParser::ElementContext *> CongParser::RawTextContentContext::element() {
  return getRuleContexts<CongParser::ElementContext>();
}

CongParser::ElementContext* CongParser::RawTextContentContext::element(size_t i) {
  return getRuleContext<CongParser::ElementContext>(i);
}


size_t CongParser::RawTextContentContext::getRuleIndex() const {
  return CongParser::RuleRawTextContent;
}


std::any CongParser::RawTextContentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitRawTextContent(this);
  else
    return visitor->visitChildren(this);
}

CongParser::RawTextContentContext* CongParser::rawTextContent() {
  RawTextContentContext *_localctx = _tracker.createInstance<RawTextContentContext>(_ctx, getState());
  enterRule(_localctx, 16, CongParser::RuleRawTextContent);
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
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 562949953388542) != 0)) {
      setState(135);
      element();
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContext ------------------------------------------------------------------

CongParser::ElementContext::ElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::ElementContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

CongParser::RawTextContentContext* CongParser::ElementContext::rawTextContent() {
  return getRuleContext<CongParser::RawTextContentContext>(0);
}

tree::TerminalNode* CongParser::ElementContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}


size_t CongParser::ElementContext::getRuleIndex() const {
  return CongParser::RuleElement;
}


std::any CongParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ElementContext* CongParser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 18, CongParser::RuleElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(146);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::LBRACE: {
        enterOuterAlt(_localctx, 1);
        setState(141);
        match(CongParser::LBRACE);
        setState(142);
        rawTextContent();
        setState(143);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::CONCEPT:
      case CongParser::FUNCTION:
      case CongParser::NAMESPACE:
      case CongParser::LET:
      case CongParser::NAME:
      case CongParser::DESCRIPTION:
      case CongParser::GENERICIMPL:
      case CongParser::REQUIRES:
      case CongParser::TIME:
      case CongParser::SPACE:
      case CongParser::LANG:
      case CongParser::QUOTE:
      case CongParser::EVAL:
      case CongParser::LPAREN:
      case CongParser::RPAREN:
      case CongParser::COLON:
      case CongParser::QUESTION_MARK:
      case CongParser::SEMI:
      case CongParser::AMP:
      case CongParser::ARROW:
      case CongParser::COMMA:
      case CongParser::ASSIGN:
      case CongParser::EQUAL:
      case CongParser::NOT_EQUAL:
      case CongParser::PLUS:
      case CongParser::MINUS:
      case CongParser::MUL:
      case CongParser::DIV:
      case CongParser::MOD:
      case CongParser::POW:
      case CongParser::LT:
      case CongParser::LESS_EQUAL:
      case CongParser::GT:
      case CongParser::GREATER_EQUAL:
      case CongParser::DOUBLE_COLON:
      case CongParser::OPEN_BINDING:
      case CongParser::DYNAMIC_ANNOTATOR:
      case CongParser::REAL:
      case CongParser::BOOL:
      case CongParser::INTEGER:
      case CongParser::STRING:
      case CongParser::IDENTIFIER:
      case CongParser::WHITESPACE:
      case CongParser::COMMENT:
      case CongParser::LINE_COMMENT:
      case CongParser::OTHER: {
        enterOuterAlt(_localctx, 2);
        setState(145);
        _la = _input->LA(1);
        if (_la == 0 || _la == Token::EOF || (_la == CongParser::LBRACE

        || _la == CongParser::RBRACE)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
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

//----------------- ParameterListContext ------------------------------------------------------------------

CongParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::ParameterListContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

tree::TerminalNode* CongParser::ParameterListContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

std::vector<CongParser::ParameterContext *> CongParser::ParameterListContext::parameter() {
  return getRuleContexts<CongParser::ParameterContext>();
}

CongParser::ParameterContext* CongParser::ParameterListContext::parameter(size_t i) {
  return getRuleContext<CongParser::ParameterContext>(i);
}

std::vector<tree::TerminalNode *> CongParser::ParameterListContext::COMMA() {
  return getTokens(CongParser::COMMA);
}

tree::TerminalNode* CongParser::ParameterListContext::COMMA(size_t i) {
  return getToken(CongParser::COMMA, i);
}


size_t CongParser::ParameterListContext::getRuleIndex() const {
  return CongParser::RuleParameterList;
}


std::any CongParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ParameterListContext* CongParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 20, CongParser::RuleParameterList);
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
    setState(148);
    match(CongParser::LPAREN);
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::IDENTIFIER) {
      setState(149);
      parameter();
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::COMMA) {
        setState(150);
        match(CongParser::COMMA);
        setState(151);
        parameter();
        setState(156);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(159);
    match(CongParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericImplDetailContext ------------------------------------------------------------------

CongParser::GenericImplDetailContext::GenericImplDetailContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::GenericImplDetailContext::TIME() {
  return getToken(CongParser::TIME, 0);
}

tree::TerminalNode* CongParser::GenericImplDetailContext::COLON() {
  return getToken(CongParser::COLON, 0);
}

CongParser::ExpressionContext* CongParser::GenericImplDetailContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

tree::TerminalNode* CongParser::GenericImplDetailContext::SPACE() {
  return getToken(CongParser::SPACE, 0);
}

tree::TerminalNode* CongParser::GenericImplDetailContext::LANG() {
  return getToken(CongParser::LANG, 0);
}

tree::TerminalNode* CongParser::GenericImplDetailContext::STRING() {
  return getToken(CongParser::STRING, 0);
}


size_t CongParser::GenericImplDetailContext::getRuleIndex() const {
  return CongParser::RuleGenericImplDetail;
}


std::any CongParser::GenericImplDetailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitGenericImplDetail(this);
  else
    return visitor->visitChildren(this);
}

CongParser::GenericImplDetailContext* CongParser::genericImplDetail() {
  GenericImplDetailContext *_localctx = _tracker.createInstance<GenericImplDetailContext>(_ctx, getState());
  enterRule(_localctx, 22, CongParser::RuleGenericImplDetail);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(175);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::TIME: {
        enterOuterAlt(_localctx, 1);
        setState(161);
        match(CongParser::TIME);
        setState(162);
        match(CongParser::COLON);
        setState(163);
        expression(0);
         antlrcpp::downCast<GenericImplDetailContext *>(_localctx)->isLangAttr =  false; 
        break;
      }

      case CongParser::SPACE: {
        enterOuterAlt(_localctx, 2);
        setState(166);
        match(CongParser::SPACE);
        setState(167);
        match(CongParser::COLON);
        setState(168);
        expression(0);
         antlrcpp::downCast<GenericImplDetailContext *>(_localctx)->isLangAttr =  false; 
        break;
      }

      case CongParser::LANG: {
        enterOuterAlt(_localctx, 3);
        setState(171);
        match(CongParser::LANG);
        setState(172);
        match(CongParser::COLON);
        setState(173);
        antlrcpp::downCast<GenericImplDetailContext *>(_localctx)->targetLang = match(CongParser::STRING);
         antlrcpp::downCast<GenericImplDetailContext *>(_localctx)->isLangAttr =  true; 
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

//----------------- RequirementDetailContext ------------------------------------------------------------------

CongParser::RequirementDetailContext::RequirementDetailContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::RequirementDetailContext::NAME() {
  return getToken(CongParser::NAME, 0);
}

tree::TerminalNode* CongParser::RequirementDetailContext::COLON() {
  return getToken(CongParser::COLON, 0);
}

tree::TerminalNode* CongParser::RequirementDetailContext::STRING() {
  return getToken(CongParser::STRING, 0);
}

tree::TerminalNode* CongParser::RequirementDetailContext::DESCRIPTION() {
  return getToken(CongParser::DESCRIPTION, 0);
}


size_t CongParser::RequirementDetailContext::getRuleIndex() const {
  return CongParser::RuleRequirementDetail;
}


std::any CongParser::RequirementDetailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitRequirementDetail(this);
  else
    return visitor->visitChildren(this);
}

CongParser::RequirementDetailContext* CongParser::requirementDetail() {
  RequirementDetailContext *_localctx = _tracker.createInstance<RequirementDetailContext>(_ctx, getState());
  enterRule(_localctx, 24, CongParser::RuleRequirementDetail);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(183);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::NAME: {
        enterOuterAlt(_localctx, 1);
        setState(177);
        match(CongParser::NAME);
        setState(178);
        match(CongParser::COLON);
        setState(179);
        antlrcpp::downCast<RequirementDetailContext *>(_localctx)->name = match(CongParser::STRING);
        break;
      }

      case CongParser::DESCRIPTION: {
        enterOuterAlt(_localctx, 2);
        setState(180);
        match(CongParser::DESCRIPTION);
        setState(181);
        match(CongParser::COLON);
        setState(182);
        antlrcpp::downCast<RequirementDetailContext *>(_localctx)->desc = match(CongParser::STRING);
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

//----------------- RequirementDetailsContext ------------------------------------------------------------------

CongParser::RequirementDetailsContext::RequirementDetailsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::RequirementDetailsContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

tree::TerminalNode* CongParser::RequirementDetailsContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

std::vector<CongParser::RequirementDetailContext *> CongParser::RequirementDetailsContext::requirementDetail() {
  return getRuleContexts<CongParser::RequirementDetailContext>();
}

CongParser::RequirementDetailContext* CongParser::RequirementDetailsContext::requirementDetail(size_t i) {
  return getRuleContext<CongParser::RequirementDetailContext>(i);
}

std::vector<tree::TerminalNode *> CongParser::RequirementDetailsContext::COMMA() {
  return getTokens(CongParser::COMMA);
}

tree::TerminalNode* CongParser::RequirementDetailsContext::COMMA(size_t i) {
  return getToken(CongParser::COMMA, i);
}


size_t CongParser::RequirementDetailsContext::getRuleIndex() const {
  return CongParser::RuleRequirementDetails;
}


std::any CongParser::RequirementDetailsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitRequirementDetails(this);
  else
    return visitor->visitChildren(this);
}

CongParser::RequirementDetailsContext* CongParser::requirementDetails() {
  RequirementDetailsContext *_localctx = _tracker.createInstance<RequirementDetailsContext>(_ctx, getState());
  enterRule(_localctx, 26, CongParser::RuleRequirementDetails);
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
    setState(185);
    match(CongParser::LPAREN);
    setState(194);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::NAME

    || _la == CongParser::DESCRIPTION) {
      setState(186);
      requirementDetail();
      setState(191);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::COMMA) {
        setState(187);
        match(CongParser::COMMA);
        setState(188);
        requirementDetail();
        setState(193);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(196);
    match(CongParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericImplDetailsContext ------------------------------------------------------------------

CongParser::GenericImplDetailsContext::GenericImplDetailsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::GenericImplDetailsContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

tree::TerminalNode* CongParser::GenericImplDetailsContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

std::vector<CongParser::GenericImplDetailContext *> CongParser::GenericImplDetailsContext::genericImplDetail() {
  return getRuleContexts<CongParser::GenericImplDetailContext>();
}

CongParser::GenericImplDetailContext* CongParser::GenericImplDetailsContext::genericImplDetail(size_t i) {
  return getRuleContext<CongParser::GenericImplDetailContext>(i);
}

std::vector<tree::TerminalNode *> CongParser::GenericImplDetailsContext::COMMA() {
  return getTokens(CongParser::COMMA);
}

tree::TerminalNode* CongParser::GenericImplDetailsContext::COMMA(size_t i) {
  return getToken(CongParser::COMMA, i);
}


size_t CongParser::GenericImplDetailsContext::getRuleIndex() const {
  return CongParser::RuleGenericImplDetails;
}


std::any CongParser::GenericImplDetailsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitGenericImplDetails(this);
  else
    return visitor->visitChildren(this);
}

CongParser::GenericImplDetailsContext* CongParser::genericImplDetails() {
  GenericImplDetailsContext *_localctx = _tracker.createInstance<GenericImplDetailsContext>(_ctx, getState());
  enterRule(_localctx, 28, CongParser::RuleGenericImplDetails);
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
     antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->hasLangArg =  false; 
    setState(199);
    match(CongParser::LPAREN);
    setState(211);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3584) != 0)) {
      setState(200);
      antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->first_detail = genericImplDetail();
       if (antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->first_detail->isLangAttr) antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->hasLangArg =  true; 
      setState(208);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::COMMA) {
        setState(202);
        match(CongParser::COMMA);
        setState(203);
        antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->next_detail = genericImplDetail();
         if (antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->next_detail->isLangAttr) antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->hasLangArg =  true; 
        setState(210);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(213);
    match(CongParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

CongParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::ParameterContext::COLON() {
  return getToken(CongParser::COLON, 0);
}

tree::TerminalNode* CongParser::ParameterContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

CongParser::PlaceholderOrQualifiedIdContext* CongParser::ParameterContext::placeholderOrQualifiedId() {
  return getRuleContext<CongParser::PlaceholderOrQualifiedIdContext>(0);
}


size_t CongParser::ParameterContext::getRuleIndex() const {
  return CongParser::RuleParameter;
}


std::any CongParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ParameterContext* CongParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 30, CongParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(215);
    antlrcpp::downCast<ParameterContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(216);
    match(CongParser::COLON);
    setState(217);
    antlrcpp::downCast<ParameterContext *>(_localctx)->type = placeholderOrQualifiedId();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CongParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CongParser::ExpressionContext::getRuleIndex() const {
  return CongParser::RuleExpression;
}

void CongParser::ExpressionContext::copyFrom(ExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParameterOrConceptReferenceExpressionContext ------------------------------------------------------------------

CongParser::QualifiedIdentifierContext* CongParser::ParameterOrConceptReferenceExpressionContext::qualifiedIdentifier() {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(0);
}

CongParser::ParameterOrConceptReferenceExpressionContext::ParameterOrConceptReferenceExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::ParameterOrConceptReferenceExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitParameterOrConceptReferenceExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesizedExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::ParenthesizedExpressionContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

CongParser::ExpressionContext* CongParser::ParenthesizedExpressionContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

tree::TerminalNode* CongParser::ParenthesizedExpressionContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

CongParser::ParenthesizedExpressionContext::ParenthesizedExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::ParenthesizedExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitParenthesizedExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RequiresCallExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::RequiresCallExpressionContext::REQUIRES() {
  return getToken(CongParser::REQUIRES, 0);
}

tree::TerminalNode* CongParser::RequiresCallExpressionContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

tree::TerminalNode* CongParser::RequiresCallExpressionContext::STRING() {
  return getToken(CongParser::STRING, 0);
}

tree::TerminalNode* CongParser::RequiresCallExpressionContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

CongParser::RequiresCallExpressionContext::RequiresCallExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::RequiresCallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitRequiresCallExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::CallExpressionContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

tree::TerminalNode* CongParser::CallExpressionContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

CongParser::QualifiedIdentifierContext* CongParser::CallExpressionContext::qualifiedIdentifier() {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(0);
}

std::vector<CongParser::ExpressionContext *> CongParser::CallExpressionContext::expression() {
  return getRuleContexts<CongParser::ExpressionContext>();
}

CongParser::ExpressionContext* CongParser::CallExpressionContext::expression(size_t i) {
  return getRuleContext<CongParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CongParser::CallExpressionContext::COMMA() {
  return getTokens(CongParser::COMMA);
}

tree::TerminalNode* CongParser::CallExpressionContext::COMMA(size_t i) {
  return getToken(CongParser::COMMA, i);
}

CongParser::CallExpressionContext::CallExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::CallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitCallExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OpenBindingExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::OpenBindingExpressionContext::OPEN_BINDING() {
  return getToken(CongParser::OPEN_BINDING, 0);
}

CongParser::OpenBindingExpressionContext::OpenBindingExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::OpenBindingExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitOpenBindingExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConditionalExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::ConditionalExpressionContext::QUESTION_MARK() {
  return getToken(CongParser::QUESTION_MARK, 0);
}

tree::TerminalNode* CongParser::ConditionalExpressionContext::COLON() {
  return getToken(CongParser::COLON, 0);
}

std::vector<CongParser::ExpressionContext *> CongParser::ConditionalExpressionContext::expression() {
  return getRuleContexts<CongParser::ExpressionContext>();
}

CongParser::ExpressionContext* CongParser::ConditionalExpressionContext::expression(size_t i) {
  return getRuleContext<CongParser::ExpressionContext>(i);
}

CongParser::ConditionalExpressionContext::ConditionalExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::ConditionalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitConditionalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LetExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::LetExpressionContext::LET() {
  return getToken(CongParser::LET, 0);
}

tree::TerminalNode* CongParser::LetExpressionContext::ASSIGN() {
  return getToken(CongParser::ASSIGN, 0);
}

tree::TerminalNode* CongParser::LetExpressionContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

tree::TerminalNode* CongParser::LetExpressionContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

tree::TerminalNode* CongParser::LetExpressionContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

CongParser::ExpressionContext* CongParser::LetExpressionContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

CongParser::ExpressionBlockContext* CongParser::LetExpressionContext::expressionBlock() {
  return getRuleContext<CongParser::ExpressionBlockContext>(0);
}

CongParser::LetExpressionContext::LetExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::LetExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitLetExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- QuoteExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::QuoteExpressionContext::QUOTE() {
  return getToken(CongParser::QUOTE, 0);
}

tree::TerminalNode* CongParser::QuoteExpressionContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

CongParser::ExpressionContext* CongParser::QuoteExpressionContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

tree::TerminalNode* CongParser::QuoteExpressionContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

CongParser::QuoteExpressionContext::QuoteExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::QuoteExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitQuoteExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EvalExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::EvalExpressionContext::EVAL() {
  return getToken(CongParser::EVAL, 0);
}

tree::TerminalNode* CongParser::EvalExpressionContext::LPAREN() {
  return getToken(CongParser::LPAREN, 0);
}

CongParser::ExpressionContext* CongParser::EvalExpressionContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

tree::TerminalNode* CongParser::EvalExpressionContext::RPAREN() {
  return getToken(CongParser::RPAREN, 0);
}

CongParser::EvalExpressionContext::EvalExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::EvalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitEvalExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparisonExpressionContext ------------------------------------------------------------------

std::vector<CongParser::ExpressionContext *> CongParser::ComparisonExpressionContext::expression() {
  return getRuleContexts<CongParser::ExpressionContext>();
}

CongParser::ExpressionContext* CongParser::ComparisonExpressionContext::expression(size_t i) {
  return getRuleContext<CongParser::ExpressionContext>(i);
}

tree::TerminalNode* CongParser::ComparisonExpressionContext::LT() {
  return getToken(CongParser::LT, 0);
}

tree::TerminalNode* CongParser::ComparisonExpressionContext::LESS_EQUAL() {
  return getToken(CongParser::LESS_EQUAL, 0);
}

tree::TerminalNode* CongParser::ComparisonExpressionContext::GT() {
  return getToken(CongParser::GT, 0);
}

tree::TerminalNode* CongParser::ComparisonExpressionContext::GREATER_EQUAL() {
  return getToken(CongParser::GREATER_EQUAL, 0);
}

tree::TerminalNode* CongParser::ComparisonExpressionContext::EQUAL() {
  return getToken(CongParser::EQUAL, 0);
}

tree::TerminalNode* CongParser::ComparisonExpressionContext::NOT_EQUAL() {
  return getToken(CongParser::NOT_EQUAL, 0);
}

CongParser::ComparisonExpressionContext::ComparisonExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::ComparisonExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitComparisonExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArithmeticExpressionContext ------------------------------------------------------------------

std::vector<CongParser::ExpressionContext *> CongParser::ArithmeticExpressionContext::expression() {
  return getRuleContexts<CongParser::ExpressionContext>();
}

CongParser::ExpressionContext* CongParser::ArithmeticExpressionContext::expression(size_t i) {
  return getRuleContext<CongParser::ExpressionContext>(i);
}

tree::TerminalNode* CongParser::ArithmeticExpressionContext::PLUS() {
  return getToken(CongParser::PLUS, 0);
}

tree::TerminalNode* CongParser::ArithmeticExpressionContext::MINUS() {
  return getToken(CongParser::MINUS, 0);
}

tree::TerminalNode* CongParser::ArithmeticExpressionContext::MUL() {
  return getToken(CongParser::MUL, 0);
}

tree::TerminalNode* CongParser::ArithmeticExpressionContext::DIV() {
  return getToken(CongParser::DIV, 0);
}

tree::TerminalNode* CongParser::ArithmeticExpressionContext::MOD() {
  return getToken(CongParser::MOD, 0);
}

tree::TerminalNode* CongParser::ArithmeticExpressionContext::POW() {
  return getToken(CongParser::POW, 0);
}

CongParser::ArithmeticExpressionContext::ArithmeticExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::ArithmeticExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitArithmeticExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralExpressionContext ------------------------------------------------------------------

CongParser::LiteralContext* CongParser::LiteralExpressionContext::literal() {
  return getRuleContext<CongParser::LiteralContext>(0);
}

CongParser::LiteralExpressionContext::LiteralExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::LiteralExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitLiteralExpression(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ExpressionContext* CongParser::expression() {
   return expression(0);
}

CongParser::ExpressionContext* CongParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CongParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  CongParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, CongParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(263);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenthesizedExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(220);
      match(CongParser::LPAREN);
      setState(221);
      expression(0);
      setState(222);
      match(CongParser::RPAREN);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(224);
      antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->val = literal();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<QuoteExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(225);
      match(CongParser::QUOTE);
      setState(226);
      match(CongParser::LPAREN);
      setState(227);
      expression(0);
      setState(228);
      match(CongParser::RPAREN);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<EvalExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(230);
      match(CongParser::EVAL);
      setState(231);
      match(CongParser::LPAREN);
      setState(232);
      expression(0);
      setState(233);
      match(CongParser::RPAREN);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<RequiresCallExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(235);
      match(CongParser::REQUIRES);
      setState(236);
      match(CongParser::LPAREN);
      setState(237);
      match(CongParser::STRING);
      setState(238);
      match(CongParser::RPAREN);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<CallExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(239);
      antlrcpp::downCast<CallExpressionContext *>(_localctx)->fun = qualifiedIdentifier();
      setState(240);
      match(CongParser::LPAREN);
      setState(249);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 34497177399568) != 0)) {
        setState(241);
        expression(0);
        setState(246);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CongParser::COMMA) {
          setState(242);
          match(CongParser::COMMA);
          setState(243);
          expression(0);
          setState(248);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(251);
      match(CongParser::RPAREN);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ParameterOrConceptReferenceExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(253);
      antlrcpp::downCast<ParameterOrConceptReferenceExpressionContext *>(_localctx)->paramOrConcept = qualifiedIdentifier();
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<LetExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(254);
      match(CongParser::LET);
      setState(255);
      antlrcpp::downCast<LetExpressionContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
      setState(256);
      match(CongParser::ASSIGN);
      setState(257);
      antlrcpp::downCast<LetExpressionContext *>(_localctx)->value = expression(0);
      setState(258);
      match(CongParser::LBRACE);
      setState(259);
      antlrcpp::downCast<LetExpressionContext *>(_localctx)->body = expressionBlock();
      setState(260);
      match(CongParser::RBRACE);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<OpenBindingExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(262);
      match(CongParser::OPEN_BINDING);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(279);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(277);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ArithmeticExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(265);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(266);
          antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8455716864) != 0))) {
            antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(267);
          antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->right = expression(12);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ComparisonExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(268);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(269);
          antlrcpp::downCast<ComparisonExpressionContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 128949682176) != 0))) {
            antlrcpp::downCast<ComparisonExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(270);
          antlrcpp::downCast<ComparisonExpressionContext *>(_localctx)->right = expression(11);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ConditionalExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->cond = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpression);
          setState(271);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(272);
          match(CongParser::QUESTION_MARK);
          setState(273);
          antlrcpp::downCast<ConditionalExpressionContext *>(_localctx)->left = expression(0);
          setState(274);
          match(CongParser::COLON);
          setState(275);
          antlrcpp::downCast<ConditionalExpressionContext *>(_localctx)->right = expression(9);
          break;
        }

        default:
          break;
        } 
      }
      setState(281);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ExpressionBlockContext ------------------------------------------------------------------

CongParser::ExpressionBlockContext::ExpressionBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CongParser::ExpressionContext *> CongParser::ExpressionBlockContext::expression() {
  return getRuleContexts<CongParser::ExpressionContext>();
}

CongParser::ExpressionContext* CongParser::ExpressionBlockContext::expression(size_t i) {
  return getRuleContext<CongParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CongParser::ExpressionBlockContext::SEMI() {
  return getTokens(CongParser::SEMI);
}

tree::TerminalNode* CongParser::ExpressionBlockContext::SEMI(size_t i) {
  return getToken(CongParser::SEMI, i);
}


size_t CongParser::ExpressionBlockContext::getRuleIndex() const {
  return CongParser::RuleExpressionBlock;
}


std::any CongParser::ExpressionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitExpressionBlock(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ExpressionBlockContext* CongParser::expressionBlock() {
  ExpressionBlockContext *_localctx = _tracker.createInstance<ExpressionBlockContext>(_ctx, getState());
  enterRule(_localctx, 34, CongParser::RuleExpressionBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(287);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(282);
        expression(0);
        setState(283);
        match(CongParser::SEMI); 
      }
      setState(289);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    }
    setState(290);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PlaceholderOrQualifiedIdContext ------------------------------------------------------------------

CongParser::PlaceholderOrQualifiedIdContext::PlaceholderOrQualifiedIdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CongParser::QualifiedIdentifierContext* CongParser::PlaceholderOrQualifiedIdContext::qualifiedIdentifier() {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(0);
}

CongParser::PlaceholderContext* CongParser::PlaceholderOrQualifiedIdContext::placeholder() {
  return getRuleContext<CongParser::PlaceholderContext>(0);
}


size_t CongParser::PlaceholderOrQualifiedIdContext::getRuleIndex() const {
  return CongParser::RulePlaceholderOrQualifiedId;
}


std::any CongParser::PlaceholderOrQualifiedIdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitPlaceholderOrQualifiedId(this);
  else
    return visitor->visitChildren(this);
}

CongParser::PlaceholderOrQualifiedIdContext* CongParser::placeholderOrQualifiedId() {
  PlaceholderOrQualifiedIdContext *_localctx = _tracker.createInstance<PlaceholderOrQualifiedIdContext>(_ctx, getState());
  enterRule(_localctx, 36, CongParser::RulePlaceholderOrQualifiedId);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(294);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::DOUBLE_COLON:
      case CongParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(292);
        qualifiedIdentifier();
        break;
      }

      case CongParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(293);
        placeholder();
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

//----------------- PlaceholderContext ------------------------------------------------------------------

CongParser::PlaceholderContext::PlaceholderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::PlaceholderContext::LT() {
  return getToken(CongParser::LT, 0);
}

tree::TerminalNode* CongParser::PlaceholderContext::GT() {
  return getToken(CongParser::GT, 0);
}

tree::TerminalNode* CongParser::PlaceholderContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}


size_t CongParser::PlaceholderContext::getRuleIndex() const {
  return CongParser::RulePlaceholder;
}


std::any CongParser::PlaceholderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitPlaceholder(this);
  else
    return visitor->visitChildren(this);
}

CongParser::PlaceholderContext* CongParser::placeholder() {
  PlaceholderContext *_localctx = _tracker.createInstance<PlaceholderContext>(_ctx, getState());
  enterRule(_localctx, 38, CongParser::RulePlaceholder);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(296);
    match(CongParser::LT);
    setState(297);
    antlrcpp::downCast<PlaceholderContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(298);
    match(CongParser::GT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedIdentifierContext ------------------------------------------------------------------

CongParser::QualifiedIdentifierContext::QualifiedIdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CongParser::QualifiedIdentifierContext::IDENTIFIER() {
  return getTokens(CongParser::IDENTIFIER);
}

tree::TerminalNode* CongParser::QualifiedIdentifierContext::IDENTIFIER(size_t i) {
  return getToken(CongParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> CongParser::QualifiedIdentifierContext::DOUBLE_COLON() {
  return getTokens(CongParser::DOUBLE_COLON);
}

tree::TerminalNode* CongParser::QualifiedIdentifierContext::DOUBLE_COLON(size_t i) {
  return getToken(CongParser::DOUBLE_COLON, i);
}


size_t CongParser::QualifiedIdentifierContext::getRuleIndex() const {
  return CongParser::RuleQualifiedIdentifier;
}


std::any CongParser::QualifiedIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitQualifiedIdentifier(this);
  else
    return visitor->visitChildren(this);
}

CongParser::QualifiedIdentifierContext* CongParser::qualifiedIdentifier() {
  QualifiedIdentifierContext *_localctx = _tracker.createInstance<QualifiedIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 40, CongParser::RuleQualifiedIdentifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(301);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::DOUBLE_COLON) {
      setState(300);
      match(CongParser::DOUBLE_COLON);
    }
    setState(303);
    match(CongParser::IDENTIFIER);
    setState(308);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(304);
        match(CongParser::DOUBLE_COLON);
        setState(305);
        match(CongParser::IDENTIFIER); 
      }
      setState(310);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

CongParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::LiteralContext::REAL() {
  return getToken(CongParser::REAL, 0);
}

tree::TerminalNode* CongParser::LiteralContext::DYNAMIC_ANNOTATOR() {
  return getToken(CongParser::DYNAMIC_ANNOTATOR, 0);
}

tree::TerminalNode* CongParser::LiteralContext::INTEGER() {
  return getToken(CongParser::INTEGER, 0);
}

tree::TerminalNode* CongParser::LiteralContext::STRING() {
  return getToken(CongParser::STRING, 0);
}

tree::TerminalNode* CongParser::LiteralContext::BOOL() {
  return getToken(CongParser::BOOL, 0);
}


size_t CongParser::LiteralContext::getRuleIndex() const {
  return CongParser::RuleLiteral;
}


std::any CongParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

CongParser::LiteralContext* CongParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 42, CongParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(324);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::REAL: {
        enterOuterAlt(_localctx, 1);
        setState(311);
        match(CongParser::REAL);
        setState(313);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
        case 1: {
          setState(312);
          match(CongParser::DYNAMIC_ANNOTATOR);
          break;
        }

        default:
          break;
        }
        break;
      }

      case CongParser::INTEGER: {
        enterOuterAlt(_localctx, 2);
        setState(315);
        match(CongParser::INTEGER);
        setState(317);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 30, _ctx)) {
        case 1: {
          setState(316);
          match(CongParser::DYNAMIC_ANNOTATOR);
          break;
        }

        default:
          break;
        }
        break;
      }

      case CongParser::STRING: {
        enterOuterAlt(_localctx, 3);
        setState(319);
        match(CongParser::STRING);
        break;
      }

      case CongParser::BOOL: {
        enterOuterAlt(_localctx, 4);
        setState(320);
        match(CongParser::BOOL);
        setState(322);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
        case 1: {
          setState(321);
          match(CongParser::DYNAMIC_ANNOTATOR);
          break;
        }

        default:
          break;
        }
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

bool CongParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 7: return functionBodyStmntSempred(antlrcpp::downCast<FunctionBodyStmntContext *>(context), predicateIndex);
    case 16: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CongParser::functionBodyStmntSempred(FunctionBodyStmntContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return  antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->g->hasLangArg ;

  default:
    break;
  }
  return true;
}

bool CongParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 11);
    case 2: return precpred(_ctx, 10);
    case 3: return precpred(_ctx, 8);

  default:
    break;
  }
  return true;
}

void CongParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  congparserParserInitialize();
#else
  ::antlr4::internal::call_once(congparserParserOnceFlag, congparserParserInitialize);
#endif
}
