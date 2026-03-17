#include "type_system.hpp"

#include <sstream>
#include <stdexcept>

namespace reactor {
namespace {

template <typename TNode>
const TNode& RequireNode(const Type& type) {
    auto node = std::dynamic_pointer_cast<const TNode>(type.Raw());
    if (!node) {
        throw std::logic_error("type access does not match actual type kind");
    }
    return *node;
}

std::string JoinStrings(const std::vector<std::string>& parts, const std::string_view separator) {
    std::ostringstream out;
    for (size_t i = 0; i < parts.size(); ++i) {
        if (i != 0) {
            out << separator;
        }
        out << parts[i];
    }
    return out.str();
}

}

namespace detail {

TypeNode::~TypeNode() noexcept = default;

PrimitiveTypeNode::PrimitiveTypeNode(TypeKind kind) noexcept : kind_(kind) {}

TypeKind PrimitiveTypeNode::kind() const noexcept {
    return kind_;
}

bool PrimitiveTypeNode::Equals(const TypeNode& other) const noexcept {
    return other.kind() == kind_;
}

std::string PrimitiveTypeNode::ToString() const {
    return reactor::ToString(kind_);
}

bool PrimitiveTypeNode::IsConcrete() const noexcept {
    return true;
}

VariableTypeNode::VariableTypeNode(std::string name) noexcept : name_(std::move(name)) {}

TypeKind VariableTypeNode::kind() const noexcept {
    return TypeKind::Variable;
}

bool VariableTypeNode::Equals(const TypeNode& other) const noexcept {
    auto* rhs = dynamic_cast<const VariableTypeNode*>(&other);
    return rhs != nullptr && rhs->name_ == name_;
}

std::string VariableTypeNode::ToString() const {
    return name_;
}

bool VariableTypeNode::IsConcrete() const noexcept {
    return false;
}

const std::string& VariableTypeNode::name() const noexcept {
    return name_;
}

TupleTypeNode::TupleTypeNode(std::vector<Type> elements) noexcept : elements_(std::move(elements)) {}

TypeKind TupleTypeNode::kind() const noexcept {
    return TypeKind::Tuple;
}

bool TupleTypeNode::Equals(const TypeNode& other) const noexcept {
    auto* rhs = dynamic_cast<const TupleTypeNode*>(&other);
    return rhs != nullptr && rhs->elements_ == elements_;
}

std::string TupleTypeNode::ToString() const {
    std::vector<std::string> parts;
    parts.reserve(elements_.size());
    for (const auto& element : elements_) {
        parts.push_back(element.ToString());
    }
    return "(" + JoinStrings(parts, ", ") + ")";
}

bool TupleTypeNode::IsConcrete() const noexcept {
    for (const auto& element : elements_) {
        if (!element.IsConcrete()) {
            return false;
        }
    }
    return true;
}

const std::vector<Type>& TupleTypeNode::elements() const noexcept {
    return elements_;
}

ListTypeNode::ListTypeNode(Type element_type) noexcept : element_type_(std::move(element_type)) {}

TypeKind ListTypeNode::kind() const noexcept {
    return TypeKind::List;
}

bool ListTypeNode::Equals(const TypeNode& other) const noexcept {
    auto* rhs = dynamic_cast<const ListTypeNode*>(&other);
    return rhs != nullptr && rhs->element_type_ == element_type_;
}

std::string ListTypeNode::ToString() const {
    return "[" + element_type_.ToString() + "]";
}

bool ListTypeNode::IsConcrete() const noexcept {
    return element_type_.IsConcrete();
}

const Type& ListTypeNode::element_type() const noexcept {
    return element_type_;
}

ChannelTypeNode::ChannelTypeNode(ChannelMode mode, Type payload_type) noexcept
    : mode_(mode), payload_type_(std::move(payload_type)) {}

TypeKind ChannelTypeNode::kind() const noexcept {
    return TypeKind::Channel;
}

bool ChannelTypeNode::Equals(const TypeNode& other) const noexcept {
    auto* rhs = dynamic_cast<const ChannelTypeNode*>(&other);
    return rhs != nullptr && rhs->mode_ == mode_ && rhs->payload_type_ == payload_type_;
}

std::string ChannelTypeNode::ToString() const {
    return reactor::ToString(mode_) + " " + payload_type_.ToString();
}

bool ChannelTypeNode::IsConcrete() const noexcept {
    return payload_type_.IsConcrete();
}

ChannelMode ChannelTypeNode::mode() const noexcept {
    return mode_;
}

const Type& ChannelTypeNode::payload_type() const noexcept {
    return payload_type_;
}

AlgebraicTypeNode::AlgebraicTypeNode(std::string name, std::vector<Type> parameters) noexcept
    : name_(std::move(name)), parameters_(std::move(parameters)) {}

TypeKind AlgebraicTypeNode::kind() const noexcept {
    return TypeKind::Algebraic;
}

bool AlgebraicTypeNode::Equals(const TypeNode& other) const noexcept {
    auto* rhs = dynamic_cast<const AlgebraicTypeNode*>(&other);
    return rhs != nullptr && rhs->name_ == name_ && rhs->parameters_ == parameters_;
}

std::string AlgebraicTypeNode::ToString() const {
    if (parameters_.empty()) {
        return name_;
    }
    std::vector<std::string> parts;
    parts.reserve(parameters_.size());
    for (const auto& parameter : parameters_) {
        parts.push_back(parameter.ToString());
    }
    return name_ + "<" + JoinStrings(parts, ", ") + ">";
}

bool AlgebraicTypeNode::IsConcrete() const noexcept {
    for (const auto& parameter : parameters_) {
        if (!parameter.IsConcrete()) {
            return false;
        }
    }
    return true;
}

const std::string& AlgebraicTypeNode::name() const noexcept {
    return name_;
}

const std::vector<Type>& AlgebraicTypeNode::parameters() const noexcept {
    return parameters_;
}

}

Type::Type() : node_(std::make_shared<detail::PrimitiveTypeNode>(TypeKind::Unit)) {}

Type::Type(Pointer<const detail::TypeNode> node) : node_(std::move(node)) {
    if (!node_) {
        throw std::invalid_argument("Type node cannot be null");
    }
}

Type Type::Unit() {
    return Type(std::make_shared<detail::PrimitiveTypeNode>(TypeKind::Unit));
}

Type Type::Int() {
    return Type(std::make_shared<detail::PrimitiveTypeNode>(TypeKind::Int));
}

Type Type::Bool() {
    return Type(std::make_shared<detail::PrimitiveTypeNode>(TypeKind::Bool));
}

Type Type::String() {
    return Type(std::make_shared<detail::PrimitiveTypeNode>(TypeKind::String));
}

Type Type::Variable(std::string name) {
    return Type(std::make_shared<detail::VariableTypeNode>(std::move(name)));
}

Type Type::Tuple(std::vector<Type> elements) {
    return Type(std::make_shared<detail::TupleTypeNode>(std::move(elements)));
}

Type Type::List(Type element_type) {
    return Type(std::make_shared<detail::ListTypeNode>(std::move(element_type)));
}

Type Type::Channel(ChannelMode mode, Type payload_type) {
    return Type(std::make_shared<detail::ChannelTypeNode>(mode, std::move(payload_type)));
}

Type Type::SyncChannel(Type payload_type) {
    return Channel(ChannelMode::Sync, std::move(payload_type));
}

Type Type::AsyncChannel(Type payload_type) {
    return Channel(ChannelMode::Async, std::move(payload_type));
}

Type Type::Algebraic(std::string name, std::vector<Type> parameters) {
    return Type(std::make_shared<detail::AlgebraicTypeNode>(std::move(name), std::move(parameters)));
}

TypeKind Type::kind() const noexcept {
    return node_->kind();
}

bool Type::IsConcrete() const noexcept {
    return node_->IsConcrete();
}

std::string Type::ToString() const {
    return node_->ToString();
}

const std::vector<Type>& Type::TupleElements() const {
    return RequireNode<detail::TupleTypeNode>(*this).elements();
}

const Type& Type::ListElementType() const {
    return RequireNode<detail::ListTypeNode>(*this).element_type();
}

ChannelMode Type::GetChannelMode() const {
    return RequireNode<detail::ChannelTypeNode>(*this).mode();
}

const Type& Type::ChannelPayloadType() const {
    return RequireNode<detail::ChannelTypeNode>(*this).payload_type();
}

const std::string& Type::Name() const {
    if (kind() == TypeKind::Variable) {
        return RequireNode<detail::VariableTypeNode>(*this).name();
    }
    return RequireNode<detail::AlgebraicTypeNode>(*this).name();
}

const std::vector<Type>& Type::Parameters() const {
    return RequireNode<detail::AlgebraicTypeNode>(*this).parameters();
}

bool Type::Accepts(const Object& object) const noexcept {
    return IsInstanceOf(object, *this);
}

const Pointer<const detail::TypeNode>& Type::Raw() const noexcept {
    return node_;
}

bool operator==(const Type& lhs, const Type& rhs) noexcept {
    if (lhs.node_ == rhs.node_) {
        return true;
    }
    if (!lhs.node_ || !rhs.node_) {
        return false;
    }
    return lhs.node_->Equals(*rhs.node_);
}

bool operator!=(const Type& lhs, const Type& rhs) noexcept {
    return !(lhs == rhs);
}

ObjectValue::~ObjectValue() noexcept = default;

ObjectKind UnitObject::kind() const noexcept {
    return ObjectKind::Unit;
}

Type UnitObject::GetType() const {
    return Type::Unit();
}

std::string UnitObject::ToString() const {
    return "nil";
}

IntObject::IntObject(std::int64_t value) noexcept : value_(value) {}

ObjectKind IntObject::kind() const noexcept {
    return ObjectKind::Int;
}

Type IntObject::GetType() const {
    return Type::Int();
}

std::string IntObject::ToString() const {
    return std::to_string(value_);
}

std::int64_t IntObject::value() const noexcept {
    return value_;
}

BoolObject::BoolObject(bool value) noexcept : value_(value) {}

ObjectKind BoolObject::kind() const noexcept {
    return ObjectKind::Bool;
}

Type BoolObject::GetType() const {
    return Type::Bool();
}

std::string BoolObject::ToString() const {
    return value_ ? "true" : "false";
}

bool BoolObject::value() const noexcept {
    return value_;
}

StringObject::StringObject(std::string value) noexcept : value_(std::move(value)) {}

ObjectKind StringObject::kind() const noexcept {
    return ObjectKind::String;
}

Type StringObject::GetType() const {
    return Type::String();
}

std::string StringObject::ToString() const {
    return '"' + value_ + '"';
}

const std::string& StringObject::value() const noexcept {
    return value_;
}

TupleObject::TupleObject(Objects elements) noexcept : elements_(std::move(elements)) {}

ObjectKind TupleObject::kind() const noexcept {
    return ObjectKind::Tuple;
}

Type TupleObject::GetType() const {
    std::vector<Type> element_types;
    element_types.reserve(elements_.size());
    for (const auto& element : elements_) {
        element_types.push_back(element.GetType());
    }
    return Type::Tuple(std::move(element_types));
}

std::string TupleObject::ToString() const {
    std::vector<std::string> parts;
    parts.reserve(elements_.size());
    for (const auto& element : elements_) {
        parts.push_back(element.ToString());
    }
    return "(" + JoinStrings(parts, ", ") + ")";
}

const Objects& TupleObject::elements() const noexcept {
    return elements_;
}

ListObject::ListObject(Objects elements, Maybe<Type> declared_element_type) noexcept
    : elements_(std::move(elements)), element_type_(InferElementType(elements_, declared_element_type)) {}

ObjectKind ListObject::kind() const noexcept {
    return ObjectKind::List;
}

Type ListObject::GetType() const {
    return Type::List(element_type_);
}

std::string ListObject::ToString() const {
    std::vector<std::string> parts;
    parts.reserve(elements_.size());
    for (const auto& element : elements_) {
        parts.push_back(element.ToString());
    }
    return "[" + JoinStrings(parts, ", ") + "]";
}

const Objects& ListObject::elements() const noexcept {
    return elements_;
}

const Type& ListObject::element_type() const noexcept {
    return element_type_;
}

Type ListObject::InferElementType(const Objects& elements, const Maybe<Type>& declared_element_type) {
    if (declared_element_type.has_value()) {
        for (const auto& element : elements) {
            if (!declared_element_type->Accepts(element)) {
                throw std::invalid_argument("list element does not match declared list type");
            }
        }
        return declared_element_type.value();
    }
    if (elements.empty()) {
        return Type::Variable("'a");
    }
    Type inferred = elements.front().GetType();
    for (const auto& element : elements) {
        if (!inferred.Accepts(element)) {
            throw std::invalid_argument("list elements must be homogeneous");
        }
    }
    return inferred;
}

AlgebraicObject::AlgebraicObject(Type algebraic_type, std::string constructor_name, Objects fields) noexcept
    : algebraic_type_(std::move(algebraic_type)), constructor_name_(std::move(constructor_name)), fields_(std::move(fields)) {}

ObjectKind AlgebraicObject::kind() const noexcept {
    return ObjectKind::Algebraic;
}

Type AlgebraicObject::GetType() const {
    return algebraic_type_;
}

std::string AlgebraicObject::ToString() const {
    if (fields_.empty()) {
        return constructor_name_;
    }
    std::vector<std::string> parts;
    parts.reserve(fields_.size());
    for (const auto& field : fields_) {
        parts.push_back(field.ToString());
    }
    return constructor_name_ + "(" + JoinStrings(parts, ", ") + ")";
}

const Type& AlgebraicObject::algebraic_type() const noexcept {
    return algebraic_type_;
}

const std::string& AlgebraicObject::constructor_name() const noexcept {
    return constructor_name_;
}

const Objects& AlgebraicObject::fields() const noexcept {
    return fields_;
}

Object::Object() : value_(std::make_shared<UnitObject>()) {}

Object::Object(Pointer<ObjectValue> value) : value_(std::move(value)) {
    if (!value_) {
        throw std::invalid_argument("Object value cannot be null");
    }
}

Object Object::Unit() {
    return Object(std::make_shared<UnitObject>());
}

Object Object::Int(std::int64_t value) {
    return Object(std::make_shared<IntObject>(value));
}

Object Object::Bool(bool value) {
    return Object(std::make_shared<BoolObject>(value));
}

Object Object::String(std::string value) {
    return Object(std::make_shared<StringObject>(std::move(value)));
}

Object Object::Tuple(Objects elements) {
    return Object(std::make_shared<TupleObject>(std::move(elements)));
}

Object Object::List(Objects elements, Maybe<Type> declared_element_type) {
    return Object(std::make_shared<ListObject>(std::move(elements), std::move(declared_element_type)));
}

Object Object::Algebraic(Type algebraic_type, std::string constructor_name, Objects fields) {
    return Object(std::make_shared<AlgebraicObject>(std::move(algebraic_type), std::move(constructor_name), std::move(fields)));
}

ObjectKind Object::kind() const noexcept {
    return value_->kind();
}

Type Object::GetType() const {
    return value_->GetType();
}

std::string Object::ToString() const {
    return value_->ToString();
}

bool Object::IsNull() const noexcept {
    return value_ == nullptr;
}

const Pointer<ObjectValue>& Object::Raw() const noexcept {
    return value_;
}

bool IsInstanceOf(const Object& object, const Type& type) noexcept {
    switch (type.kind()) {
        case TypeKind::Unit:
            return object.kind() == ObjectKind::Unit;
        case TypeKind::Int:
            return object.kind() == ObjectKind::Int;
        case TypeKind::Bool:
            return object.kind() == ObjectKind::Bool;
        case TypeKind::String:
            return object.kind() == ObjectKind::String;
        case TypeKind::Variable:
            return true;
        case TypeKind::Tuple: {
            auto tuple_object = object.As<TupleObject>();
            if (!tuple_object) {
                return false;
            }
            const auto& elements = tuple_object->elements();
            const auto& element_types = type.TupleElements();
            if (elements.size() != element_types.size()) {
                return false;
            }
            for (size_t i = 0; i < elements.size(); ++i) {
                if (!element_types[i].Accepts(elements[i])) {
                    return false;
                }
            }
            return true;
        }
        case TypeKind::List: {
            auto list_object = object.As<ListObject>();
            if (!list_object) {
                return false;
            }
            const auto& element_type = type.ListElementType();
            for (const auto& element : list_object->elements()) {
                if (!element_type.Accepts(element)) {
                    return false;
                }
            }
            return true;
        }
        case TypeKind::Channel:
            return object.kind() == ObjectKind::Channel && object.GetType() == type;
        case TypeKind::Algebraic:
            return object.kind() == ObjectKind::Algebraic && object.GetType() == type;
    }
    return false;
}

std::string ToString(ChannelMode mode) {
    switch (mode) {
        case ChannelMode::Sync:
            return "sync";
        case ChannelMode::Async:
            return "async";
    }
    return "unknown-channel-mode";
}

std::string ToString(TypeKind kind) {
    switch (kind) {
        case TypeKind::Unit:
            return "nil";
        case TypeKind::Int:
            return "int";
        case TypeKind::Bool:
            return "bool";
        case TypeKind::String:
            return "string";
        case TypeKind::Tuple:
            return "tuple";
        case TypeKind::List:
            return "list";
        case TypeKind::Channel:
            return "channel";
        case TypeKind::Algebraic:
            return "adt";
        case TypeKind::Variable:
            return "type-variable";
    }
    return "unknown-type-kind";
}

std::string ToString(ObjectKind kind) {
    switch (kind) {
        case ObjectKind::Unit:
            return "unit";
        case ObjectKind::Int:
            return "int";
        case ObjectKind::Bool:
            return "bool";
        case ObjectKind::String:
            return "string";
        case ObjectKind::Tuple:
            return "tuple";
        case ObjectKind::List:
            return "list";
        case ObjectKind::Algebraic:
            return "adt";
        case ObjectKind::Channel:
            return "channel";
    }
    return "unknown-object-kind";
}

}
