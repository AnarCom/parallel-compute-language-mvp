include_directories(antlr4_runtime/src)

add_library(generated STATIC TLexer.cpp TParser.cpp TParserBaseVisitor.cpp TParserVisitor.cpp)
