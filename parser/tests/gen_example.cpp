#include "../../runtime/reactor/src/cycle_impl.hpp"

#include <iostream>
#include <memory>
#include <tuple>

using namespace reactor;

std::shared_ptr<Repository> repository__ = std::make_shared<CycleRepository>();

template <class T>
void print(T var) {
    std::cout << var << std::endl;
}

std::tuple<ChannelPtr, ChannelPtr> makeAtomicCounter(int init) {
    ChannelPtr AsyncGet = repository__->NewChannel();
    ChannelPtr Inc = repository__->NewChannel();
    ChannelPtr Val = repository__->NewChannel();
    Channels inputs0__= {Inc, Val};
    
    auto match0 = std::make_shared<RunnableOrLambda>([=](Objects inp__) {
        auto val = inp__[0].Get<int>();
        auto emitExprRightRes0 = val+1;
        Val->Push(emitExprRightRes0);
    });
    repository__->RegisterJoinCase(std::move(inputs0__), {}, match0);
    Channels inputs1__= {AsyncGet, Val};
    
    auto match1 = std::make_shared<RunnableOrLambda>([=](Objects inp__) {
        auto ReplyCh = inp__[0].Get<ChannelPtr>();
        auto val = inp__[1].Get<int>();
        auto emitExprRightRes1 = val;
        ReplyCh->Push(emitExprRightRes1);
        auto emitExprRightRes2 = val;
        Val->Push(emitExprRightRes2);
    });
    repository__->RegisterJoinCase(std::move(inputs1__), {}, match1);
    auto emitExprRightRes3 = init;
    Val->Push(emitExprRightRes3);
    return std::tuple(AsyncGet, Inc);
}


void EntryFunc__() { 
    std::tuple tuple0 = makeAtomicCounter(0);
    auto AsyncGet = std::move(std::get<0>(tuple0));
    auto Inc = std::move(std::get<1>(tuple0));
    auto emitExprRightRes4 = 1;
    Inc->Push(emitExprRightRes4);
    auto emitExprRightRes5 = 1;
    Inc->Push(emitExprRightRes5);
    ChannelPtr Result = repository__->NewChannel();
    Channels inputs2__= {Result};
    
    auto match2 = std::make_shared<RunnableOrLambda>([=](Objects inp__) {
        auto res = inp__[0].Get<int>();
        print(res);
    });
    repository__->RegisterJoinCase(std::move(inputs2__), {}, match2);
    auto emitExprRightRes6 = Result;
    AsyncGet->Push(emitExprRightRes6);
}

int main() {
    repository__->Run(std::make_shared<RunnableOrLambda>([](Objects){ EntryFunc__(); }));
    return 0;
}