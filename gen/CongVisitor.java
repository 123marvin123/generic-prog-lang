// Generated from /Users/haschker/CLionProjects/masterthesis-transpiler/grammar/Cong.g4 by ANTLR 4.13.2
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link CongParser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface CongVisitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link CongParser#translationUnit}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitTranslationUnit(CongParser.TranslationUnitContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#stmnt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStmnt(CongParser.StmntContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#conceptDefinitionStmnt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConceptDefinitionStmnt(CongParser.ConceptDefinitionStmntContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#conceptDefinitionBases}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConceptDefinitionBases(CongParser.ConceptDefinitionBasesContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#namespaceStmnt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNamespaceStmnt(CongParser.NamespaceStmntContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#functionStmnt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionStmnt(CongParser.FunctionStmntContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#functionBody}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionBody(CongParser.FunctionBodyContext ctx);
	/**
	 * Visit a parse tree produced by the {@code functionDescription}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionDescription(CongParser.FunctionDescriptionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code functionGenericImpl}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionGenericImpl(CongParser.FunctionGenericImplContext ctx);
	/**
	 * Visit a parse tree produced by the {@code functionExpRequires}
	 * labeled alternative in {@link CongParser#functionBodyStmnt}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFunctionExpRequires(CongParser.FunctionExpRequiresContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#parameterList}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParameterList(CongParser.ParameterListContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#parameter}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParameter(CongParser.ParameterContext ctx);
	/**
	 * Visit a parse tree produced by the {@code callExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCallExpression(CongParser.CallExpressionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code arithmeticExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitArithmeticExpression(CongParser.ArithmeticExpressionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code literalExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteralExpression(CongParser.LiteralExpressionContext ctx);
	/**
	 * Visit a parse tree produced by the {@code parameterReferenceExpression}
	 * labeled alternative in {@link CongParser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitParameterReferenceExpression(CongParser.ParameterReferenceExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#placeholderOrQualifiedId}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitPlaceholderOrQualifiedId(CongParser.PlaceholderOrQualifiedIdContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#conceptPlaceholder}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConceptPlaceholder(CongParser.ConceptPlaceholderContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#qualifiedIdentifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitQualifiedIdentifier(CongParser.QualifiedIdentifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link CongParser#literal}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitLiteral(CongParser.LiteralContext ctx);
}