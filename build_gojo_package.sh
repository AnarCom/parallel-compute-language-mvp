#! /bin/sh

mkdir -p parser/build && cd parser/build && cmake .. && make && cd ../../
mkdir -p runtime/reactor/build && cd runtime/reactor/build && cmake .. && make && cd ../../../
mkdir -p package && cp parser/build/parser package/parser && cp runtime/reactor/build/libReactor.a package/ && cp runtime/reactor/src/cycle_impl.hpp package/
cp gojo package/