#include "antlr4-runtime.h"

#include "generated/TLexer.h"
#include "generated/TParser.h"

#include <ios>
#include <iostream>
#include <string>

using namespace antlr4;

int main(int argc, const char** argv) {
  if (argc < 2) {
    return 0;
  }
  
  std::ifstream sourceFile(argv[1]);
  std::string sourceFileData;
  sourceFile.seekg(0, std::ios::end);
  sourceFileData.reserve(sourceFile.tellg());
  sourceFile.seekg(0, std::ios::beg);
  sourceFileData.assign(std::istreambuf_iterator<char>(sourceFile), std::istreambuf_iterator<char>());

  ANTLRInputStream input(sourceFileData);
  TLexer lexer(&input);
  CommonTokenStream tokens(&lexer);

  tokens.fill();
  for (auto token : tokens.getTokens()) {
    std::cout << token->toString() << std::endl;
  }

  TParser parser(&tokens);
  tree::ParseTree* tree = parser.sourceFile();

  std::cout << tree->toStringTree(&parser) << std::endl << std::endl;

  return 0;
}