#! /bin/sh

mkdir -p parser/build && cd parser/build && cmake .. && make && cd ../../
mkdir -p runtime/reactor/build && cd runtime/reactor/build && cmake .. && make && cd ../../../
mkdir -p package/include && cp parser/build/parser package/parser && cp runtime/reactor/build/libReactor.a package/ && cp runtime/reactor/src/*.hpp package/include/
cp gojo package/