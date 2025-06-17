
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
      "genericImplDetails", "parameter", "expression", "expressionBlock", 
      "placeholderOrQualifiedId", "placeholder", "qualifiedIdentifier", 
      "literal"
    },
    std::vector<std::string>{
      "", "'concept'", "'fun'", "'namespace'", "'let'", "'description'", 
      "'generic'", "'requires'", "'time'", "'space'", "'lang'", "'{'", "'}'", 
      "'...'", "'('", "')'", "':'", "';'", "'&'", "'->'", "','", "'='", 
      "'+'", "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'::'", "", "'_d'"
    },
    std::vector<std::string>{
      "", "CONCEPT", "FUNCTION", "NAMESPACE", "LET", "DESCRIPTION", "GENERICIMPL", 
      "REQUIRES", "TIME", "SPACE", "LANG", "LBRACE", "RBRACE", "VARARGS", 
      "LPAREN", "RPAREN", "COLON", "SEMI", "AMP", "ARROW", "COMMA", "ASSIGN", 
      "PLUS", "MINUS", "MUL", "DIV", "MOD", "LT", "GT", "DOUBLE_COLON", 
      "OPEN_BINDING", "DYNAMIC_ANNOTATOR", "REAL", "BOOL", "NUMBER", "STRING", 
      "IDENTIFIER", "WHITESPACE", "COMMENT", "LINE_COMMENT", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,40,275,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,1,0,5,0,42,8,0,10,
  	0,12,0,45,9,0,1,0,1,0,1,1,1,1,1,1,3,1,52,8,1,1,2,1,2,1,2,1,2,1,2,1,2,
  	1,2,3,2,61,8,2,1,2,3,2,64,8,2,1,2,1,2,1,3,1,3,1,3,1,3,5,3,72,8,3,10,3,
  	12,3,75,9,3,1,4,1,4,1,4,1,4,5,4,81,8,4,10,4,12,4,84,9,4,1,4,1,4,1,5,1,
  	5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,5,6,97,8,6,10,6,12,6,100,9,6,1,6,1,6,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,120,
  	8,7,1,7,1,7,3,7,124,8,7,1,7,1,7,1,7,1,7,3,7,130,8,7,1,8,5,8,133,8,8,10,
  	8,12,8,136,9,8,1,9,1,9,1,9,1,9,1,9,3,9,143,8,9,1,10,1,10,1,10,1,10,5,
  	10,149,8,10,10,10,12,10,152,9,10,3,10,154,8,10,1,10,1,10,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,3,11,172,8,
  	11,1,12,1,12,1,12,1,12,1,12,1,12,1,12,1,12,5,12,182,8,12,10,12,12,12,
  	185,9,12,3,12,187,8,12,1,12,1,12,1,13,1,13,1,13,1,13,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,5,14,202,8,14,10,14,12,14,205,9,14,3,14,207,8,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,14,221,8,
  	14,1,14,1,14,1,14,5,14,226,8,14,10,14,12,14,229,9,14,1,15,1,15,1,15,5,
  	15,234,8,15,10,15,12,15,237,9,15,1,15,1,15,1,16,1,16,3,16,243,8,16,1,
  	17,1,17,1,17,1,17,1,18,3,18,250,8,18,1,18,1,18,1,18,5,18,255,8,18,10,
  	18,12,18,258,9,18,1,19,1,19,3,19,262,8,19,1,19,1,19,3,19,266,8,19,1,19,
  	1,19,1,19,3,19,271,8,19,3,19,273,8,19,1,19,0,1,28,20,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,0,2,1,0,11,12,1,0,22,26,291,0,
  	43,1,0,0,0,2,51,1,0,0,0,4,53,1,0,0,0,6,67,1,0,0,0,8,76,1,0,0,0,10,87,
  	1,0,0,0,12,94,1,0,0,0,14,129,1,0,0,0,16,134,1,0,0,0,18,142,1,0,0,0,20,
  	144,1,0,0,0,22,171,1,0,0,0,24,173,1,0,0,0,26,190,1,0,0,0,28,220,1,0,0,
  	0,30,235,1,0,0,0,32,242,1,0,0,0,34,244,1,0,0,0,36,249,1,0,0,0,38,272,
  	1,0,0,0,40,42,3,2,1,0,41,40,1,0,0,0,42,45,1,0,0,0,43,41,1,0,0,0,43,44,
  	1,0,0,0,44,46,1,0,0,0,45,43,1,0,0,0,46,47,5,0,0,1,47,1,1,0,0,0,48,52,
  	3,4,2,0,49,52,3,8,4,0,50,52,3,10,5,0,51,48,1,0,0,0,51,49,1,0,0,0,51,50,
  	1,0,0,0,52,3,1,0,0,0,53,54,5,1,0,0,54,60,5,36,0,0,55,56,5,14,0,0,56,57,
  	5,5,0,0,57,58,5,16,0,0,58,59,5,35,0,0,59,61,5,15,0,0,60,55,1,0,0,0,60,
  	61,1,0,0,0,61,63,1,0,0,0,62,64,3,6,3,0,63,62,1,0,0,0,63,64,1,0,0,0,64,
  	65,1,0,0,0,65,66,5,17,0,0,66,5,1,0,0,0,67,68,5,16,0,0,68,73,3,36,18,0,
  	69,70,5,18,0,0,70,72,3,36,18,0,71,69,1,0,0,0,72,75,1,0,0,0,73,71,1,0,
  	0,0,73,74,1,0,0,0,74,7,1,0,0,0,75,73,1,0,0,0,76,77,5,3,0,0,77,78,5,36,
  	0,0,78,82,5,11,0,0,79,81,3,2,1,0,80,79,1,0,0,0,81,84,1,0,0,0,82,80,1,
  	0,0,0,82,83,1,0,0,0,83,85,1,0,0,0,84,82,1,0,0,0,85,86,5,12,0,0,86,9,1,
  	0,0,0,87,88,5,2,0,0,88,89,5,36,0,0,89,90,3,20,10,0,90,91,5,19,0,0,91,
  	92,3,36,18,0,92,93,3,12,6,0,93,11,1,0,0,0,94,98,5,11,0,0,95,97,3,14,7,
  	0,96,95,1,0,0,0,97,100,1,0,0,0,98,96,1,0,0,0,98,99,1,0,0,0,99,101,1,0,
  	0,0,100,98,1,0,0,0,101,102,5,12,0,0,102,13,1,0,0,0,103,104,5,5,0,0,104,
  	105,5,11,0,0,105,106,3,38,19,0,106,107,5,12,0,0,107,130,1,0,0,0,108,109,
  	5,6,0,0,109,119,3,24,12,0,110,111,4,7,0,1,111,112,5,11,0,0,112,113,3,
  	16,8,0,113,114,5,12,0,0,114,120,1,0,0,0,115,116,5,11,0,0,116,117,3,28,
  	14,0,117,118,5,12,0,0,118,120,1,0,0,0,119,110,1,0,0,0,119,115,1,0,0,0,
  	120,130,1,0,0,0,121,123,5,7,0,0,122,124,5,36,0,0,123,122,1,0,0,0,123,
  	124,1,0,0,0,124,125,1,0,0,0,125,126,5,11,0,0,126,127,3,28,14,0,127,128,
  	5,12,0,0,128,130,1,0,0,0,129,103,1,0,0,0,129,108,1,0,0,0,129,121,1,0,
  	0,0,130,15,1,0,0,0,131,133,3,18,9,0,132,131,1,0,0,0,133,136,1,0,0,0,134,
  	132,1,0,0,0,134,135,1,0,0,0,135,17,1,0,0,0,136,134,1,0,0,0,137,138,5,
  	11,0,0,138,139,3,16,8,0,139,140,5,12,0,0,140,143,1,0,0,0,141,143,8,0,
  	0,0,142,137,1,0,0,0,142,141,1,0,0,0,143,19,1,0,0,0,144,153,5,14,0,0,145,
  	150,3,26,13,0,146,147,5,20,0,0,147,149,3,26,13,0,148,146,1,0,0,0,149,
  	152,1,0,0,0,150,148,1,0,0,0,150,151,1,0,0,0,151,154,1,0,0,0,152,150,1,
  	0,0,0,153,145,1,0,0,0,153,154,1,0,0,0,154,155,1,0,0,0,155,156,5,15,0,
  	0,156,21,1,0,0,0,157,158,5,8,0,0,158,159,5,16,0,0,159,160,3,28,14,0,160,
  	161,6,11,-1,0,161,172,1,0,0,0,162,163,5,9,0,0,163,164,5,16,0,0,164,165,
  	3,28,14,0,165,166,6,11,-1,0,166,172,1,0,0,0,167,168,5,10,0,0,168,169,
  	5,16,0,0,169,170,5,35,0,0,170,172,6,11,-1,0,171,157,1,0,0,0,171,162,1,
  	0,0,0,171,167,1,0,0,0,172,23,1,0,0,0,173,174,6,12,-1,0,174,186,5,14,0,
  	0,175,176,3,22,11,0,176,183,6,12,-1,0,177,178,5,20,0,0,178,179,3,22,11,
  	0,179,180,6,12,-1,0,180,182,1,0,0,0,181,177,1,0,0,0,182,185,1,0,0,0,183,
  	181,1,0,0,0,183,184,1,0,0,0,184,187,1,0,0,0,185,183,1,0,0,0,186,175,1,
  	0,0,0,186,187,1,0,0,0,187,188,1,0,0,0,188,189,5,15,0,0,189,25,1,0,0,0,
  	190,191,5,36,0,0,191,192,5,16,0,0,192,193,3,32,16,0,193,27,1,0,0,0,194,
  	195,6,14,-1,0,195,221,3,38,19,0,196,197,3,36,18,0,197,206,5,14,0,0,198,
  	203,3,28,14,0,199,200,5,20,0,0,200,202,3,28,14,0,201,199,1,0,0,0,202,
  	205,1,0,0,0,203,201,1,0,0,0,203,204,1,0,0,0,204,207,1,0,0,0,205,203,1,
  	0,0,0,206,198,1,0,0,0,206,207,1,0,0,0,207,208,1,0,0,0,208,209,5,15,0,
  	0,209,221,1,0,0,0,210,221,5,36,0,0,211,212,5,4,0,0,212,213,5,36,0,0,213,
  	214,5,21,0,0,214,215,3,28,14,0,215,216,5,11,0,0,216,217,3,30,15,0,217,
  	218,5,12,0,0,218,221,1,0,0,0,219,221,5,30,0,0,220,194,1,0,0,0,220,196,
  	1,0,0,0,220,210,1,0,0,0,220,211,1,0,0,0,220,219,1,0,0,0,221,227,1,0,0,
  	0,222,223,10,6,0,0,223,224,7,1,0,0,224,226,3,28,14,7,225,222,1,0,0,0,
  	226,229,1,0,0,0,227,225,1,0,0,0,227,228,1,0,0,0,228,29,1,0,0,0,229,227,
  	1,0,0,0,230,231,3,28,14,0,231,232,5,17,0,0,232,234,1,0,0,0,233,230,1,
  	0,0,0,234,237,1,0,0,0,235,233,1,0,0,0,235,236,1,0,0,0,236,238,1,0,0,0,
  	237,235,1,0,0,0,238,239,3,28,14,0,239,31,1,0,0,0,240,243,3,36,18,0,241,
  	243,3,34,17,0,242,240,1,0,0,0,242,241,1,0,0,0,243,33,1,0,0,0,244,245,
  	5,27,0,0,245,246,5,36,0,0,246,247,5,28,0,0,247,35,1,0,0,0,248,250,5,29,
  	0,0,249,248,1,0,0,0,249,250,1,0,0,0,250,251,1,0,0,0,251,256,5,36,0,0,
  	252,253,5,29,0,0,253,255,5,36,0,0,254,252,1,0,0,0,255,258,1,0,0,0,256,
  	254,1,0,0,0,256,257,1,0,0,0,257,37,1,0,0,0,258,256,1,0,0,0,259,261,5,
  	32,0,0,260,262,5,31,0,0,261,260,1,0,0,0,261,262,1,0,0,0,262,273,1,0,0,
  	0,263,265,5,34,0,0,264,266,5,31,0,0,265,264,1,0,0,0,265,266,1,0,0,0,266,
  	273,1,0,0,0,267,273,5,35,0,0,268,270,5,33,0,0,269,271,5,31,0,0,270,269,
  	1,0,0,0,270,271,1,0,0,0,271,273,1,0,0,0,272,259,1,0,0,0,272,263,1,0,0,
  	0,272,267,1,0,0,0,272,268,1,0,0,0,273,39,1,0,0,0,29,43,51,60,63,73,82,
  	98,119,123,129,134,142,150,153,171,183,186,203,206,220,227,235,242,249,
  	256,261,265,270,272
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
    setState(43);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 14) != 0)) {
      setState(40);
      stmnt();
      setState(45);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(46);
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
    setState(51);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::CONCEPT: {
        enterOuterAlt(_localctx, 1);
        setState(48);
        conceptDefinitionStmnt();
        break;
      }

      case CongParser::NAMESPACE: {
        enterOuterAlt(_localctx, 2);
        setState(49);
        namespaceStmnt();
        break;
      }

      case CongParser::FUNCTION: {
        enterOuterAlt(_localctx, 3);
        setState(50);
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
    setState(53);
    match(CongParser::CONCEPT);
    setState(54);
    antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(60);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::LPAREN) {
      setState(55);
      match(CongParser::LPAREN);
      setState(56);
      match(CongParser::DESCRIPTION);
      setState(57);
      match(CongParser::COLON);
      setState(58);
      antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->desc = match(CongParser::STRING);
      setState(59);
      match(CongParser::RPAREN);
    }
    setState(63);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::COLON) {
      setState(62);
      conceptDefinitionBases();
    }
    setState(65);
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
    setState(67);
    match(CongParser::COLON);
    setState(68);
    qualifiedIdentifier();
    setState(73);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::AMP) {
      setState(69);
      match(CongParser::AMP);
      setState(70);
      qualifiedIdentifier();
      setState(75);
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
    setState(76);
    match(CongParser::NAMESPACE);
    setState(77);
    antlrcpp::downCast<NamespaceStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(78);
    match(CongParser::LBRACE);
    setState(82);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 14) != 0)) {
      setState(79);
      stmnt();
      setState(84);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(85);
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
    setState(87);
    match(CongParser::FUNCTION);
    setState(88);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(89);
    parameterList();
    setState(90);
    match(CongParser::ARROW);
    setState(91);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->type = qualifiedIdentifier();
    setState(92);
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
    setState(94);
    match(CongParser::LBRACE);
    setState(98);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 224) != 0)) {
      setState(95);
      functionBodyStmnt();
      setState(100);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(101);
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

CongParser::GenericImplDetailsContext* CongParser::FunctionGenericImplContext::genericImplDetails() {
  return getRuleContext<CongParser::GenericImplDetailsContext>(0);
}

tree::TerminalNode* CongParser::FunctionGenericImplContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

tree::TerminalNode* CongParser::FunctionGenericImplContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
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

tree::TerminalNode* CongParser::FunctionExpRequiresContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
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
    setState(129);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::DESCRIPTION: {
        _localctx = _tracker.createInstance<CongParser::FunctionDescriptionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(103);
        match(CongParser::DESCRIPTION);
        setState(104);
        match(CongParser::LBRACE);
        setState(105);
        literal();
        setState(106);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::GENERICIMPL: {
        _localctx = _tracker.createInstance<CongParser::FunctionGenericImplContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(108);
        match(CongParser::GENERICIMPL);
        setState(109);
        antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->g = genericImplDetails();
        setState(119);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
        case 1: {
          setState(110);

          if (!( antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->g->hasLangArg )) throw FailedPredicateException(this, " $g.hasLangArg ");
          setState(111);
          match(CongParser::LBRACE);
          setState(112);
          antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->body_native = rawTextContent();
          setState(113);
          match(CongParser::RBRACE);
          break;
        }

        case 2: {
          setState(115);
          match(CongParser::LBRACE);
          setState(116);
          antlrcpp::downCast<FunctionGenericImplContext *>(_localctx)->body_expr = expression(0);
          setState(117);
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
        setState(121);
        match(CongParser::REQUIRES);
        setState(123);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CongParser::IDENTIFIER) {
          setState(122);
          antlrcpp::downCast<FunctionExpRequiresContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
        }
        setState(125);
        match(CongParser::LBRACE);
        setState(126);
        expression(0);
        setState(127);
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
    setState(134);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2199023251454) != 0)) {
      setState(131);
      element();
      setState(136);
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
    setState(142);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::LBRACE: {
        enterOuterAlt(_localctx, 1);
        setState(137);
        match(CongParser::LBRACE);
        setState(138);
        rawTextContent();
        setState(139);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::CONCEPT:
      case CongParser::FUNCTION:
      case CongParser::NAMESPACE:
      case CongParser::LET:
      case CongParser::DESCRIPTION:
      case CongParser::GENERICIMPL:
      case CongParser::REQUIRES:
      case CongParser::TIME:
      case CongParser::SPACE:
      case CongParser::LANG:
      case CongParser::VARARGS:
      case CongParser::LPAREN:
      case CongParser::RPAREN:
      case CongParser::COLON:
      case CongParser::SEMI:
      case CongParser::AMP:
      case CongParser::ARROW:
      case CongParser::COMMA:
      case CongParser::ASSIGN:
      case CongParser::PLUS:
      case CongParser::MINUS:
      case CongParser::MUL:
      case CongParser::DIV:
      case CongParser::MOD:
      case CongParser::LT:
      case CongParser::GT:
      case CongParser::DOUBLE_COLON:
      case CongParser::OPEN_BINDING:
      case CongParser::DYNAMIC_ANNOTATOR:
      case CongParser::REAL:
      case CongParser::BOOL:
      case CongParser::NUMBER:
      case CongParser::STRING:
      case CongParser::IDENTIFIER:
      case CongParser::WHITESPACE:
      case CongParser::COMMENT:
      case CongParser::LINE_COMMENT:
      case CongParser::OTHER: {
        enterOuterAlt(_localctx, 2);
        setState(141);
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
    setState(144);
    match(CongParser::LPAREN);
    setState(153);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::IDENTIFIER) {
      setState(145);
      parameter();
      setState(150);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::COMMA) {
        setState(146);
        match(CongParser::COMMA);
        setState(147);
        parameter();
        setState(152);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(155);
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
    setState(171);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::TIME: {
        enterOuterAlt(_localctx, 1);
        setState(157);
        match(CongParser::TIME);
        setState(158);
        match(CongParser::COLON);
        setState(159);
        expression(0);
         antlrcpp::downCast<GenericImplDetailContext *>(_localctx)->isLangAttr =  false; 
        break;
      }

      case CongParser::SPACE: {
        enterOuterAlt(_localctx, 2);
        setState(162);
        match(CongParser::SPACE);
        setState(163);
        match(CongParser::COLON);
        setState(164);
        expression(0);
         antlrcpp::downCast<GenericImplDetailContext *>(_localctx)->isLangAttr =  false; 
        break;
      }

      case CongParser::LANG: {
        enterOuterAlt(_localctx, 3);
        setState(167);
        match(CongParser::LANG);
        setState(168);
        match(CongParser::COLON);
        setState(169);
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
  enterRule(_localctx, 24, CongParser::RuleGenericImplDetails);
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
    setState(174);
    match(CongParser::LPAREN);
    setState(186);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1792) != 0)) {
      setState(175);
      antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->first_detail = genericImplDetail();
       if (antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->first_detail->isLangAttr) antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->hasLangArg =  true; 
      setState(183);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::COMMA) {
        setState(177);
        match(CongParser::COMMA);
        setState(178);
        antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->next_detail = genericImplDetail();
         if (antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->next_detail->isLangAttr) antlrcpp::downCast<GenericImplDetailsContext *>(_localctx)->hasLangArg =  true; 
        setState(185);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(188);
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
  enterRule(_localctx, 26, CongParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    antlrcpp::downCast<ParameterContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(191);
    match(CongParser::COLON);
    setState(192);
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
//----------------- ParameterReferenceExpressionContext ------------------------------------------------------------------

tree::TerminalNode* CongParser::ParameterReferenceExpressionContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

CongParser::ParameterReferenceExpressionContext::ParameterReferenceExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::ParameterReferenceExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongParserVisitor*>(visitor))
    return parserVisitor->visitParameterReferenceExpression(this);
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
  size_t startState = 28;
  enterRecursionRule(_localctx, 28, CongParser::RuleExpression, precedence);

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
    setState(220);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(195);
      antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->val = literal();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CallExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(196);
      antlrcpp::downCast<CallExpressionContext *>(_localctx)->fun = qualifiedIdentifier();
      setState(197);
      match(CongParser::LPAREN);
      setState(206);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 134754598928) != 0)) {
        setState(198);
        expression(0);
        setState(203);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CongParser::COMMA) {
          setState(199);
          match(CongParser::COMMA);
          setState(200);
          expression(0);
          setState(205);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(208);
      match(CongParser::RPAREN);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ParameterReferenceExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(210);
      antlrcpp::downCast<ParameterReferenceExpressionContext *>(_localctx)->param = match(CongParser::IDENTIFIER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LetExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(211);
      match(CongParser::LET);
      setState(212);
      antlrcpp::downCast<LetExpressionContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
      setState(213);
      match(CongParser::ASSIGN);
      setState(214);
      antlrcpp::downCast<LetExpressionContext *>(_localctx)->value = expression(0);
      setState(215);
      match(CongParser::LBRACE);
      setState(216);
      antlrcpp::downCast<LetExpressionContext *>(_localctx)->body = expressionBlock();
      setState(217);
      match(CongParser::RBRACE);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<OpenBindingExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(219);
      match(CongParser::OPEN_BINDING);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(227);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArithmeticExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        newContext->left = previousContext;
        pushNewRecursionContext(newContext, startState, RuleExpression);
        setState(222);

        if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
        setState(223);
        antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 130023424) != 0))) {
          antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(224);
        antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->right = expression(7); 
      }
      setState(229);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx);
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
  enterRule(_localctx, 30, CongParser::RuleExpressionBlock);

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
    setState(235);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(230);
        expression(0);
        setState(231);
        match(CongParser::SEMI); 
      }
      setState(237);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
    setState(238);
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
  enterRule(_localctx, 32, CongParser::RulePlaceholderOrQualifiedId);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(242);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::DOUBLE_COLON:
      case CongParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(240);
        qualifiedIdentifier();
        break;
      }

      case CongParser::LT: {
        enterOuterAlt(_localctx, 2);
        setState(241);
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
  enterRule(_localctx, 34, CongParser::RulePlaceholder);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    match(CongParser::LT);
    setState(245);
    antlrcpp::downCast<PlaceholderContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(246);
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
  enterRule(_localctx, 36, CongParser::RuleQualifiedIdentifier);
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
    setState(249);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::DOUBLE_COLON) {
      setState(248);
      match(CongParser::DOUBLE_COLON);
    }
    setState(251);
    match(CongParser::IDENTIFIER);
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::DOUBLE_COLON) {
      setState(252);
      match(CongParser::DOUBLE_COLON);
      setState(253);
      match(CongParser::IDENTIFIER);
      setState(258);
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

tree::TerminalNode* CongParser::LiteralContext::NUMBER() {
  return getToken(CongParser::NUMBER, 0);
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
  enterRule(_localctx, 38, CongParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(272);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::REAL: {
        enterOuterAlt(_localctx, 1);
        setState(259);
        match(CongParser::REAL);
        setState(261);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
        case 1: {
          setState(260);
          match(CongParser::DYNAMIC_ANNOTATOR);
          break;
        }

        default:
          break;
        }
        break;
      }

      case CongParser::NUMBER: {
        enterOuterAlt(_localctx, 2);
        setState(263);
        match(CongParser::NUMBER);
        setState(265);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          setState(264);
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
        setState(267);
        match(CongParser::STRING);
        break;
      }

      case CongParser::BOOL: {
        enterOuterAlt(_localctx, 4);
        setState(268);
        match(CongParser::BOOL);
        setState(270);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
        case 1: {
          setState(269);
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
    case 14: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
    case 1: return precpred(_ctx, 6);

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
