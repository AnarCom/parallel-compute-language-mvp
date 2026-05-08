
// Generated from TParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by TParser.
 */
class  TParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterSourceFile(TParser::SourceFileContext *ctx) = 0;
  virtual void exitSourceFile(TParser::SourceFileContext *ctx) = 0;

  virtual void enterIdentifier(TParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(TParser::IdentifierContext *ctx) = 0;

  virtual void enterDeclaration(TParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(TParser::DeclarationContext *ctx) = 0;

  virtual void enterConstDecl(TParser::ConstDeclContext *ctx) = 0;
  virtual void exitConstDecl(TParser::ConstDeclContext *ctx) = 0;

  virtual void enterConstSpec(TParser::ConstSpecContext *ctx) = 0;
  virtual void exitConstSpec(TParser::ConstSpecContext *ctx) = 0;

  virtual void enterIdentifierList(TParser::IdentifierListContext *ctx) = 0;
  virtual void exitIdentifierList(TParser::IdentifierListContext *ctx) = 0;

  virtual void enterExpressionList(TParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(TParser::ExpressionListContext *ctx) = 0;

  virtual void enterTypeSpec(TParser::TypeSpecContext *ctx) = 0;
  virtual void exitTypeSpec(TParser::TypeSpecContext *ctx) = 0;

  virtual void enterAliasDecl(TParser::AliasDeclContext *ctx) = 0;
  virtual void exitAliasDecl(TParser::AliasDeclContext *ctx) = 0;

  virtual void enterTypeDef(TParser::TypeDefContext *ctx) = 0;
  virtual void exitTypeDef(TParser::TypeDefContext *ctx) = 0;

  virtual void enterTypeParameters(TParser::TypeParametersContext *ctx) = 0;
  virtual void exitTypeParameters(TParser::TypeParametersContext *ctx) = 0;

  virtual void enterTypeParameterDecl(TParser::TypeParameterDeclContext *ctx) = 0;
  virtual void exitTypeParameterDecl(TParser::TypeParameterDeclContext *ctx) = 0;

  virtual void enterTypeElement(TParser::TypeElementContext *ctx) = 0;
  virtual void exitTypeElement(TParser::TypeElementContext *ctx) = 0;

  virtual void enterTypeTerm(TParser::TypeTermContext *ctx) = 0;
  virtual void exitTypeTerm(TParser::TypeTermContext *ctx) = 0;

  virtual void enterFunctionDecl(TParser::FunctionDeclContext *ctx) = 0;
  virtual void exitFunctionDecl(TParser::FunctionDeclContext *ctx) = 0;

  virtual void enterVarDecl(TParser::VarDeclContext *ctx) = 0;
  virtual void exitVarDecl(TParser::VarDeclContext *ctx) = 0;

  virtual void enterVarSpec(TParser::VarSpecContext *ctx) = 0;
  virtual void exitVarSpec(TParser::VarSpecContext *ctx) = 0;

  virtual void enterBlock(TParser::BlockContext *ctx) = 0;
  virtual void exitBlock(TParser::BlockContext *ctx) = 0;

  virtual void enterStatementList(TParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(TParser::StatementListContext *ctx) = 0;

  virtual void enterStatement(TParser::StatementContext *ctx) = 0;
  virtual void exitStatement(TParser::StatementContext *ctx) = 0;

  virtual void enterSimpleStmt(TParser::SimpleStmtContext *ctx) = 0;
  virtual void exitSimpleStmt(TParser::SimpleStmtContext *ctx) = 0;

  virtual void enterExpressionStmt(TParser::ExpressionStmtContext *ctx) = 0;
  virtual void exitExpressionStmt(TParser::ExpressionStmtContext *ctx) = 0;

  virtual void enterSyncReturnStmt(TParser::SyncReturnStmtContext *ctx) = 0;
  virtual void exitSyncReturnStmt(TParser::SyncReturnStmtContext *ctx) = 0;

  virtual void enterEmitStmt(TParser::EmitStmtContext *ctx) = 0;
  virtual void exitEmitStmt(TParser::EmitStmtContext *ctx) = 0;

  virtual void enterIncDecStmt(TParser::IncDecStmtContext *ctx) = 0;
  virtual void exitIncDecStmt(TParser::IncDecStmtContext *ctx) = 0;

  virtual void enterAssignment(TParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(TParser::AssignmentContext *ctx) = 0;

  virtual void enterAssign_op(TParser::Assign_opContext *ctx) = 0;
  virtual void exitAssign_op(TParser::Assign_opContext *ctx) = 0;

  virtual void enterShortVarDecl(TParser::ShortVarDeclContext *ctx) = 0;
  virtual void exitShortVarDecl(TParser::ShortVarDeclContext *ctx) = 0;

  virtual void enterReturnStmt(TParser::ReturnStmtContext *ctx) = 0;
  virtual void exitReturnStmt(TParser::ReturnStmtContext *ctx) = 0;

  virtual void enterBreakStmt(TParser::BreakStmtContext *ctx) = 0;
  virtual void exitBreakStmt(TParser::BreakStmtContext *ctx) = 0;

  virtual void enterContinueStmt(TParser::ContinueStmtContext *ctx) = 0;
  virtual void exitContinueStmt(TParser::ContinueStmtContext *ctx) = 0;

  virtual void enterIfStmt(TParser::IfStmtContext *ctx) = 0;
  virtual void exitIfStmt(TParser::IfStmtContext *ctx) = 0;

  virtual void enterTypeList(TParser::TypeListContext *ctx) = 0;
  virtual void exitTypeList(TParser::TypeListContext *ctx) = 0;

  virtual void enterJoinStmt(TParser::JoinStmtContext *ctx) = 0;
  virtual void exitJoinStmt(TParser::JoinStmtContext *ctx) = 0;

  virtual void enterMatchClause(TParser::MatchClauseContext *ctx) = 0;
  virtual void exitMatchClause(TParser::MatchClauseContext *ctx) = 0;

  virtual void enterMatchCase(TParser::MatchCaseContext *ctx) = 0;
  virtual void exitMatchCase(TParser::MatchCaseContext *ctx) = 0;

  virtual void enterFromChanAs(TParser::FromChanAsContext *ctx) = 0;
  virtual void exitFromChanAs(TParser::FromChanAsContext *ctx) = 0;

  virtual void enterForStmt(TParser::ForStmtContext *ctx) = 0;
  virtual void exitForStmt(TParser::ForStmtContext *ctx) = 0;

  virtual void enterCondition(TParser::ConditionContext *ctx) = 0;
  virtual void exitCondition(TParser::ConditionContext *ctx) = 0;

  virtual void enterForClause(TParser::ForClauseContext *ctx) = 0;
  virtual void exitForClause(TParser::ForClauseContext *ctx) = 0;

  virtual void enterType_(TParser::Type_Context *ctx) = 0;
  virtual void exitType_(TParser::Type_Context *ctx) = 0;

  virtual void enterTypeArgs(TParser::TypeArgsContext *ctx) = 0;
  virtual void exitTypeArgs(TParser::TypeArgsContext *ctx) = 0;

  virtual void enterTypeName(TParser::TypeNameContext *ctx) = 0;
  virtual void exitTypeName(TParser::TypeNameContext *ctx) = 0;

  virtual void enterTypeLit(TParser::TypeLitContext *ctx) = 0;
  virtual void exitTypeLit(TParser::TypeLitContext *ctx) = 0;

  virtual void enterArrayType(TParser::ArrayTypeContext *ctx) = 0;
  virtual void exitArrayType(TParser::ArrayTypeContext *ctx) = 0;

  virtual void enterArrayLength(TParser::ArrayLengthContext *ctx) = 0;
  virtual void exitArrayLength(TParser::ArrayLengthContext *ctx) = 0;

  virtual void enterElementType(TParser::ElementTypeContext *ctx) = 0;
  virtual void exitElementType(TParser::ElementTypeContext *ctx) = 0;

  virtual void enterAsyncChannelType(TParser::AsyncChannelTypeContext *ctx) = 0;
  virtual void exitAsyncChannelType(TParser::AsyncChannelTypeContext *ctx) = 0;

  virtual void enterSyncChannelType(TParser::SyncChannelTypeContext *ctx) = 0;
  virtual void exitSyncChannelType(TParser::SyncChannelTypeContext *ctx) = 0;

  virtual void enterFunctionType(TParser::FunctionTypeContext *ctx) = 0;
  virtual void exitFunctionType(TParser::FunctionTypeContext *ctx) = 0;

  virtual void enterSignature(TParser::SignatureContext *ctx) = 0;
  virtual void exitSignature(TParser::SignatureContext *ctx) = 0;

  virtual void enterResult(TParser::ResultContext *ctx) = 0;
  virtual void exitResult(TParser::ResultContext *ctx) = 0;

  virtual void enterParameters(TParser::ParametersContext *ctx) = 0;
  virtual void exitParameters(TParser::ParametersContext *ctx) = 0;

  virtual void enterParameterDecl(TParser::ParameterDeclContext *ctx) = 0;
  virtual void exitParameterDecl(TParser::ParameterDeclContext *ctx) = 0;

  virtual void enterExpression(TParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(TParser::ExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpr(TParser::PrimaryExprContext *ctx) = 0;
  virtual void exitPrimaryExpr(TParser::PrimaryExprContext *ctx) = 0;

  virtual void enterConversion(TParser::ConversionContext *ctx) = 0;
  virtual void exitConversion(TParser::ConversionContext *ctx) = 0;

  virtual void enterOperand(TParser::OperandContext *ctx) = 0;
  virtual void exitOperand(TParser::OperandContext *ctx) = 0;

  virtual void enterLiteral(TParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(TParser::LiteralContext *ctx) = 0;

  virtual void enterBasicLit(TParser::BasicLitContext *ctx) = 0;
  virtual void exitBasicLit(TParser::BasicLitContext *ctx) = 0;

  virtual void enterInteger(TParser::IntegerContext *ctx) = 0;
  virtual void exitInteger(TParser::IntegerContext *ctx) = 0;

  virtual void enterOperandName(TParser::OperandNameContext *ctx) = 0;
  virtual void exitOperandName(TParser::OperandNameContext *ctx) = 0;

  virtual void enterCompositeLit(TParser::CompositeLitContext *ctx) = 0;
  virtual void exitCompositeLit(TParser::CompositeLitContext *ctx) = 0;

  virtual void enterLiteralType(TParser::LiteralTypeContext *ctx) = 0;
  virtual void exitLiteralType(TParser::LiteralTypeContext *ctx) = 0;

  virtual void enterLiteralValue(TParser::LiteralValueContext *ctx) = 0;
  virtual void exitLiteralValue(TParser::LiteralValueContext *ctx) = 0;

  virtual void enterElementList(TParser::ElementListContext *ctx) = 0;
  virtual void exitElementList(TParser::ElementListContext *ctx) = 0;

  virtual void enterKeyedElement(TParser::KeyedElementContext *ctx) = 0;
  virtual void exitKeyedElement(TParser::KeyedElementContext *ctx) = 0;

  virtual void enterKey(TParser::KeyContext *ctx) = 0;
  virtual void exitKey(TParser::KeyContext *ctx) = 0;

  virtual void enterElement(TParser::ElementContext *ctx) = 0;
  virtual void exitElement(TParser::ElementContext *ctx) = 0;

  virtual void enterString_(TParser::String_Context *ctx) = 0;
  virtual void exitString_(TParser::String_Context *ctx) = 0;

  virtual void enterFunctionLit(TParser::FunctionLitContext *ctx) = 0;
  virtual void exitFunctionLit(TParser::FunctionLitContext *ctx) = 0;

  virtual void enterIndex(TParser::IndexContext *ctx) = 0;
  virtual void exitIndex(TParser::IndexContext *ctx) = 0;

  virtual void enterArguments(TParser::ArgumentsContext *ctx) = 0;
  virtual void exitArguments(TParser::ArgumentsContext *ctx) = 0;

  virtual void enterEos(TParser::EosContext *ctx) = 0;
  virtual void exitEos(TParser::EosContext *ctx) = 0;


};

