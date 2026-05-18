#include "antlr4-runtime.h"

#include "generated/TParserVisitor.h"
#include "visitor/visitor.h"

#include "generated/TLexer.h"
#include "generated/TParser.h"

#include <ios>
#include <iostream>
#include <string>

#define DEBUG

using namespace antlr4;

int main(int argc, const char** argv) {
  if (argc < 2) {
    return 0;
  }
  
  try {
    std::ifstream sourceFile(argv[1]);
    if (!sourceFile.is_open()) {
      std::cerr << "Failed to open file " << argv[1] << std::endl;
      return 0;
    }
    std::string sourceFileData;
    sourceFile.seekg(0, std::ios::end);
    sourceFileData.reserve(sourceFile.tellg());
    sourceFile.seekg(0, std::ios::beg);
    sourceFileData.assign(std::istreambuf_iterator<char>(sourceFile), std::istreambuf_iterator<char>());

    ANTLRInputStream input(sourceFileData);
    TLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    tokens.fill();

    TParser parser(&tokens);
    tree::ParseTree* tree = parser.sourceFile();

#ifndef DEBUG
   if (argc < 3) {
      std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
      return 0;
    }
    std::string outFilePath(argv[2]);

    Visitor visitor(outFilePath);
#else
    Visitor visitor;
# endif
    visitor.WriteHeaders();
    visitor.WriteGlobals();
    visitor.WritePredefinedFunctions();
    visitor.WriteFunctions(tree);
    visitor.StartEntryFunc();
    visitor.visit(tree);
    visitor.EndEntryFunc();
    visitor.WriteMain();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  catch (...) {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}