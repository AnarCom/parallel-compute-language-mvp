
// Generated from TParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by TParser.
 */
class  TParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by TParser.
   */
    virtual std::any visitSourceFile(TParser::SourceFileContext *context) = 0;

    virtual std::any visitIdentifier(TParser::IdentifierContext *context) = 0;

    virtual std::any visitDeclaration(TParser::DeclarationContext *context) = 0;

    virtual std::any visitConstDecl(TParser::ConstDeclContext *context) = 0;

    virtual std::any visitConstSpec(TParser::ConstSpecContext *context) = 0;

    virtual std::any visitIdentifierList(TParser::IdentifierListContext *context) = 0;

    virtual std::any visitExpressionList(TParser::ExpressionListContext *context) = 0;

    virtual std::any visitTypeSpec(TParser::TypeSpecContext *context) = 0;

    virtual std::any visitAliasDecl(TParser::AliasDeclContext *context) = 0;

    virtual std::any visitTypeDef(TParser::TypeDefContext *context) = 0;

    virtual std::any visitTypeParameters(TParser::TypeParametersContext *context) = 0;

    virtual std::any visitTypeParameterDecl(TParser::TypeParameterDeclContext *context) = 0;

    virtual std::any visitTypeElement(TParser::TypeElementContext *context) = 0;

    virtual std::any visitTypeTerm(TParser::TypeTermContext *context) = 0;

    virtual std::any visitFunctionDecl(TParser::FunctionDeclContext *context) = 0;

    virtual std::any visitVarDecl(TParser::VarDeclContext *context) = 0;

    virtual std::any visitVarSpec(TParser::VarSpecContext *context) = 0;

    virtual std::any visitBlock(TParser::BlockContext *context) = 0;

    virtual std::any visitStatementList(TParser::StatementListContext *context) = 0;

    virtual std::any visitStatement(TParser::StatementContext *context) = 0;

    virtual std::any visitSimpleStmt(TParser::SimpleStmtContext *context) = 0;

    virtual std::any visitExpressionStmt(TParser::ExpressionStmtContext *context) = 0;

    virtual std::any visitSyncReturnStmt(TParser::SyncReturnStmtContext *context) = 0;

    virtual std::any visitEmitStmt(TParser::EmitStmtContext *context) = 0;

    virtual std::any visitIncDecStmt(TParser::IncDecStmtContext *context) = 0;

    virtual std::any visitAssignment(TParser::AssignmentContext *context) = 0;

    virtual std::any visitAssign_op(TParser::Assign_opContext *context) = 0;

    virtual std::any visitShortVarDecl(TParser::ShortVarDeclContext *context) = 0;

    virtual std::any visitReturnStmt(TParser::ReturnStmtContext *context) = 0;

    virtual std::any visitBreakStmt(TParser::BreakStmtContext *context) = 0;

    virtual std::any visitContinueStmt(TParser::ContinueStmtContext *context) = 0;

    virtual std::any visitIfStmt(TParser::IfStmtContext *context) = 0;

    virtual std::any visitTypeList(TParser::TypeListContext *context) = 0;

    virtual std::any visitJoinStmt(TParser::JoinStmtContext *context) = 0;

    virtual std::any visitMatchClause(TParser::MatchClauseContext *context) = 0;

    virtual std::any visitMatchCase(TParser::MatchCaseContext *context) = 0;

    virtual std::any visitFromChanAs(TParser::FromChanAsContext *context) = 0;

    virtual std::any visitForStmt(TParser::ForStmtContext *context) = 0;

    virtual std::any visitCondition(TParser::ConditionContext *context) = 0;

    virtual std::any visitForClause(TParser::ForClauseContext *context) = 0;

    virtual std::any visitType_(TParser::Type_Context *context) = 0;

    virtual std::any visitTypeArgs(TParser::TypeArgsContext *context) = 0;

    virtual std::any visitTypeName(TParser::TypeNameContext *context) = 0;

    virtual std::any visitTypeLit(TParser::TypeLitContext *context) = 0;

    virtual std::any visitArrayType(TParser::ArrayTypeContext *context) = 0;

    virtual std::any visitArrayLength(TParser::ArrayLengthContext *context) = 0;

    virtual std::any visitElementType(TParser::ElementTypeContext *context) = 0;

    virtual std::any visitAsyncChannelType(TParser::AsyncChannelTypeContext *context) = 0;

    virtual std::any visitSyncChannelType(TParser::SyncChannelTypeContext *context) = 0;

    virtual std::any visitFunctionType(TParser::FunctionTypeContext *context) = 0;

    virtual std::any visitSignature(TParser::SignatureContext *context) = 0;

    virtual std::any visitResult(TParser::ResultContext *context) = 0;

    virtual std::any visitParameters(TParser::ParametersContext *context) = 0;

    virtual std::any visitParameterDecl(TParser::ParameterDeclContext *context) = 0;

    virtual std::any visitExpression(TParser::ExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpr(TParser::PrimaryExprContext *context) = 0;

    virtual std::any visitConversion(TParser::ConversionContext *context) = 0;

    virtual std::any visitOperand(TParser::OperandContext *context) = 0;

    virtual std::any visitLiteral(TParser::LiteralContext *context) = 0;

    virtual std::any visitBasicLit(TParser::BasicLitContext *context) = 0;

    virtual std::any visitInteger(TParser::IntegerContext *context) = 0;

    virtual std::any visitOperandName(TParser::OperandNameContext *context) = 0;

    virtual std::any visitCompositeLit(TParser::CompositeLitContext *context) = 0;

    virtual std::any visitLiteralType(TParser::LiteralTypeContext *context) = 0;

    virtual std::any visitLiteralValue(TParser::LiteralValueContext *context) = 0;

    virtual std::any visitElementList(TParser::ElementListContext *context) = 0;

    virtual std::any visitKeyedElement(TParser::KeyedElementContext *context) = 0;

    virtual std::any visitKey(TParser::KeyContext *context) = 0;

    virtual std::any visitElement(TParser::ElementContext *context) = 0;

    virtual std::any visitString_(TParser::String_Context *context) = 0;

    virtual std::any visitFunctionLit(TParser::FunctionLitContext *context) = 0;

    virtual std::any visitIndex(TParser::IndexContext *context) = 0;

    virtual std::any visitArguments(TParser::ArgumentsContext *context) = 0;

    virtual std::any visitEos(TParser::EosContext *context) = 0;


};

