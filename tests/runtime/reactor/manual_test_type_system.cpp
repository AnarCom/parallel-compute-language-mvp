#include <repository.hpp>
#include "type_system.hpp"
#include <iostream>
#include <sstream>
#include <cassert>
#include <unordered_map>

using namespace reactor;

void test_serialization() {
    std::cout << "Testing Type Serialization..." << std::endl;
    
    // Test primitive types
    assert(Type::Int().Serialize() == "int");
    assert(Type::Bool().Serialize() == "bool");
    assert(Type::String().Serialize() == "string");
    
    // Test composite types
    auto tuple_type = Type::Tuple({Type::Int(), Type::Bool()});
    std::string serialized = tuple_type.Serialize();
    Type deserialized = Type::Deserialize(serialized);
    assert(tuple_type == deserialized);
    
    std::cout << "  ✓ Type serialization works" << std::endl;
    
    // Test object serialization
    std::cout << "Testing Object Serialization..." << std::endl;
    
    auto obj = Object::Tuple({Object::Int(42), Object::Bool(true)});
    std::string obj_ser = obj.Serialize();
    Object obj_deser = Object::Deserialize(obj_ser);
    assert(obj == obj_deser);
    
    std::cout << "  ✓ Object serialization works" << std::endl;
}

void test_hashing() {
    std::cout << "Testing Hash Support..." << std::endl;
    
    // Test type hashing
    std::unordered_map<Type, std::string> type_map;
    type_map[Type::Int()] = "integer";
    type_map[Type::Bool()] = "boolean";
    
    assert(type_map[Type::Int()] == "integer");
    assert(type_map[Type::Bool()] == "boolean");
    
    std::cout << "  ✓ Type hashing works" << std::endl;
    
    // Test object hashing
    std::unordered_map<Object, int> object_map;
    object_map[Object::Int(1)] = 100;
    object_map[Object::String("test")] = 200;
    
    assert(object_map[Object::Int(1)] == 100);
    assert(object_map[Object::String("test")] == 200);
    
    std::cout << "  ✓ Object hashing works" << std::endl;
}

void test_channel_object() {
    std::cout << "Testing ChannelObject Integration..." << std::endl;
    
    auto& repo = CycleRepository::GetRepository();
    auto channel = repo.NewChannel(ChannelMode::Async, Type::Int());
    
    // Wrap channel as Object
    Object channel_obj = Object::Channel(channel);
    
    assert(channel_obj.kind() == ObjectKind::Channel);
    assert(channel_obj.GetType() == Type::AsyncChannel(Type::Int()));
    
    // Retrieve channel
    auto retrieved = channel_obj.AsChannel();
    assert(retrieved == channel);
    
    std::cout << "  ✓ ChannelObject integration works" << std::endl;
}

void test_convenience_accessors() {
    std::cout << "Testing Convenience Accessors..." << std::endl;
    
    auto int_obj = Object::Int(42);
    assert(int_obj.AsInt() == 42);
    
    auto bool_obj = Object::Bool(true);
    assert(bool_obj.AsBool() == true);
    
    auto string_obj = Object::String("hello");
    assert(string_obj.AsString() == "hello");
    
    auto tuple_obj = Object::Tuple({Object::Int(1), Object::Bool(true)});
    assert(tuple_obj.AsTuple().size() == 2);
    assert(tuple_obj.AsTuple()[0].AsInt() == 1);
    
    auto list_obj = Object::List({Object::Int(1), Object::Int(2)});
    assert(list_obj.AsList().size() == 2);
    assert(list_obj.AsList()[1].AsInt() == 2);
    
    std::cout << "  ✓ Convenience accessors work" << std::endl;
}

void test_stream_operators() {
    std::cout << "Testing Stream Operators..." << std::endl;
    
    std::ostringstream oss;
    
    oss << Type::Int();
    assert(oss.str() == "int");
    oss.str("");
    
    oss << Object::String("test");
    assert(oss.str() == "\"test\"");
    oss.str("");
    
    oss << ChannelMode::Async;
    assert(oss.str() == "async");
    
    std::cout << "  ✓ Stream operators work" << std::endl;
}

void test_equality() {
    std::cout << "Testing Object Equality..." << std::endl;
    
    assert(Object::Int(42) == Object::Int(42));
    assert(Object::Int(42) != Object::Int(43));
    
    auto tuple1 = Object::Tuple({Object::Int(1), Object::Bool(true)});
    auto tuple2 = Object::Tuple({Object::Int(1), Object::Bool(true)});
    auto tuple3 = Object::Tuple({Object::Int(1), Object::Bool(false)});
    
    assert(tuple1 == tuple2);
    assert(tuple1 != tuple3);
    
    std::cout << "  ✓ Object equality works" << std::endl;
}

int main() {
    std::cout << "=== Type System Extended Tests ===" << std::endl << std::endl;
    
    try {
        test_serialization();
        test_hashing();
        test_channel_object();
        test_convenience_accessors();
        test_stream_operators();
        test_equality();
        
        std::cout << std::endl << "=== All Tests Passed! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << std::endl << "ERROR: " << e.what() << std::endl;
        return 1;
    }
}
