#include "type_system.hpp"
#include "interface.hpp"

#include <sstream>
#include <stdexcept>
#include <ostream>
#include <functional>
#include <cctype>

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

size_t HashCombine(size_t seed, size_t hash) noexcept {
    // Based on boost::hash_combine
    return seed ^ (hash + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}

std::string EscapeString(const std::string& str) {
    std::ostringstream out;
    for (char c : str) {
        switch (c) {
            case '"': out << "\\\""; break;
            case '\\': out << "\\\\"; break;
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            default: out << c; break;
        }
    }
    return out.str();
}

std::string UnescapeString(const std::string& str) {
    std::ostringstream out;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '\\' && i + 1 < str.size()) {
            switch (str[i + 1]) {
                case '"': out << '"'; ++i; break;
                case '\\': out << '\\'; ++i; break;
                case 'n': out << '\n'; ++i; break;
                case 'r': out << '\r'; ++i; break;
                case 't': out << '\t'; ++i; break;
                default: out << str[i]; break;
            }
        } else {
            out << str[i];
        }
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

size_t PrimitiveTypeNode::Hash() const noexcept {
    return std::hash<int>{}(static_cast<int>(kind_));
}

std::string PrimitiveTypeNode::Serialize() const {
    return ToString();
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

size_t VariableTypeNode::Hash() const noexcept {
    size_t h = std::hash<int>{}(static_cast<int>(TypeKind::Variable));
    return HashCombine(h, std::hash<std::string>{}(name_));
}

std::string VariableTypeNode::Serialize() const {
    return "'" + name_;
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

size_t TupleTypeNode::Hash() const noexcept {
    size_t h = std::hash<int>{}(static_cast<int>(TypeKind::Tuple));
    for (const auto& element : elements_) {
        h = HashCombine(h, element.Hash());
    }
    return h;
}

std::string TupleTypeNode::Serialize() const {
    std::vector<std::string> parts;
    parts.reserve(elements_.size());
    for (const auto& element : elements_) {
        parts.push_back(element.Serialize());
    }
    return "(" + JoinStrings(parts, ",") + ")";
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

size_t ListTypeNode::Hash() const noexcept {
    size_t h = std::hash<int>{}(static_cast<int>(TypeKind::List));
    return HashCombine(h, element_type_.Hash());
}

std::string ListTypeNode::Serialize() const {
    return "[" + element_type_.Serialize() + "]";
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

size_t ChannelTypeNode::Hash() const noexcept {
    size_t h = std::hash<int>{}(static_cast<int>(TypeKind::Channel));
    h = HashCombine(h, std::hash<int>{}(static_cast<int>(mode_)));
    return HashCombine(h, payload_type_.Hash());
}

std::string ChannelTypeNode::Serialize() const {
    std::string mode_str = (mode_ == ChannelMode::Sync) ? "sync" : "async";
    return "channel<" + mode_str + "," + payload_type_.Serialize() + ">";
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

size_t AlgebraicTypeNode::Hash() const noexcept {
    size_t h = std::hash<int>{}(static_cast<int>(TypeKind::Algebraic));
    h = HashCombine(h, std::hash<std::string>{}(name_));
    for (const auto& parameter : parameters_) {
        h = HashCombine(h, parameter.Hash());
    }
    return h;
}

std::string AlgebraicTypeNode::Serialize() const {
    if (parameters_.empty()) {
        return name_;
    }
    std::vector<std::string> parts;
    parts.reserve(parameters_.size());
    for (const auto& parameter : parameters_) {
        parts.push_back(parameter.Serialize());
    }
    return name_ + "<" + JoinStrings(parts, ",") + ">";
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

std::string Type::Serialize() const {
    return node_->Serialize();
}

Type Type::Deserialize(const std::string& serialized) {
    if (serialized.empty()) {
        throw std::invalid_argument("Cannot deserialize empty string");
    }

    // Handle primitive types
    if (serialized == "nil") return Type::Unit();
    if (serialized == "int") return Type::Int();
    if (serialized == "bool") return Type::Bool();
    if (serialized == "string") return Type::String();

    // Handle type variables (start with ')
    if (serialized[0] == '\'') {
        return Type::Variable(serialized.substr(1));
    }

    // Handle list types [T]
    if (serialized[0] == '[' && serialized.back() == ']') {
        std::string inner = serialized.substr(1, serialized.size() - 2);
        return Type::List(Deserialize(inner));
    }

    // Handle tuple types (T1,T2,...)
    if (serialized[0] == '(' && serialized.back() == ')') {
        std::string inner = serialized.substr(1, serialized.size() - 2);
        std::vector<Type> elements;
        size_t depth = 0;
        size_t start = 0;
        for (size_t i = 0; i < inner.size(); ++i) {
            if (inner[i] == '(' || inner[i] == '[' || inner[i] == '<') ++depth;
            if (inner[i] == ')' || inner[i] == ']' || inner[i] == '>') --depth;
            if (depth == 0 && inner[i] == ',') {
                elements.push_back(Deserialize(inner.substr(start, i - start)));
                start = i + 1;
            }
        }
        if (start < inner.size()) {
            elements.push_back(Deserialize(inner.substr(start)));
        }
        return Type::Tuple(std::move(elements));
    }

    // Handle channel types channel<mode,payload>
    if (serialized.substr(0, 8) == "channel<" && serialized.back() == '>') {
        std::string inner = serialized.substr(8, serialized.size() - 9);
        size_t comma_pos = inner.find(',');
        if (comma_pos == std::string::npos) {
            throw std::invalid_argument("Invalid channel type serialization");
        }
        std::string mode_str = inner.substr(0, comma_pos);
        std::string payload_str = inner.substr(comma_pos + 1);
        ChannelMode mode = (mode_str == "sync") ? ChannelMode::Sync : ChannelMode::Async;
        return Type::Channel(mode, Deserialize(payload_str));
    }

    // Handle algebraic types Name or Name<T1,T2,...>
    size_t angle_pos = serialized.find('<');
    if (angle_pos != std::string::npos && serialized.back() == '>') {
        std::string name = serialized.substr(0, angle_pos);
        std::string inner = serialized.substr(angle_pos + 1, serialized.size() - angle_pos - 2);
        std::vector<Type> parameters;
        size_t depth = 0;
        size_t start = 0;
        for (size_t i = 0; i < inner.size(); ++i) {
            if (inner[i] == '(' || inner[i] == '[' || inner[i] == '<') ++depth;
            if (inner[i] == ')' || inner[i] == ']' || inner[i] == '>') --depth;
            if (depth == 0 && inner[i] == ',') {
                parameters.push_back(Deserialize(inner.substr(start, i - start)));
                start = i + 1;
            }
        }
        if (start < inner.size()) {
            parameters.push_back(Deserialize(inner.substr(start)));
        }
        return Type::Algebraic(name, std::move(parameters));
    }

    // Otherwise it's a simple algebraic type name
    return Type::Algebraic(serialized);
}

size_t Type::Hash() const noexcept {
    return node_->Hash();
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

std::string UnitObject::Serialize() const {
    return "unit:nil";
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

std::string IntObject::Serialize() const {
    return "int:" + std::to_string(value_);
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

std::string BoolObject::Serialize() const {
    return value_ ? "bool:true" : "bool:false";
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

std::string StringObject::Serialize() const {
    return "string:\"" + EscapeString(value_) + "\"";
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

std::string TupleObject::Serialize() const {
    std::vector<std::string> parts;
    parts.reserve(elements_.size());
    for (const auto& element : elements_) {
        parts.push_back(element.Serialize());
    }
    return "tuple:(" + JoinStrings(parts, ",") + ")";
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

std::string ListObject::Serialize() const {
    std::vector<std::string> parts;
    parts.reserve(elements_.size());
    for (const auto& element : elements_) {
        parts.push_back(element.Serialize());
    }
    return "list:[" + JoinStrings(parts, ",") + "]:" + element_type_.Serialize();
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

std::string AlgebraicObject::Serialize() const {
    std::vector<std::string> parts;
    parts.reserve(fields_.size());
    for (const auto& field : fields_) {
        parts.push_back(field.Serialize());
    }
    return "adt:" + algebraic_type_.Serialize() + ":" + constructor_name_ + ":(" + JoinStrings(parts, ",") + ")";
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

Object Object::Channel(Pointer<ChannelBase> channel) {
    return Object(std::make_shared<ChannelObject>(std::move(channel)));
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

std::int64_t Object::AsInt() const {
    auto int_obj = As<IntObject>();
    if (!int_obj) {
        throw std::logic_error("Object is not an Int");
    }
    return int_obj->value();
}

bool Object::AsBool() const {
    auto bool_obj = As<BoolObject>();
    if (!bool_obj) {
        throw std::logic_error("Object is not a Bool");
    }
    return bool_obj->value();
}

const std::string& Object::AsString() const {
    auto string_obj = As<StringObject>();
    if (!string_obj) {
        throw std::logic_error("Object is not a String");
    }
    return string_obj->value();
}

const Objects& Object::AsTuple() const {
    auto tuple_obj = As<TupleObject>();
    if (!tuple_obj) {
        throw std::logic_error("Object is not a Tuple");
    }
    return tuple_obj->elements();
}

const Objects& Object::AsList() const {
    auto list_obj = As<ListObject>();
    if (!list_obj) {
        throw std::logic_error("Object is not a List");
    }
    return list_obj->elements();
}

Pointer<ChannelBase> Object::AsChannel() const {
    auto channel_obj = As<ChannelObject>();
    if (!channel_obj) {
        throw std::logic_error("Object is not a Channel");
    }
    return channel_obj->channel();
}

std::string Object::Serialize() const {
    return value_->Serialize();
}

Object Object::Deserialize(const std::string& serialized) {
    if (serialized.empty()) {
        throw std::invalid_argument("Cannot deserialize empty string");
    }

    size_t colon_pos = serialized.find(':');
    if (colon_pos == std::string::npos) {
        throw std::invalid_argument("Invalid object serialization format");
    }

    std::string kind_str = serialized.substr(0, colon_pos);
    std::string data = serialized.substr(colon_pos + 1);

    if (kind_str == "unit") {
        return Object::Unit();
    } else if (kind_str == "int") {
        return Object::Int(std::stoll(data));
    } else if (kind_str == "bool") {
        return Object::Bool(data == "true");
    } else if (kind_str == "string") {
        if (data.size() < 2 || data.front() != '"' || data.back() != '"') {
            throw std::invalid_argument("Invalid string serialization");
        }
        return Object::String(UnescapeString(data.substr(1, data.size() - 2)));
    } else if (kind_str == "tuple") {
        if (data.size() < 2 || data.front() != '(' || data.back() != ')') {
            throw std::invalid_argument("Invalid tuple serialization");
        }
        std::string inner = data.substr(1, data.size() - 2);
        Objects elements;
        size_t depth = 0;
        size_t start = 0;
        for (size_t i = 0; i < inner.size(); ++i) {
            if (inner[i] == '(' || inner[i] == '[') ++depth;
            if (inner[i] == ')' || inner[i] == ']') --depth;
            if (depth == 0 && inner[i] == ',') {
                elements.push_back(Deserialize(inner.substr(start, i - start)));
                start = i + 1;
            }
        }
        if (start < inner.size()) {
            elements.push_back(Deserialize(inner.substr(start)));
        }
        return Object::Tuple(std::move(elements));
    } else if (kind_str == "list") {
        size_t bracket_pos = data.find('[');
        size_t bracket_end = data.find(']', bracket_pos);
        size_t type_colon = data.find(':', bracket_end);
        if (bracket_pos == std::string::npos || bracket_end == std::string::npos || type_colon == std::string::npos) {
            throw std::invalid_argument("Invalid list serialization");
        }
        std::string inner = data.substr(bracket_pos + 1, bracket_end - bracket_pos - 1);
        std::string type_str = data.substr(type_colon + 1);
        Type element_type = Type::Deserialize(type_str);
        Objects elements;
        if (!inner.empty()) {
            size_t depth = 0;
            size_t start = 0;
            for (size_t i = 0; i < inner.size(); ++i) {
                if (inner[i] == '(' || inner[i] == '[') ++depth;
                if (inner[i] == ')' || inner[i] == ']') --depth;
                if (depth == 0 && inner[i] == ',') {
                    elements.push_back(Deserialize(inner.substr(start, i - start)));
                    start = i + 1;
                }
            }
            if (start < inner.size()) {
                elements.push_back(Deserialize(inner.substr(start)));
            }
        }
        return Object::List(std::move(elements), element_type);
    } else if (kind_str == "adt") {
        // Format: adt:type:constructor:(fields)
        size_t first_colon = colon_pos;
        size_t second_colon = serialized.find(':', first_colon + 1);
        size_t third_colon = serialized.find(':', second_colon + 1);
        if (second_colon == std::string::npos || third_colon == std::string::npos) {
            throw std::invalid_argument("Invalid algebraic object serialization");
        }
        std::string type_str = serialized.substr(first_colon + 1, second_colon - first_colon - 1);
        std::string constructor = serialized.substr(second_colon + 1, third_colon - second_colon - 1);
        std::string fields_str = serialized.substr(third_colon + 1);
        if (fields_str.size() < 2 || fields_str.front() != '(' || fields_str.back() != ')') {
            throw std::invalid_argument("Invalid algebraic object fields serialization");
        }
        std::string inner = fields_str.substr(1, fields_str.size() - 2);
        Objects fields;
        if (!inner.empty()) {
            size_t depth = 0;
            size_t start = 0;
            for (size_t i = 0; i < inner.size(); ++i) {
                if (inner[i] == '(' || inner[i] == '[') ++depth;
                if (inner[i] == ')' || inner[i] == ']') --depth;
                if (depth == 0 && inner[i] == ',') {
                    fields.push_back(Deserialize(inner.substr(start, i - start)));
                    start = i + 1;
                }
            }
            if (start < inner.size()) {
                fields.push_back(Deserialize(inner.substr(start)));
            }
        }
        return Object::Algebraic(Type::Deserialize(type_str), constructor, std::move(fields));
    } else if (kind_str == "channel") {
        throw std::logic_error("Channel objects cannot be deserialized (they are runtime-only)");
    }

    throw std::invalid_argument("Unknown object kind: " + kind_str);
}

size_t Object::Hash() const noexcept {
    size_t h = std::hash<int>{}(static_cast<int>(kind()));
    switch (kind()) {
        case ObjectKind::Unit:
            return h;
        case ObjectKind::Int:
            return HashCombine(h, std::hash<std::int64_t>{}(As<IntObject>()->value()));
        case ObjectKind::Bool:
            return HashCombine(h, std::hash<bool>{}(As<BoolObject>()->value()));
        case ObjectKind::String:
            return HashCombine(h, std::hash<std::string>{}(As<StringObject>()->value()));
        case ObjectKind::Tuple: {
            for (const auto& element : As<TupleObject>()->elements()) {
                h = HashCombine(h, element.Hash());
            }
            return h;
        }
        case ObjectKind::List: {
            auto list_obj = As<ListObject>();
            h = HashCombine(h, list_obj->element_type().Hash());
            for (const auto& element : list_obj->elements()) {
                h = HashCombine(h, element.Hash());
            }
            return h;
        }
        case ObjectKind::Algebraic: {
            auto alg_obj = As<AlgebraicObject>();
            h = HashCombine(h, alg_obj->algebraic_type().Hash());
            h = HashCombine(h, std::hash<std::string>{}(alg_obj->constructor_name()));
            for (const auto& field : alg_obj->fields()) {
                h = HashCombine(h, field.Hash());
            }
            return h;
        }
        case ObjectKind::Channel: {
            auto channel_obj = As<ChannelObject>();
            auto id = channel_obj->channel()->GetID();
            if (id.has_value()) {
                return HashCombine(h, std::hash<uint64_t>{}(*id));
            }
            return HashCombine(h, reinterpret_cast<size_t>(channel_obj->channel().get()));
        }
    }
    return h;
}

bool operator==(const Object& lhs, const Object& rhs) noexcept {
    if (lhs.kind() != rhs.kind()) {
        return false;
    }
    switch (lhs.kind()) {
        case ObjectKind::Unit:
            return true;
        case ObjectKind::Int:
            return lhs.As<IntObject>()->value() == rhs.As<IntObject>()->value();
        case ObjectKind::Bool:
            return lhs.As<BoolObject>()->value() == rhs.As<BoolObject>()->value();
        case ObjectKind::String:
            return lhs.As<StringObject>()->value() == rhs.As<StringObject>()->value();
        case ObjectKind::Tuple: {
            const auto& lhs_elems = lhs.As<TupleObject>()->elements();
            const auto& rhs_elems = rhs.As<TupleObject>()->elements();
            if (lhs_elems.size() != rhs_elems.size()) {
                return false;
            }
            for (size_t i = 0; i < lhs_elems.size(); ++i) {
                if (lhs_elems[i] != rhs_elems[i]) {
                    return false;
                }
            }
            return true;
        }
        case ObjectKind::List: {
            const auto& lhs_elems = lhs.As<ListObject>()->elements();
            const auto& rhs_elems = rhs.As<ListObject>()->elements();
            if (lhs_elems.size() != rhs_elems.size()) {
                return false;
            }
            for (size_t i = 0; i < lhs_elems.size(); ++i) {
                if (lhs_elems[i] != rhs_elems[i]) {
                    return false;
                }
            }
            return true;
        }
        case ObjectKind::Algebraic: {
            auto lhs_alg = lhs.As<AlgebraicObject>();
            auto rhs_alg = rhs.As<AlgebraicObject>();
            if (lhs_alg->algebraic_type() != rhs_alg->algebraic_type()) {
                return false;
            }
            if (lhs_alg->constructor_name() != rhs_alg->constructor_name()) {
                return false;
            }
            const auto& lhs_fields = lhs_alg->fields();
            const auto& rhs_fields = rhs_alg->fields();
            if (lhs_fields.size() != rhs_fields.size()) {
                return false;
            }
            for (size_t i = 0; i < lhs_fields.size(); ++i) {
                if (lhs_fields[i] != rhs_fields[i]) {
                    return false;
                }
            }
            return true;
        }
        case ObjectKind::Channel: {
            auto lhs_ch = lhs.As<ChannelObject>();
            auto rhs_ch = rhs.As<ChannelObject>();
            return lhs_ch->channel() == rhs_ch->channel();
        }
    }
    return false;
}

bool operator!=(const Object& lhs, const Object& rhs) noexcept {
    return !(lhs == rhs);
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

// Stream operators
std::ostream& operator<<(std::ostream& os, const Type& type) {
    return os << type.ToString();
}

std::ostream& operator<<(std::ostream& os, const Object& object) {
    return os << object.ToString();
}

std::ostream& operator<<(std::ostream& os, ChannelMode mode) {
    return os << ToString(mode);
}

std::ostream& operator<<(std::ostream& os, TypeKind kind) {
    return os << ToString(kind);
}

std::ostream& operator<<(std::ostream& os, ObjectKind kind) {
    return os << ToString(kind);
}

}
