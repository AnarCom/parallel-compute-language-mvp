#pragma once

#include <generated/TParserBaseVisitor.h>

#include <string>
#include <vector>
#include <unordered_map>

// TODO: not cringy type system later
struct Type {
    Type(const std::string& literal);
    Type(TParser::Type_Context* typeCtx);
    const std::string& GetLiteral() const;
    const Type* GetUnderlyingType() const;
    const std::string& GetCppName() const;
private:
    std::string literal;
    std::string cppName;
    std::shared_ptr<Type> underlyingType = nullptr;
};

struct Frame {
    std::string name;
    std::unordered_map<std::string, Type> variablesTypes;
};

class StackFrame {
public:
    const Type* GetType(const std::string& name) const;
    void AddVariable(const std::string& name, const Type& type);
    void NewFrame(const std::string& name);
    void Pop();
    const Frame& Top() const;
private:
    std::vector<Frame> frames_;
};
