/* lexer header section */

// Generated from TLexer.g4 by ANTLR 4.13.2

#pragma once

/* lexer precinclude section */

#include "antlr4-runtime.h"


/* lexer postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif



/* lexer context section */

class  TLexer : public antlr4::Lexer {
public:
  enum {
    AS = 1, ASYNC = 2, BREAK = 3, CASE = 4, CONST = 5, CONTINUE = 6, ELSE = 7, 
    FOR = 8, FROM = 9, FUNC = 10, JOIN = 11, IF = 12, NIL_LIT = 13, RETURN = 14, 
    SYNC = 15, STRUCT = 16, TYPE = 17, VAR = 18, IDENTIFIER = 19, L_PAREN = 20, 
    R_PAREN = 21, L_CURLY = 22, R_CURLY = 23, L_BRACKET = 24, R_BRACKET = 25, 
    ASSIGN = 26, COMMA = 27, SEMI = 28, COLON = 29, DOT = 30, PLUS_PLUS = 31, 
    MINUS_MINUS = 32, DECLARE_ASSIGN = 33, LOGICAL_OR = 34, LOGICAL_AND = 35, 
    SYNC_RETURN = 36, EQUALS = 37, NOT_EQUALS = 38, LESS = 39, LESS_OR_EQUALS = 40, 
    GREATER = 41, GREATER_OR_EQUALS = 42, OR = 43, DIV = 44, MOD = 45, LSHIFT = 46, 
    RSHIFT = 47, BIT_CLEAR = 48, UNDERLYING = 49, EXCLAMATION = 50, PLUS = 51, 
    MINUS = 52, CARET = 53, STAR = 54, AMPERSAND = 55, EMIT = 56, DECIMAL_LIT = 57, 
    BINARY_LIT = 58, OCTAL_LIT = 59, HEX_LIT = 60, FLOAT_LIT = 61, DECIMAL_FLOAT_LIT = 62, 
    HEX_FLOAT_LIT = 63, IMAGINARY_LIT = 64, RUNE_LIT = 65, BYTE_VALUE = 66, 
    OCTAL_BYTE_VALUE = 67, HEX_BYTE_VALUE = 68, LITTLE_U_VALUE = 69, BIG_U_VALUE = 70, 
    RAW_STRING_LIT = 71, INTERPRETED_STRING_LIT = 72, WS = 73, COMMENT = 74, 
    TERMINATOR = 75, LINE_COMMENT = 76, WS_NLSEMI = 77, COMMENT_NLSEMI = 78, 
    LINE_COMMENT_NLSEMI = 79, EOS = 80, OTHER = 81
  };

  enum {
    NLSEMI = 1
  };

  explicit TLexer(antlr4::CharStream *input);

  ~TLexer() override;

  /* public lexer declarations section */
  bool isItFoo() { return true; }
  bool isItBar() { return true; }

  void myFooLexerAction() { /* do something*/ };
  void myBarLexerAction() { /* do something*/ };


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

