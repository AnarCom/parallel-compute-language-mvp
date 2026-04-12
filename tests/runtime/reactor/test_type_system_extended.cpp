#include "gtest/gtest.h"

#include <repository.hpp>
#include "type_system.hpp"
#include <unordered_map>
#include <unordered_set>

TEST(TypeSystemExtended, TypeSerialization) {
    using namespace reactor;

    // Test primitive types
    EXPECT_EQ(Type::Int().Serialize(), "int");
    EXPECT_EQ(Type::Bool().Serialize(), "bool");
    EXPECT_EQ(Type::String().Serialize(), "string");
    EXPECT_EQ(Type::Unit().Serialize(), "nil");

    // Test variable types
    EXPECT_EQ(Type::Variable("T").Serialize(), "'T");

    // Test composite types
    auto tuple_type = Type::Tuple({Type::Int(), Type::Bool()});
    EXPECT_EQ(tuple_type.Serialize(), "(int,bool)");

    auto list_type = Type::List(Type::String());
    EXPECT_EQ(list_type.Serialize(), "[string]");

    auto channel_type = Type::AsyncChannel(Type::Int());
    EXPECT_EQ(channel_type.Serialize(), "channel<async,int>");

    auto sync_channel_type = Type::SyncChannel(Type::Bool());
    EXPECT_EQ(sync_channel_type.Serialize(), "channel<sync,bool>");

    // Test algebraic types
    auto maybe_int = Type::Algebraic("Maybe", {Type::Int()});
    EXPECT_EQ(maybe_int.Serialize(), "Maybe<int>");

    auto simple_adt = Type::Algebraic("Result");
    EXPECT_EQ(simple_adt.Serialize(), "Result");
}

TEST(TypeSystemExtended, TypeDeserialization) {
    using namespace reactor;

    // Test primitive types
    EXPECT_EQ(Type::Deserialize("int"), Type::Int());
    EXPECT_EQ(Type::Deserialize("bool"), Type::Bool());
    EXPECT_EQ(Type::Deserialize("string"), Type::String());
    EXPECT_EQ(Type::Deserialize("nil"), Type::Unit());

    // Test variable types
    EXPECT_EQ(Type::Deserialize("'T"), Type::Variable("T"));

    // Test composite types
    auto tuple_type = Type::Deserialize("(int,bool)");
    EXPECT_EQ(tuple_type, Type::Tuple({Type::Int(), Type::Bool()}));

    auto list_type = Type::Deserialize("[string]");
    EXPECT_EQ(list_type, Type::List(Type::String()));

    auto channel_type = Type::Deserialize("channel<async,int>");
    EXPECT_EQ(channel_type, Type::AsyncChannel(Type::Int()));

    // Test algebraic types
    auto maybe_int = Type::Deserialize("Maybe<int>");
    EXPECT_EQ(maybe_int, Type::Algebraic("Maybe", {Type::Int()}));
}

TEST(TypeSystemExtended, TypeRoundTripSerialization) {
    using namespace reactor;

    std::vector<Type> test_types = {
        Type::Int(),
        Type::Bool(),
        Type::String(),
        Type::Unit(),
        Type::Variable("T"),
        Type::Tuple({Type::Int(), Type::Bool(), Type::String()}),
        Type::List(Type::Int()),
        Type::List(Type::List(Type::Bool())),
        Type::AsyncChannel(Type::Int()),
        Type::SyncChannel(Type::String()),
        Type::Algebraic("Maybe", {Type::Int()}),
        Type::Algebraic("Result", {Type::String(), Type::Int()}),
        Type::Tuple({Type::List(Type::Int()), Type::AsyncChannel(Type::Bool())}),
    };

    for (const auto& original : test_types) {
        std::string serialized = original.Serialize();
        Type deserialized = Type::Deserialize(serialized);
        EXPECT_EQ(original, deserialized) << "Failed for: " << serialized;
    }
}

TEST(TypeSystemExtended, ObjectSerialization) {
    using namespace reactor;

    // Test primitive objects
    EXPECT_EQ(Object::Unit().Serialize(), "unit:nil");
    EXPECT_EQ(Object::Int(42).Serialize(), "int:42");
    EXPECT_EQ(Object::Bool(true).Serialize(), "bool:true");
    EXPECT_EQ(Object::Bool(false).Serialize(), "bool:false");
    EXPECT_EQ(Object::String("hello").Serialize(), "string:\"hello\"");

    // Test string escaping
    auto escaped_str = Object::String("hello\n\"world\"");
    std::string serialized = escaped_str.Serialize();
    EXPECT_TRUE(serialized.find("\\n") != std::string::npos);
    EXPECT_TRUE(serialized.find("\\\"") != std::string::npos);

    // Test composite objects
    auto tuple_obj = Object::Tuple({Object::Int(1), Object::Bool(true)});
    EXPECT_EQ(tuple_obj.Serialize(), "tuple:(int:1,bool:true)");

    auto list_obj = Object::List({Object::Int(1), Object::Int(2), Object::Int(3)});
    std::string list_ser = list_obj.Serialize();
    EXPECT_TRUE(list_ser.find("list:[") != std::string::npos);
    EXPECT_TRUE(list_ser.find("]:int") != std::string::npos);

    // Test algebraic objects
    auto maybe_int = Type::Algebraic("Maybe", {Type::Int()});
    auto just_five = Object::Algebraic(maybe_int, "Just", {Object::Int(5)});
    std::string adt_ser = just_five.Serialize();
    EXPECT_TRUE(adt_ser.find("adt:") != std::string::npos);
    EXPECT_TRUE(adt_ser.find("Just") != std::string::npos);
}

TEST(TypeSystemExtended, ObjectDeserialization) {
    using namespace reactor;

    // Test primitive objects
    EXPECT_EQ(Object::Deserialize("unit:nil").kind(), ObjectKind::Unit);
    EXPECT_EQ(Object::Deserialize("int:42").AsInt(), 42);
    EXPECT_EQ(Object::Deserialize("bool:true").AsBool(), true);
    EXPECT_EQ(Object::Deserialize("bool:false").AsBool(), false);
    EXPECT_EQ(Object::Deserialize("string:\"hello\"").AsString(), "hello");

    // Test tuple deserialization
    auto tuple_obj = Object::Deserialize("tuple:(int:1,bool:true)");
    EXPECT_EQ(tuple_obj.kind(), ObjectKind::Tuple);
    EXPECT_EQ(tuple_obj.AsTuple().size(), 2);
    EXPECT_EQ(tuple_obj.AsTuple()[0].AsInt(), 1);
    EXPECT_EQ(tuple_obj.AsTuple()[1].AsBool(), true);

    // Test list deserialization
    auto list_obj = Object::Deserialize("list:[int:1,int:2,int:3]:int");
    EXPECT_EQ(list_obj.kind(), ObjectKind::List);
    EXPECT_EQ(list_obj.AsList().size(), 3);
    EXPECT_EQ(list_obj.AsList()[0].AsInt(), 1);
    EXPECT_EQ(list_obj.AsList()[2].AsInt(), 3);
}

TEST(TypeSystemExtended, ObjectRoundTripSerialization) {
    using namespace reactor;

    std::vector<Object> test_objects = {
        Object::Unit(),
        Object::Int(42),
        Object::Int(-100),
        Object::Bool(true),
        Object::Bool(false),
        Object::String("hello world"),
        Object::String("with\nnewlines\tand\ttabs"),
        Object::Tuple({Object::Int(1), Object::Bool(true), Object::String("test")}),
        Object::List({Object::Int(1), Object::Int(2), Object::Int(3)}),
        Object::List({Object::String("a"), Object::String("b")}),
        Object::Algebraic(Type::Algebraic("Maybe", {Type::Int()}), "Just", {Object::Int(5)}),
        Object::Algebraic(Type::Algebraic("Maybe", {Type::Int()}), "Nothing", {}),
    };

    for (const auto& original : test_objects) {
        std::string serialized = original.Serialize();
        Object deserialized = Object::Deserialize(serialized);
        EXPECT_EQ(original, deserialized) << "Failed for: " << serialized;
    }
}

TEST(TypeSystemExtended, TypeHashing) {
    using namespace reactor;

    // Test that equal types have equal hashes
    EXPECT_EQ(Type::Int().Hash(), Type::Int().Hash());
    EXPECT_EQ(Type::List(Type::Bool()).Hash(), Type::List(Type::Bool()).Hash());

    // Test that different types have different hashes (usually)
    EXPECT_NE(Type::Int().Hash(), Type::Bool().Hash());
    EXPECT_NE(Type::List(Type::Int()).Hash(), Type::List(Type::Bool()).Hash());

    // Test hash map usage
    std::unordered_map<Type, std::string> type_map;
    type_map[Type::Int()] = "integer";
    type_map[Type::Bool()] = "boolean";
    type_map[Type::String()] = "string";

    EXPECT_EQ(type_map[Type::Int()], "integer");
    EXPECT_EQ(type_map[Type::Bool()], "boolean");
    EXPECT_EQ(type_map[Type::String()], "string");

    // Test hash set usage
    std::unordered_set<Type> type_set;
    type_set.insert(Type::Int());
    type_set.insert(Type::Bool());
    type_set.insert(Type::Int()); // Duplicate

    EXPECT_EQ(type_set.size(), 2);
    EXPECT_TRUE(type_set.find(Type::Int()) != type_set.end());
    EXPECT_TRUE(type_set.find(Type::Bool()) != type_set.end());
}

TEST(TypeSystemExtended, ObjectHashing) {
    using namespace reactor;

    // Test that equal objects have equal hashes
    EXPECT_EQ(Object::Int(42).Hash(), Object::Int(42).Hash());
    EXPECT_EQ(Object::String("test").Hash(), Object::String("test").Hash());

    // Test that different objects have different hashes (usually)
    EXPECT_NE(Object::Int(42).Hash(), Object::Int(43).Hash());
    EXPECT_NE(Object::String("test").Hash(), Object::String("other").Hash());

    // Test hash map usage
    std::unordered_map<Object, std::string> object_map;
    object_map[Object::Int(1)] = "one";
    object_map[Object::Int(2)] = "two";
    object_map[Object::Bool(true)] = "true";

    EXPECT_EQ(object_map[Object::Int(1)], "one");
    EXPECT_EQ(object_map[Object::Int(2)], "two");
    EXPECT_EQ(object_map[Object::Bool(true)], "true");
}

TEST(TypeSystemExtended, ObjectEquality) {
    using namespace reactor;

    // Test primitive equality
    EXPECT_EQ(Object::Int(42), Object::Int(42));
    EXPECT_NE(Object::Int(42), Object::Int(43));
    EXPECT_EQ(Object::Bool(true), Object::Bool(true));
    EXPECT_NE(Object::Bool(true), Object::Bool(false));
    EXPECT_EQ(Object::String("test"), Object::String("test"));
    EXPECT_NE(Object::String("test"), Object::String("other"));

    // Test tuple equality
    auto tuple1 = Object::Tuple({Object::Int(1), Object::Bool(true)});
    auto tuple2 = Object::Tuple({Object::Int(1), Object::Bool(true)});
    auto tuple3 = Object::Tuple({Object::Int(1), Object::Bool(false)});
    EXPECT_EQ(tuple1, tuple2);
    EXPECT_NE(tuple1, tuple3);

    // Test list equality
    auto list1 = Object::List({Object::Int(1), Object::Int(2)});
    auto list2 = Object::List({Object::Int(1), Object::Int(2)});
    auto list3 = Object::List({Object::Int(1), Object::Int(3)});
    EXPECT_EQ(list1, list2);
    EXPECT_NE(list1, list3);
}

TEST(TypeSystemExtended, ConvenienceAccessors) {
    using namespace reactor;

    // Test AsInt
    auto int_obj = Object::Int(42);
    EXPECT_EQ(int_obj.AsInt(), 42);

    // Test AsBool
    auto bool_obj = Object::Bool(true);
    EXPECT_EQ(bool_obj.AsBool(), true);

    // Test AsString
    auto string_obj = Object::String("hello");
    EXPECT_EQ(string_obj.AsString(), "hello");

    // Test AsTuple
    auto tuple_obj = Object::Tuple({Object::Int(1), Object::Bool(true)});
    EXPECT_EQ(tuple_obj.AsTuple().size(), 2);
    EXPECT_EQ(tuple_obj.AsTuple()[0].AsInt(), 1);

    // Test AsList
    auto list_obj = Object::List({Object::Int(1), Object::Int(2), Object::Int(3)});
    EXPECT_EQ(list_obj.AsList().size(), 3);
    EXPECT_EQ(list_obj.AsList()[1].AsInt(), 2);

    // Test error cases
    EXPECT_THROW((void)bool_obj.AsInt(), std::logic_error);
    EXPECT_THROW((void)int_obj.AsBool(), std::logic_error);
    EXPECT_THROW((void)string_obj.AsTuple(), std::logic_error);
}

TEST(TypeSystemExtended, ChannelObjectIntegration) {
    using namespace reactor;

    auto& repo = CycleRepository::GetRepository();
    auto int_channel = repo.NewChannel(ChannelMode::Async, Type::Int());
    
    // Test wrapping channel in Object
    Object channel_obj = Object::Channel(int_channel);
    
    EXPECT_EQ(channel_obj.kind(), ObjectKind::Channel);
    EXPECT_EQ(channel_obj.GetType(), Type::AsyncChannel(Type::Int()));
    EXPECT_TRUE(IsInstanceOf(channel_obj, Type::AsyncChannel(Type::Int())));
    
    // Test AsChannel accessor
    auto retrieved_channel = channel_obj.AsChannel();
    EXPECT_EQ(retrieved_channel, int_channel);
    
    // Test that channel has an ID
    EXPECT_TRUE(retrieved_channel->GetID().has_value());
}

TEST(TypeSystemExtended, StreamOperators) {
    using namespace reactor;

    std::ostringstream oss;
    
    // Test Type stream operator
    oss << Type::Int();
    EXPECT_EQ(oss.str(), "int");
    oss.str("");
    
    oss << Type::List(Type::Bool());
    EXPECT_EQ(oss.str(), "[bool]");
    oss.str("");
    
    // Test Object stream operator
    oss << Object::Int(42);
    EXPECT_EQ(oss.str(), "42");
    oss.str("");
    
    oss << Object::String("test");
    EXPECT_EQ(oss.str(), "\"test\"");
    oss.str("");
    
    // Test enum stream operators
    oss << ChannelMode::Async;
    EXPECT_EQ(oss.str(), "async");
    oss.str("");
    
    oss << TypeKind::Int;
    EXPECT_EQ(oss.str(), "int");
    oss.str("");
    
    oss << ObjectKind::Tuple;
    EXPECT_EQ(oss.str(), "tuple");
}

TEST(TypeSystemExtended, ComplexNestedSerialization) {
    using namespace reactor;

    // Create a complex nested structure
    auto complex_type = Type::Tuple({
        Type::List(Type::Int()),
        Type::AsyncChannel(Type::Tuple({Type::Bool(), Type::String()})),
        Type::Algebraic("Result", {Type::String(), Type::Int()})
    });

    std::string serialized = complex_type.Serialize();
    Type deserialized = Type::Deserialize(serialized);
    EXPECT_EQ(complex_type, deserialized);

    // Create a complex nested object
    auto complex_obj = Object::Tuple({
        Object::List({Object::Int(1), Object::Int(2)}),
        Object::String("nested"),
        Object::Tuple({Object::Bool(true), Object::Int(99)})
    });

    std::string obj_serialized = complex_obj.Serialize();
    Object obj_deserialized = Object::Deserialize(obj_serialized);
    EXPECT_EQ(complex_obj, obj_deserialized);
}

TEST(TypeSystemExtended, ChannelSerialization) {
    using namespace reactor;

    auto& repo = CycleRepository::GetRepository();
    auto channel = repo.NewChannel(ChannelMode::Async, Type::Int());
    Object channel_obj = Object::Channel(channel);

    // Channels can be serialized (for debugging/logging)
    std::string serialized = channel_obj.Serialize();
    EXPECT_TRUE(serialized.find("channel:") != std::string::npos);
    
    // But they cannot be deserialized (runtime-only objects)
    EXPECT_THROW(Object::Deserialize(serialized), std::logic_error);
}

TEST(TypeSystemExtended, TypeHashConsistency) {
    using namespace reactor;

    // Hash should be consistent across multiple calls
    auto type1 = Type::Tuple({Type::Int(), Type::Bool()});
    size_t hash1 = type1.Hash();
    size_t hash2 = type1.Hash();
    EXPECT_EQ(hash1, hash2);

    // Equal types should have equal hashes
    auto type2 = Type::Tuple({Type::Int(), Type::Bool()});
    EXPECT_EQ(type1.Hash(), type2.Hash());
}

TEST(TypeSystemExtended, ObjectHashConsistency) {
    using namespace reactor;

    // Hash should be consistent across multiple calls
    auto obj1 = Object::Tuple({Object::Int(1), Object::Bool(true)});
    size_t hash1 = obj1.Hash();
    size_t hash2 = obj1.Hash();
    EXPECT_EQ(hash1, hash2);

    // Equal objects should have equal hashes
    auto obj2 = Object::Tuple({Object::Int(1), Object::Bool(true)});
    EXPECT_EQ(obj1.Hash(), obj2.Hash());
}
