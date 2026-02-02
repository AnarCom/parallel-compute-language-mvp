
// Generated from TParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "TParserListener.h"


/**
 * This class provides an empty implementation of TParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  TParserBaseListener : public TParserListener {
public:

  virtual void enterSourceFile(TParser::SourceFileContext * /*ctx*/) override { }
  virtual void exitSourceFile(TParser::SourceFileContext * /*ctx*/) override { }

  virtual void enterIdentifier(TParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(TParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterDeclaration(TParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(TParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterConstDecl(TParser::ConstDeclContext * /*ctx*/) override { }
  virtual void exitConstDecl(TParser::ConstDeclContext * /*ctx*/) override { }

  virtual void enterConstSpec(TParser::ConstSpecContext * /*ctx*/) override { }
  virtual void exitConstSpec(TParser::ConstSpecContext * /*ctx*/) override { }

  virtual void enterIdentifierList(TParser::IdentifierListContext * /*ctx*/) override { }
  virtual void exitIdentifierList(TParser::IdentifierListContext * /*ctx*/) override { }

  virtual void enterExpressionList(TParser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(TParser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterTypeSpec(TParser::TypeSpecContext * /*ctx*/) override { }
  virtual void exitTypeSpec(TParser::TypeSpecContext * /*ctx*/) override { }

  virtual void enterAliasDecl(TParser::AliasDeclContext * /*ctx*/) override { }
  virtual void exitAliasDecl(TParser::AliasDeclContext * /*ctx*/) override { }

  virtual void enterTypeDef(TParser::TypeDefContext * /*ctx*/) override { }
  virtual void exitTypeDef(TParser::TypeDefContext * /*ctx*/) override { }

  virtual void enterTypeParameters(TParser::TypeParametersContext * /*ctx*/) override { }
  virtual void exitTypeParameters(TParser::TypeParametersContext * /*ctx*/) override { }

  virtual void enterTypeParameterDecl(TParser::TypeParameterDeclContext * /*ctx*/) override { }
  virtual void exitTypeParameterDecl(TParser::TypeParameterDeclContext * /*ctx*/) override { }

  virtual void enterTypeElement(TParser::TypeElementContext * /*ctx*/) override { }
  virtual void exitTypeElement(TParser::TypeElementContext * /*ctx*/) override { }

  virtual void enterTypeTerm(TParser::TypeTermContext * /*ctx*/) override { }
  virtual void exitTypeTerm(TParser::TypeTermContext * /*ctx*/) override { }

  virtual void enterFunctionDecl(TParser::FunctionDeclContext * /*ctx*/) override { }
  virtual void exitFunctionDecl(TParser::FunctionDeclContext * /*ctx*/) override { }

  virtual void enterVarDecl(TParser::VarDeclContext * /*ctx*/) override { }
  virtual void exitVarDecl(TParser::VarDeclContext * /*ctx*/) override { }

  virtual void enterVarSpec(TParser::VarSpecContext * /*ctx*/) override { }
  virtual void exitVarSpec(TParser::VarSpecContext * /*ctx*/) override { }

  virtual void enterBlock(TParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(TParser::BlockContext * /*ctx*/) override { }

  virtual void enterStatementList(TParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(TParser::StatementListContext * /*ctx*/) override { }

  virtual void enterStatement(TParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(TParser::StatementContext * /*ctx*/) override { }

  virtual void enterSimpleStmt(TParser::SimpleStmtContext * /*ctx*/) override { }
  virtual void exitSimpleStmt(TParser::SimpleStmtContext * /*ctx*/) override { }

  virtual void enterExpressionStmt(TParser::ExpressionStmtContext * /*ctx*/) override { }
  virtual void exitExpressionStmt(TParser::ExpressionStmtContext * /*ctx*/) override { }

  virtual void enterSyncReturnStmt(TParser::SyncReturnStmtContext * /*ctx*/) override { }
  virtual void exitSyncReturnStmt(TParser::SyncReturnStmtContext * /*ctx*/) override { }

  virtual void enterEmitStmt(TParser::EmitStmtContext * /*ctx*/) override { }
  virtual void exitEmitStmt(TParser::EmitStmtContext * /*ctx*/) override { }

  virtual void enterIncDecStmt(TParser::IncDecStmtContext * /*ctx*/) override { }
  virtual void exitIncDecStmt(TParser::IncDecStmtContext * /*ctx*/) override { }

  virtual void enterAssignment(TParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(TParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterAssign_op(TParser::Assign_opContext * /*ctx*/) override { }
  virtual void exitAssign_op(TParser::Assign_opContext * /*ctx*/) override { }

  virtual void enterShortVarDecl(TParser::ShortVarDeclContext * /*ctx*/) override { }
  virtual void exitShortVarDecl(TParser::ShortVarDeclContext * /*ctx*/) override { }

  virtual void enterReturnStmt(TParser::ReturnStmtContext * /*ctx*/) override { }
  virtual void exitReturnStmt(TParser::ReturnStmtContext * /*ctx*/) override { }

  virtual void enterBreakStmt(TParser::BreakStmtContext * /*ctx*/) override { }
  virtual void exitBreakStmt(TParser::BreakStmtContext * /*ctx*/) override { }

  virtual void enterContinueStmt(TParser::ContinueStmtContext * /*ctx*/) override { }
  virtual void exitContinueStmt(TParser::ContinueStmtContext * /*ctx*/) override { }

  virtual void enterIfStmt(TParser::IfStmtContext * /*ctx*/) override { }
  virtual void exitIfStmt(TParser::IfStmtContext * /*ctx*/) override { }

  virtual void enterTypeList(TParser::TypeListContext * /*ctx*/) override { }
  virtual void exitTypeList(TParser::TypeListContext * /*ctx*/) override { }

  virtual void enterJoinStmt(TParser::JoinStmtContext * /*ctx*/) override { }
  virtual void exitJoinStmt(TParser::JoinStmtContext * /*ctx*/) override { }

  virtual void enterMatchClause(TParser::MatchClauseContext * /*ctx*/) override { }
  virtual void exitMatchClause(TParser::MatchClauseContext * /*ctx*/) override { }

  virtual void enterMatchCase(TParser::MatchCaseContext * /*ctx*/) override { }
  virtual void exitMatchCase(TParser::MatchCaseContext * /*ctx*/) override { }

  virtual void enterFromChanAs(TParser::FromChanAsContext * /*ctx*/) override { }
  virtual void exitFromChanAs(TParser::FromChanAsContext * /*ctx*/) override { }

  virtual void enterForStmt(TParser::ForStmtContext * /*ctx*/) override { }
  virtual void exitForStmt(TParser::ForStmtContext * /*ctx*/) override { }

  virtual void enterCondition(TParser::ConditionContext * /*ctx*/) override { }
  virtual void exitCondition(TParser::ConditionContext * /*ctx*/) override { }

  virtual void enterForClause(TParser::ForClauseContext * /*ctx*/) override { }
  virtual void exitForClause(TParser::ForClauseContext * /*ctx*/) override { }

  virtual void enterType_(TParser::Type_Context * /*ctx*/) override { }
  virtual void exitType_(TParser::Type_Context * /*ctx*/) override { }

  virtual void enterTypeArgs(TParser::TypeArgsContext * /*ctx*/) override { }
  virtual void exitTypeArgs(TParser::TypeArgsContext * /*ctx*/) override { }

  virtual void enterTypeName(TParser::TypeNameContext * /*ctx*/) override { }
  virtual void exitTypeName(TParser::TypeNameContext * /*ctx*/) override { }

  virtual void enterTypeLit(TParser::TypeLitContext * /*ctx*/) override { }
  virtual void exitTypeLit(TParser::TypeLitContext * /*ctx*/) override { }

  virtual void enterArrayType(TParser::ArrayTypeContext * /*ctx*/) override { }
  virtual void exitArrayType(TParser::ArrayTypeContext * /*ctx*/) override { }

  virtual void enterArrayLength(TParser::ArrayLengthContext * /*ctx*/) override { }
  virtual void exitArrayLength(TParser::ArrayLengthContext * /*ctx*/) override { }

  virtual void enterElementType(TParser::ElementTypeContext * /*ctx*/) override { }
  virtual void exitElementType(TParser::ElementTypeContext * /*ctx*/) override { }

  virtual void enterAsyncChannelType(TParser::AsyncChannelTypeContext * /*ctx*/) override { }
  virtual void exitAsyncChannelType(TParser::AsyncChannelTypeContext * /*ctx*/) override { }

  virtual void enterSyncChannelType(TParser::SyncChannelTypeContext * /*ctx*/) override { }
  virtual void exitSyncChannelType(TParser::SyncChannelTypeContext * /*ctx*/) override { }

  virtual void enterFunctionType(TParser::FunctionTypeContext * /*ctx*/) override { }
  virtual void exitFunctionType(TParser::FunctionTypeContext * /*ctx*/) override { }

  virtual void enterSignature(TParser::SignatureContext * /*ctx*/) override { }
  virtual void exitSignature(TParser::SignatureContext * /*ctx*/) override { }

  virtual void enterResult(TParser::ResultContext * /*ctx*/) override { }
  virtual void exitResult(TParser::ResultContext * /*ctx*/) override { }

  virtual void enterParameters(TParser::ParametersContext * /*ctx*/) override { }
  virtual void exitParameters(TParser::ParametersContext * /*ctx*/) override { }

  virtual void enterParameterDecl(TParser::ParameterDeclContext * /*ctx*/) override { }
  virtual void exitParameterDecl(TParser::ParameterDeclContext * /*ctx*/) override { }

  virtual void enterExpression(TParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(TParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpr(TParser::PrimaryExprContext * /*ctx*/) override { }
  virtual void exitPrimaryExpr(TParser::PrimaryExprContext * /*ctx*/) override { }

  virtual void enterConversion(TParser::ConversionContext * /*ctx*/) override { }
  virtual void exitConversion(TParser::ConversionContext * /*ctx*/) override { }

  virtual void enterOperand(TParser::OperandContext * /*ctx*/) override { }
  virtual void exitOperand(TParser::OperandContext * /*ctx*/) override { }

  virtual void enterLiteral(TParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(TParser::LiteralContext * /*ctx*/) override { }

  virtual void enterBasicLit(TParser::BasicLitContext * /*ctx*/) override { }
  virtual void exitBasicLit(TParser::BasicLitContext * /*ctx*/) override { }

  virtual void enterInteger(TParser::IntegerContext * /*ctx*/) override { }
  virtual void exitInteger(TParser::IntegerContext * /*ctx*/) override { }

  virtual void enterOperandName(TParser::OperandNameContext * /*ctx*/) override { }
  virtual void exitOperandName(TParser::OperandNameContext * /*ctx*/) override { }

  virtual void enterCompositeLit(TParser::CompositeLitContext * /*ctx*/) override { }
  virtual void exitCompositeLit(TParser::CompositeLitContext * /*ctx*/) override { }

  virtual void enterLiteralType(TParser::LiteralTypeContext * /*ctx*/) override { }
  virtual void exitLiteralType(TParser::LiteralTypeContext * /*ctx*/) override { }

  virtual void enterLiteralValue(TParser::LiteralValueContext * /*ctx*/) override { }
  virtual void exitLiteralValue(TParser::LiteralValueContext * /*ctx*/) override { }

  virtual void enterElementList(TParser::ElementListContext * /*ctx*/) override { }
  virtual void exitElementList(TParser::ElementListContext * /*ctx*/) override { }

  virtual void enterKeyedElement(TParser::KeyedElementContext * /*ctx*/) override { }
  virtual void exitKeyedElement(TParser::KeyedElementContext * /*ctx*/) override { }

  virtual void enterKey(TParser::KeyContext * /*ctx*/) override { }
  virtual void exitKey(TParser::KeyContext * /*ctx*/) override { }

  virtual void enterElement(TParser::ElementContext * /*ctx*/) override { }
  virtual void exitElement(TParser::ElementContext * /*ctx*/) override { }

  virtual void enterString_(TParser::String_Context * /*ctx*/) override { }
  virtual void exitString_(TParser::String_Context * /*ctx*/) override { }

  virtual void enterFunctionLit(TParser::FunctionLitContext * /*ctx*/) override { }
  virtual void exitFunctionLit(TParser::FunctionLitContext * /*ctx*/) override { }

  virtual void enterIndex(TParser::IndexContext * /*ctx*/) override { }
  virtual void exitIndex(TParser::IndexContext * /*ctx*/) override { }

  virtual void enterArguments(TParser::ArgumentsContext * /*ctx*/) override { }
  virtual void exitArguments(TParser::ArgumentsContext * /*ctx*/) override { }

  virtual void enterEos(TParser::EosContext * /*ctx*/) override { }
  virtual void exitEos(TParser::EosContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

