#pragma once

#include "../antlr4-runtime.h"
#include "generated/TParser.h"
#include "generated/TParserVisitor.h"

#include "stackframe.h"

#include <generated/TParserBaseVisitor.h>

#include <memory>

class Visitor : public TParserBaseVisitor {
public:
    Visitor();
    Visitor(std::string_view outFilePath);
    ~Visitor();

    void WriteHeaders();
    void WriteGlobals();
    void WritePredefinedFunctions();
    void WriteFunctions(antlr4::tree::ParseTree* tree);
    void StartEntryFunc();
    void WriteMain();
    void EndEntryFunc();

    virtual std::any visitJoinStmt(TParser::JoinStmtContext *ctx) override;
    virtual std::any visitVarDecl(TParser::VarDeclContext *ctx) override;
    virtual std::any visitFunctionDecl(TParser::FunctionDeclContext *ctx) override;
    virtual std::any visitDeclaration(TParser::DeclarationContext *ctx) override;
    virtual std::any visitStatement(TParser::StatementContext *ctx) override;
    virtual std::any visitExpressionStmt(TParser::ExpressionStmtContext *ctx) override;
    virtual std::any visitEmitStmt(TParser::EmitStmtContext *ctx) override;
    virtual std::any visitSyncReturnStmt(TParser::SyncReturnStmtContext *ctx) override;
    virtual std::any visitReturnStmt(TParser::ReturnStmtContext *ctx) override;
    virtual std::any visitShortVarDecl(TParser::ShortVarDeclContext *ctx) override;

private:
    std::ostream& GetOutWithIndent();
    std::ostream& GetOut();
    void ProcessDefaultVarDecl(TParser::Type_Context* typeCtx, TParser::IdentifierListContext* identifierListCtx);
    std::string GetCppType(TParser::Type_Context* typeCtx);

private:
    std::size_t indent_ = 0;
    std::unique_ptr<std::ostream> out_;
    bool debug_ = false;
    bool functionsOnly_ = false;
    bool insideFunction_ = false;
    StackFrame stackFrame_;
};
