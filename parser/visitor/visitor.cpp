#include "visitor.h"
#include "visitor/stackframe.h"

#include <any>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

Visitor::Visitor() : out_(&std::cout), debug_(true) {}

Visitor::~Visitor() {
    if (debug_) {
        auto p = out_.release();
        (void)p;
    }
}

Visitor::Visitor(std::string_view outFilePath) : out_(std::make_unique<std::ofstream>(outFilePath.data())) {
    if (!dynamic_cast<std::ofstream*>(out_.get())->is_open()) {
        throw std::runtime_error("Failed to open file " + std::string(outFilePath));
    }
}

void Visitor::WriteHeaders() {
    GetOut() << "#include <cycle_impl.hpp>" << std::endl << std::endl;

    GetOut() << "#include <iostream>" << std::endl;
    GetOut() << "#include <memory>" << std::endl;
    GetOut() << "#include <tuple>" << std::endl;

    GetOut() << std::endl;

    GetOut() << "using namespace reactor;" << std::endl;

    GetOut() << std::endl;
}

void Visitor::WriteGlobals() {
    GetOut() << "std::shared_ptr<Repository> repository__ = std::make_shared<CycleRepository>();" << std::endl << std::endl;
}

void Visitor::WritePredefinedFunctions() {
    GetOut() << "template <class T>" << std::endl;
    GetOut() << "void print(T var) {" << std::endl;
    GetOut() << "    std::cout << var << std::endl;" << std::endl;
    GetOut() << "}" << std::endl;

    GetOut() << std::endl;
}

void Visitor::WriteFunctions(antlr4::tree::ParseTree* tree) {
    functionsOnly_ = true;
    visit(tree);
    functionsOnly_ = false;

    GetOut() << std::endl;
}

void Visitor::StartEntryFunc() {
    GetOut() << "void EntryFunc__() { " << std::endl;
    stackFrame_.NewFrame("main");
    ++ indent_;
}

void Visitor::EndEntryFunc() {
    --indent_;
    GetOut() << "}" << std::endl << std::endl;
    stackFrame_.Pop();
}

void Visitor::WriteMain() {
    GetOut() << "int main() {" << std::endl;
    ++indent_;
    GetOutWithIndent() << "repository__->Run(std::make_shared<RunnableOrLambda>([](Objects){ EntryFunc__(); }));" << std::endl;
    GetOutWithIndent() << "return 0;" << std::endl;
    --indent_;
    GetOut() << "}" << std::endl;
}

std::ostream& Visitor::GetOutWithIndent() {
    for (std::size_t i = 0; i < indent_; ++i) {
        (*out_) << "    ";
    }
    return *out_;
}

std::ostream& Visitor::GetOut() {
    return *out_;
}

std::any Visitor::visitJoinStmt(TParser::JoinStmtContext *ctx) {
    stackFrame_.NewFrame("join"); // TODO: add source file line
    static std::size_t matchBlockId = 0;

    for (TParser::MatchClauseContext* matchClause : ctx->matchClause()) {
        std::vector<std::string> asVars;
        std::vector<std::string> asVarsChannelNames;
        std::string inputsName = "inputs" + std::to_string(matchBlockId) + "__";
        GetOutWithIndent() << "Channels " << inputsName << "= {";
        for (TParser::FromChanAsContext* fromChanAsContext : matchClause->matchCase()->fromChanAs()) {
            GetOut() << fromChanAsContext->chanName->getText();
            if (fromChanAsContext != matchClause->matchCase()->fromChanAs().back()) {
                GetOut() << ", ";
            }
            if (fromChanAsContext->varName) { 
                asVars.push_back(fromChanAsContext->varName->getText());
                asVarsChannelNames.push_back(fromChanAsContext->chanName->getText());
            }
        }
        GetOut() << "};" << std::endl;
        GetOutWithIndent() << std::endl;
        std::string matchBlockName = "match" + std::to_string(matchBlockId++);
        GetOutWithIndent() << "auto " << matchBlockName << " = std::make_shared<RunnableOrLambda>([=](Objects inp__) {" << std::endl; // TODO: capture and arguments
        ++indent_; 
        std::size_t asIdx = 0;
        for (std::size_t idx = 0; idx < asVars.size(); ++idx) {
            const std::string& asVar = asVars[idx];
            const std::string& asVarChannelName = asVarsChannelNames[idx];
            auto channelType = stackFrame_.GetType(asVarChannelName);
            if (!channelType) {
                throw std::runtime_error("Channel " + asVarChannelName + " not define in scope");
            }
            auto underlyingType = channelType->GetUnderlyingType();
            if (!underlyingType) {
                throw std::runtime_error("Channel " + asVarChannelName + " has no underlying type. Implementation error.");
            }
            const std::string& channeMessageType = underlyingType->GetCppName();
            GetOutWithIndent() << "auto " << asVar << " = inp__[" << asIdx++ << "].Get<" << channeMessageType << ">();" << std::endl;
        }
        visit(matchClause->statementList());
        --indent_;
        GetOutWithIndent() << "});" << std::endl;
        GetOutWithIndent() << "repository__->RegisterJoinCase(std::move(" << inputsName <<"), {}, " << matchBlockName << ");" << std::endl;
        
    }
    stackFrame_.Pop();
    return std::any{};
}

void Visitor::ProcessDefaultVarDecl(TParser::Type_Context* typeCtx, TParser::IdentifierListContext* identifierListCtx) {
    std::string typeName = "unknown_type";
    std::string typeConstructor = "()";
    Type type(typeCtx);
    if (typeCtx->typeName()) {
        // Just type identifier
        // Just wrtie cpp stmt "type var;" but need to find type def and call correct constructor or return error
        typeName = typeCtx->typeName()->IDENTIFIER()->getText();
        typeConstructor = "()";
    }
    else if (auto typeLitCtx = typeCtx->typeLit(); typeLitCtx) {
        // array, function, sync or async channel
        if (auto syncCtx = typeLitCtx->syncChannelType(); syncCtx) {
            typeName = "ChannelPtr";
            typeConstructor = "() //not implemented";
        }
        else if (auto asyncCtx = typeLitCtx->asyncChannelType(); asyncCtx) {
            typeName = "ChannelPtr";
            typeConstructor = " = repository__->NewChannel()";
        }
        else {
            // TODO: Process other types
        }
    }
    else {
        // Process rule type := (type)
        return ProcessDefaultVarDecl(typeCtx->type_(), identifierListCtx);
    }
    for (auto id : identifierListCtx->IDENTIFIER()) {
        GetOutWithIndent() << typeName << " " << id->getText() << typeConstructor << ";" << std::endl;
        stackFrame_.AddVariable(id->getText(), type);
    }
}

std::any Visitor::visitVarDecl(TParser::VarDeclContext *ctx) {
    for (TParser::VarSpecContext* varSpec : ctx->varSpec()) {
       if (!varSpec->expressionList()) {
            // Creating type with default value
            ProcessDefaultVarDecl(varSpec->type_(), varSpec->identifierList());
       }
       else {
            // Deduce type from expr
            if (varSpec->type_()) {
                // check type if need
            }
       }
    }
    return visitChildren(ctx);
}

std::string Visitor::GetCppType(TParser::Type_Context* typeCtx) {
    if (typeCtx->typeName()) {
        return typeCtx->typeName()->getText();
    }
    if (auto typeLitCtx = typeCtx->typeLit(); typeLitCtx) {
        // array, function, sync or async channel
        if (auto syncCtx = typeLitCtx->syncChannelType(); syncCtx) {
            return "ChannelPtr";
        }
        else if (auto asyncCtx = typeLitCtx->asyncChannelType(); asyncCtx) {
            return "ChannelPtr";
        }
        else {
            // TODO: Process other types
            return "unknown_type";
        }
    }
    // Process rule type := (type)
    return GetCppType(typeCtx->type_());
}

std::any Visitor::visitFunctionDecl(TParser::FunctionDeclContext *ctx) {
    if (!functionsOnly_) {
        return std::any{};
    }
    if (ctx->typeParameters()) {
        throw std::runtime_error("Type parameters are not supported yet");
    }
    insideFunction_ = true;
    {
        // Writing result type
        auto resTypeCtx = ctx->signature()->result();
        if (resTypeCtx->type_()) {
            GetOutWithIndent() << GetCppType(resTypeCtx->type_()) << " ";
        }
        else {
            GetOutWithIndent() << "std::tuple<";
            auto params = resTypeCtx->parameters()->parameterDecl();
            for (auto param = params.begin(); param != params.end(); ++param) {
                std::size_t numOfParamsWithType = (*param)->identifierList() ? (*param)->identifierList()->IDENTIFIER().size() : 1ul;
                for (std::size_t i = 0; i < numOfParamsWithType; ++i) {
                    // in Go we can give names for result vars and have multiple vars with one type
                    GetOut() << GetCppType((*param)->type_());
                    if (param + 1 != params.end()) {
                        GetOut() << ", ";
                    }
                }
            }
            GetOut() << ">";
        }
        GetOut() << " ";
    }

    // Writing function name
    GetOut() << ctx->IDENTIFIER()->getText();

    stackFrame_.NewFrame(ctx->IDENTIFIER()->getText());

    {
        // Writing parameters
        GetOut() << "(";
        auto params = ctx->signature()->parameters()->parameterDecl();
        for (auto param = params.begin(); param != params.end(); ++param) {
            for (auto name : (*param)->identifierList()->IDENTIFIER()) {
                stackFrame_.AddVariable(name->getText(), (*param)->type_()->getText());
                GetOut() << GetCppType((*param)->type_()) << " ";
                GetOut() << name->getText();
                if (param + 1 != params.end()) {
                    GetOut() << ", ";
                }
            }
        }
        GetOut() << ") ";
    }

    if (!ctx->block()) {
        GetOut() << ";" << std::endl;
        insideFunction_ = false;
        return std::any();
    }
    GetOut() << "{" << std::endl;
    ++indent_;
    auto res =  visitChildren(ctx->block());
    stackFrame_.Pop();
    --indent_;
    GetOutWithIndent() << "}" << std::endl << std::endl;
    insideFunction_ = false;
    return res;
}

std::any Visitor::visitDeclaration(TParser::DeclarationContext *ctx) {
    if (functionsOnly_ && !insideFunction_) {
        return std::any{};
    }
    return visitChildren(ctx);
}
std::any Visitor::visitStatement(TParser::StatementContext *ctx) {
    if (functionsOnly_ && !insideFunction_) {
        return std::any{};
    }
    return visitChildren(ctx);
}

std::any Visitor::visitExpressionStmt(TParser::ExpressionStmtContext *ctx) {
    GetOutWithIndent() << ctx->getText() << ";" << std::endl;
    return std::any{};
}

std::any Visitor::visitEmitStmt(TParser::EmitStmtContext *ctx) {
    static std::size_t helpingIndex = 0;
    GetOutWithIndent() << "auto emitExprRightRes" << helpingIndex << " = " << ctx->expression(1)->getText() << ";" << std::endl;
    std::string channelName = ctx->expression(0)->getText(); // only variable name for the first time without expr computation
    GetOutWithIndent() << channelName << "->Push(emitExprRightRes" << (helpingIndex++) << ");"  << std::endl;
    return std::any{};
}

std::any Visitor::visitSyncReturnStmt(TParser::SyncReturnStmtContext *ctx) {
    static std::size_t helpingIndex = 0;
    GetOutWithIndent() << "auto syncReturnExprRightRes" << helpingIndex << " = " << ctx->expression(1)->getText() << ";" << std::endl;
    std::string channelName = ctx->expression(0)->getText(); // only variable name for the first time without expr computation
    GetOutWithIndent() << channelName << ".return(syncReturnExprRightRes" << (helpingIndex++) << ");"  << std::endl;
    return std::any{};
}

std::any Visitor::visitReturnStmt(TParser::ReturnStmtContext *ctx) {
    if (!ctx->expressionList()) {
        GetOutWithIndent() << "return;" << std::endl;
        return std::any{};
    }

    const auto& exprs = ctx->expressionList()->expression();
    if (exprs.size() == 1) {
        GetOutWithIndent() << "return " << ctx->expressionList()->expression(0)->getText() << ";" << std::endl;
        return std::any{};
    }

    GetOutWithIndent() << "return std::tuple(";
    for (auto exprIt = exprs.begin(); exprIt + 1 != exprs.end(); ++exprIt) {
        GetOut() << (*exprIt)->getText() << ", ";
    }
    GetOut() << exprs.back()->getText() << ");" << std::endl;
    return std::any{};
}

std::any Visitor::visitShortVarDecl(TParser::ShortVarDeclContext *ctx) {
    static std::size_t helpingIndex = 0;
    const auto& ids = ctx->identifierList()->IDENTIFIER();
    const auto& exprs = ctx->expressionList()->expression();
    if (exprs.size() > ids.size()) {
        throw std::runtime_error("Assigning error");
    }
    if (exprs.size() > 1) {
        throw std::runtime_error("Multiple expressions assignment not implemented");
    }
    if (ids.size() == 1) {
        GetOutWithIndent() << "auto " << ids[0]->getText() << " = " << exprs[0]->getText() << ";" << std::endl;
        return std::any{};
    }
    std::string tupleName = "tuple" + std::to_string(helpingIndex++);
    GetOutWithIndent() << "std::tuple " << tupleName << " = " << exprs[0]->getText() << ";" << std::endl;
    std::size_t idNum = 0;
    for (auto id : ids) {
        GetOutWithIndent() << "auto " << id->getText() << " = " << "std::move(std::get<" << (idNum++) << ">(" << tupleName <<"));" << std::endl;
    }
    return std::any{};
}
