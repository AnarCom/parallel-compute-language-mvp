#! /bin/sh
java -jar tools/antlr-4.13.2-complete.jar -Dlanguage=Cpp -o generated/ TLexer.g4
java -jar tools/antlr-4.13.2-complete.jar -Dlanguage=Cpp -visitor -o generated/ TParser.g4
