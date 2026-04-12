#include "gtest/gtest.h"

#include "cycle_impl.hpp"
#include "type_system.hpp"

TEST(TypeSystem, PrimitiveAndCompositeRuntimeChecks) {
    using namespace reactor;

    const auto tuple_type = Type::Tuple({Type::Int(), Type::Bool(), Type::String()});
    const auto tuple_value = Object::Tuple({Object::Int(42), Object::Bool(true), Object::String("ok")});

    EXPECT_TRUE(IsInstanceOf(Object::Int(1), Type::Int()));
    EXPECT_FALSE(IsInstanceOf(Object::Bool(true), Type::Int()));
    EXPECT_TRUE(IsInstanceOf(tuple_value, tuple_type));
    EXPECT_FALSE(IsInstanceOf(tuple_value, Type::Tuple({Type::Int(), Type::Bool()})));

    const auto list_type = Type::List(Type::Int());
    const auto list_value = Object::List({Object::Int(1), Object::Int(2), Object::Int(3)});
    EXPECT_TRUE(IsInstanceOf(list_value, list_type));
    EXPECT_FALSE(IsInstanceOf(list_value, Type::List(Type::Bool())));
}

TEST(TypeSystem, AlgebraicAndChannelTypes) {
    using namespace reactor;

    const auto maybe_int = Type::Algebraic("Maybe", {Type::Int()});
    const auto just_five = Object::Algebraic(maybe_int, "Just", {Object::Int(5)});
    const auto none_int = Object::Algebraic(maybe_int, "Nothing", {});

    EXPECT_TRUE(IsInstanceOf(just_five, maybe_int));
    EXPECT_TRUE(IsInstanceOf(none_int, maybe_int));
    EXPECT_FALSE(IsInstanceOf(just_five, Type::Algebraic("Maybe", {Type::Bool()})));

    auto& repo = CycleRepository::GetRepository();
    auto int_channel = repo.NewChannel(ChannelMode::Async, Type::Int());
    Object channel_as_object(int_channel);

    EXPECT_TRUE(IsInstanceOf(channel_as_object, Type::AsyncChannel(Type::Int())));
    EXPECT_FALSE(IsInstanceOf(channel_as_object, Type::AsyncChannel(Type::Bool())));
}

TEST(TypeSystem, StaticTypeBridge) {
    using namespace reactor;

    EXPECT_EQ(StaticTypeOf<int>(), Type::Int());
    EXPECT_EQ(StaticTypeOf<std::vector<bool>>(), Type::List(Type::Bool()));
    EXPECT_EQ((StaticTypeOf<std::tuple<int, bool, std::string>>()),
              Type::Tuple({Type::Int(), Type::Bool(), Type::String()}));
}
