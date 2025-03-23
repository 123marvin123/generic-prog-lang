// Generated from /Users/haschker/CLionProjects/masterthesis-transpiler/grammar/Cong.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class CongParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.2", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, CONCEPT=16, 
		FUNCTION=17, NAMESPACE=18, DESCRIPTION=19, GENERICIMPL=20, REQUIRES=21, 
		LBRACE=22, RBRACE=23, VARARGS=24, REAL=25, BOOL=26, NUMBER=27, STRING=28, 
		IDENTIFIER=29, WHITESPACE=30, COMMENT=31, LINE_COMMENT=32, OTHER=33;
	public static final int
		RULE_translationUnit = 0, RULE_stmnt = 1, RULE_conceptDefinitionStmnt = 2, 
		RULE_conceptDefinitionBases = 3, RULE_namespaceStmnt = 4, RULE_functionStmnt = 5, 
		RULE_functionBody = 6, RULE_functionBodyStmnt = 7, RULE_parameterList = 8, 
		RULE_parameter = 9, RULE_expression = 10, RULE_placeholderOrQualifiedId = 11, 
		RULE_conceptPlaceholder = 12, RULE_qualifiedIdentifier = 13, RULE_literal = 14;
	private static String[] makeRuleNames() {
		return new String[] {
			"translationUnit", "stmnt", "conceptDefinitionStmnt", "conceptDefinitionBases", 
			"namespaceStmnt", "functionStmnt", "functionBody", "functionBodyStmnt", 
			"parameterList", "parameter", "expression", "placeholderOrQualifiedId", 
			"conceptPlaceholder", "qualifiedIdentifier", "literal"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'('", "':'", "')'", "';'", "'&'", "'->'", "','", "'+'", "'-'", 
			"'*'", "'/'", "'%'", "'<'", "'>'", "'::'", "'concept'", "'fun'", "'namespace'", 
			"'description'", "'generic'", "'requires'", "'{'", "'}'", "'...'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, "CONCEPT", "FUNCTION", "NAMESPACE", "DESCRIPTION", 
			"GENERICIMPL", "REQUIRES", "LBRACE", "RBRACE", "VARARGS", "REAL", "BOOL", 
			"NUMBER", "STRING", "IDENTIFIER", "WHITESPACE", "COMMENT", "LINE_COMMENT", 
			"OTHER"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "Cong.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public CongParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class TranslationUnitContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(CongParser.EOF, 0); }
		public List<StmntContext> stmnt() {
			return getRuleContexts(StmntContext.class);
		}
		public StmntContext stmnt(int i) {
			return getRuleContext(StmntContext.class,i);
		}
		public TranslationUnitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_translationUnit; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterTranslationUnit(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitTranslationUnit(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitTranslationUnit(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TranslationUnitContext translationUnit() throws RecognitionException {
		TranslationUnitContext _localctx = new TranslationUnitContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_translationUnit);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(33);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 458752L) != 0)) {
				{
				{
				setState(30);
				stmnt();
				}
				}
				setState(35);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(36);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StmntContext extends ParserRuleContext {
		public ConceptDefinitionStmntContext conceptDefinitionStmnt() {
			return getRuleContext(ConceptDefinitionStmntContext.class,0);
		}
		public NamespaceStmntContext namespaceStmnt() {
			return getRuleContext(NamespaceStmntContext.class,0);
		}
		public FunctionStmntContext functionStmnt() {
			return getRuleContext(FunctionStmntContext.class,0);
		}
		public StmntContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmnt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterStmnt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitStmnt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitStmnt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StmntContext stmnt() throws RecognitionException {
		StmntContext _localctx = new StmntContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_stmnt);
		try {
			setState(41);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case CONCEPT:
				enterOuterAlt(_localctx, 1);
				{
				setState(38);
				conceptDefinitionStmnt();
				}
				break;
			case NAMESPACE:
				enterOuterAlt(_localctx, 2);
				{
				setState(39);
				namespaceStmnt();
				}
				break;
			case FUNCTION:
				enterOuterAlt(_localctx, 3);
				{
				setState(40);
				functionStmnt();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConceptDefinitionStmntContext extends ParserRuleContext {
		public Token name;
		public Token desc;
		public TerminalNode CONCEPT() { return getToken(CongParser.CONCEPT, 0); }
		public TerminalNode IDENTIFIER() { return getToken(CongParser.IDENTIFIER, 0); }
		public TerminalNode DESCRIPTION() { return getToken(CongParser.DESCRIPTION, 0); }
		public ConceptDefinitionBasesContext conceptDefinitionBases() {
			return getRuleContext(ConceptDefinitionBasesContext.class,0);
		}
		public TerminalNode STRING() { return getToken(CongParser.STRING, 0); }
		public ConceptDefinitionStmntContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_conceptDefinitionStmnt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterConceptDefinitionStmnt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitConceptDefinitionStmnt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitConceptDefinitionStmnt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ConceptDefinitionStmntContext conceptDefinitionStmnt() throws RecognitionException {
		ConceptDefinitionStmntContext _localctx = new ConceptDefinitionStmntContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_conceptDefinitionStmnt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(43);
			match(CONCEPT);
			setState(44);
			((ConceptDefinitionStmntContext)_localctx).name = match(IDENTIFIER);
			setState(50);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__0) {
				{
				setState(45);
				match(T__0);
				setState(46);
				match(DESCRIPTION);
				setState(47);
				match(T__1);
				setState(48);
				((ConceptDefinitionStmntContext)_localctx).desc = match(STRING);
				setState(49);
				match(T__2);
				}
			}

			setState(53);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__1) {
				{
				setState(52);
				conceptDefinitionBases();
				}
			}

			setState(55);
			match(T__3);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConceptDefinitionBasesContext extends ParserRuleContext {
		public List<QualifiedIdentifierContext> qualifiedIdentifier() {
			return getRuleContexts(QualifiedIdentifierContext.class);
		}
		public QualifiedIdentifierContext qualifiedIdentifier(int i) {
			return getRuleContext(QualifiedIdentifierContext.class,i);
		}
		public ConceptDefinitionBasesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_conceptDefinitionBases; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterConceptDefinitionBases(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitConceptDefinitionBases(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitConceptDefinitionBases(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ConceptDefinitionBasesContext conceptDefinitionBases() throws RecognitionException {
		ConceptDefinitionBasesContext _localctx = new ConceptDefinitionBasesContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_conceptDefinitionBases);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(57);
			match(T__1);
			setState(58);
			qualifiedIdentifier();
			setState(63);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__4) {
				{
				{
				setState(59);
				match(T__4);
				setState(60);
				qualifiedIdentifier();
				}
				}
				setState(65);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class NamespaceStmntContext extends ParserRuleContext {
		public Token name;
		public TerminalNode NAMESPACE() { return getToken(CongParser.NAMESPACE, 0); }
		public TerminalNode LBRACE() { return getToken(CongParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(CongParser.RBRACE, 0); }
		public TerminalNode IDENTIFIER() { return getToken(CongParser.IDENTIFIER, 0); }
		public List<StmntContext> stmnt() {
			return getRuleContexts(StmntContext.class);
		}
		public StmntContext stmnt(int i) {
			return getRuleContext(StmntContext.class,i);
		}
		public NamespaceStmntContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_namespaceStmnt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterNamespaceStmnt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitNamespaceStmnt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitNamespaceStmnt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final NamespaceStmntContext namespaceStmnt() throws RecognitionException {
		NamespaceStmntContext _localctx = new NamespaceStmntContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_namespaceStmnt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(66);
			match(NAMESPACE);
			setState(67);
			((NamespaceStmntContext)_localctx).name = match(IDENTIFIER);
			setState(68);
			match(LBRACE);
			setState(72);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 458752L) != 0)) {
				{
				{
				setState(69);
				stmnt();
				}
				}
				setState(74);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(75);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionStmntContext extends ParserRuleContext {
		public Token name;
		public QualifiedIdentifierContext type;
		public TerminalNode FUNCTION() { return getToken(CongParser.FUNCTION, 0); }
		public ParameterListContext parameterList() {
			return getRuleContext(ParameterListContext.class,0);
		}
		public FunctionBodyContext functionBody() {
			return getRuleContext(FunctionBodyContext.class,0);
		}
		public TerminalNode IDENTIFIER() { return getToken(CongParser.IDENTIFIER, 0); }
		public QualifiedIdentifierContext qualifiedIdentifier() {
			return getRuleContext(QualifiedIdentifierContext.class,0);
		}
		public FunctionStmntContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionStmnt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterFunctionStmnt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitFunctionStmnt(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitFunctionStmnt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionStmntContext functionStmnt() throws RecognitionException {
		FunctionStmntContext _localctx = new FunctionStmntContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_functionStmnt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(77);
			match(FUNCTION);
			setState(78);
			((FunctionStmntContext)_localctx).name = match(IDENTIFIER);
			setState(79);
			parameterList();
			setState(80);
			match(T__5);
			setState(81);
			((FunctionStmntContext)_localctx).type = qualifiedIdentifier();
			setState(82);
			functionBody();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionBodyContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(CongParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(CongParser.RBRACE, 0); }
		public List<FunctionBodyStmntContext> functionBodyStmnt() {
			return getRuleContexts(FunctionBodyStmntContext.class);
		}
		public FunctionBodyStmntContext functionBodyStmnt(int i) {
			return getRuleContext(FunctionBodyStmntContext.class,i);
		}
		public FunctionBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionBody; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterFunctionBody(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitFunctionBody(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitFunctionBody(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionBodyContext functionBody() throws RecognitionException {
		FunctionBodyContext _localctx = new FunctionBodyContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_functionBody);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(84);
			match(LBRACE);
			setState(88);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 3670016L) != 0)) {
				{
				{
				setState(85);
				functionBodyStmnt();
				}
				}
				setState(90);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(91);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunctionBodyStmntContext extends ParserRuleContext {
		public FunctionBodyStmntContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionBodyStmnt; }
	 
		public FunctionBodyStmntContext() { }
		public void copyFrom(FunctionBodyStmntContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FunctionGenericImplContext extends FunctionBodyStmntContext {
		public TerminalNode GENERICIMPL() { return getToken(CongParser.GENERICIMPL, 0); }
		public TerminalNode LBRACE() { return getToken(CongParser.LBRACE, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RBRACE() { return getToken(CongParser.RBRACE, 0); }
		public FunctionGenericImplContext(FunctionBodyStmntContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterFunctionGenericImpl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitFunctionGenericImpl(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitFunctionGenericImpl(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FunctionExpRequiresContext extends FunctionBodyStmntContext {
		public TerminalNode REQUIRES() { return getToken(CongParser.REQUIRES, 0); }
		public TerminalNode LBRACE() { return getToken(CongParser.LBRACE, 0); }
		public ExpressionContext expression() {
			return getRuleContext(ExpressionContext.class,0);
		}
		public TerminalNode RBRACE() { return getToken(CongParser.RBRACE, 0); }
		public FunctionExpRequiresContext(FunctionBodyStmntContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterFunctionExpRequires(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitFunctionExpRequires(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitFunctionExpRequires(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class FunctionDescriptionContext extends FunctionBodyStmntContext {
		public TerminalNode DESCRIPTION() { return getToken(CongParser.DESCRIPTION, 0); }
		public TerminalNode LBRACE() { return getToken(CongParser.LBRACE, 0); }
		public LiteralContext literal() {
			return getRuleContext(LiteralContext.class,0);
		}
		public TerminalNode RBRACE() { return getToken(CongParser.RBRACE, 0); }
		public FunctionDescriptionContext(FunctionBodyStmntContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterFunctionDescription(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitFunctionDescription(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitFunctionDescription(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionBodyStmntContext functionBodyStmnt() throws RecognitionException {
		FunctionBodyStmntContext _localctx = new FunctionBodyStmntContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_functionBodyStmnt);
		try {
			setState(108);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case DESCRIPTION:
				_localctx = new FunctionDescriptionContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(93);
				match(DESCRIPTION);
				setState(94);
				match(LBRACE);
				setState(95);
				literal();
				setState(96);
				match(RBRACE);
				}
				break;
			case GENERICIMPL:
				_localctx = new FunctionGenericImplContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(98);
				match(GENERICIMPL);
				setState(99);
				match(LBRACE);
				setState(100);
				expression(0);
				setState(101);
				match(RBRACE);
				}
				break;
			case REQUIRES:
				_localctx = new FunctionExpRequiresContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(103);
				match(REQUIRES);
				setState(104);
				match(LBRACE);
				setState(105);
				expression(0);
				setState(106);
				match(RBRACE);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ParameterListContext extends ParserRuleContext {
		public List<ParameterContext> parameter() {
			return getRuleContexts(ParameterContext.class);
		}
		public ParameterContext parameter(int i) {
			return getRuleContext(ParameterContext.class,i);
		}
		public ParameterListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parameterList; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterParameterList(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitParameterList(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitParameterList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ParameterListContext parameterList() throws RecognitionException {
		ParameterListContext _localctx = new ParameterListContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_parameterList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(110);
			match(T__0);
			setState(119);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(111);
				parameter();
				setState(116);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==T__6) {
					{
					{
					setState(112);
					match(T__6);
					setState(113);
					parameter();
					}
					}
					setState(118);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(121);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ParameterContext extends ParserRuleContext {
		public Token name;
		public PlaceholderOrQualifiedIdContext type;
		public TerminalNode IDENTIFIER() { return getToken(CongParser.IDENTIFIER, 0); }
		public PlaceholderOrQualifiedIdContext placeholderOrQualifiedId() {
			return getRuleContext(PlaceholderOrQualifiedIdContext.class,0);
		}
		public ParameterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_parameter; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterParameter(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitParameter(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitParameter(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ParameterContext parameter() throws RecognitionException {
		ParameterContext _localctx = new ParameterContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_parameter);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(123);
			((ParameterContext)_localctx).name = match(IDENTIFIER);
			setState(124);
			match(T__1);
			setState(125);
			((ParameterContext)_localctx).type = placeholderOrQualifiedId();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExpressionContext extends ParserRuleContext {
		public ExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expression; }
	 
		public ExpressionContext() { }
		public void copyFrom(ExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class CallExpressionContext extends ExpressionContext {
		public QualifiedIdentifierContext fun;
		public QualifiedIdentifierContext qualifiedIdentifier() {
			return getRuleContext(QualifiedIdentifierContext.class,0);
		}
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public CallExpressionContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterCallExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitCallExpression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitCallExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ArithmeticExpressionContext extends ExpressionContext {
		public ExpressionContext left;
		public Token op;
		public ExpressionContext right;
		public List<ExpressionContext> expression() {
			return getRuleContexts(ExpressionContext.class);
		}
		public ExpressionContext expression(int i) {
			return getRuleContext(ExpressionContext.class,i);
		}
		public ArithmeticExpressionContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterArithmeticExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitArithmeticExpression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitArithmeticExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class LiteralExpressionContext extends ExpressionContext {
		public LiteralContext val;
		public LiteralContext literal() {
			return getRuleContext(LiteralContext.class,0);
		}
		public LiteralExpressionContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterLiteralExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitLiteralExpression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitLiteralExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	@SuppressWarnings("CheckReturnValue")
	public static class ParameterReferenceExpressionContext extends ExpressionContext {
		public Token param;
		public TerminalNode IDENTIFIER() { return getToken(CongParser.IDENTIFIER, 0); }
		public ParameterReferenceExpressionContext(ExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterParameterReferenceExpression(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitParameterReferenceExpression(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitParameterReferenceExpression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionContext expression() throws RecognitionException {
		return expression(0);
	}

	private ExpressionContext expression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		ExpressionContext _localctx = new ExpressionContext(_ctx, _parentState);
		ExpressionContext _prevctx = _localctx;
		int _startState = 20;
		enterRecursionRule(_localctx, 20, RULE_expression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(144);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				{
				_localctx = new LiteralExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(128);
				((LiteralExpressionContext)_localctx).val = literal();
				}
				break;
			case 2:
				{
				_localctx = new CallExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(129);
				((CallExpressionContext)_localctx).fun = qualifiedIdentifier();
				setState(130);
				match(T__0);
				setState(139);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1040220160L) != 0)) {
					{
					setState(131);
					expression(0);
					setState(136);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==T__6) {
						{
						{
						setState(132);
						match(T__6);
						setState(133);
						expression(0);
						}
						}
						setState(138);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(141);
				match(T__2);
				}
				break;
			case 3:
				{
				_localctx = new ParameterReferenceExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(143);
				((ParameterReferenceExpressionContext)_localctx).param = match(IDENTIFIER);
				}
				break;
			}
			_ctx.stop = _input.LT(-1);
			setState(151);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,13,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					{
					_localctx = new ArithmeticExpressionContext(new ExpressionContext(_parentctx, _parentState));
					((ArithmeticExpressionContext)_localctx).left = _prevctx;
					pushNewRecursionContext(_localctx, _startState, RULE_expression);
					setState(146);
					if (!(precpred(_ctx, 4))) throw new FailedPredicateException(this, "precpred(_ctx, 4)");
					setState(147);
					((ArithmeticExpressionContext)_localctx).op = _input.LT(1);
					_la = _input.LA(1);
					if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 7936L) != 0)) ) {
						((ArithmeticExpressionContext)_localctx).op = (Token)_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(148);
					((ArithmeticExpressionContext)_localctx).right = expression(5);
					}
					} 
				}
				setState(153);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,13,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PlaceholderOrQualifiedIdContext extends ParserRuleContext {
		public QualifiedIdentifierContext qualifiedIdentifier() {
			return getRuleContext(QualifiedIdentifierContext.class,0);
		}
		public ConceptPlaceholderContext conceptPlaceholder() {
			return getRuleContext(ConceptPlaceholderContext.class,0);
		}
		public PlaceholderOrQualifiedIdContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_placeholderOrQualifiedId; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterPlaceholderOrQualifiedId(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitPlaceholderOrQualifiedId(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitPlaceholderOrQualifiedId(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PlaceholderOrQualifiedIdContext placeholderOrQualifiedId() throws RecognitionException {
		PlaceholderOrQualifiedIdContext _localctx = new PlaceholderOrQualifiedIdContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_placeholderOrQualifiedId);
		try {
			setState(156);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__14:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(154);
				qualifiedIdentifier();
				}
				break;
			case T__12:
				enterOuterAlt(_localctx, 2);
				{
				setState(155);
				conceptPlaceholder();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ConceptPlaceholderContext extends ParserRuleContext {
		public Token name;
		public TerminalNode IDENTIFIER() { return getToken(CongParser.IDENTIFIER, 0); }
		public ConceptPlaceholderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_conceptPlaceholder; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterConceptPlaceholder(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitConceptPlaceholder(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitConceptPlaceholder(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ConceptPlaceholderContext conceptPlaceholder() throws RecognitionException {
		ConceptPlaceholderContext _localctx = new ConceptPlaceholderContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_conceptPlaceholder);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(158);
			match(T__12);
			setState(159);
			((ConceptPlaceholderContext)_localctx).name = match(IDENTIFIER);
			setState(160);
			match(T__13);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class QualifiedIdentifierContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(CongParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(CongParser.IDENTIFIER, i);
		}
		public QualifiedIdentifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_qualifiedIdentifier; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterQualifiedIdentifier(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitQualifiedIdentifier(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitQualifiedIdentifier(this);
			else return visitor.visitChildren(this);
		}
	}

	public final QualifiedIdentifierContext qualifiedIdentifier() throws RecognitionException {
		QualifiedIdentifierContext _localctx = new QualifiedIdentifierContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_qualifiedIdentifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(163);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__14) {
				{
				setState(162);
				match(T__14);
				}
			}

			setState(165);
			match(IDENTIFIER);
			setState(170);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==T__14) {
				{
				{
				setState(166);
				match(T__14);
				setState(167);
				match(IDENTIFIER);
				}
				}
				setState(172);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class LiteralContext extends ParserRuleContext {
		public TerminalNode REAL() { return getToken(CongParser.REAL, 0); }
		public TerminalNode NUMBER() { return getToken(CongParser.NUMBER, 0); }
		public TerminalNode STRING() { return getToken(CongParser.STRING, 0); }
		public TerminalNode BOOL() { return getToken(CongParser.BOOL, 0); }
		public LiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).enterLiteral(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof CongListener ) ((CongListener)listener).exitLiteral(this);
		}
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof CongVisitor ) return ((CongVisitor<? extends T>)visitor).visitLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LiteralContext literal() throws RecognitionException {
		LiteralContext _localctx = new LiteralContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_literal);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(173);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 503316480L) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 10:
			return expression_sempred((ExpressionContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean expression_sempred(ExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return precpred(_ctx, 4);
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001!\u00b0\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0001\u0000\u0005\u0000"+
		" \b\u0000\n\u0000\f\u0000#\t\u0000\u0001\u0000\u0001\u0000\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0003\u0001*\b\u0001\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0003\u0002"+
		"3\b\u0002\u0001\u0002\u0003\u00026\b\u0002\u0001\u0002\u0001\u0002\u0001"+
		"\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0005\u0003>\b\u0003\n\u0003"+
		"\f\u0003A\t\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0005"+
		"\u0004G\b\u0004\n\u0004\f\u0004J\t\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0006\u0001\u0006\u0005\u0006W\b\u0006\n\u0006\f\u0006Z\t"+
		"\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001"+
		"\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0003"+
		"\u0007m\b\u0007\u0001\b\u0001\b\u0001\b\u0001\b\u0005\bs\b\b\n\b\f\bv"+
		"\t\b\u0003\bx\b\b\u0001\b\u0001\b\u0001\t\u0001\t\u0001\t\u0001\t\u0001"+
		"\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0005\n\u0087\b\n\n"+
		"\n\f\n\u008a\t\n\u0003\n\u008c\b\n\u0001\n\u0001\n\u0001\n\u0003\n\u0091"+
		"\b\n\u0001\n\u0001\n\u0001\n\u0005\n\u0096\b\n\n\n\f\n\u0099\t\n\u0001"+
		"\u000b\u0001\u000b\u0003\u000b\u009d\b\u000b\u0001\f\u0001\f\u0001\f\u0001"+
		"\f\u0001\r\u0003\r\u00a4\b\r\u0001\r\u0001\r\u0001\r\u0005\r\u00a9\b\r"+
		"\n\r\f\r\u00ac\t\r\u0001\u000e\u0001\u000e\u0001\u000e\u0000\u0001\u0014"+
		"\u000f\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012\u0014\u0016\u0018"+
		"\u001a\u001c\u0000\u0002\u0001\u0000\b\f\u0001\u0000\u0019\u001c\u00b4"+
		"\u0000!\u0001\u0000\u0000\u0000\u0002)\u0001\u0000\u0000\u0000\u0004+"+
		"\u0001\u0000\u0000\u0000\u00069\u0001\u0000\u0000\u0000\bB\u0001\u0000"+
		"\u0000\u0000\nM\u0001\u0000\u0000\u0000\fT\u0001\u0000\u0000\u0000\u000e"+
		"l\u0001\u0000\u0000\u0000\u0010n\u0001\u0000\u0000\u0000\u0012{\u0001"+
		"\u0000\u0000\u0000\u0014\u0090\u0001\u0000\u0000\u0000\u0016\u009c\u0001"+
		"\u0000\u0000\u0000\u0018\u009e\u0001\u0000\u0000\u0000\u001a\u00a3\u0001"+
		"\u0000\u0000\u0000\u001c\u00ad\u0001\u0000\u0000\u0000\u001e \u0003\u0002"+
		"\u0001\u0000\u001f\u001e\u0001\u0000\u0000\u0000 #\u0001\u0000\u0000\u0000"+
		"!\u001f\u0001\u0000\u0000\u0000!\"\u0001\u0000\u0000\u0000\"$\u0001\u0000"+
		"\u0000\u0000#!\u0001\u0000\u0000\u0000$%\u0005\u0000\u0000\u0001%\u0001"+
		"\u0001\u0000\u0000\u0000&*\u0003\u0004\u0002\u0000\'*\u0003\b\u0004\u0000"+
		"(*\u0003\n\u0005\u0000)&\u0001\u0000\u0000\u0000)\'\u0001\u0000\u0000"+
		"\u0000)(\u0001\u0000\u0000\u0000*\u0003\u0001\u0000\u0000\u0000+,\u0005"+
		"\u0010\u0000\u0000,2\u0005\u001d\u0000\u0000-.\u0005\u0001\u0000\u0000"+
		"./\u0005\u0013\u0000\u0000/0\u0005\u0002\u0000\u000001\u0005\u001c\u0000"+
		"\u000013\u0005\u0003\u0000\u00002-\u0001\u0000\u0000\u000023\u0001\u0000"+
		"\u0000\u000035\u0001\u0000\u0000\u000046\u0003\u0006\u0003\u000054\u0001"+
		"\u0000\u0000\u000056\u0001\u0000\u0000\u000067\u0001\u0000\u0000\u0000"+
		"78\u0005\u0004\u0000\u00008\u0005\u0001\u0000\u0000\u00009:\u0005\u0002"+
		"\u0000\u0000:?\u0003\u001a\r\u0000;<\u0005\u0005\u0000\u0000<>\u0003\u001a"+
		"\r\u0000=;\u0001\u0000\u0000\u0000>A\u0001\u0000\u0000\u0000?=\u0001\u0000"+
		"\u0000\u0000?@\u0001\u0000\u0000\u0000@\u0007\u0001\u0000\u0000\u0000"+
		"A?\u0001\u0000\u0000\u0000BC\u0005\u0012\u0000\u0000CD\u0005\u001d\u0000"+
		"\u0000DH\u0005\u0016\u0000\u0000EG\u0003\u0002\u0001\u0000FE\u0001\u0000"+
		"\u0000\u0000GJ\u0001\u0000\u0000\u0000HF\u0001\u0000\u0000\u0000HI\u0001"+
		"\u0000\u0000\u0000IK\u0001\u0000\u0000\u0000JH\u0001\u0000\u0000\u0000"+
		"KL\u0005\u0017\u0000\u0000L\t\u0001\u0000\u0000\u0000MN\u0005\u0011\u0000"+
		"\u0000NO\u0005\u001d\u0000\u0000OP\u0003\u0010\b\u0000PQ\u0005\u0006\u0000"+
		"\u0000QR\u0003\u001a\r\u0000RS\u0003\f\u0006\u0000S\u000b\u0001\u0000"+
		"\u0000\u0000TX\u0005\u0016\u0000\u0000UW\u0003\u000e\u0007\u0000VU\u0001"+
		"\u0000\u0000\u0000WZ\u0001\u0000\u0000\u0000XV\u0001\u0000\u0000\u0000"+
		"XY\u0001\u0000\u0000\u0000Y[\u0001\u0000\u0000\u0000ZX\u0001\u0000\u0000"+
		"\u0000[\\\u0005\u0017\u0000\u0000\\\r\u0001\u0000\u0000\u0000]^\u0005"+
		"\u0013\u0000\u0000^_\u0005\u0016\u0000\u0000_`\u0003\u001c\u000e\u0000"+
		"`a\u0005\u0017\u0000\u0000am\u0001\u0000\u0000\u0000bc\u0005\u0014\u0000"+
		"\u0000cd\u0005\u0016\u0000\u0000de\u0003\u0014\n\u0000ef\u0005\u0017\u0000"+
		"\u0000fm\u0001\u0000\u0000\u0000gh\u0005\u0015\u0000\u0000hi\u0005\u0016"+
		"\u0000\u0000ij\u0003\u0014\n\u0000jk\u0005\u0017\u0000\u0000km\u0001\u0000"+
		"\u0000\u0000l]\u0001\u0000\u0000\u0000lb\u0001\u0000\u0000\u0000lg\u0001"+
		"\u0000\u0000\u0000m\u000f\u0001\u0000\u0000\u0000nw\u0005\u0001\u0000"+
		"\u0000ot\u0003\u0012\t\u0000pq\u0005\u0007\u0000\u0000qs\u0003\u0012\t"+
		"\u0000rp\u0001\u0000\u0000\u0000sv\u0001\u0000\u0000\u0000tr\u0001\u0000"+
		"\u0000\u0000tu\u0001\u0000\u0000\u0000ux\u0001\u0000\u0000\u0000vt\u0001"+
		"\u0000\u0000\u0000wo\u0001\u0000\u0000\u0000wx\u0001\u0000\u0000\u0000"+
		"xy\u0001\u0000\u0000\u0000yz\u0005\u0003\u0000\u0000z\u0011\u0001\u0000"+
		"\u0000\u0000{|\u0005\u001d\u0000\u0000|}\u0005\u0002\u0000\u0000}~\u0003"+
		"\u0016\u000b\u0000~\u0013\u0001\u0000\u0000\u0000\u007f\u0080\u0006\n"+
		"\uffff\uffff\u0000\u0080\u0091\u0003\u001c\u000e\u0000\u0081\u0082\u0003"+
		"\u001a\r\u0000\u0082\u008b\u0005\u0001\u0000\u0000\u0083\u0088\u0003\u0014"+
		"\n\u0000\u0084\u0085\u0005\u0007\u0000\u0000\u0085\u0087\u0003\u0014\n"+
		"\u0000\u0086\u0084\u0001\u0000\u0000\u0000\u0087\u008a\u0001\u0000\u0000"+
		"\u0000\u0088\u0086\u0001\u0000\u0000\u0000\u0088\u0089\u0001\u0000\u0000"+
		"\u0000\u0089\u008c\u0001\u0000\u0000\u0000\u008a\u0088\u0001\u0000\u0000"+
		"\u0000\u008b\u0083\u0001\u0000\u0000\u0000\u008b\u008c\u0001\u0000\u0000"+
		"\u0000\u008c\u008d\u0001\u0000\u0000\u0000\u008d\u008e\u0005\u0003\u0000"+
		"\u0000\u008e\u0091\u0001\u0000\u0000\u0000\u008f\u0091\u0005\u001d\u0000"+
		"\u0000\u0090\u007f\u0001\u0000\u0000\u0000\u0090\u0081\u0001\u0000\u0000"+
		"\u0000\u0090\u008f\u0001\u0000\u0000\u0000\u0091\u0097\u0001\u0000\u0000"+
		"\u0000\u0092\u0093\n\u0004\u0000\u0000\u0093\u0094\u0007\u0000\u0000\u0000"+
		"\u0094\u0096\u0003\u0014\n\u0005\u0095\u0092\u0001\u0000\u0000\u0000\u0096"+
		"\u0099\u0001\u0000\u0000\u0000\u0097\u0095\u0001\u0000\u0000\u0000\u0097"+
		"\u0098\u0001\u0000\u0000\u0000\u0098\u0015\u0001\u0000\u0000\u0000\u0099"+
		"\u0097\u0001\u0000\u0000\u0000\u009a\u009d\u0003\u001a\r\u0000\u009b\u009d"+
		"\u0003\u0018\f\u0000\u009c\u009a\u0001\u0000\u0000\u0000\u009c\u009b\u0001"+
		"\u0000\u0000\u0000\u009d\u0017\u0001\u0000\u0000\u0000\u009e\u009f\u0005"+
		"\r\u0000\u0000\u009f\u00a0\u0005\u001d\u0000\u0000\u00a0\u00a1\u0005\u000e"+
		"\u0000\u0000\u00a1\u0019\u0001\u0000\u0000\u0000\u00a2\u00a4\u0005\u000f"+
		"\u0000\u0000\u00a3\u00a2\u0001\u0000\u0000\u0000\u00a3\u00a4\u0001\u0000"+
		"\u0000\u0000\u00a4\u00a5\u0001\u0000\u0000\u0000\u00a5\u00aa\u0005\u001d"+
		"\u0000\u0000\u00a6\u00a7\u0005\u000f\u0000\u0000\u00a7\u00a9\u0005\u001d"+
		"\u0000\u0000\u00a8\u00a6\u0001\u0000\u0000\u0000\u00a9\u00ac\u0001\u0000"+
		"\u0000\u0000\u00aa\u00a8\u0001\u0000\u0000\u0000\u00aa\u00ab\u0001\u0000"+
		"\u0000\u0000\u00ab\u001b\u0001\u0000\u0000\u0000\u00ac\u00aa\u0001\u0000"+
		"\u0000\u0000\u00ad\u00ae\u0007\u0001\u0000\u0000\u00ae\u001d\u0001\u0000"+
		"\u0000\u0000\u0011!)25?HXltw\u0088\u008b\u0090\u0097\u009c\u00a3\u00aa";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}