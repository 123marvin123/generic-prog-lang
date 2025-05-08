
// Generated from /Users/haschker/Arbeitsbereich/generic-prog-lang/grammar/Cong.g4 by ANTLR 4.13.2


#include "CongVisitor.h"

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

::antlr4::internal::OnceFlag congParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<CongParserStaticData> congParserStaticData = nullptr;

void congParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (congParserStaticData != nullptr) {
    return;
  }
#else
  assert(congParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<CongParserStaticData>(
    std::vector<std::string>{
      "translationUnit", "stmnt", "conceptDefinitionStmnt", "conceptDefinitionBases", 
      "namespaceStmnt", "functionStmnt", "functionBody", "functionBodyStmnt", 
      "parameterList", "genericImplDetails", "genericImplDetail", "parameter", 
      "expression", "placeholderOrQualifiedId", "placeholder", "qualifiedIdentifier", 
      "literal"
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
  	4,1,35,207,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,5,0,36,8,0,10,0,12,0,39,9,0,1,0,1,0,1,1,1,
  	1,1,1,3,1,46,8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,3,2,55,8,2,1,2,3,2,58,8,
  	2,1,2,1,2,1,3,1,3,1,3,1,3,5,3,66,8,3,10,3,12,3,69,9,3,1,4,1,4,1,4,1,4,
  	5,4,75,8,4,10,4,12,4,78,9,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,
  	6,5,6,91,8,6,10,6,12,6,94,9,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,
  	105,8,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,113,8,7,1,7,1,7,1,7,1,7,3,7,119,8,
  	7,1,8,1,8,1,8,1,8,5,8,125,8,8,10,8,12,8,128,9,8,3,8,130,8,8,1,8,1,8,1,
  	9,1,9,1,9,1,9,5,9,138,8,9,10,9,12,9,141,9,9,3,9,143,8,9,1,9,1,9,1,10,
  	1,10,1,10,1,10,1,10,1,10,3,10,153,8,10,1,11,1,11,1,11,1,11,1,12,1,12,
  	1,12,1,12,1,12,1,12,1,12,5,12,166,8,12,10,12,12,12,169,9,12,3,12,171,
  	8,12,1,12,1,12,1,12,3,12,176,8,12,1,12,1,12,1,12,5,12,181,8,12,10,12,
  	12,12,184,9,12,1,13,1,13,3,13,188,8,13,1,14,1,14,1,14,1,14,1,15,3,15,
  	195,8,15,1,15,1,15,1,15,5,15,200,8,15,10,15,12,15,203,9,15,1,16,1,16,
  	1,16,0,1,24,17,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,0,2,1,0,
  	8,12,1,0,27,30,214,0,37,1,0,0,0,2,45,1,0,0,0,4,47,1,0,0,0,6,61,1,0,0,
  	0,8,70,1,0,0,0,10,81,1,0,0,0,12,88,1,0,0,0,14,118,1,0,0,0,16,120,1,0,
  	0,0,18,133,1,0,0,0,20,152,1,0,0,0,22,154,1,0,0,0,24,175,1,0,0,0,26,187,
  	1,0,0,0,28,189,1,0,0,0,30,194,1,0,0,0,32,204,1,0,0,0,34,36,3,2,1,0,35,
  	34,1,0,0,0,36,39,1,0,0,0,37,35,1,0,0,0,37,38,1,0,0,0,38,40,1,0,0,0,39,
  	37,1,0,0,0,40,41,5,0,0,1,41,1,1,0,0,0,42,46,3,4,2,0,43,46,3,8,4,0,44,
  	46,3,10,5,0,45,42,1,0,0,0,45,43,1,0,0,0,45,44,1,0,0,0,46,3,1,0,0,0,47,
  	48,5,16,0,0,48,54,5,31,0,0,49,50,5,1,0,0,50,51,5,19,0,0,51,52,5,2,0,0,
  	52,53,5,30,0,0,53,55,5,3,0,0,54,49,1,0,0,0,54,55,1,0,0,0,55,57,1,0,0,
  	0,56,58,3,6,3,0,57,56,1,0,0,0,57,58,1,0,0,0,58,59,1,0,0,0,59,60,5,4,0,
  	0,60,5,1,0,0,0,61,62,5,2,0,0,62,67,3,30,15,0,63,64,5,5,0,0,64,66,3,30,
  	15,0,65,63,1,0,0,0,66,69,1,0,0,0,67,65,1,0,0,0,67,68,1,0,0,0,68,7,1,0,
  	0,0,69,67,1,0,0,0,70,71,5,18,0,0,71,72,5,31,0,0,72,76,5,24,0,0,73,75,
  	3,2,1,0,74,73,1,0,0,0,75,78,1,0,0,0,76,74,1,0,0,0,76,77,1,0,0,0,77,79,
  	1,0,0,0,78,76,1,0,0,0,79,80,5,25,0,0,80,9,1,0,0,0,81,82,5,17,0,0,82,83,
  	5,31,0,0,83,84,3,16,8,0,84,85,5,6,0,0,85,86,3,30,15,0,86,87,3,12,6,0,
  	87,11,1,0,0,0,88,92,5,24,0,0,89,91,3,14,7,0,90,89,1,0,0,0,91,94,1,0,0,
  	0,92,90,1,0,0,0,92,93,1,0,0,0,93,95,1,0,0,0,94,92,1,0,0,0,95,96,5,25,
  	0,0,96,13,1,0,0,0,97,98,5,19,0,0,98,99,5,24,0,0,99,100,3,32,16,0,100,
  	101,5,25,0,0,101,119,1,0,0,0,102,104,5,20,0,0,103,105,3,18,9,0,104,103,
  	1,0,0,0,104,105,1,0,0,0,105,106,1,0,0,0,106,107,5,24,0,0,107,108,3,24,
  	12,0,108,109,5,25,0,0,109,119,1,0,0,0,110,112,5,21,0,0,111,113,5,31,0,
  	0,112,111,1,0,0,0,112,113,1,0,0,0,113,114,1,0,0,0,114,115,5,24,0,0,115,
  	116,3,24,12,0,116,117,5,25,0,0,117,119,1,0,0,0,118,97,1,0,0,0,118,102,
  	1,0,0,0,118,110,1,0,0,0,119,15,1,0,0,0,120,129,5,1,0,0,121,126,3,22,11,
  	0,122,123,5,7,0,0,123,125,3,22,11,0,124,122,1,0,0,0,125,128,1,0,0,0,126,
  	124,1,0,0,0,126,127,1,0,0,0,127,130,1,0,0,0,128,126,1,0,0,0,129,121,1,
  	0,0,0,129,130,1,0,0,0,130,131,1,0,0,0,131,132,5,3,0,0,132,17,1,0,0,0,
  	133,142,5,1,0,0,134,139,3,20,10,0,135,136,5,7,0,0,136,138,3,20,10,0,137,
  	135,1,0,0,0,138,141,1,0,0,0,139,137,1,0,0,0,139,140,1,0,0,0,140,143,1,
  	0,0,0,141,139,1,0,0,0,142,134,1,0,0,0,142,143,1,0,0,0,143,144,1,0,0,0,
  	144,145,5,3,0,0,145,19,1,0,0,0,146,147,5,22,0,0,147,148,5,2,0,0,148,153,
  	3,24,12,0,149,150,5,23,0,0,150,151,5,2,0,0,151,153,3,24,12,0,152,146,
  	1,0,0,0,152,149,1,0,0,0,153,21,1,0,0,0,154,155,5,31,0,0,155,156,5,2,0,
  	0,156,157,3,26,13,0,157,23,1,0,0,0,158,159,6,12,-1,0,159,176,3,32,16,
  	0,160,161,3,30,15,0,161,170,5,1,0,0,162,167,3,24,12,0,163,164,5,7,0,0,
  	164,166,3,24,12,0,165,163,1,0,0,0,166,169,1,0,0,0,167,165,1,0,0,0,167,
  	168,1,0,0,0,168,171,1,0,0,0,169,167,1,0,0,0,170,162,1,0,0,0,170,171,1,
  	0,0,0,171,172,1,0,0,0,172,173,5,3,0,0,173,176,1,0,0,0,174,176,5,31,0,
  	0,175,158,1,0,0,0,175,160,1,0,0,0,175,174,1,0,0,0,176,182,1,0,0,0,177,
  	178,10,4,0,0,178,179,7,0,0,0,179,181,3,24,12,5,180,177,1,0,0,0,181,184,
  	1,0,0,0,182,180,1,0,0,0,182,183,1,0,0,0,183,25,1,0,0,0,184,182,1,0,0,
  	0,185,188,3,30,15,0,186,188,3,28,14,0,187,185,1,0,0,0,187,186,1,0,0,0,
  	188,27,1,0,0,0,189,190,5,13,0,0,190,191,5,31,0,0,191,192,5,14,0,0,192,
  	29,1,0,0,0,193,195,5,15,0,0,194,193,1,0,0,0,194,195,1,0,0,0,195,196,1,
  	0,0,0,196,201,5,31,0,0,197,198,5,15,0,0,198,200,5,31,0,0,199,197,1,0,
  	0,0,200,203,1,0,0,0,201,199,1,0,0,0,201,202,1,0,0,0,202,31,1,0,0,0,203,
  	201,1,0,0,0,204,205,7,1,0,0,205,33,1,0,0,0,22,37,45,54,57,67,76,92,104,
  	112,118,126,129,139,142,152,167,170,175,182,187,194,201
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  congParserStaticData = std::move(staticData);
}

}

CongParser::CongParser(TokenStream *input) : CongParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CongParser::CongParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CongParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *congParserStaticData->atn, congParserStaticData->decisionToDFA, congParserStaticData->sharedContextCache, options);
}

CongParser::~CongParser() {
  delete _interpreter;
}

const atn::ATN& CongParser::getATN() const {
  return *congParserStaticData->atn;
}

std::string CongParser::getGrammarFileName() const {
  return "Cong.g4";
}

const std::vector<std::string>& CongParser::getRuleNames() const {
  return congParserStaticData->ruleNames;
}

const dfa::Vocabulary& CongParser::getVocabulary() const {
  return congParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CongParser::getSerializedATN() const {
  return congParserStaticData->serializedATN;
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(37);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 458752) != 0)) {
      setState(34);
      stmnt();
      setState(39);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(40);
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(45);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::CONCEPT: {
        enterOuterAlt(_localctx, 1);
        setState(42);
        conceptDefinitionStmnt();
        break;
      }

      case CongParser::NAMESPACE: {
        enterOuterAlt(_localctx, 2);
        setState(43);
        namespaceStmnt();
        break;
      }

      case CongParser::FUNCTION: {
        enterOuterAlt(_localctx, 3);
        setState(44);
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

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

tree::TerminalNode* CongParser::ConceptDefinitionStmntContext::DESCRIPTION() {
  return getToken(CongParser::DESCRIPTION, 0);
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(47);
    match(CongParser::CONCEPT);
    setState(48);
    antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(54);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::T__0) {
      setState(49);
      match(CongParser::T__0);
      setState(50);
      match(CongParser::DESCRIPTION);
      setState(51);
      match(CongParser::T__1);
      setState(52);
      antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->desc = match(CongParser::STRING);
      setState(53);
      match(CongParser::T__2);
    }
    setState(57);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::T__1) {
      setState(56);
      conceptDefinitionBases();
    }
    setState(59);
    match(CongParser::T__3);
   
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

std::vector<CongParser::QualifiedIdentifierContext *> CongParser::ConceptDefinitionBasesContext::qualifiedIdentifier() {
  return getRuleContexts<CongParser::QualifiedIdentifierContext>();
}

CongParser::QualifiedIdentifierContext* CongParser::ConceptDefinitionBasesContext::qualifiedIdentifier(size_t i) {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(i);
}


size_t CongParser::ConceptDefinitionBasesContext::getRuleIndex() const {
  return CongParser::RuleConceptDefinitionBases;
}


std::any CongParser::ConceptDefinitionBasesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(61);
    match(CongParser::T__1);
    setState(62);
    qualifiedIdentifier();
    setState(67);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::T__4) {
      setState(63);
      match(CongParser::T__4);
      setState(64);
      qualifiedIdentifier();
      setState(69);
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(70);
    match(CongParser::NAMESPACE);
    setState(71);
    antlrcpp::downCast<NamespaceStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(72);
    match(CongParser::LBRACE);
    setState(76);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 458752) != 0)) {
      setState(73);
      stmnt();
      setState(78);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(79);
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(81);
    match(CongParser::FUNCTION);
    setState(82);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(83);
    parameterList();
    setState(84);
    match(CongParser::T__5);
    setState(85);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->type = qualifiedIdentifier();
    setState(86);
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(88);
    match(CongParser::LBRACE);
    setState(92);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3670016) != 0)) {
      setState(89);
      functionBodyStmnt();
      setState(94);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(95);
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

CongParser::ExpressionContext* CongParser::FunctionGenericImplContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

tree::TerminalNode* CongParser::FunctionGenericImplContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

CongParser::GenericImplDetailsContext* CongParser::FunctionGenericImplContext::genericImplDetails() {
  return getRuleContext<CongParser::GenericImplDetailsContext>(0);
}

CongParser::FunctionGenericImplContext::FunctionGenericImplContext(FunctionBodyStmntContext *ctx) { copyFrom(ctx); }


std::any CongParser::FunctionGenericImplContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
    setState(118);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::DESCRIPTION: {
        _localctx = _tracker.createInstance<CongParser::FunctionDescriptionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(97);
        match(CongParser::DESCRIPTION);
        setState(98);
        match(CongParser::LBRACE);
        setState(99);
        literal();
        setState(100);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::GENERICIMPL: {
        _localctx = _tracker.createInstance<CongParser::FunctionGenericImplContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(102);
        match(CongParser::GENERICIMPL);
        setState(104);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CongParser::T__0) {
          setState(103);
          genericImplDetails();
        }
        setState(106);
        match(CongParser::LBRACE);
        setState(107);
        expression(0);
        setState(108);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::REQUIRES: {
        _localctx = _tracker.createInstance<CongParser::FunctionExpRequiresContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(110);
        match(CongParser::REQUIRES);
        setState(112);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CongParser::IDENTIFIER) {
          setState(111);
          antlrcpp::downCast<FunctionExpRequiresContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
        }
        setState(114);
        match(CongParser::LBRACE);
        setState(115);
        expression(0);
        setState(116);
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

//----------------- ParameterListContext ------------------------------------------------------------------

CongParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CongParser::ParameterContext *> CongParser::ParameterListContext::parameter() {
  return getRuleContexts<CongParser::ParameterContext>();
}

CongParser::ParameterContext* CongParser::ParameterListContext::parameter(size_t i) {
  return getRuleContext<CongParser::ParameterContext>(i);
}


size_t CongParser::ParameterListContext::getRuleIndex() const {
  return CongParser::RuleParameterList;
}


std::any CongParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ParameterListContext* CongParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 16, CongParser::RuleParameterList);
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
    setState(120);
    match(CongParser::T__0);
    setState(129);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::IDENTIFIER) {
      setState(121);
      parameter();
      setState(126);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::T__6) {
        setState(122);
        match(CongParser::T__6);
        setState(123);
        parameter();
        setState(128);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(131);
    match(CongParser::T__2);
   
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

std::vector<CongParser::GenericImplDetailContext *> CongParser::GenericImplDetailsContext::genericImplDetail() {
  return getRuleContexts<CongParser::GenericImplDetailContext>();
}

CongParser::GenericImplDetailContext* CongParser::GenericImplDetailsContext::genericImplDetail(size_t i) {
  return getRuleContext<CongParser::GenericImplDetailContext>(i);
}


size_t CongParser::GenericImplDetailsContext::getRuleIndex() const {
  return CongParser::RuleGenericImplDetails;
}


std::any CongParser::GenericImplDetailsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitGenericImplDetails(this);
  else
    return visitor->visitChildren(this);
}

CongParser::GenericImplDetailsContext* CongParser::genericImplDetails() {
  GenericImplDetailsContext *_localctx = _tracker.createInstance<GenericImplDetailsContext>(_ctx, getState());
  enterRule(_localctx, 18, CongParser::RuleGenericImplDetails);
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
    setState(133);
    match(CongParser::T__0);
    setState(142);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::TIME

    || _la == CongParser::SPACE) {
      setState(134);
      genericImplDetail();
      setState(139);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::T__6) {
        setState(135);
        match(CongParser::T__6);
        setState(136);
        genericImplDetail();
        setState(141);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(144);
    match(CongParser::T__2);
   
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

CongParser::ExpressionContext* CongParser::GenericImplDetailContext::expression() {
  return getRuleContext<CongParser::ExpressionContext>(0);
}

tree::TerminalNode* CongParser::GenericImplDetailContext::SPACE() {
  return getToken(CongParser::SPACE, 0);
}


size_t CongParser::GenericImplDetailContext::getRuleIndex() const {
  return CongParser::RuleGenericImplDetail;
}


std::any CongParser::GenericImplDetailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitGenericImplDetail(this);
  else
    return visitor->visitChildren(this);
}

CongParser::GenericImplDetailContext* CongParser::genericImplDetail() {
  GenericImplDetailContext *_localctx = _tracker.createInstance<GenericImplDetailContext>(_ctx, getState());
  enterRule(_localctx, 20, CongParser::RuleGenericImplDetail);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(152);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::TIME: {
        enterOuterAlt(_localctx, 1);
        setState(146);
        match(CongParser::TIME);
        setState(147);
        match(CongParser::T__1);
        setState(148);
        expression(0);
        break;
      }

      case CongParser::SPACE: {
        enterOuterAlt(_localctx, 2);
        setState(149);
        match(CongParser::SPACE);
        setState(150);
        match(CongParser::T__1);
        setState(151);
        expression(0);
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

//----------------- ParameterContext ------------------------------------------------------------------

CongParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ParameterContext* CongParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 22, CongParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(154);
    antlrcpp::downCast<ParameterContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(155);
    match(CongParser::T__1);
    setState(156);
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

CongParser::QualifiedIdentifierContext* CongParser::CallExpressionContext::qualifiedIdentifier() {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(0);
}

std::vector<CongParser::ExpressionContext *> CongParser::CallExpressionContext::expression() {
  return getRuleContexts<CongParser::ExpressionContext>();
}

CongParser::ExpressionContext* CongParser::CallExpressionContext::expression(size_t i) {
  return getRuleContext<CongParser::ExpressionContext>(i);
}

CongParser::CallExpressionContext::CallExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::CallExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitCallExpression(this);
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

CongParser::ArithmeticExpressionContext::ArithmeticExpressionContext(ExpressionContext *ctx) { copyFrom(ctx); }


std::any CongParser::ArithmeticExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
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
  size_t startState = 24;
  enterRecursionRule(_localctx, 24, CongParser::RuleExpression, precedence);

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
    setState(175);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(159);
      antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->val = literal();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CallExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(160);
      antlrcpp::downCast<CallExpressionContext *>(_localctx)->fun = qualifiedIdentifier();
      setState(161);
      match(CongParser::T__0);
      setState(170);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4160782336) != 0)) {
        setState(162);
        expression(0);
        setState(167);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CongParser::T__6) {
          setState(163);
          match(CongParser::T__6);
          setState(164);
          expression(0);
          setState(169);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(172);
      match(CongParser::T__2);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ParameterReferenceExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(174);
      antlrcpp::downCast<ParameterReferenceExpressionContext *>(_localctx)->param = match(CongParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(182);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArithmeticExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        newContext->left = previousContext;
        pushNewRecursionContext(newContext, startState, RuleExpression);
        setState(177);

        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
        setState(178);
        antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 7936) != 0))) {
          antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(179);
        antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->right = expression(5); 
      }
      setState(184);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    }
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitPlaceholderOrQualifiedId(this);
  else
    return visitor->visitChildren(this);
}

CongParser::PlaceholderOrQualifiedIdContext* CongParser::placeholderOrQualifiedId() {
  PlaceholderOrQualifiedIdContext *_localctx = _tracker.createInstance<PlaceholderOrQualifiedIdContext>(_ctx, getState());
  enterRule(_localctx, 26, CongParser::RulePlaceholderOrQualifiedId);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(187);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::T__14:
      case CongParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(185);
        qualifiedIdentifier();
        break;
      }

      case CongParser::T__12: {
        enterOuterAlt(_localctx, 2);
        setState(186);
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

tree::TerminalNode* CongParser::PlaceholderContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}


size_t CongParser::PlaceholderContext::getRuleIndex() const {
  return CongParser::RulePlaceholder;
}


std::any CongParser::PlaceholderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitPlaceholder(this);
  else
    return visitor->visitChildren(this);
}

CongParser::PlaceholderContext* CongParser::placeholder() {
  PlaceholderContext *_localctx = _tracker.createInstance<PlaceholderContext>(_ctx, getState());
  enterRule(_localctx, 28, CongParser::RulePlaceholder);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(CongParser::T__12);
    setState(190);
    antlrcpp::downCast<PlaceholderContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(191);
    match(CongParser::T__13);
   
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


size_t CongParser::QualifiedIdentifierContext::getRuleIndex() const {
  return CongParser::RuleQualifiedIdentifier;
}


std::any CongParser::QualifiedIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitQualifiedIdentifier(this);
  else
    return visitor->visitChildren(this);
}

CongParser::QualifiedIdentifierContext* CongParser::qualifiedIdentifier() {
  QualifiedIdentifierContext *_localctx = _tracker.createInstance<QualifiedIdentifierContext>(_ctx, getState());
  enterRule(_localctx, 30, CongParser::RuleQualifiedIdentifier);
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
    setState(194);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::T__14) {
      setState(193);
      match(CongParser::T__14);
    }
    setState(196);
    match(CongParser::IDENTIFIER);
    setState(201);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::T__14) {
      setState(197);
      match(CongParser::T__14);
      setState(198);
      match(CongParser::IDENTIFIER);
      setState(203);
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
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

CongParser::LiteralContext* CongParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 32, CongParser::RuleLiteral);
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
    setState(204);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2013265920) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
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
    case 12: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CongParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);

  default:
    break;
  }
  return true;
}

void CongParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  congParserInitialize();
#else
  ::antlr4::internal::call_once(congParserOnceFlag, congParserInitialize);
#endif
}
