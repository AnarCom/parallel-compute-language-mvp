
// Generated from TParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TParserVisitor.h"


/**
 * This class provides an empty implementation of TParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  TParserBaseVisitor : public TParserVisitor {
public:

  virtual std::any visitSourceFile(TParser::SourceFileContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(TParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(TParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDecl(TParser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstSpec(TParser::ConstSpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierList(TParser::IdentifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(TParser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeSpec(TParser::TypeSpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAliasDecl(TParser::AliasDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDef(TParser::TypeDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeParameters(TParser::TypeParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeParameterDecl(TParser::TypeParameterDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeElement(TParser::TypeElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeTerm(TParser::TypeTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDecl(TParser::FunctionDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(TParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarSpec(TParser::VarSpecContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(TParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementList(TParser::StatementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(TParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleStmt(TParser::SimpleStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStmt(TParser::ExpressionStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSyncReturnStmt(TParser::SyncReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmitStmt(TParser::EmitStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIncDecStmt(TParser::IncDecStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(TParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssign_op(TParser::Assign_opContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitShortVarDecl(TParser::ShortVarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStmt(TParser::ReturnStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStmt(TParser::BreakStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStmt(TParser::ContinueStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStmt(TParser::IfStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeList(TParser::TypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJoinStmt(TParser::JoinStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchClause(TParser::MatchClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchCase(TParser::MatchCaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFromChanAs(TParser::FromChanAsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStmt(TParser::ForStmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCondition(TParser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForClause(TParser::ForClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType_(TParser::Type_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeArgs(TParser::TypeArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeName(TParser::TypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeLit(TParser::TypeLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayType(TParser::ArrayTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayLength(TParser::ArrayLengthContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementType(TParser::ElementTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAsyncChannelType(TParser::AsyncChannelTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSyncChannelType(TParser::SyncChannelTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionType(TParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSignature(TParser::SignatureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitResult(TParser::ResultContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameters(TParser::ParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterDecl(TParser::ParameterDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(TParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpr(TParser::PrimaryExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConversion(TParser::ConversionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperand(TParser::OperandContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(TParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicLit(TParser::BasicLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInteger(TParser::IntegerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOperandName(TParser::OperandNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCompositeLit(TParser::CompositeLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralType(TParser::LiteralTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralValue(TParser::LiteralValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementList(TParser::ElementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKeyedElement(TParser::KeyedElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitKey(TParser::KeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(TParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitString_(TParser::String_Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionLit(TParser::FunctionLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIndex(TParser::IndexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArguments(TParser::ArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEos(TParser::EosContext *ctx) override {
    return visitChildren(ctx);
  }


};

