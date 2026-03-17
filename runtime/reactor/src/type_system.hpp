#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

namespace reactor {

template <typename T>
using Pointer = std::shared_ptr<T>;

template <typename T>
using Maybe = std::optional<T>;

class Object;
class ObjectValue;

using Objects = std::vector<Object>;

enum class ChannelMode {
    Sync,
    Async,
};

enum class TypeKind {
    Unit,
    Int,
    Bool,
    String,
    Tuple,
    List,
    Channel,
    Algebraic,
    Variable,
};

enum class ObjectKind {
    Unit,
    Int,
    Bool,
    String,
    Tuple,
    List,
    Algebraic,
    Channel,
};

namespace detail {
class TypeNode;
class PrimitiveTypeNode;
class VariableTypeNode;
class TupleTypeNode;
class ListTypeNode;
class ChannelTypeNode;
class AlgebraicTypeNode;
}  // namespace detail

class Type {
public:
    Type();
    explicit Type(Pointer<const detail::TypeNode> node);

    static Type Unit();
    static Type Int();
    static Type Bool();
    static Type String();
    static Type Variable(std::string name);
    static Type Tuple(std::vector<Type> elements);
    static Type List(Type element_type);
    static Type Channel(ChannelMode mode, Type payload_type);
    static Type SyncChannel(Type payload_type);
    static Type AsyncChannel(Type payload_type);
    static Type Algebraic(std::string name, std::vector<Type> parameters = {});

    [[nodiscard]] TypeKind kind() const noexcept;
    [[nodiscard]] bool IsConcrete() const noexcept;
    [[nodiscard]] std::string ToString() const;

    [[nodiscard]] const std::vector<Type>& TupleElements() const;
    [[nodiscard]] const Type& ListElementType() const;
    [[nodiscard]] ChannelMode GetChannelMode() const;
    [[nodiscard]] const Type& ChannelPayloadType() const;
    [[nodiscard]] const std::string& Name() const;
    [[nodiscard]] const std::vector<Type>& Parameters() const;

    [[nodiscard]] bool Accepts(const Object& object) const noexcept;
    [[nodiscard]] const Pointer<const detail::TypeNode>& Raw() const noexcept;

    friend bool operator==(const Type& lhs, const Type& rhs) noexcept;
    friend bool operator!=(const Type& lhs, const Type& rhs) noexcept;

private:
    Pointer<const detail::TypeNode> node_;
};

namespace detail {

class TypeNode {
public:
    virtual ~TypeNode() noexcept;
    virtual TypeKind kind() const noexcept = 0;
    virtual bool Equals(const TypeNode& other) const noexcept = 0;
    virtual std::string ToString() const = 0;
    virtual bool IsConcrete() const noexcept = 0;
};

class PrimitiveTypeNode final : public TypeNode {
public:
    explicit PrimitiveTypeNode(TypeKind kind) noexcept;

    TypeKind kind() const noexcept override;
    bool Equals(const TypeNode& other) const noexcept override;
    std::string ToString() const override;
    bool IsConcrete() const noexcept override;

private:
    TypeKind kind_;
};

class VariableTypeNode final : public TypeNode {
public:
    explicit VariableTypeNode(std::string name) noexcept;

    TypeKind kind() const noexcept override;
    bool Equals(const TypeNode& other) const noexcept override;
    std::string ToString() const override;
    bool IsConcrete() const noexcept override;

    const std::string& name() const noexcept;

private:
    std::string name_;
};

class TupleTypeNode final : public TypeNode {
public:
    explicit TupleTypeNode(std::vector<Type> elements) noexcept;

    TypeKind kind() const noexcept override;
    bool Equals(const TypeNode& other) const noexcept override;
    std::string ToString() const override;
    bool IsConcrete() const noexcept override;

    const std::vector<Type>& elements() const noexcept;

private:
    std::vector<Type> elements_;
};

class ListTypeNode final : public TypeNode {
public:
    explicit ListTypeNode(Type element_type) noexcept;

    TypeKind kind() const noexcept override;
    bool Equals(const TypeNode& other) const noexcept override;
    std::string ToString() const override;
    bool IsConcrete() const noexcept override;

    const Type& element_type() const noexcept;

private:
    Type element_type_;
};

class ChannelTypeNode final : public TypeNode {
public:
    ChannelTypeNode(ChannelMode mode, Type payload_type) noexcept;

    TypeKind kind() const noexcept override;
    bool Equals(const TypeNode& other) const noexcept override;
    std::string ToString() const override;
    bool IsConcrete() const noexcept override;

    ChannelMode mode() const noexcept;
    const Type& payload_type() const noexcept;

private:
    ChannelMode mode_;
    Type payload_type_;
};

class AlgebraicTypeNode final : public TypeNode {
public:
    AlgebraicTypeNode(std::string name, std::vector<Type> parameters) noexcept;

    TypeKind kind() const noexcept override;
    bool Equals(const TypeNode& other) const noexcept override;
    std::string ToString() const override;
    bool IsConcrete() const noexcept override;

    const std::string& name() const noexcept;
    const std::vector<Type>& parameters() const noexcept;

private:
    std::string name_;
    std::vector<Type> parameters_;
};

}  // namespace detail

class ObjectValue {
public:
    virtual ~ObjectValue() noexcept;
    virtual ObjectKind kind() const noexcept = 0;
    virtual Type GetType() const = 0;
    virtual std::string ToString() const = 0;
};

class UnitObject final : public ObjectValue {
public:
    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;
};

class IntObject final : public ObjectValue {
public:
    explicit IntObject(std::int64_t value) noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;

    std::int64_t value() const noexcept;

private:
    std::int64_t value_;
};

class BoolObject final : public ObjectValue {
public:
    explicit BoolObject(bool value) noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;

    bool value() const noexcept;

private:
    bool value_;
};

class StringObject final : public ObjectValue {
public:
    explicit StringObject(std::string value) noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;

    const std::string& value() const noexcept;

private:
    std::string value_;
};

class TupleObject final : public ObjectValue {
public:
    explicit TupleObject(Objects elements) noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;

    const Objects& elements() const noexcept;

private:
    Objects elements_;
};

class ListObject final : public ObjectValue {
public:
    ListObject(Objects elements, Maybe<Type> declared_element_type = {}) noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;

    const Objects& elements() const noexcept;
    const Type& element_type() const noexcept;

private:
    static Type InferElementType(const Objects& elements, const Maybe<Type>& declared_element_type);

    Objects elements_;
    Type element_type_;
};

class AlgebraicObject final : public ObjectValue {
public:
    AlgebraicObject(Type algebraic_type, std::string constructor_name, Objects fields) noexcept;

    ObjectKind kind() const noexcept override;
    Type GetType() const override;
    std::string ToString() const override;

    const Type& algebraic_type() const noexcept;
    const std::string& constructor_name() const noexcept;
    const Objects& fields() const noexcept;

private:
    Type algebraic_type_;
    std::string constructor_name_;
    Objects fields_;
};

class Object {
public:
    Object();
    explicit Object(Pointer<ObjectValue> value);

    static Object Unit();
    static Object Int(std::int64_t value);
    static Object Bool(bool value);
    static Object String(std::string value);
    static Object Tuple(Objects elements);
    static Object List(Objects elements, Maybe<Type> declared_element_type = {});
    static Object Algebraic(Type algebraic_type, std::string constructor_name, Objects fields = {});

    [[nodiscard]] ObjectKind kind() const noexcept;
    [[nodiscard]] Type GetType() const;
    [[nodiscard]] std::string ToString() const;
    [[nodiscard]] bool IsNull() const noexcept;

    template <typename TObject>
    [[nodiscard]] bool Is() const noexcept {
        return std::dynamic_pointer_cast<TObject>(value_) != nullptr;
    }

    template <typename TObject>
    [[nodiscard]] Pointer<TObject> As() const noexcept {
        return std::dynamic_pointer_cast<TObject>(value_);
    }

    [[nodiscard]] const Pointer<ObjectValue>& Raw() const noexcept;

private:
    Pointer<ObjectValue> value_;
};

bool IsInstanceOf(const Object& object, const Type& type) noexcept;

[[nodiscard]] std::string ToString(ChannelMode mode);
[[nodiscard]] std::string ToString(TypeKind kind);
[[nodiscard]] std::string ToString(ObjectKind kind);

template <typename T>
struct StaticType;

template <>
struct StaticType<std::int64_t> {
    static Type Get() { return Type::Int(); }
};

template <>
struct StaticType<int> {
    static Type Get() { return Type::Int(); }
};

template <>
struct StaticType<bool> {
    static Type Get() { return Type::Bool(); }
};

template <>
struct StaticType<std::string> {
    static Type Get() { return Type::String(); }
};

template <>
struct StaticType<std::string_view> {
    static Type Get() { return Type::String(); }
};

template <>
struct StaticType<std::monostate> {
    static Type Get() { return Type::Unit(); }
};

template <typename T>
struct StaticType<std::vector<T>> {
    static Type Get() { return Type::List(StaticType<T>::Get()); }
};

template <typename... Ts>
struct StaticType<std::tuple<Ts...>> {
    static Type Get() { return Type::Tuple({StaticType<Ts>::Get()...}); }
};

template <typename T>
Type StaticTypeOf() {
    return StaticType<T>::Get();
}

}  // namespace reactor
