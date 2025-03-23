// Generated from /Users/haschker/CLionProjects/masterthesis-transpiler/grammar/Cong.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link CongParser}.
 */
public interface CongListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link CongParser#translationUnit}.
	 * @param ctx the parse tree
	 */
	void enterTranslationUnit(CongParser.TranslationUnitContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#translationUnit}.
	 * @param ctx the parse tree
	 */
	void exitTranslationUnit(CongParser.TranslationUnitContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#stmnt}.
	 * @param ctx the parse tree
	 */
	void enterStmnt(CongParser.StmntContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#stmnt}.
	 * @param ctx the parse tree
	 */
	void exitStmnt(CongParser.StmntContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#conceptDefinitionStmnt}.
	 * @param ctx the parse tree
	 */
	void enterConceptDefinitionStmnt(CongParser.ConceptDefinitionStmntContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#conceptDefinitionStmnt}.
	 * @param ctx the parse tree
	 */
	void exitConceptDefinitionStmnt(CongParser.ConceptDefinitionStmntContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#conceptDefinitionBases}.
	 * @param ctx the parse tree
	 */
	void enterConceptDefinitionBases(CongParser.ConceptDefinitionBasesContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#conceptDefinitionBases}.
	 * @param ctx the parse tree
	 */
	void exitConceptDefinitionBases(CongParser.ConceptDefinitionBasesContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#namespaceStmnt}.
	 * @param ctx the parse tree
	 */
	void enterNamespaceStmnt(CongParser.NamespaceStmntContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#namespaceStmnt}.
	 * @param ctx the parse tree
	 */
	void exitNamespaceStmnt(CongParser.NamespaceStmntContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#functionStmnt}.
	 * @param ctx the parse tree
	 */
	void enterFunctionStmnt(CongParser.FunctionStmntContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#functionStmnt}.
	 * @param ctx the parse tree
	 */
	void exitFunctionStmnt(CongParser.FunctionStmntContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#functionBody}.
	 * @param ctx the parse tree
	 */
	void enterFunctionBody(CongParser.FunctionBodyContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#functionBody}.
	 * @param ctx the parse tree
	 */
	void exitFunctionBody(CongParser.FunctionBodyContext ctx);
	/**
	 * Enter a parse tree produced by the {@code functionDescription}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 */
	void enterFunctionDescription(CongParser.FunctionDescriptionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code functionDescription}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 */
	void exitFunctionDescription(CongParser.FunctionDescriptionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code functionGenericImpl}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 */
	void enterFunctionGenericImpl(CongParser.FunctionGenericImplContext ctx);
	/**
	 * Exit a parse tree produced by the {@code functionGenericImpl}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 */
	void exitFunctionGenericImpl(CongParser.FunctionGenericImplContext ctx);
	/**
	 * Enter a parse tree produced by the {@code functionExpRequires}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 */
	void enterFunctionExpRequires(CongParser.FunctionExpRequiresContext ctx);
	/**
	 * Exit a parse tree produced by the {@code functionExpRequires}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 */
	void exitFunctionExpRequires(CongParser.FunctionExpRequiresContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#parameterList}.
	 * @param ctx the parse tree
	 */
	void enterParameterList(CongParser.ParameterListContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#parameterList}.
	 * @param ctx the parse tree
	 */
	void exitParameterList(CongParser.ParameterListContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#parameter}.
	 * @param ctx the parse tree
	 */
	void enterParameter(CongParser.ParameterContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#parameter}.
	 * @param ctx the parse tree
	 */
	void exitParameter(CongParser.ParameterContext ctx);
	/**
	 * Enter a parse tree produced by the {@code callExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterCallExpression(CongParser.CallExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code callExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitCallExpression(CongParser.CallExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code arithmeticExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterArithmeticExpression(CongParser.ArithmeticExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code arithmeticExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitArithmeticExpression(CongParser.ArithmeticExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code literalExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterLiteralExpression(CongParser.LiteralExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code literalExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitLiteralExpression(CongParser.LiteralExpressionContext ctx);
	/**
	 * Enter a parse tree produced by the {@code parameterReferenceExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void enterParameterReferenceExpression(CongParser.ParameterReferenceExpressionContext ctx);
	/**
	 * Exit a parse tree produced by the {@code parameterReferenceExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 */
	void exitParameterReferenceExpression(CongParser.ParameterReferenceExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#placeholderOrQualifiedId}.
	 * @param ctx the parse tree
	 */
	void enterPlaceholderOrQualifiedId(CongParser.PlaceholderOrQualifiedIdContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#placeholderOrQualifiedId}.
	 * @param ctx the parse tree
	 */
	void exitPlaceholderOrQualifiedId(CongParser.PlaceholderOrQualifiedIdContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#conceptPlaceholder}.
	 * @param ctx the parse tree
	 */
	void enterConceptPlaceholder(CongParser.ConceptPlaceholderContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#conceptPlaceholder}.
	 * @param ctx the parse tree
	 */
	void exitConceptPlaceholder(CongParser.ConceptPlaceholderContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#qualifiedIdentifier}.
	 * @param ctx the parse tree
	 */
	void enterQualifiedIdentifier(CongParser.QualifiedIdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#qualifiedIdentifier}.
	 * @param ctx the parse tree
	 */
	void exitQualifiedIdentifier(CongParser.QualifiedIdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link CongParser#literal}.
	 * @param ctx the parse tree
	 */
	void enterLiteral(CongParser.LiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link CongParser#literal}.
	 * @param ctx the parse tree
	 */
	void exitLiteral(CongParser.LiteralContext ctx);
}