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
    SYNC = 15, STRUCT = 16, TYPE = 17, VAR = 18, IDENTIFIER = 19, L_PAREN = 20, 
    R_PAREN = 21, L_CURLY = 22, R_CURLY = 23, L_BRACKET = 24, R_BRACKET = 25, 
    ASSIGN = 26, COMMA = 27, SEMI = 28, COLON = 29, DOT = 30, PLUS_PLUS = 31, 
    MINUS_MINUS = 32, DECLARE_ASSIGN = 33, LOGICAL_OR = 34, LOGICAL_AND = 35, 
    SYNC_RETURN = 36, EQUALS = 37, NOT_EQUALS = 38, LESS = 39, LESS_OR_EQUALS = 40, 
    GREATER = 41, GREATER_OR_EQUALS = 42, OR = 43, DIV = 44, MOD = 45, LSHIFT = 46, 
    RSHIFT = 47, BIT_CLEAR = 48, UNDERLYING = 49, EXCLAMATION = 50, PLUS = 51, 
    MINUS = 52, CARET = 53, STAR = 54, AMPERSAND = 55, EMIT = 56, DECIMAL_LIT = 57, 
    BINARY_LIT = 58, OCTAL_LIT = 59, HEX_LIT = 60, FLOAT_LIT = 61, DECIMAL_FLOAT_LIT = 62, 
    HEX_FLOAT_LIT = 63, IMAGINARY_LIT = 64, RUNE_LIT = 65, BYTE_VALUE = 66, 
    OCTAL_BYTE_VALUE = 67, HEX_BYTE_VALUE = 68, LITTLE_U_VALUE = 69, BIG_U_VALUE = 70, 
    RAW_STRING_LIT = 71, INTERPRETED_STRING_LIT = 72, WS = 73, COMMENT = 74, 
    TERMINATOR = 75, LINE_COMMENT = 76, WS_NLSEMI = 77, COMMENT_NLSEMI = 78, 
    LINE_COMMENT_NLSEMI = 79, EOS = 80, OTHER = 81
  };

  enum {
    RuleSourceFile = 0, RuleIdentifier = 1, RuleDeclaration = 2, RuleConstDecl = 3, 
    RuleConstSpec = 4, RuleIdentifierList = 5, RuleExpressionList = 6, RuleTypeDecl = 7, 
    RuleTypeSpec = 8, RuleAliasDecl = 9, RuleTypeDef = 10, RuleTypeParameters = 11, 
    RuleTypeParameterDecl = 12, RuleTypeElement = 13, RuleTypeTerm = 14, 
    RuleFunctionDecl = 15, RuleVarDecl = 16, RuleVarSpec = 17, RuleBlock = 18, 
    RuleStatementList = 19, RuleStatement = 20, RuleSimpleStmt = 21, RuleExpressionStmt = 22, 
    RuleSyncReturnStmt = 23, RuleEmitStmt = 24, RuleIncDecStmt = 25, RuleAssignment = 26, 
    RuleAssign_op = 27, RuleShortVarDecl = 28, RuleReturnStmt = 29, RuleBreakStmt = 30, 
    RuleContinueStmt = 31, RuleIfStmt = 32, RuleTypeList = 33, RuleJoinStmt = 34, 
    RuleMatchClause = 35, RuleMatchCase = 36, RuleFromChanAs = 37, RuleForStmt = 38, 
    RuleCondition = 39, RuleForClause = 40, RuleType_ = 41, RuleTypeArgs = 42, 
    RuleTypeName = 43, RuleTypeLit = 44, RuleArrayType = 45, RuleArrayLength = 46, 
    RuleElementType = 47, RuleSliceType = 48, RuleAsyncChannelType = 49, 
    RuleSyncChannelType = 50, RuleFunctionType = 51, RuleSignature = 52, 
    RuleResult = 53, RuleParameters = 54, RuleParameterDecl = 55, RuleExpression = 56, 
    RulePrimaryExpr = 57, RuleConversion = 58, RuleOperand = 59, RuleLiteral = 60, 
    RuleBasicLit = 61, RuleInteger = 62, RuleOperandName = 63, RuleQualifiedIdent = 64, 
    RuleCompositeLit = 65, RuleLiteralType = 66, RuleLiteralValue = 67, 
    RuleElementList = 68, RuleKeyedElement = 69, RuleKey = 70, RuleElement = 71, 
    RuleStructType = 72, RuleFieldDecl = 73, RuleString_ = 74, RuleEmbeddedField = 75, 
    RuleFunctionLit = 76, RuleIndex = 77, RuleSlice_ = 78, RuleArguments = 79, 
    RuleEos = 80
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
  class TypeDeclContext;
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
  class SliceTypeContext;
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
  class QualifiedIdentContext;
  class CompositeLitContext;
  class LiteralTypeContext;
  class LiteralValueContext;
  class ElementListContext;
  class KeyedElementContext;
  class KeyContext;
  class ElementContext;
  class StructTypeContext;
  class FieldDeclContext;
  class String_Context;
  class EmbeddedFieldContext;
  class FunctionLitContext;
  class IndexContext;
  class Slice_Context;
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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SourceFileContext* sourceFile();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstDeclContext *constDecl();
    TypeDeclContext *typeDecl();
    VarDeclContext *varDecl();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionListContext* expressionList();

  class  TypeDeclContext : public antlr4::ParserRuleContext {
  public:
    TypeDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    std::vector<TypeSpecContext *> typeSpec();
    TypeSpecContext* typeSpec(size_t i);
    antlr4::tree::TerminalNode *L_PAREN();
    antlr4::tree::TerminalNode *R_PAREN();
    std::vector<EosContext *> eos();
    EosContext* eos(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDeclContext* typeDecl();

  class  TypeSpecContext : public antlr4::ParserRuleContext {
  public:
    TypeSpecContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AliasDeclContext *aliasDecl();
    TypeDefContext *typeDef();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeParametersContext* typeParameters();

  class  TypeParameterDeclContext : public antlr4::ParserRuleContext {
  public:
    TypeParameterDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierListContext *identifierList();
    TypeElementContext *typeElement();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeElementContext* typeElement();

  class  TypeTermContext : public antlr4::ParserRuleContext {
  public:
    TypeTermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_Context *type_();
    antlr4::tree::TerminalNode *UNDERLYING();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleStmtContext* simpleStmt();

  class  ExpressionStmtContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShortVarDeclContext* shortVarDecl();

  class  ReturnStmtContext : public antlr4::ParserRuleContext {
  public:
    ReturnStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    ExpressionListContext *expressionList();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReturnStmtContext* returnStmt();

  class  BreakStmtContext : public antlr4::ParserRuleContext {
  public:
    BreakStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BreakStmtContext* breakStmt();

  class  ContinueStmtContext : public antlr4::ParserRuleContext {
  public:
    ContinueStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *IDENTIFIER();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchCaseContext* matchCase();

  class  FromChanAsContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *chanName = nullptr;
    antlr4::Token *varName = nullptr;
    FromChanAsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *AS();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForStmtContext* forStmt();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeArgsContext* typeArgs();

  class  TypeNameContext : public antlr4::ParserRuleContext {
  public:
    TypeNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedIdentContext *qualifiedIdent();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeNameContext* typeName();

  class  TypeLitContext : public antlr4::ParserRuleContext {
  public:
    TypeLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArrayTypeContext *arrayType();
    StructTypeContext *structType();
    FunctionTypeContext *functionType();
    SliceTypeContext *sliceType();
    SyncChannelTypeContext *syncChannelType();
    AsyncChannelTypeContext *asyncChannelType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeLitContext* typeLit();

  class  ArrayTypeContext : public antlr4::ParserRuleContext {
  public:
    ArrayTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACKET();
    antlr4::tree::TerminalNode *R_BRACKET();
    ElementTypeContext *elementType();
    ArrayLengthContext *arrayLength();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayTypeContext* arrayType();

  class  ArrayLengthContext : public antlr4::ParserRuleContext {
  public:
    ArrayLengthContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArrayLengthContext* arrayLength();

  class  ElementTypeContext : public antlr4::ParserRuleContext {
  public:
    ElementTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_Context *type_();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementTypeContext* elementType();

  class  SliceTypeContext : public antlr4::ParserRuleContext {
  public:
    SliceTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACKET();
    antlr4::tree::TerminalNode *R_BRACKET();
    ElementTypeContext *elementType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SliceTypeContext* sliceType();

  class  AsyncChannelTypeContext : public antlr4::ParserRuleContext {
  public:
    AsyncChannelTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASYNC();
    ElementTypeContext *elementType();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AsyncChannelTypeContext* asyncChannelType();

  class  SyncChannelTypeContext : public antlr4::ParserRuleContext {
  public:
    SyncChannelTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYNC();
    SignatureContext *signature();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SyncChannelTypeContext* syncChannelType();

  class  FunctionTypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNC();
    SignatureContext *signature();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionTypeContext* functionType();

  class  SignatureContext : public antlr4::ParserRuleContext {
  public:
    SignatureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParametersContext *parameters();
    ResultContext *result();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SignatureContext* signature();

  class  ResultContext : public antlr4::ParserRuleContext {
  public:
    ResultContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ParametersContext *parameters();
    Type_Context *type_();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParametersContext* parameters();

  class  ParameterDeclContext : public antlr4::ParserRuleContext {
  public:
    ParameterDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Type_Context *type_();
    IdentifierListContext *identifierList();


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
    antlr4::tree::TerminalNode *EMIT();
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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();
  ExpressionContext* expression(int precedence);
  class  PrimaryExprContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OperandContext *operand();
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);
    std::vector<IndexContext *> index();
    IndexContext* index(size_t i);
    std::vector<Slice_Context *> slice_();
    Slice_Context* slice_(size_t i);
    std::vector<ArgumentsContext *> arguments();
    ArgumentsContext* arguments(size_t i);
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntegerContext* integer();

  class  OperandNameContext : public antlr4::ParserRuleContext {
  public:
    OperandNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    QualifiedIdentContext *qualifiedIdent();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OperandNameContext* operandName();

  class  QualifiedIdentContext : public antlr4::ParserRuleContext {
  public:
    QualifiedIdentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    antlr4::tree::TerminalNode *DOT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QualifiedIdentContext* qualifiedIdent();

  class  CompositeLitContext : public antlr4::ParserRuleContext {
  public:
    CompositeLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralTypeContext *literalType();
    LiteralValueContext *literalValue();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompositeLitContext* compositeLit();

  class  LiteralTypeContext : public antlr4::ParserRuleContext {
  public:
    LiteralTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StructTypeContext *structType();
    ArrayTypeContext *arrayType();
    SliceTypeContext *sliceType();
    TypeNameContext *typeName();
    TypeArgsContext *typeArgs();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyedElementContext* keyedElement();

  class  KeyContext : public antlr4::ParserRuleContext {
  public:
    KeyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    LiteralValueContext *literalValue();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KeyContext* key();

  class  ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    LiteralValueContext *literalValue();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContext* element();

  class  StructTypeContext : public antlr4::ParserRuleContext {
  public:
    StructTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRUCT();
    antlr4::tree::TerminalNode *L_CURLY();
    antlr4::tree::TerminalNode *R_CURLY();
    std::vector<FieldDeclContext *> fieldDecl();
    FieldDeclContext* fieldDecl(size_t i);
    std::vector<EosContext *> eos();
    EosContext* eos(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructTypeContext* structType();

  class  FieldDeclContext : public antlr4::ParserRuleContext {
  public:
    TParser::String_Context *tag = nullptr;
    FieldDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdentifierListContext *identifierList();
    Type_Context *type_();
    EmbeddedFieldContext *embeddedField();
    String_Context *string_();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FieldDeclContext* fieldDecl();

  class  String_Context : public antlr4::ParserRuleContext {
  public:
    String_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RAW_STRING_LIT();
    antlr4::tree::TerminalNode *INTERPRETED_STRING_LIT();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  String_Context* string_();

  class  EmbeddedFieldContext : public antlr4::ParserRuleContext {
  public:
    EmbeddedFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeNameContext *typeName();
    antlr4::tree::TerminalNode *STAR();
    TypeArgsContext *typeArgs();


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmbeddedFieldContext* embeddedField();

  class  FunctionLitContext : public antlr4::ParserRuleContext {
  public:
    FunctionLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUNC();
    SignatureContext *signature();
    BlockContext *block();


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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IndexContext* index();

  class  Slice_Context : public antlr4::ParserRuleContext {
  public:
    Slice_Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *L_BRACKET();
    antlr4::tree::TerminalNode *R_BRACKET();
    std::vector<antlr4::tree::TerminalNode *> COLON();
    antlr4::tree::TerminalNode* COLON(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Slice_Context* slice_();

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


    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentsContext* arguments();

  class  EosContext : public antlr4::ParserRuleContext {
  public:
    EosContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *EOS();
    antlr4::tree::TerminalNode *EOF();


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

