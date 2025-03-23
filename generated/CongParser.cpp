
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
      "translationUnit", "stmnt", "familyStmnt", "familyHeader", "familyBody", 
      "familyBodyStmnt", "conceptDefinitionStmnt", "conceptDefinitionBases", 
      "namespaceStmnt", "functionStmnt", "functionBody", "functionBodyStmnt", 
      "parameterList", "parameter", "expression", "placeholderOrQualifiedId", 
      "conceptPlaceholder", "typename", "qualifiedIdentifier", "literal"
    },
    std::vector<std::string>{
      "", "','", "':'", "'void'", "'('", "')'", "';'", "'&'", "'->'", "'+'", 
      "'-'", "'*'", "'/'", "'%'", "'<'", "'>'", "'String'", "'Number'", 
      "'Real'", "'Bool'", "'Void'", "'::'", "'concept'", "'fun'", "'namespace'", 
      "'description'", "'generic'", "'requires'", "'family'", "'{'", "'}'", 
      "'...'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "CONCEPT", "FUNCTION", "NAMESPACE", "DESCRIPTION", 
      "GENERICIMPL", "REQUIRES", "FAMILY", "LBRACE", "RBRACE", "VARARGS", 
      "REAL", "BOOL", "NUMBER", "STRING", "IDENTIFIER", "WHITESPACE", "COMMENT", 
      "LINE_COMMENT", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,40,223,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,1,0,5,0,42,8,0,10,
  	0,12,0,45,9,0,1,0,1,0,1,1,1,1,1,1,3,1,52,8,1,1,2,1,2,1,2,1,2,1,2,5,2,
  	59,8,2,10,2,12,2,62,9,2,3,2,64,8,2,1,2,1,2,1,3,1,3,1,3,1,3,1,4,1,4,5,
  	4,74,8,4,10,4,12,4,77,9,4,1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	3,6,90,8,6,1,6,3,6,93,8,6,1,6,1,6,1,7,1,7,1,7,1,7,5,7,101,8,7,10,7,12,
  	7,104,9,7,1,8,1,8,1,8,1,8,5,8,110,8,8,10,8,12,8,113,9,8,1,8,1,8,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,5,10,126,8,10,10,10,12,10,129,9,10,1,
  	10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,
  	11,1,11,1,11,3,11,148,8,11,1,12,1,12,1,12,1,12,5,12,154,8,12,10,12,12,
  	12,157,9,12,3,12,159,8,12,1,12,1,12,1,13,1,13,1,13,1,13,1,14,1,14,1,14,
  	1,14,1,14,1,14,1,14,5,14,174,8,14,10,14,12,14,177,9,14,3,14,179,8,14,
  	1,14,1,14,1,14,3,14,184,8,14,1,14,1,14,1,14,5,14,189,8,14,10,14,12,14,
  	192,9,14,1,15,1,15,3,15,196,8,15,1,16,1,16,1,16,1,16,1,17,1,17,1,17,1,
  	17,1,17,1,17,3,17,208,8,17,1,18,3,18,211,8,18,1,18,1,18,1,18,5,18,216,
  	8,18,10,18,12,18,219,9,18,1,19,1,19,1,19,0,1,28,20,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,36,38,0,2,1,0,9,13,1,0,32,35,230,0,43,1,
  	0,0,0,2,51,1,0,0,0,4,53,1,0,0,0,6,67,1,0,0,0,8,71,1,0,0,0,10,80,1,0,0,
  	0,12,82,1,0,0,0,14,96,1,0,0,0,16,105,1,0,0,0,18,116,1,0,0,0,20,123,1,
  	0,0,0,22,147,1,0,0,0,24,149,1,0,0,0,26,162,1,0,0,0,28,183,1,0,0,0,30,
  	195,1,0,0,0,32,197,1,0,0,0,34,207,1,0,0,0,36,210,1,0,0,0,38,220,1,0,0,
  	0,40,42,3,2,1,0,41,40,1,0,0,0,42,45,1,0,0,0,43,41,1,0,0,0,43,44,1,0,0,
  	0,44,46,1,0,0,0,45,43,1,0,0,0,46,47,5,0,0,1,47,1,1,0,0,0,48,52,3,12,6,
  	0,49,52,3,16,8,0,50,52,3,18,9,0,51,48,1,0,0,0,51,49,1,0,0,0,51,50,1,0,
  	0,0,52,3,1,0,0,0,53,54,5,28,0,0,54,63,5,36,0,0,55,60,3,6,3,0,56,57,5,
  	1,0,0,57,59,3,6,3,0,58,56,1,0,0,0,59,62,1,0,0,0,60,58,1,0,0,0,60,61,1,
  	0,0,0,61,64,1,0,0,0,62,60,1,0,0,0,63,55,1,0,0,0,63,64,1,0,0,0,64,65,1,
  	0,0,0,65,66,3,8,4,0,66,5,1,0,0,0,67,68,5,36,0,0,68,69,5,2,0,0,69,70,3,
  	34,17,0,70,7,1,0,0,0,71,75,5,29,0,0,72,74,3,10,5,0,73,72,1,0,0,0,74,77,
  	1,0,0,0,75,73,1,0,0,0,75,76,1,0,0,0,76,78,1,0,0,0,77,75,1,0,0,0,78,79,
  	5,30,0,0,79,9,1,0,0,0,80,81,5,3,0,0,81,11,1,0,0,0,82,83,5,22,0,0,83,89,
  	5,36,0,0,84,85,5,4,0,0,85,86,5,25,0,0,86,87,5,2,0,0,87,88,5,35,0,0,88,
  	90,5,5,0,0,89,84,1,0,0,0,89,90,1,0,0,0,90,92,1,0,0,0,91,93,3,14,7,0,92,
  	91,1,0,0,0,92,93,1,0,0,0,93,94,1,0,0,0,94,95,5,6,0,0,95,13,1,0,0,0,96,
  	97,5,2,0,0,97,102,3,36,18,0,98,99,5,7,0,0,99,101,3,36,18,0,100,98,1,0,
  	0,0,101,104,1,0,0,0,102,100,1,0,0,0,102,103,1,0,0,0,103,15,1,0,0,0,104,
  	102,1,0,0,0,105,106,5,24,0,0,106,107,5,36,0,0,107,111,5,29,0,0,108,110,
  	3,2,1,0,109,108,1,0,0,0,110,113,1,0,0,0,111,109,1,0,0,0,111,112,1,0,0,
  	0,112,114,1,0,0,0,113,111,1,0,0,0,114,115,5,30,0,0,115,17,1,0,0,0,116,
  	117,5,23,0,0,117,118,5,36,0,0,118,119,3,24,12,0,119,120,5,8,0,0,120,121,
  	3,36,18,0,121,122,3,20,10,0,122,19,1,0,0,0,123,127,5,29,0,0,124,126,3,
  	22,11,0,125,124,1,0,0,0,126,129,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,
  	0,128,130,1,0,0,0,129,127,1,0,0,0,130,131,5,30,0,0,131,21,1,0,0,0,132,
  	133,5,25,0,0,133,134,5,29,0,0,134,135,3,38,19,0,135,136,5,30,0,0,136,
  	148,1,0,0,0,137,138,5,26,0,0,138,139,5,29,0,0,139,140,3,28,14,0,140,141,
  	5,30,0,0,141,148,1,0,0,0,142,143,5,27,0,0,143,144,5,29,0,0,144,145,3,
  	28,14,0,145,146,5,30,0,0,146,148,1,0,0,0,147,132,1,0,0,0,147,137,1,0,
  	0,0,147,142,1,0,0,0,148,23,1,0,0,0,149,158,5,4,0,0,150,155,3,26,13,0,
  	151,152,5,1,0,0,152,154,3,26,13,0,153,151,1,0,0,0,154,157,1,0,0,0,155,
  	153,1,0,0,0,155,156,1,0,0,0,156,159,1,0,0,0,157,155,1,0,0,0,158,150,1,
  	0,0,0,158,159,1,0,0,0,159,160,1,0,0,0,160,161,5,5,0,0,161,25,1,0,0,0,
  	162,163,5,36,0,0,163,164,5,2,0,0,164,165,3,30,15,0,165,27,1,0,0,0,166,
  	167,6,14,-1,0,167,184,3,38,19,0,168,169,3,36,18,0,169,178,5,4,0,0,170,
  	175,3,28,14,0,171,172,5,1,0,0,172,174,3,28,14,0,173,171,1,0,0,0,174,177,
  	1,0,0,0,175,173,1,0,0,0,175,176,1,0,0,0,176,179,1,0,0,0,177,175,1,0,0,
  	0,178,170,1,0,0,0,178,179,1,0,0,0,179,180,1,0,0,0,180,181,5,5,0,0,181,
  	184,1,0,0,0,182,184,5,36,0,0,183,166,1,0,0,0,183,168,1,0,0,0,183,182,
  	1,0,0,0,184,190,1,0,0,0,185,186,10,4,0,0,186,187,7,0,0,0,187,189,3,28,
  	14,5,188,185,1,0,0,0,189,192,1,0,0,0,190,188,1,0,0,0,190,191,1,0,0,0,
  	191,29,1,0,0,0,192,190,1,0,0,0,193,196,3,36,18,0,194,196,3,32,16,0,195,
  	193,1,0,0,0,195,194,1,0,0,0,196,31,1,0,0,0,197,198,5,14,0,0,198,199,5,
  	36,0,0,199,200,5,15,0,0,200,33,1,0,0,0,201,208,5,16,0,0,202,208,5,17,
  	0,0,203,208,5,18,0,0,204,208,5,19,0,0,205,208,5,20,0,0,206,208,3,36,18,
  	0,207,201,1,0,0,0,207,202,1,0,0,0,207,203,1,0,0,0,207,204,1,0,0,0,207,
  	205,1,0,0,0,207,206,1,0,0,0,208,35,1,0,0,0,209,211,5,21,0,0,210,209,1,
  	0,0,0,210,211,1,0,0,0,211,212,1,0,0,0,212,217,5,36,0,0,213,214,5,21,0,
  	0,214,216,5,36,0,0,215,213,1,0,0,0,216,219,1,0,0,0,217,215,1,0,0,0,217,
  	218,1,0,0,0,218,37,1,0,0,0,219,217,1,0,0,0,220,221,7,1,0,0,221,39,1,0,
  	0,0,21,43,51,60,63,75,89,92,102,111,127,147,155,158,175,178,183,190,195,
  	207,210,217
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
    setState(43);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 29360128) != 0)) {
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

//----------------- FamilyStmntContext ------------------------------------------------------------------

CongParser::FamilyStmntContext::FamilyStmntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::FamilyStmntContext::FAMILY() {
  return getToken(CongParser::FAMILY, 0);
}

CongParser::FamilyBodyContext* CongParser::FamilyStmntContext::familyBody() {
  return getRuleContext<CongParser::FamilyBodyContext>(0);
}

tree::TerminalNode* CongParser::FamilyStmntContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

std::vector<CongParser::FamilyHeaderContext *> CongParser::FamilyStmntContext::familyHeader() {
  return getRuleContexts<CongParser::FamilyHeaderContext>();
}

CongParser::FamilyHeaderContext* CongParser::FamilyStmntContext::familyHeader(size_t i) {
  return getRuleContext<CongParser::FamilyHeaderContext>(i);
}


size_t CongParser::FamilyStmntContext::getRuleIndex() const {
  return CongParser::RuleFamilyStmnt;
}


std::any CongParser::FamilyStmntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitFamilyStmnt(this);
  else
    return visitor->visitChildren(this);
}

CongParser::FamilyStmntContext* CongParser::familyStmnt() {
  FamilyStmntContext *_localctx = _tracker.createInstance<FamilyStmntContext>(_ctx, getState());
  enterRule(_localctx, 4, CongParser::RuleFamilyStmnt);
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
    match(CongParser::FAMILY);
    setState(54);
    antlrcpp::downCast<FamilyStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(63);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::IDENTIFIER) {
      setState(55);
      familyHeader();
      setState(60);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::T__0) {
        setState(56);
        match(CongParser::T__0);
        setState(57);
        familyHeader();
        setState(62);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(65);
    familyBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FamilyHeaderContext ------------------------------------------------------------------

CongParser::FamilyHeaderContext::FamilyHeaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::FamilyHeaderContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}

CongParser::TypenameContext* CongParser::FamilyHeaderContext::typename_() {
  return getRuleContext<CongParser::TypenameContext>(0);
}


size_t CongParser::FamilyHeaderContext::getRuleIndex() const {
  return CongParser::RuleFamilyHeader;
}


std::any CongParser::FamilyHeaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitFamilyHeader(this);
  else
    return visitor->visitChildren(this);
}

CongParser::FamilyHeaderContext* CongParser::familyHeader() {
  FamilyHeaderContext *_localctx = _tracker.createInstance<FamilyHeaderContext>(_ctx, getState());
  enterRule(_localctx, 6, CongParser::RuleFamilyHeader);

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
    match(CongParser::IDENTIFIER);
    setState(68);
    match(CongParser::T__1);
    setState(69);
    antlrcpp::downCast<FamilyHeaderContext *>(_localctx)->type = typename_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FamilyBodyContext ------------------------------------------------------------------

CongParser::FamilyBodyContext::FamilyBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::FamilyBodyContext::LBRACE() {
  return getToken(CongParser::LBRACE, 0);
}

tree::TerminalNode* CongParser::FamilyBodyContext::RBRACE() {
  return getToken(CongParser::RBRACE, 0);
}

std::vector<CongParser::FamilyBodyStmntContext *> CongParser::FamilyBodyContext::familyBodyStmnt() {
  return getRuleContexts<CongParser::FamilyBodyStmntContext>();
}

CongParser::FamilyBodyStmntContext* CongParser::FamilyBodyContext::familyBodyStmnt(size_t i) {
  return getRuleContext<CongParser::FamilyBodyStmntContext>(i);
}


size_t CongParser::FamilyBodyContext::getRuleIndex() const {
  return CongParser::RuleFamilyBody;
}


std::any CongParser::FamilyBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitFamilyBody(this);
  else
    return visitor->visitChildren(this);
}

CongParser::FamilyBodyContext* CongParser::familyBody() {
  FamilyBodyContext *_localctx = _tracker.createInstance<FamilyBodyContext>(_ctx, getState());
  enterRule(_localctx, 8, CongParser::RuleFamilyBody);
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
    match(CongParser::LBRACE);
    setState(75);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::T__2) {
      setState(72);
      familyBodyStmnt();
      setState(77);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(78);
    match(CongParser::RBRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FamilyBodyStmntContext ------------------------------------------------------------------

CongParser::FamilyBodyStmntContext::FamilyBodyStmntContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CongParser::FamilyBodyStmntContext::getRuleIndex() const {
  return CongParser::RuleFamilyBodyStmnt;
}


std::any CongParser::FamilyBodyStmntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitFamilyBodyStmnt(this);
  else
    return visitor->visitChildren(this);
}

CongParser::FamilyBodyStmntContext* CongParser::familyBodyStmnt() {
  FamilyBodyStmntContext *_localctx = _tracker.createInstance<FamilyBodyStmntContext>(_ctx, getState());
  enterRule(_localctx, 10, CongParser::RuleFamilyBodyStmnt);

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
    match(CongParser::T__2);
   
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
  enterRule(_localctx, 12, CongParser::RuleConceptDefinitionStmnt);
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
    setState(82);
    match(CongParser::CONCEPT);
    setState(83);
    antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(89);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::T__3) {
      setState(84);
      match(CongParser::T__3);
      setState(85);
      match(CongParser::DESCRIPTION);
      setState(86);
      match(CongParser::T__1);
      setState(87);
      antlrcpp::downCast<ConceptDefinitionStmntContext *>(_localctx)->desc = match(CongParser::STRING);
      setState(88);
      match(CongParser::T__4);
    }
    setState(92);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::T__1) {
      setState(91);
      conceptDefinitionBases();
    }
    setState(94);
    match(CongParser::T__5);
   
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
  enterRule(_localctx, 14, CongParser::RuleConceptDefinitionBases);
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
    setState(96);
    match(CongParser::T__1);
    setState(97);
    qualifiedIdentifier();
    setState(102);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::T__6) {
      setState(98);
      match(CongParser::T__6);
      setState(99);
      qualifiedIdentifier();
      setState(104);
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
  enterRule(_localctx, 16, CongParser::RuleNamespaceStmnt);
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
    setState(105);
    match(CongParser::NAMESPACE);
    setState(106);
    antlrcpp::downCast<NamespaceStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(107);
    match(CongParser::LBRACE);
    setState(111);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 29360128) != 0)) {
      setState(108);
      stmnt();
      setState(113);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(114);
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
  enterRule(_localctx, 18, CongParser::RuleFunctionStmnt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(CongParser::FUNCTION);
    setState(117);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(118);
    parameterList();
    setState(119);
    match(CongParser::T__7);
    setState(120);
    antlrcpp::downCast<FunctionStmntContext *>(_localctx)->type = qualifiedIdentifier();
    setState(121);
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
  enterRule(_localctx, 20, CongParser::RuleFunctionBody);
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
    setState(123);
    match(CongParser::LBRACE);
    setState(127);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 234881024) != 0)) {
      setState(124);
      functionBodyStmnt();
      setState(129);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(130);
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
  enterRule(_localctx, 22, CongParser::RuleFunctionBodyStmnt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(147);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::DESCRIPTION: {
        _localctx = _tracker.createInstance<CongParser::FunctionDescriptionContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(132);
        match(CongParser::DESCRIPTION);
        setState(133);
        match(CongParser::LBRACE);
        setState(134);
        literal();
        setState(135);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::GENERICIMPL: {
        _localctx = _tracker.createInstance<CongParser::FunctionGenericImplContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(137);
        match(CongParser::GENERICIMPL);
        setState(138);
        match(CongParser::LBRACE);
        setState(139);
        expression(0);
        setState(140);
        match(CongParser::RBRACE);
        break;
      }

      case CongParser::REQUIRES: {
        _localctx = _tracker.createInstance<CongParser::FunctionExpRequiresContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(142);
        match(CongParser::REQUIRES);
        setState(143);
        match(CongParser::LBRACE);
        setState(144);
        expression(0);
        setState(145);
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
  enterRule(_localctx, 24, CongParser::RuleParameterList);
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
    setState(149);
    match(CongParser::T__3);
    setState(158);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::IDENTIFIER) {
      setState(150);
      parameter();
      setState(155);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CongParser::T__0) {
        setState(151);
        match(CongParser::T__0);
        setState(152);
        parameter();
        setState(157);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(160);
    match(CongParser::T__4);
   
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
    setState(162);
    antlrcpp::downCast<ParameterContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(163);
    match(CongParser::T__1);
    setState(164);
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
    setState(183);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<LiteralExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(167);
      antlrcpp::downCast<LiteralExpressionContext *>(_localctx)->val = literal();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CallExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(168);
      antlrcpp::downCast<CallExpressionContext *>(_localctx)->fun = qualifiedIdentifier();
      setState(169);
      match(CongParser::T__3);
      setState(178);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 133146083328) != 0)) {
        setState(170);
        expression(0);
        setState(175);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CongParser::T__0) {
          setState(171);
          match(CongParser::T__0);
          setState(172);
          expression(0);
          setState(177);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(180);
      match(CongParser::T__4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ParameterReferenceExpressionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(182);
      antlrcpp::downCast<ParameterReferenceExpressionContext *>(_localctx)->param = match(CongParser::IDENTIFIER);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(190);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArithmeticExpressionContext>(_tracker.createInstance<ExpressionContext>(parentContext, parentState));
        _localctx = newContext;
        newContext->left = previousContext;
        pushNewRecursionContext(newContext, startState, RuleExpression);
        setState(185);

        if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
        setState(186);
        antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 15872) != 0))) {
          antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(187);
        antlrcpp::downCast<ArithmeticExpressionContext *>(_localctx)->right = expression(5); 
      }
      setState(192);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
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

CongParser::ConceptPlaceholderContext* CongParser::PlaceholderOrQualifiedIdContext::conceptPlaceholder() {
  return getRuleContext<CongParser::ConceptPlaceholderContext>(0);
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
  enterRule(_localctx, 30, CongParser::RulePlaceholderOrQualifiedId);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::T__20:
      case CongParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(193);
        qualifiedIdentifier();
        break;
      }

      case CongParser::T__13: {
        enterOuterAlt(_localctx, 2);
        setState(194);
        conceptPlaceholder();
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

//----------------- ConceptPlaceholderContext ------------------------------------------------------------------

CongParser::ConceptPlaceholderContext::ConceptPlaceholderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CongParser::ConceptPlaceholderContext::IDENTIFIER() {
  return getToken(CongParser::IDENTIFIER, 0);
}


size_t CongParser::ConceptPlaceholderContext::getRuleIndex() const {
  return CongParser::RuleConceptPlaceholder;
}


std::any CongParser::ConceptPlaceholderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitConceptPlaceholder(this);
  else
    return visitor->visitChildren(this);
}

CongParser::ConceptPlaceholderContext* CongParser::conceptPlaceholder() {
  ConceptPlaceholderContext *_localctx = _tracker.createInstance<ConceptPlaceholderContext>(_ctx, getState());
  enterRule(_localctx, 32, CongParser::RuleConceptPlaceholder);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    match(CongParser::T__13);
    setState(198);
    antlrcpp::downCast<ConceptPlaceholderContext *>(_localctx)->name = match(CongParser::IDENTIFIER);
    setState(199);
    match(CongParser::T__14);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypenameContext ------------------------------------------------------------------

CongParser::TypenameContext::TypenameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CongParser::QualifiedIdentifierContext* CongParser::TypenameContext::qualifiedIdentifier() {
  return getRuleContext<CongParser::QualifiedIdentifierContext>(0);
}


size_t CongParser::TypenameContext::getRuleIndex() const {
  return CongParser::RuleTypename;
}


std::any CongParser::TypenameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CongVisitor*>(visitor))
    return parserVisitor->visitTypename(this);
  else
    return visitor->visitChildren(this);
}

CongParser::TypenameContext* CongParser::typename_() {
  TypenameContext *_localctx = _tracker.createInstance<TypenameContext>(_ctx, getState());
  enterRule(_localctx, 34, CongParser::RuleTypename);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(207);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CongParser::T__15: {
        enterOuterAlt(_localctx, 1);
        setState(201);
        match(CongParser::T__15);
        break;
      }

      case CongParser::T__16: {
        enterOuterAlt(_localctx, 2);
        setState(202);
        match(CongParser::T__16);
        break;
      }

      case CongParser::T__17: {
        enterOuterAlt(_localctx, 3);
        setState(203);
        match(CongParser::T__17);
        break;
      }

      case CongParser::T__18: {
        enterOuterAlt(_localctx, 4);
        setState(204);
        match(CongParser::T__18);
        break;
      }

      case CongParser::T__19: {
        enterOuterAlt(_localctx, 5);
        setState(205);
        match(CongParser::T__19);
        break;
      }

      case CongParser::T__20:
      case CongParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 6);
        setState(206);
        qualifiedIdentifier();
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
    setState(210);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CongParser::T__20) {
      setState(209);
      match(CongParser::T__20);
    }
    setState(212);
    match(CongParser::IDENTIFIER);
    setState(217);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CongParser::T__20) {
      setState(213);
      match(CongParser::T__20);
      setState(214);
      match(CongParser::IDENTIFIER);
      setState(219);
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
  enterRule(_localctx, 38, CongParser::RuleLiteral);
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
    setState(220);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 64424509440) != 0))) {
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
    case 14: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

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
