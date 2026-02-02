/* parser/listener/visitor header section */

// Generated from TParser.g4 by ANTLR 4.13.2

#pragma once

/* parser precinclude section */

#include "antlr4-runtime.h"


/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif



/* parser context section */

class  TParser : public antlr4::Parser {
public:
  enum {
    AS = 1, ASYNC = 2, BREAK = 3, CASE = 4, CONST = 5, CONTINUE = 6, ELSE = 7, 
    FOR = 8, FROM = 9, FUNC = 10, JOIN = 11, IF = 12, NIL_LIT = 13, RETURN = 14, 
    SYNC = 15, VAR = 16, IDENTIFIER = 17, L_PAREN = 18, R_PAREN = 19, L_CURLY = 20, 
    R_CURLY = 21, L_BRACKET = 22, R_BRACKET = 23, ASSIGN = 24, COMMA = 25, 
    SEMI = 26, COLON = 27, PLUS_PLUS = 28, MINUS_MINUS = 29, DECLARE_ASSIGN = 30, 
    LOGICAL_OR = 31, LOGICAL_AND = 32, EQUALS = 33, NOT_EQUALS = 34, LESS = 35, 
    LESS_OR_EQUALS = 36, GREATER = 37, GREATER_OR_EQUALS = 38, OR = 39, 
    DIV = 40, MOD = 41, LSHIFT = 42, RSHIFT = 43, BIT_CLEAR = 44, UNDERLYING = 45, 
    EXCLAMATION = 46, PLUS = 47, MINUS = 48, CARET = 49, STAR = 50, AMPERSAND = 51, 
    EMIT = 52, SYNC_RETURN = 53, DECIMAL_LIT = 54, BINARY_LIT = 55, OCTAL_LIT = 56, 
    HEX_LIT = 57, FLOAT_LIT = 58, DECIMAL_FLOAT_LIT = 59, HEX_FLOAT_LIT = 60, 
    IMAGINARY_LIT = 61, RUNE_LIT = 62, BYTE_VALUE = 63, OCTAL_BYTE_VALUE = 64, 
    HEX_BYTE_VALUE = 65, LITTLE_U_VALUE = 66, BIG_U_VALUE = 67, RAW_STRING_LIT = 68, 
    INTERPRETED_STRING_LIT = 69, WS = 70, COMMENT = 71, TERMINATOR = 72, 
    LINE_COMMENT = 73, WS_NLSEMI = 74, COMMENT_NLSEMI = 75, LINE_COMMENT_NLSEMI = 76, 
    EOS = 77, OTHER = 78
  };

  enum {
    RuleSourceFile = 0, RuleIdentifier = 1, RuleDeclaration = 2, RuleConstDecl = 3, 
    RuleConstSpec = 4, RuleIdentifierList = 5, RuleExpressionList = 6, RuleTypeSpec = 7, 
    RuleAliasDecl = 8, RuleTypeDef = 9, RuleTypeParameters = 10, RuleTypeParameterDecl = 11, 
    RuleTypeElement = 12, RuleTypeTerm = 13, RuleFunctionDecl = 14, RuleVarDecl = 15, 
    RuleVarSpec = 16, RuleBlock = 17, RuleStatementList = 18, RuleStatement = 19, 
    RuleSimpleStmt = 20, RuleExpressionStmt = 21, RuleSyncReturnStmt = 22, 
    RuleEmitStmt = 23, RuleIncDecStmt = 24, RuleAssignment = 25, RuleAssign_op = 26, 
    RuleShortVarDecl = 27, RuleReturnStmt = 28, RuleBreakStmt = 29, RuleContinueStmt = 30, 
    RuleIfStmt = 31, RuleTypeList = 32, RuleJoinStmt = 33, RuleMatchClause = 34, 
    RuleMatchCase = 35, RuleFromChanAs = 36, RuleForStmt = 37, RuleCondition = 38, 
    RuleForClause = 39, RuleType_ = 40, RuleTypeArgs = 41, RuleTypeName = 42, 
    RuleTypeLit = 43, RuleArrayType = 44, RuleArrayLength = 45, RuleElementType = 46, 
    RuleAsyncChannelType = 47, RuleSyncChannelType = 48, RuleFunctionType = 49, 
    RuleSignature = 50, RuleResult = 51, RuleParameters = 52, RuleParameterDecl = 53, 
    RuleExpression = 54, RulePrimaryExpr = 55, RuleConversion = 56, RuleOperand = 57, 
    RuleLiteral = 58, RuleBasicLit = 59, RuleInteger = 60, RuleOperandName = 61, 
    RuleCompositeLit = 62, RuleLiteralType = 63, RuleLiteralValue = 64, 
    RuleElementList = 65, RuleKeyedElement = 66, RuleKey = 67, RuleElement = 68, 
    RuleString_ = 69, RuleFunctionLit = 70, RuleIndex = 71, RuleArguments = 72, 
    RuleEos = 73
  };

  explicit TParser(antlr4::TokenStream *input);

  TParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~TParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  /* public parser declarations/members section */
  bool myAction() { return true; }
  bool doesItBlend() { return true; }
  void cleanUp() {}
  void doInit() {}
  void doAfter() {}


  class SourceFileContext;
  class IdentifierContext;
  class DeclarationContext;
  class ConstDeclContext;
  class ConstSpecContext;
  class IdentifierListContext;
  class ExpressionListContext;
  class TypeSpecContext;
  class AliasDeclContext;
  class TypeDefContext;
  class TypeParametersContext;
  class TypeParameterDeclContext;
  class TypeElementContext;
  class TypeTermContext;
  class FunctionDeclContext;
  class VarDeclContext;
  class VarSpecContext;
  class BlockContext;
  class StatementListContext;
  class StatementContext;
  class SimpleStmtContext;
  class ExpressionStmtContext;
  class SyncReturnStmtContext;
  class EmitStmtContext;
  class IncDecStmtContext;
  class AssignmentContext;
  class Assign_opContext;
  class ShortVarDeclContext;
  class ReturnStmtContext;
  class BreakStmtContext;
  class ContinueStmtContext;
  class IfStmtContext;
  class TypeListContext;
  class JoinStmtContext;
  class MatchClauseContext;
  class MatchCaseContext;
  class FromChanAsContext;
  class ForStmtContext;
  class ConditionContext;
  class ForClauseContext;
  class Type_Context;
  class TypeArgsContext;
  class TypeNameContext;
  class TypeLitContext;
  class ArrayTypeContext;
  class ArrayLengthContext;
  class ElementTypeContext;
  class AsyncChannelTypeContext;
  class SyncChannelTypeContext;
  class FunctionTypeContext;
  class SignatureContext;
  class ResultContext;
  class ParametersContext;
  class ParameterDeclContext;
  class ExpressionContext;
  class PrimaryExprContext;
  class ConversionContext;
  class OperandContext;
  class LiteralContext;
  class BasicLitContext;
  class IntegerContext;
  class OperandNameContext;
  class CompositeLitContext;
  class LiteralTypeContext;
  class LiteralValueContext;
  class ElementListContext;
  class KeyedElementContext;
  class KeyContext;
  class ElementContext;
  class String_Context;
  class FunctionLitContext;
  class IndexContext;
  class ArgumentsContext;
  class EosContext; 

  class  SourceFileContext : public antlr4::ParserRuleContext {
  public:
    SourceFileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<EosContext *> eos();
    EosContext* eos(size_t i);
    std::vector<FunctionDeclContext *> functionDecl();
    FunctionDeclContext* functionDecl(size_t i);
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SourceFileContext* sourceFile();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstDeclContext *constDecl();
    VarDeclContext *varDecl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  ConstDeclContext : public antlr4::ParserRuleContext {
  public:
    ConstDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONST();
    std::vector<ConstSpecContext *> constSpec();
    ConstSpecContext* constSpec(size_t i);
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    std::vector<EosContext *> eos();
    EosContext* eos(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstDeclContext* constDecl();

  class  ConstSpecContext : public antlr4::ParserRuleContext {
  public:
    ConstSpecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierListContext *identifierList();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionListContext *expressionList();
    Type_Context *type_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstSpecContext* constSpec();

  class  IdentifierListContext : public antlr4::ParserRuleContext {
  public:
    IdentifierListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierListContext* identifierList();

  class  ExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionListContext* expressionList();

  class  TypeSpecContext : public antlr4::ParserRuleContext {
  public:
    TypeSpecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AliasDeclContext *aliasDecl();
    TypeDefContext *typeDef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeSpecContext* typeSpec();

  class  AliasDeclContext : public antlr4::ParserRuleContext {
  public:
    AliasDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *ASSIGN();
    Type_Context *type_();
    TypeParametersContext *typeParameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AliasDeclContext* aliasDecl();

  class  TypeDefContext : public antlr4::ParserRuleContext {
  public:
    TypeDefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    Type_Context *type_();
    TypeParametersContext *typeParameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDefContext* typeDef();

  class  TypeParametersContext : public antlr4::ParserRuleContext {
  public:
    TypeParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACKET();
    std::vector<TypeParameterDeclContext *> typeParameterDecl();
    TypeParameterDeclContext* typeParameterDecl(size_t i);
    antlr4::tree::TerminalNode *R_BRACKET();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeParametersContext* typeParameters();

  class  TypeParameterDeclContext : public antlr4::ParserRuleContext {
  public:
    TypeParameterDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierListContext *identifierList();
    TypeElementContext *typeElement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeParameterDeclContext* typeParameterDecl();

  class  TypeElementContext : public antlr4::ParserRuleContext {
  public:
    TypeElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeTermContext *> typeTerm();
    TypeTermContext* typeTerm(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeElementContext* typeElement();

  class  TypeTermContext : public antlr4::ParserRuleContext {
  public:
    TypeTermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_Context *type_();
    antlr4::tree::TerminalNode *UNDERLYING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeTermContext* typeTerm();

  class  FunctionDeclContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNC();
    antlr4::tree::TerminalNode *IDENTIFIER();
    SignatureContext *signature();
    TypeParametersContext *typeParameters();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDeclContext* functionDecl();

  class  VarDeclContext : public antlr4::ParserRuleContext {
  public:
    VarDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR();
    std::vector<VarSpecContext *> varSpec();
    VarSpecContext* varSpec(size_t i);
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    std::vector<EosContext *> eos();
    EosContext* eos(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarDeclContext* varDecl();

  class  VarSpecContext : public antlr4::ParserRuleContext {
  public:
    VarSpecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierListContext *identifierList();
    Type_Context *type_();
    antlr4::tree::TerminalNode *ASSIGN();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VarSpecContext* varSpec();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_CURLY();
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *R_CURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  StatementListContext : public antlr4::ParserRuleContext {
  public:
    StatementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<EosContext *> eos();
    EosContext* eos(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EOS();
    antlr4::tree::TerminalNode* EOS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementListContext* statementList();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationContext *declaration();
    SimpleStmtContext *simpleStmt();
    ReturnStmtContext *returnStmt();
    BreakStmtContext *breakStmt();
    ContinueStmtContext *continueStmt();
    BlockContext *block();
    IfStmtContext *ifStmt();
    JoinStmtContext *joinStmt();
    ForStmtContext *forStmt();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  SimpleStmtContext : public antlr4::ParserRuleContext {
  public:
    SimpleStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    EmitStmtContext *emitStmt();
    SyncReturnStmtContext *syncReturnStmt();
    IncDecStmtContext *incDecStmt();
    AssignmentContext *assignment();
    ExpressionStmtContext *expressionStmt();
    ShortVarDeclContext *shortVarDecl();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleStmtContext* simpleStmt();

  class  ExpressionStmtContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStmtContext* expressionStmt();

  class  SyncReturnStmtContext : public antlr4::ParserRuleContext {
  public:
    TParser::ExpressionContext *channel = nullptr;
    SyncReturnStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYNC_RETURN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SyncReturnStmtContext* syncReturnStmt();

  class  EmitStmtContext : public antlr4::ParserRuleContext {
  public:
    TParser::ExpressionContext *channel = nullptr;
    EmitStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EMIT();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmitStmtContext* emitStmt();

  class  IncDecStmtContext : public antlr4::ParserRuleContext {
  public:
    IncDecStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *PLUS_PLUS();
    antlr4::tree::TerminalNode *MINUS_MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IncDecStmtContext* incDecStmt();

  class  AssignmentContext : public antlr4::ParserRuleContext {
  public:
    AssignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionListContext *> expressionList();
    ExpressionListContext* expressionList(size_t i);
    Assign_opContext *assign_op();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentContext* assignment();

  class  Assign_opContext : public antlr4::ParserRuleContext {
  public:
    Assign_opContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSIGN();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *CARET();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();
    antlr4::tree::TerminalNode *AMPERSAND();
    antlr4::tree::TerminalNode *BIT_CLEAR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Assign_opContext* assign_op();

  class  ShortVarDeclContext : public antlr4::ParserRuleContext {
  public:
    ShortVarDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierListContext *identifierList();
    antlr4::tree::TerminalNode *DECLARE_ASSIGN();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShortVarDeclContext* shortVarDecl();

  class  ReturnStmtContext : public antlr4::ParserRuleContext {
  public:
    ReturnStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStmtContext* returnStmt();

  class  BreakStmtContext : public antlr4::ParserRuleContext {
  public:
    BreakStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakStmtContext* breakStmt();

  class  ContinueStmtContext : public antlr4::ParserRuleContext {
  public:
    ContinueStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ContinueStmtContext* continueStmt();

  class  IfStmtContext : public antlr4::ParserRuleContext {
  public:
    IfStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    std::vector<BlockContext *> block();
    BlockContext* block(size_t i);
    ExpressionContext *expression();
    SimpleStmtContext *simpleStmt();
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *EOS();
    antlr4::tree::TerminalNode *ELSE();
    IfStmtContext *ifStmt();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IfStmtContext* ifStmt();

  class  TypeListContext : public antlr4::ParserRuleContext {
  public:
    TypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Type_Context *> type_();
    Type_Context* type_(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NIL_LIT();
    antlr4::tree::TerminalNode* NIL_LIT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeListContext* typeList();

  class  JoinStmtContext : public antlr4::ParserRuleContext {
  public:
    JoinStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *JOIN();
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    std::vector<MatchClauseContext *> matchClause();
    MatchClauseContext* matchClause(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JoinStmtContext* joinStmt();

  class  MatchClauseContext : public antlr4::ParserRuleContext {
  public:
    MatchClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MatchCaseContext *matchCase();
    antlr4::tree::TerminalNode *COLON();
    StatementListContext *statementList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchClauseContext* matchClause();

  class  MatchCaseContext : public antlr4::ParserRuleContext {
  public:
    MatchCaseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CASE();
    std::vector<FromChanAsContext *> fromChanAs();
    FromChanAsContext* fromChanAs(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchCaseContext* matchCase();

  class  FromChanAsContext : public antlr4::ParserRuleContext {
  public:
    FromChanAsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FromChanAsContext* fromChanAs();

  class  ForStmtContext : public antlr4::ParserRuleContext {
  public:
    ForStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    BlockContext *block();
    ConditionContext *condition();
    ForClauseContext *forClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForStmtContext* forStmt();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionContext* condition();

  class  ForClauseContext : public antlr4::ParserRuleContext {
  public:
    TParser::SimpleStmtContext *initStmt = nullptr;
    TParser::SimpleStmtContext *postStmt = nullptr;
    ForClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EosContext *> eos();
    EosContext* eos(size_t i);
    ExpressionContext *expression();
    std::vector<SimpleStmtContext *> simpleStmt();
    SimpleStmtContext* simpleStmt(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForClauseContext* forClause();

  class  Type_Context : public antlr4::ParserRuleContext {
  public:
    Type_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    TypeArgsContext *typeArgs();
    TypeLitContext *typeLit();
    antlr4::tree::TerminalNode *L_PAREN();
    Type_Context *type_();
    antlr4::tree::TerminalNode *R_PAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Type_Context* type_();

  class  TypeArgsContext : public antlr4::ParserRuleContext {
  public:
    TypeArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACKET();
    TypeListContext *typeList();
    antlr4::tree::TerminalNode *R_BRACKET();
    antlr4::tree::TerminalNode *COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeArgsContext* typeArgs();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNameContext* typeName();

  class  TypeLitContext : public antlr4::ParserRuleContext {
  public:
    TypeLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrayTypeContext *arrayType();
    FunctionTypeContext *functionType();
    SyncChannelTypeContext *syncChannelType();
    AsyncChannelTypeContext *asyncChannelType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeLitContext* typeLit();

  class  ArrayTypeContext : public antlr4::ParserRuleContext {
  public:
    ArrayTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACKET();
    ArrayLengthContext *arrayLength();
    antlr4::tree::TerminalNode *R_BRACKET();
    ElementTypeContext *elementType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayTypeContext* arrayType();

  class  ArrayLengthContext : public antlr4::ParserRuleContext {
  public:
    ArrayLengthContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayLengthContext* arrayLength();

  class  ElementTypeContext : public antlr4::ParserRuleContext {
  public:
    ElementTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_Context *type_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementTypeContext* elementType();

  class  AsyncChannelTypeContext : public antlr4::ParserRuleContext {
  public:
    AsyncChannelTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASYNC();
    ElementTypeContext *elementType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AsyncChannelTypeContext* asyncChannelType();

  class  SyncChannelTypeContext : public antlr4::ParserRuleContext {
  public:
    SyncChannelTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYNC();
    SignatureContext *signature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SyncChannelTypeContext* syncChannelType();

  class  FunctionTypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNC();
    SignatureContext *signature();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionTypeContext* functionType();

  class  SignatureContext : public antlr4::ParserRuleContext {
  public:
    SignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParametersContext *parameters();
    ResultContext *result();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SignatureContext* signature();

  class  ResultContext : public antlr4::ParserRuleContext {
  public:
    ResultContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParametersContext *parameters();
    Type_Context *type_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ResultContext* result();

  class  ParametersContext : public antlr4::ParserRuleContext {
  public:
    ParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    std::vector<ParameterDeclContext *> parameterDecl();
    ParameterDeclContext* parameterDecl(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParametersContext* parameters();

  class  ParameterDeclContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_Context *type_();
    IdentifierListContext *identifierList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterDeclContext* parameterDecl();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *unary_op = nullptr;
    antlr4::Token *mul_op = nullptr;
    antlr4::Token *add_op = nullptr;
    antlr4::Token *rel_op = nullptr;
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExprContext *primaryExpr();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    antlr4::tree::TerminalNode *EXCLAMATION();
    antlr4::tree::TerminalNode *CARET();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *AMPERSAND();
    antlr4::tree::TerminalNode *DIV();
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *LSHIFT();
    antlr4::tree::TerminalNode *RSHIFT();
    antlr4::tree::TerminalNode *BIT_CLEAR();
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *NOT_EQUALS();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *LESS_OR_EQUALS();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *GREATER_OR_EQUALS();
    antlr4::tree::TerminalNode *LOGICAL_AND();
    antlr4::tree::TerminalNode *LOGICAL_OR();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  PrimaryExprContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OperandContext *operand();
    std::vector<ArgumentsContext *> arguments();
    ArgumentsContext* arguments(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExprContext* primaryExpr();

  class  ConversionContext : public antlr4::ParserRuleContext {
  public:
    ConversionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_Context *type_();
    antlr4::tree::TerminalNode *L_PAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *R_PAREN();
    antlr4::tree::TerminalNode *COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConversionContext* conversion();

  class  OperandContext : public antlr4::ParserRuleContext {
  public:
    OperandContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralContext *literal();
    OperandNameContext *operandName();
    TypeArgsContext *typeArgs();
    antlr4::tree::TerminalNode *L_PAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *R_PAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperandContext* operand();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BasicLitContext *basicLit();
    CompositeLitContext *compositeLit();
    FunctionLitContext *functionLit();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  BasicLitContext : public antlr4::ParserRuleContext {
  public:
    BasicLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NIL_LIT();
    IntegerContext *integer();
    String_Context *string_();
    antlr4::tree::TerminalNode *FLOAT_LIT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BasicLitContext* basicLit();

  class  IntegerContext : public antlr4::ParserRuleContext {
  public:
    IntegerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DECIMAL_LIT();
    antlr4::tree::TerminalNode *BINARY_LIT();
    antlr4::tree::TerminalNode *OCTAL_LIT();
    antlr4::tree::TerminalNode *HEX_LIT();
    antlr4::tree::TerminalNode *IMAGINARY_LIT();
    antlr4::tree::TerminalNode *RUNE_LIT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerContext* integer();

  class  OperandNameContext : public antlr4::ParserRuleContext {
  public:
    OperandNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperandNameContext* operandName();

  class  CompositeLitContext : public antlr4::ParserRuleContext {
  public:
    CompositeLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralTypeContext *literalType();
    LiteralValueContext *literalValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompositeLitContext* compositeLit();

  class  LiteralTypeContext : public antlr4::ParserRuleContext {
  public:
    LiteralTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrayTypeContext *arrayType();
    TypeNameContext *typeName();
    TypeArgsContext *typeArgs();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralTypeContext* literalType();

  class  LiteralValueContext : public antlr4::ParserRuleContext {
  public:
    LiteralValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    ElementListContext *elementList();
    antlr4::tree::TerminalNode *COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralValueContext* literalValue();

  class  ElementListContext : public antlr4::ParserRuleContext {
  public:
    ElementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<KeyedElementContext *> keyedElement();
    KeyedElementContext* keyedElement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementListContext* elementList();

  class  KeyedElementContext : public antlr4::ParserRuleContext {
  public:
    KeyedElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementContext *element();
    KeyContext *key();
    antlr4::tree::TerminalNode *COLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyedElementContext* keyedElement();

  class  KeyContext : public antlr4::ParserRuleContext {
  public:
    KeyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    LiteralValueContext *literalValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyContext* key();

  class  ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    LiteralValueContext *literalValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContext* element();

  class  String_Context : public antlr4::ParserRuleContext {
  public:
    String_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RAW_STRING_LIT();
    antlr4::tree::TerminalNode *INTERPRETED_STRING_LIT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  String_Context* string_();

  class  FunctionLitContext : public antlr4::ParserRuleContext {
  public:
    FunctionLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNC();
    SignatureContext *signature();
    BlockContext *block();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionLitContext* functionLit();

  class  IndexContext : public antlr4::ParserRuleContext {
  public:
    IndexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACKET();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *R_BRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexContext* index();

  class  ArgumentsContext : public antlr4::ParserRuleContext {
  public:
    ArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    ExpressionListContext *expressionList();
    Type_Context *type_();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  EosContext : public antlr4::ParserRuleContext {
  public:
    EosContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *EOS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EosContext* eos();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool expressionSempred(ExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
  /* private parser declarations section */
};

