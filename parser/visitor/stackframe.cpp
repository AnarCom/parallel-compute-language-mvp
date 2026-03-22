#include "stackframe.h"

#include <sstream>

Type::Type(const std::string& literal) : literal(literal) {
    if (literal.rfind("async") != 0) {
        cppName = literal;
        return;
    }
    std::istringstream in(literal);
    std::string async, underlyingTypeLiteral;
    in >> async >> underlyingTypeLiteral;
    underlyingType = std::make_shared<Type>(underlyingTypeLiteral);
    cppName = "ChannelPtr";
}

Type::Type(TParser::Type_Context* typeCtx) : Type(typeCtx->getText()) {
    if (typeCtx->typeName()) {
        // Just type identifier
        cppName = typeCtx->typeName()->IDENTIFIER()->getText();
    }
    else if (auto typeLitCtx = typeCtx->typeLit(); typeLitCtx) {
        // array, function, sync or async channel
        if (auto syncCtx = typeLitCtx->syncChannelType(); syncCtx) {
            cppName = "ChannelPtr";
            //underlyingType = std::make_shared<Type>(syncCtx->elementType()->type_());
        }
        else if (auto asyncCtx = typeLitCtx->asyncChannelType(); asyncCtx) {
            cppName = "ChannelPtr";
            underlyingType = std::make_shared<Type>(asyncCtx->elementType()->type_());
        }
        else {
            // TODO: Process other types
            throw std::runtime_error("Unknown type");
        }
    }
    else {
        // TODO: Process other types
        throw std::runtime_error("Unknown type");
    }
}

const std::string& Type::GetLiteral() const {
    return literal;
}

const Type* Type::GetUnderlyingType() const {
    return underlyingType.get();
}

const std::string& Type::GetCppName() const {
    return cppName;
}

const Type* StackFrame::GetType(const std::string& name) const {
    for (auto it = frames_.rbegin(); it != frames_.rend(); ++it) {
        auto it2 = it->variablesTypes.find(name);
        if (it2 != it->variablesTypes.end()) {
            return &it2->second;
        }
    }

    return nullptr;
}

void StackFrame::AddVariable(const std::string& name, const Type& type) {
    frames_.back().variablesTypes.insert({name, type});
}

void StackFrame::NewFrame(const std::string& name) {
    frames_.push_back({name, {}});
}

void StackFrame::Pop() {
    frames_.pop_back();
}

const Frame& StackFrame::Top() const {
    return frames_.back();
}
