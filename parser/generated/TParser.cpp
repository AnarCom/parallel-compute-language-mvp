/* parser/listener/visitor header section */

// Generated from TParser.g4 by ANTLR 4.13.2

/* parser precinclude section */

#include "TParserListener.h"
#include "TParserVisitor.h"

#include "TParser.h"


/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct TParserStaticData final {
  TParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  TParserStaticData(const TParserStaticData&) = delete;
  TParserStaticData(TParserStaticData&&) = delete;
  TParserStaticData& operator=(const TParserStaticData&) = delete;
  TParserStaticData& operator=(TParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag tparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<TParserStaticData> tparserParserStaticData = nullptr;

void tparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (tparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(tparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<TParserStaticData>(
    std::vector<std::string>{
      "sourceFile", "identifier", "declaration", "constDecl", "constSpec", 
      "identifierList", "expressionList", "typeSpec", "aliasDecl", "typeDef", 
      "typeParameters", "typeParameterDecl", "typeElement", "typeTerm", 
      "functionDecl", "varDecl", "varSpec", "block", "statementList", "statement", 
      "simpleStmt", "expressionStmt", "syncReturnStmt", "emitStmt", "incDecStmt", 
      "assignment", "assign_op", "shortVarDecl", "returnStmt", "breakStmt", 
      "continueStmt", "ifStmt", "typeList", "joinStmt", "matchClause", "matchCase", 
      "fromChanAs", "forStmt", "condition", "forClause", "type_", "typeArgs", 
      "typeName", "typeLit", "arrayType", "arrayLength", "elementType", 
      "asyncChannelType", "syncChannelType", "functionType", "signature", 
      "result", "parameters", "parameterDecl", "expression", "primaryExpr", 
      "conversion", "operand", "literal", "basicLit", "integer", "operandName", 
      "compositeLit", "literalType", "literalValue", "elementList", "keyedElement", 
      "key", "element", "string_", "functionLit", "index", "arguments", 
      "eos"
    },
    std::vector<std::string>{
      "", "'as'", "'async'", "'break'", "'case'", "'const'", "'continue'", 
      "'else'", "'for'", "'from'", "'func'", "'join'", "'if'", "'nil'", 
      "'return'", "'sync'", "'var'", "", "'('", "')'", "'{'", "'}'", "'['", 
      "']'", "'='", "','", "';'", "':'", "'++'", "'--'", "':='", "'||'", 
      "'&&'", "'=='", "'!='", "'<'", "'<='", "'>'", "'>='", "'|'", "'/'", 
      "'%'", "'<<'", "'>>'", "'&^'", "'~'", "'!'", "'+'", "'-'", "'^'", 
      "'*'", "'&'", "'<-'", "'<|'"
    },
    std::vector<std::string>{
      "", "AS", "ASYNC", "BREAK", "CASE", "CONST", "CONTINUE", "ELSE", "FOR", 
      "FROM", "FUNC", "JOIN", "IF", "NIL_LIT", "RETURN", "SYNC", "VAR", 
      "IDENTIFIER", "L_PAREN", "R_PAREN", "L_CURLY", "R_CURLY", "L_BRACKET", 
      "R_BRACKET", "ASSIGN", "COMMA", "SEMI", "COLON", "PLUS_PLUS", "MINUS_MINUS", 
      "DECLARE_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", "EQUALS", "NOT_EQUALS", 
      "LESS", "LESS_OR_EQUALS", "GREATER", "GREATER_OR_EQUALS", "OR", "DIV", 
      "MOD", "LSHIFT", "RSHIFT", "BIT_CLEAR", "UNDERLYING", "EXCLAMATION", 
      "PLUS", "MINUS", "CARET", "STAR", "AMPERSAND", "EMIT", "SYNC_RETURN", 
      "DECIMAL_LIT", "BINARY_LIT", "OCTAL_LIT", "HEX_LIT", "FLOAT_LIT", 
      "DECIMAL_FLOAT_LIT", "HEX_FLOAT_LIT", "IMAGINARY_LIT", "RUNE_LIT", 
      "BYTE_VALUE", "OCTAL_BYTE_VALUE", "HEX_BYTE_VALUE", "LITTLE_U_VALUE", 
      "BIG_U_VALUE", "RAW_STRING_LIT", "INTERPRETED_STRING_LIT", "WS", "COMMENT", 
      "TERMINATOR", "LINE_COMMENT", "WS_NLSEMI", "COMMENT_NLSEMI", "LINE_COMMENT_NLSEMI", 
      "EOS", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,78,651,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,1,0,1,0,1,0,3,0,152,8,0,1,0,1,0,5,0,
  	156,8,0,10,0,12,0,159,9,0,1,0,1,0,1,1,1,1,1,2,1,2,3,2,167,8,2,1,3,1,3,
  	1,3,1,3,1,3,1,3,5,3,175,8,3,10,3,12,3,178,9,3,1,3,3,3,181,8,3,1,4,1,4,
  	3,4,185,8,4,1,4,1,4,3,4,189,8,4,1,5,1,5,1,5,5,5,194,8,5,10,5,12,5,197,
  	9,5,1,6,1,6,1,6,5,6,202,8,6,10,6,12,6,205,9,6,1,7,1,7,3,7,209,8,7,1,8,
  	1,8,3,8,213,8,8,1,8,1,8,1,8,1,9,1,9,3,9,220,8,9,1,9,1,9,1,10,1,10,1,10,
  	1,10,5,10,228,8,10,10,10,12,10,231,9,10,1,10,1,10,1,11,1,11,1,11,1,12,
  	1,12,1,12,5,12,241,8,12,10,12,12,12,244,9,12,1,13,3,13,247,8,13,1,13,
  	1,13,1,14,1,14,1,14,3,14,254,8,14,1,14,1,14,3,14,258,8,14,1,15,1,15,1,
  	15,1,15,1,15,1,15,5,15,266,8,15,10,15,12,15,269,9,15,1,15,3,15,272,8,
  	15,1,16,1,16,1,16,1,16,3,16,278,8,16,1,16,1,16,3,16,282,8,16,1,17,1,17,
  	1,17,1,17,1,18,1,18,1,18,3,18,291,8,18,1,18,1,18,1,18,5,18,296,8,18,10,
  	18,12,18,299,9,18,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,1,19,3,19,310,
  	8,19,1,20,1,20,1,20,1,20,1,20,1,20,3,20,318,8,20,1,21,1,21,1,22,1,22,
  	1,22,1,22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,25,1,25,1,25,1,25,1,26,
  	3,26,338,8,26,1,26,1,26,1,27,1,27,1,27,1,27,1,28,1,28,3,28,348,8,28,1,
  	29,1,29,3,29,352,8,29,1,30,1,30,3,30,356,8,30,1,31,1,31,1,31,1,31,1,31,
  	1,31,1,31,1,31,3,31,366,8,31,1,31,1,31,1,31,1,31,3,31,372,8,31,3,31,374,
  	8,31,1,32,1,32,3,32,378,8,32,1,32,1,32,1,32,3,32,383,8,32,5,32,385,8,
  	32,10,32,12,32,388,9,32,1,33,1,33,1,33,5,33,393,8,33,10,33,12,33,396,
  	9,33,1,33,1,33,1,34,1,34,1,34,1,34,1,35,1,35,1,35,1,35,5,35,408,8,35,
  	10,35,12,35,411,9,35,1,35,1,35,1,36,1,36,1,36,1,36,3,36,419,8,36,1,37,
  	1,37,1,37,3,37,424,8,37,1,37,1,37,1,38,1,38,1,39,3,39,431,8,39,1,39,1,
  	39,3,39,435,8,39,1,39,1,39,3,39,439,8,39,1,40,1,40,3,40,443,8,40,1,40,
  	1,40,1,40,1,40,1,40,3,40,450,8,40,1,41,1,41,1,41,3,41,455,8,41,1,41,1,
  	41,1,42,1,42,1,43,1,43,1,43,1,43,3,43,465,8,43,1,44,1,44,1,44,1,44,1,
  	44,1,45,1,45,1,46,1,46,1,47,1,47,1,47,1,48,1,48,1,48,1,49,1,49,1,49,1,
  	50,1,50,3,50,487,8,50,1,51,1,51,3,51,491,8,51,1,52,1,52,1,52,1,52,5,52,
  	497,8,52,10,52,12,52,500,9,52,1,52,3,52,503,8,52,3,52,505,8,52,1,52,1,
  	52,1,53,3,53,510,8,53,1,53,1,53,1,54,1,54,1,54,1,54,3,54,518,8,54,1,54,
  	1,54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,1,54,
  	5,54,535,8,54,10,54,12,54,538,9,54,1,55,1,55,5,55,542,8,55,10,55,12,55,
  	545,9,55,1,56,1,56,1,56,1,56,3,56,551,8,56,1,56,1,56,1,57,1,57,1,57,3,
  	57,558,8,57,1,57,1,57,1,57,1,57,3,57,564,8,57,1,58,1,58,1,58,3,58,569,
  	8,58,1,59,1,59,1,59,1,59,3,59,575,8,59,1,60,1,60,1,61,1,61,1,62,1,62,
  	1,62,1,63,1,63,1,63,3,63,587,8,63,3,63,589,8,63,1,64,1,64,1,64,3,64,594,
  	8,64,3,64,596,8,64,1,64,1,64,1,65,1,65,1,65,5,65,603,8,65,10,65,12,65,
  	606,9,65,1,66,1,66,1,66,3,66,611,8,66,1,66,1,66,1,67,1,67,3,67,617,8,
  	67,1,68,1,68,3,68,621,8,68,1,69,1,69,1,70,1,70,1,70,1,70,1,71,1,71,1,
  	71,1,71,1,72,1,72,1,72,1,72,1,72,3,72,638,8,72,3,72,640,8,72,1,72,3,72,
  	643,8,72,3,72,645,8,72,1,72,1,72,1,73,1,73,1,73,0,1,108,74,0,2,4,6,8,
  	10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,
  	56,58,60,62,64,66,68,70,72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,
  	102,104,106,108,110,112,114,116,118,120,122,124,126,128,130,132,134,136,
  	138,140,142,144,146,0,9,1,0,28,29,2,0,39,44,47,51,2,0,26,26,77,77,1,0,
  	46,51,2,0,40,44,50,51,2,0,39,39,47,49,1,0,33,38,2,0,54,57,61,62,1,0,68,
  	69,674,0,157,1,0,0,0,2,162,1,0,0,0,4,166,1,0,0,0,6,168,1,0,0,0,8,182,
  	1,0,0,0,10,190,1,0,0,0,12,198,1,0,0,0,14,208,1,0,0,0,16,210,1,0,0,0,18,
  	217,1,0,0,0,20,223,1,0,0,0,22,234,1,0,0,0,24,237,1,0,0,0,26,246,1,0,0,
  	0,28,250,1,0,0,0,30,259,1,0,0,0,32,273,1,0,0,0,34,283,1,0,0,0,36,297,
  	1,0,0,0,38,309,1,0,0,0,40,317,1,0,0,0,42,319,1,0,0,0,44,321,1,0,0,0,46,
  	325,1,0,0,0,48,329,1,0,0,0,50,332,1,0,0,0,52,337,1,0,0,0,54,341,1,0,0,
  	0,56,345,1,0,0,0,58,349,1,0,0,0,60,353,1,0,0,0,62,357,1,0,0,0,64,377,
  	1,0,0,0,66,389,1,0,0,0,68,399,1,0,0,0,70,403,1,0,0,0,72,414,1,0,0,0,74,
  	420,1,0,0,0,76,427,1,0,0,0,78,430,1,0,0,0,80,449,1,0,0,0,82,451,1,0,0,
  	0,84,458,1,0,0,0,86,464,1,0,0,0,88,466,1,0,0,0,90,471,1,0,0,0,92,473,
  	1,0,0,0,94,475,1,0,0,0,96,478,1,0,0,0,98,481,1,0,0,0,100,484,1,0,0,0,
  	102,490,1,0,0,0,104,492,1,0,0,0,106,509,1,0,0,0,108,517,1,0,0,0,110,539,
  	1,0,0,0,112,546,1,0,0,0,114,563,1,0,0,0,116,568,1,0,0,0,118,574,1,0,0,
  	0,120,576,1,0,0,0,122,578,1,0,0,0,124,580,1,0,0,0,126,588,1,0,0,0,128,
  	590,1,0,0,0,130,599,1,0,0,0,132,610,1,0,0,0,134,616,1,0,0,0,136,620,1,
  	0,0,0,138,622,1,0,0,0,140,624,1,0,0,0,142,628,1,0,0,0,144,632,1,0,0,0,
  	146,648,1,0,0,0,148,152,3,28,14,0,149,152,3,4,2,0,150,152,3,38,19,0,151,
  	148,1,0,0,0,151,149,1,0,0,0,151,150,1,0,0,0,152,153,1,0,0,0,153,154,3,
  	146,73,0,154,156,1,0,0,0,155,151,1,0,0,0,156,159,1,0,0,0,157,155,1,0,
  	0,0,157,158,1,0,0,0,158,160,1,0,0,0,159,157,1,0,0,0,160,161,5,0,0,1,161,
  	1,1,0,0,0,162,163,5,17,0,0,163,3,1,0,0,0,164,167,3,6,3,0,165,167,3,30,
  	15,0,166,164,1,0,0,0,166,165,1,0,0,0,167,5,1,0,0,0,168,180,5,5,0,0,169,
  	181,3,8,4,0,170,176,5,18,0,0,171,172,3,8,4,0,172,173,3,146,73,0,173,175,
  	1,0,0,0,174,171,1,0,0,0,175,178,1,0,0,0,176,174,1,0,0,0,176,177,1,0,0,
  	0,177,179,1,0,0,0,178,176,1,0,0,0,179,181,5,19,0,0,180,169,1,0,0,0,180,
  	170,1,0,0,0,181,7,1,0,0,0,182,188,3,10,5,0,183,185,3,80,40,0,184,183,
  	1,0,0,0,184,185,1,0,0,0,185,186,1,0,0,0,186,187,5,24,0,0,187,189,3,12,
  	6,0,188,184,1,0,0,0,188,189,1,0,0,0,189,9,1,0,0,0,190,195,5,17,0,0,191,
  	192,5,25,0,0,192,194,5,17,0,0,193,191,1,0,0,0,194,197,1,0,0,0,195,193,
  	1,0,0,0,195,196,1,0,0,0,196,11,1,0,0,0,197,195,1,0,0,0,198,203,3,108,
  	54,0,199,200,5,25,0,0,200,202,3,108,54,0,201,199,1,0,0,0,202,205,1,0,
  	0,0,203,201,1,0,0,0,203,204,1,0,0,0,204,13,1,0,0,0,205,203,1,0,0,0,206,
  	209,3,16,8,0,207,209,3,18,9,0,208,206,1,0,0,0,208,207,1,0,0,0,209,15,
  	1,0,0,0,210,212,5,17,0,0,211,213,3,20,10,0,212,211,1,0,0,0,212,213,1,
  	0,0,0,213,214,1,0,0,0,214,215,5,24,0,0,215,216,3,80,40,0,216,17,1,0,0,
  	0,217,219,5,17,0,0,218,220,3,20,10,0,219,218,1,0,0,0,219,220,1,0,0,0,
  	220,221,1,0,0,0,221,222,3,80,40,0,222,19,1,0,0,0,223,224,5,22,0,0,224,
  	229,3,22,11,0,225,226,5,25,0,0,226,228,3,22,11,0,227,225,1,0,0,0,228,
  	231,1,0,0,0,229,227,1,0,0,0,229,230,1,0,0,0,230,232,1,0,0,0,231,229,1,
  	0,0,0,232,233,5,23,0,0,233,21,1,0,0,0,234,235,3,10,5,0,235,236,3,24,12,
  	0,236,23,1,0,0,0,237,242,3,26,13,0,238,239,5,39,0,0,239,241,3,26,13,0,
  	240,238,1,0,0,0,241,244,1,0,0,0,242,240,1,0,0,0,242,243,1,0,0,0,243,25,
  	1,0,0,0,244,242,1,0,0,0,245,247,5,45,0,0,246,245,1,0,0,0,246,247,1,0,
  	0,0,247,248,1,0,0,0,248,249,3,80,40,0,249,27,1,0,0,0,250,251,5,10,0,0,
  	251,253,5,17,0,0,252,254,3,20,10,0,253,252,1,0,0,0,253,254,1,0,0,0,254,
  	255,1,0,0,0,255,257,3,100,50,0,256,258,3,34,17,0,257,256,1,0,0,0,257,
  	258,1,0,0,0,258,29,1,0,0,0,259,271,5,16,0,0,260,272,3,32,16,0,261,267,
  	5,18,0,0,262,263,3,32,16,0,263,264,3,146,73,0,264,266,1,0,0,0,265,262,
  	1,0,0,0,266,269,1,0,0,0,267,265,1,0,0,0,267,268,1,0,0,0,268,270,1,0,0,
  	0,269,267,1,0,0,0,270,272,5,19,0,0,271,260,1,0,0,0,271,261,1,0,0,0,272,
  	31,1,0,0,0,273,281,3,10,5,0,274,277,3,80,40,0,275,276,5,24,0,0,276,278,
  	3,12,6,0,277,275,1,0,0,0,277,278,1,0,0,0,278,282,1,0,0,0,279,280,5,24,
  	0,0,280,282,3,12,6,0,281,274,1,0,0,0,281,279,1,0,0,0,282,33,1,0,0,0,283,
  	284,5,20,0,0,284,285,3,36,18,0,285,286,5,21,0,0,286,35,1,0,0,0,287,291,
  	5,26,0,0,288,291,5,77,0,0,289,291,1,0,0,0,290,287,1,0,0,0,290,288,1,0,
  	0,0,290,289,1,0,0,0,291,292,1,0,0,0,292,293,3,38,19,0,293,294,3,146,73,
  	0,294,296,1,0,0,0,295,290,1,0,0,0,296,299,1,0,0,0,297,295,1,0,0,0,297,
  	298,1,0,0,0,298,37,1,0,0,0,299,297,1,0,0,0,300,310,3,4,2,0,301,310,3,
  	40,20,0,302,310,3,56,28,0,303,310,3,58,29,0,304,310,3,60,30,0,305,310,
  	3,34,17,0,306,310,3,62,31,0,307,310,3,66,33,0,308,310,3,74,37,0,309,300,
  	1,0,0,0,309,301,1,0,0,0,309,302,1,0,0,0,309,303,1,0,0,0,309,304,1,0,0,
  	0,309,305,1,0,0,0,309,306,1,0,0,0,309,307,1,0,0,0,309,308,1,0,0,0,310,
  	39,1,0,0,0,311,318,3,46,23,0,312,318,3,44,22,0,313,318,3,48,24,0,314,
  	318,3,50,25,0,315,318,3,42,21,0,316,318,3,54,27,0,317,311,1,0,0,0,317,
  	312,1,0,0,0,317,313,1,0,0,0,317,314,1,0,0,0,317,315,1,0,0,0,317,316,1,
  	0,0,0,318,41,1,0,0,0,319,320,3,108,54,0,320,43,1,0,0,0,321,322,3,108,
  	54,0,322,323,5,53,0,0,323,324,3,108,54,0,324,45,1,0,0,0,325,326,3,108,
  	54,0,326,327,5,52,0,0,327,328,3,108,54,0,328,47,1,0,0,0,329,330,3,108,
  	54,0,330,331,7,0,0,0,331,49,1,0,0,0,332,333,3,12,6,0,333,334,3,52,26,
  	0,334,335,3,12,6,0,335,51,1,0,0,0,336,338,7,1,0,0,337,336,1,0,0,0,337,
  	338,1,0,0,0,338,339,1,0,0,0,339,340,5,24,0,0,340,53,1,0,0,0,341,342,3,
  	10,5,0,342,343,5,30,0,0,343,344,3,12,6,0,344,55,1,0,0,0,345,347,5,14,
  	0,0,346,348,3,12,6,0,347,346,1,0,0,0,347,348,1,0,0,0,348,57,1,0,0,0,349,
  	351,5,3,0,0,350,352,5,17,0,0,351,350,1,0,0,0,351,352,1,0,0,0,352,59,1,
  	0,0,0,353,355,5,6,0,0,354,356,5,17,0,0,355,354,1,0,0,0,355,356,1,0,0,
  	0,356,61,1,0,0,0,357,365,5,12,0,0,358,366,3,108,54,0,359,360,7,2,0,0,
  	360,366,3,108,54,0,361,362,3,40,20,0,362,363,7,2,0,0,363,364,3,108,54,
  	0,364,366,1,0,0,0,365,358,1,0,0,0,365,359,1,0,0,0,365,361,1,0,0,0,366,
  	367,1,0,0,0,367,373,3,34,17,0,368,371,5,7,0,0,369,372,3,62,31,0,370,372,
  	3,34,17,0,371,369,1,0,0,0,371,370,1,0,0,0,372,374,1,0,0,0,373,368,1,0,
  	0,0,373,374,1,0,0,0,374,63,1,0,0,0,375,378,3,80,40,0,376,378,5,13,0,0,
  	377,375,1,0,0,0,377,376,1,0,0,0,378,386,1,0,0,0,379,382,5,25,0,0,380,
  	383,3,80,40,0,381,383,5,13,0,0,382,380,1,0,0,0,382,381,1,0,0,0,383,385,
  	1,0,0,0,384,379,1,0,0,0,385,388,1,0,0,0,386,384,1,0,0,0,386,387,1,0,0,
  	0,387,65,1,0,0,0,388,386,1,0,0,0,389,390,5,11,0,0,390,394,5,20,0,0,391,
  	393,3,68,34,0,392,391,1,0,0,0,393,396,1,0,0,0,394,392,1,0,0,0,394,395,
  	1,0,0,0,395,397,1,0,0,0,396,394,1,0,0,0,397,398,5,21,0,0,398,67,1,0,0,
  	0,399,400,3,70,35,0,400,401,5,27,0,0,401,402,3,36,18,0,402,69,1,0,0,0,
  	403,409,5,4,0,0,404,405,3,72,36,0,405,406,5,25,0,0,406,408,1,0,0,0,407,
  	404,1,0,0,0,408,411,1,0,0,0,409,407,1,0,0,0,409,410,1,0,0,0,410,412,1,
  	0,0,0,411,409,1,0,0,0,412,413,3,72,36,0,413,71,1,0,0,0,414,415,5,9,0,
  	0,415,418,5,17,0,0,416,417,5,1,0,0,417,419,5,17,0,0,418,416,1,0,0,0,418,
  	419,1,0,0,0,419,73,1,0,0,0,420,423,5,8,0,0,421,424,3,76,38,0,422,424,
  	3,78,39,0,423,421,1,0,0,0,423,422,1,0,0,0,423,424,1,0,0,0,424,425,1,0,
  	0,0,425,426,3,34,17,0,426,75,1,0,0,0,427,428,3,108,54,0,428,77,1,0,0,
  	0,429,431,3,40,20,0,430,429,1,0,0,0,430,431,1,0,0,0,431,432,1,0,0,0,432,
  	434,3,146,73,0,433,435,3,108,54,0,434,433,1,0,0,0,434,435,1,0,0,0,435,
  	436,1,0,0,0,436,438,3,146,73,0,437,439,3,40,20,0,438,437,1,0,0,0,438,
  	439,1,0,0,0,439,79,1,0,0,0,440,442,3,84,42,0,441,443,3,82,41,0,442,441,
  	1,0,0,0,442,443,1,0,0,0,443,450,1,0,0,0,444,450,3,86,43,0,445,446,5,18,
  	0,0,446,447,3,80,40,0,447,448,5,19,0,0,448,450,1,0,0,0,449,440,1,0,0,
  	0,449,444,1,0,0,0,449,445,1,0,0,0,450,81,1,0,0,0,451,452,5,22,0,0,452,
  	454,3,64,32,0,453,455,5,25,0,0,454,453,1,0,0,0,454,455,1,0,0,0,455,456,
  	1,0,0,0,456,457,5,23,0,0,457,83,1,0,0,0,458,459,5,17,0,0,459,85,1,0,0,
  	0,460,465,3,88,44,0,461,465,3,98,49,0,462,465,3,96,48,0,463,465,3,94,
  	47,0,464,460,1,0,0,0,464,461,1,0,0,0,464,462,1,0,0,0,464,463,1,0,0,0,
  	465,87,1,0,0,0,466,467,5,22,0,0,467,468,3,90,45,0,468,469,5,23,0,0,469,
  	470,3,92,46,0,470,89,1,0,0,0,471,472,3,108,54,0,472,91,1,0,0,0,473,474,
  	3,80,40,0,474,93,1,0,0,0,475,476,5,2,0,0,476,477,3,92,46,0,477,95,1,0,
  	0,0,478,479,5,15,0,0,479,480,3,100,50,0,480,97,1,0,0,0,481,482,5,10,0,
  	0,482,483,3,100,50,0,483,99,1,0,0,0,484,486,3,104,52,0,485,487,3,102,
  	51,0,486,485,1,0,0,0,486,487,1,0,0,0,487,101,1,0,0,0,488,491,3,104,52,
  	0,489,491,3,80,40,0,490,488,1,0,0,0,490,489,1,0,0,0,491,103,1,0,0,0,492,
  	504,5,18,0,0,493,498,3,106,53,0,494,495,5,25,0,0,495,497,3,106,53,0,496,
  	494,1,0,0,0,497,500,1,0,0,0,498,496,1,0,0,0,498,499,1,0,0,0,499,502,1,
  	0,0,0,500,498,1,0,0,0,501,503,5,25,0,0,502,501,1,0,0,0,502,503,1,0,0,
  	0,503,505,1,0,0,0,504,493,1,0,0,0,504,505,1,0,0,0,505,506,1,0,0,0,506,
  	507,5,19,0,0,507,105,1,0,0,0,508,510,3,10,5,0,509,508,1,0,0,0,509,510,
  	1,0,0,0,510,511,1,0,0,0,511,512,3,80,40,0,512,107,1,0,0,0,513,514,6,54,
  	-1,0,514,518,3,110,55,0,515,516,7,3,0,0,516,518,3,108,54,6,517,513,1,
  	0,0,0,517,515,1,0,0,0,518,536,1,0,0,0,519,520,10,5,0,0,520,521,7,4,0,
  	0,521,535,3,108,54,6,522,523,10,4,0,0,523,524,7,5,0,0,524,535,3,108,54,
  	5,525,526,10,3,0,0,526,527,7,6,0,0,527,535,3,108,54,4,528,529,10,2,0,
  	0,529,530,5,32,0,0,530,535,3,108,54,3,531,532,10,1,0,0,532,533,5,31,0,
  	0,533,535,3,108,54,2,534,519,1,0,0,0,534,522,1,0,0,0,534,525,1,0,0,0,
  	534,528,1,0,0,0,534,531,1,0,0,0,535,538,1,0,0,0,536,534,1,0,0,0,536,537,
  	1,0,0,0,537,109,1,0,0,0,538,536,1,0,0,0,539,543,3,114,57,0,540,542,3,
  	144,72,0,541,540,1,0,0,0,542,545,1,0,0,0,543,541,1,0,0,0,543,544,1,0,
  	0,0,544,111,1,0,0,0,545,543,1,0,0,0,546,547,3,80,40,0,547,548,5,18,0,
  	0,548,550,3,108,54,0,549,551,5,25,0,0,550,549,1,0,0,0,550,551,1,0,0,0,
  	551,552,1,0,0,0,552,553,5,19,0,0,553,113,1,0,0,0,554,564,3,116,58,0,555,
  	557,3,122,61,0,556,558,3,82,41,0,557,556,1,0,0,0,557,558,1,0,0,0,558,
  	564,1,0,0,0,559,560,5,18,0,0,560,561,3,108,54,0,561,562,5,19,0,0,562,
  	564,1,0,0,0,563,554,1,0,0,0,563,555,1,0,0,0,563,559,1,0,0,0,564,115,1,
  	0,0,0,565,569,3,118,59,0,566,569,3,124,62,0,567,569,3,140,70,0,568,565,
  	1,0,0,0,568,566,1,0,0,0,568,567,1,0,0,0,569,117,1,0,0,0,570,575,5,13,
  	0,0,571,575,3,120,60,0,572,575,3,138,69,0,573,575,5,58,0,0,574,570,1,
  	0,0,0,574,571,1,0,0,0,574,572,1,0,0,0,574,573,1,0,0,0,575,119,1,0,0,0,
  	576,577,7,7,0,0,577,121,1,0,0,0,578,579,5,17,0,0,579,123,1,0,0,0,580,
  	581,3,126,63,0,581,582,3,128,64,0,582,125,1,0,0,0,583,589,3,88,44,0,584,
  	586,3,84,42,0,585,587,3,82,41,0,586,585,1,0,0,0,586,587,1,0,0,0,587,589,
  	1,0,0,0,588,583,1,0,0,0,588,584,1,0,0,0,589,127,1,0,0,0,590,595,5,20,
  	0,0,591,593,3,130,65,0,592,594,5,25,0,0,593,592,1,0,0,0,593,594,1,0,0,
  	0,594,596,1,0,0,0,595,591,1,0,0,0,595,596,1,0,0,0,596,597,1,0,0,0,597,
  	598,5,21,0,0,598,129,1,0,0,0,599,604,3,132,66,0,600,601,5,25,0,0,601,
  	603,3,132,66,0,602,600,1,0,0,0,603,606,1,0,0,0,604,602,1,0,0,0,604,605,
  	1,0,0,0,605,131,1,0,0,0,606,604,1,0,0,0,607,608,3,134,67,0,608,609,5,
  	27,0,0,609,611,1,0,0,0,610,607,1,0,0,0,610,611,1,0,0,0,611,612,1,0,0,
  	0,612,613,3,136,68,0,613,133,1,0,0,0,614,617,3,108,54,0,615,617,3,128,
  	64,0,616,614,1,0,0,0,616,615,1,0,0,0,617,135,1,0,0,0,618,621,3,108,54,
  	0,619,621,3,128,64,0,620,618,1,0,0,0,620,619,1,0,0,0,621,137,1,0,0,0,
  	622,623,7,8,0,0,623,139,1,0,0,0,624,625,5,10,0,0,625,626,3,100,50,0,626,
  	627,3,34,17,0,627,141,1,0,0,0,628,629,5,22,0,0,629,630,3,108,54,0,630,
  	631,5,23,0,0,631,143,1,0,0,0,632,644,5,18,0,0,633,640,3,12,6,0,634,637,
  	3,80,40,0,635,636,5,25,0,0,636,638,3,12,6,0,637,635,1,0,0,0,637,638,1,
  	0,0,0,638,640,1,0,0,0,639,633,1,0,0,0,639,634,1,0,0,0,640,642,1,0,0,0,
  	641,643,5,25,0,0,642,641,1,0,0,0,642,643,1,0,0,0,643,645,1,0,0,0,644,
  	639,1,0,0,0,644,645,1,0,0,0,645,646,1,0,0,0,646,647,5,19,0,0,647,145,
  	1,0,0,0,648,649,7,2,0,0,649,147,1,0,0,0,73,151,157,166,176,180,184,188,
  	195,203,208,212,219,229,242,246,253,257,267,271,277,281,290,297,309,317,
  	337,347,351,355,365,371,373,377,382,386,394,409,418,423,430,434,438,442,
  	449,454,464,486,490,498,502,504,509,517,534,536,543,550,557,563,568,574,
  	586,588,593,595,604,610,616,620,637,639,642,644
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  tparserParserStaticData = std::move(staticData);
}

}

TParser::TParser(TokenStream *input) : TParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

TParser::TParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  TParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *tparserParserStaticData->atn, tparserParserStaticData->decisionToDFA, tparserParserStaticData->sharedContextCache, options);
}

TParser::~TParser() {
  delete _interpreter;
}

const atn::ATN& TParser::getATN() const {
  return *tparserParserStaticData->atn;
}

std::string TParser::getGrammarFileName() const {
  return "TParser.g4";
}

const std::vector<std::string>& TParser::getRuleNames() const {
  return tparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& TParser::getVocabulary() const {
  return tparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView TParser::getSerializedATN() const {
  return tparserParserStaticData->serializedATN;
}

/* parser definitions section */

//----------------- SourceFileContext ------------------------------------------------------------------

TParser::SourceFileContext::SourceFileContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::SourceFileContext::EOF() {
  return getToken(TParser::EOF, 0);
}

std::vector<TParser::EosContext *> TParser::SourceFileContext::eos() {
  return getRuleContexts<TParser::EosContext>();
}

TParser::EosContext* TParser::SourceFileContext::eos(size_t i) {
  return getRuleContext<TParser::EosContext>(i);
}

std::vector<TParser::FunctionDeclContext *> TParser::SourceFileContext::functionDecl() {
  return getRuleContexts<TParser::FunctionDeclContext>();
}

TParser::FunctionDeclContext* TParser::SourceFileContext::functionDecl(size_t i) {
  return getRuleContext<TParser::FunctionDeclContext>(i);
}

std::vector<TParser::DeclarationContext *> TParser::SourceFileContext::declaration() {
  return getRuleContexts<TParser::DeclarationContext>();
}

TParser::DeclarationContext* TParser::SourceFileContext::declaration(size_t i) {
  return getRuleContext<TParser::DeclarationContext>(i);
}

std::vector<TParser::StatementContext *> TParser::SourceFileContext::statement() {
  return getRuleContexts<TParser::StatementContext>();
}

TParser::StatementContext* TParser::SourceFileContext::statement(size_t i) {
  return getRuleContext<TParser::StatementContext>(i);
}


size_t TParser::SourceFileContext::getRuleIndex() const {
  return TParser::RuleSourceFile;
}

void TParser::SourceFileContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSourceFile(this);
}

void TParser::SourceFileContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSourceFile(this);
}


std::any TParser::SourceFileContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSourceFile(this);
  else
    return visitor->visitChildren(this);
}

TParser::SourceFileContext* TParser::sourceFile() {
  SourceFileContext *_localctx = _tracker.createInstance<SourceFileContext>(_ctx, getState());
  enterRule(_localctx, 0, TParser::RuleSourceFile);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(157);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7480408612323949928) != 0) || _la == TParser::RAW_STRING_LIT

    || _la == TParser::INTERPRETED_STRING_LIT) {
      setState(151);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(148);
        functionDecl();
        break;
      }

      case 2: {
        setState(149);
        declaration();
        break;
      }

      case 3: {
        setState(150);
        statement();
        break;
      }

      default:
        break;
      }
      setState(153);
      eos();
      setState(159);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(160);
    match(TParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

TParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::IdentifierContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}


size_t TParser::IdentifierContext::getRuleIndex() const {
  return TParser::RuleIdentifier;
}

void TParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void TParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


std::any TParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

TParser::IdentifierContext* TParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 2, TParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    match(TParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

TParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ConstDeclContext* TParser::DeclarationContext::constDecl() {
  return getRuleContext<TParser::ConstDeclContext>(0);
}

TParser::VarDeclContext* TParser::DeclarationContext::varDecl() {
  return getRuleContext<TParser::VarDeclContext>(0);
}


size_t TParser::DeclarationContext::getRuleIndex() const {
  return TParser::RuleDeclaration;
}

void TParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void TParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


std::any TParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

TParser::DeclarationContext* TParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, TParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(166);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(164);
        constDecl();
        break;
      }

      case TParser::VAR: {
        enterOuterAlt(_localctx, 2);
        setState(165);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

TParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ConstDeclContext::CONST() {
  return getToken(TParser::CONST, 0);
}

std::vector<TParser::ConstSpecContext *> TParser::ConstDeclContext::constSpec() {
  return getRuleContexts<TParser::ConstSpecContext>();
}

TParser::ConstSpecContext* TParser::ConstDeclContext::constSpec(size_t i) {
  return getRuleContext<TParser::ConstSpecContext>(i);
}

tree::TerminalNode* TParser::ConstDeclContext::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

tree::TerminalNode* TParser::ConstDeclContext::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}

std::vector<TParser::EosContext *> TParser::ConstDeclContext::eos() {
  return getRuleContexts<TParser::EosContext>();
}

TParser::EosContext* TParser::ConstDeclContext::eos(size_t i) {
  return getRuleContext<TParser::EosContext>(i);
}


size_t TParser::ConstDeclContext::getRuleIndex() const {
  return TParser::RuleConstDecl;
}

void TParser::ConstDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstDecl(this);
}

void TParser::ConstDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstDecl(this);
}


std::any TParser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::ConstDeclContext* TParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, TParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(168);
    match(TParser::CONST);
    setState(180);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::IDENTIFIER: {
        setState(169);
        constSpec();
        break;
      }

      case TParser::L_PAREN: {
        setState(170);
        match(TParser::L_PAREN);
        setState(176);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == TParser::IDENTIFIER) {
          setState(171);
          constSpec();
          setState(172);
          eos();
          setState(178);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(179);
        match(TParser::R_PAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstSpecContext ------------------------------------------------------------------

TParser::ConstSpecContext::ConstSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::IdentifierListContext* TParser::ConstSpecContext::identifierList() {
  return getRuleContext<TParser::IdentifierListContext>(0);
}

tree::TerminalNode* TParser::ConstSpecContext::ASSIGN() {
  return getToken(TParser::ASSIGN, 0);
}

TParser::ExpressionListContext* TParser::ConstSpecContext::expressionList() {
  return getRuleContext<TParser::ExpressionListContext>(0);
}

TParser::Type_Context* TParser::ConstSpecContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}


size_t TParser::ConstSpecContext::getRuleIndex() const {
  return TParser::RuleConstSpec;
}

void TParser::ConstSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstSpec(this);
}

void TParser::ConstSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstSpec(this);
}


std::any TParser::ConstSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitConstSpec(this);
  else
    return visitor->visitChildren(this);
}

TParser::ConstSpecContext* TParser::constSpec() {
  ConstSpecContext *_localctx = _tracker.createInstance<ConstSpecContext>(_ctx, getState());
  enterRule(_localctx, 8, TParser::RuleConstSpec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(182);
    identifierList();
    setState(188);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 21398532) != 0)) {
      setState(184);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4621316) != 0)) {
        setState(183);
        type_();
      }
      setState(186);
      match(TParser::ASSIGN);
      setState(187);
      expressionList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierListContext ------------------------------------------------------------------

TParser::IdentifierListContext::IdentifierListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TParser::IdentifierListContext::IDENTIFIER() {
  return getTokens(TParser::IDENTIFIER);
}

tree::TerminalNode* TParser::IdentifierListContext::IDENTIFIER(size_t i) {
  return getToken(TParser::IDENTIFIER, i);
}

std::vector<tree::TerminalNode *> TParser::IdentifierListContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::IdentifierListContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::IdentifierListContext::getRuleIndex() const {
  return TParser::RuleIdentifierList;
}

void TParser::IdentifierListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierList(this);
}

void TParser::IdentifierListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierList(this);
}


std::any TParser::IdentifierListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIdentifierList(this);
  else
    return visitor->visitChildren(this);
}

TParser::IdentifierListContext* TParser::identifierList() {
  IdentifierListContext *_localctx = _tracker.createInstance<IdentifierListContext>(_ctx, getState());
  enterRule(_localctx, 10, TParser::RuleIdentifierList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(190);
    match(TParser::IDENTIFIER);
    setState(195);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::COMMA) {
      setState(191);
      match(TParser::COMMA);
      setState(192);
      match(TParser::IDENTIFIER);
      setState(197);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionListContext ------------------------------------------------------------------

TParser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TParser::ExpressionContext *> TParser::ExpressionListContext::expression() {
  return getRuleContexts<TParser::ExpressionContext>();
}

TParser::ExpressionContext* TParser::ExpressionListContext::expression(size_t i) {
  return getRuleContext<TParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> TParser::ExpressionListContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::ExpressionListContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::ExpressionListContext::getRuleIndex() const {
  return TParser::RuleExpressionList;
}

void TParser::ExpressionListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionList(this);
}

void TParser::ExpressionListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionList(this);
}


std::any TParser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitExpressionList(this);
  else
    return visitor->visitChildren(this);
}

TParser::ExpressionListContext* TParser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 12, TParser::RuleExpressionList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(198);
    expression(0);
    setState(203);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(199);
        match(TParser::COMMA);
        setState(200);
        expression(0); 
      }
      setState(205);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecContext ------------------------------------------------------------------

TParser::TypeSpecContext::TypeSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::AliasDeclContext* TParser::TypeSpecContext::aliasDecl() {
  return getRuleContext<TParser::AliasDeclContext>(0);
}

TParser::TypeDefContext* TParser::TypeSpecContext::typeDef() {
  return getRuleContext<TParser::TypeDefContext>(0);
}


size_t TParser::TypeSpecContext::getRuleIndex() const {
  return TParser::RuleTypeSpec;
}

void TParser::TypeSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpec(this);
}

void TParser::TypeSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpec(this);
}


std::any TParser::TypeSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeSpec(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeSpecContext* TParser::typeSpec() {
  TypeSpecContext *_localctx = _tracker.createInstance<TypeSpecContext>(_ctx, getState());
  enterRule(_localctx, 14, TParser::RuleTypeSpec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(208);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(206);
      aliasDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(207);
      typeDef();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AliasDeclContext ------------------------------------------------------------------

TParser::AliasDeclContext::AliasDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::AliasDeclContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}

tree::TerminalNode* TParser::AliasDeclContext::ASSIGN() {
  return getToken(TParser::ASSIGN, 0);
}

TParser::Type_Context* TParser::AliasDeclContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

TParser::TypeParametersContext* TParser::AliasDeclContext::typeParameters() {
  return getRuleContext<TParser::TypeParametersContext>(0);
}


size_t TParser::AliasDeclContext::getRuleIndex() const {
  return TParser::RuleAliasDecl;
}

void TParser::AliasDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAliasDecl(this);
}

void TParser::AliasDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAliasDecl(this);
}


std::any TParser::AliasDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAliasDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::AliasDeclContext* TParser::aliasDecl() {
  AliasDeclContext *_localctx = _tracker.createInstance<AliasDeclContext>(_ctx, getState());
  enterRule(_localctx, 16, TParser::RuleAliasDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(210);
    match(TParser::IDENTIFIER);
    setState(212);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::L_BRACKET) {
      setState(211);
      typeParameters();
    }
    setState(214);
    match(TParser::ASSIGN);
    setState(215);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeDefContext ------------------------------------------------------------------

TParser::TypeDefContext::TypeDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::TypeDefContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}

TParser::Type_Context* TParser::TypeDefContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

TParser::TypeParametersContext* TParser::TypeDefContext::typeParameters() {
  return getRuleContext<TParser::TypeParametersContext>(0);
}


size_t TParser::TypeDefContext::getRuleIndex() const {
  return TParser::RuleTypeDef;
}

void TParser::TypeDefContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeDef(this);
}

void TParser::TypeDefContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeDef(this);
}


std::any TParser::TypeDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeDef(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeDefContext* TParser::typeDef() {
  TypeDefContext *_localctx = _tracker.createInstance<TypeDefContext>(_ctx, getState());
  enterRule(_localctx, 18, TParser::RuleTypeDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    match(TParser::IDENTIFIER);
    setState(219);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(218);
      typeParameters();
      break;
    }

    default:
      break;
    }
    setState(221);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeParametersContext ------------------------------------------------------------------

TParser::TypeParametersContext::TypeParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::TypeParametersContext::L_BRACKET() {
  return getToken(TParser::L_BRACKET, 0);
}

std::vector<TParser::TypeParameterDeclContext *> TParser::TypeParametersContext::typeParameterDecl() {
  return getRuleContexts<TParser::TypeParameterDeclContext>();
}

TParser::TypeParameterDeclContext* TParser::TypeParametersContext::typeParameterDecl(size_t i) {
  return getRuleContext<TParser::TypeParameterDeclContext>(i);
}

tree::TerminalNode* TParser::TypeParametersContext::R_BRACKET() {
  return getToken(TParser::R_BRACKET, 0);
}

std::vector<tree::TerminalNode *> TParser::TypeParametersContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::TypeParametersContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::TypeParametersContext::getRuleIndex() const {
  return TParser::RuleTypeParameters;
}

void TParser::TypeParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeParameters(this);
}

void TParser::TypeParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeParameters(this);
}


std::any TParser::TypeParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeParameters(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeParametersContext* TParser::typeParameters() {
  TypeParametersContext *_localctx = _tracker.createInstance<TypeParametersContext>(_ctx, getState());
  enterRule(_localctx, 20, TParser::RuleTypeParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    match(TParser::L_BRACKET);
    setState(224);
    typeParameterDecl();
    setState(229);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::COMMA) {
      setState(225);
      match(TParser::COMMA);
      setState(226);
      typeParameterDecl();
      setState(231);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(232);
    match(TParser::R_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeParameterDeclContext ------------------------------------------------------------------

TParser::TypeParameterDeclContext::TypeParameterDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::IdentifierListContext* TParser::TypeParameterDeclContext::identifierList() {
  return getRuleContext<TParser::IdentifierListContext>(0);
}

TParser::TypeElementContext* TParser::TypeParameterDeclContext::typeElement() {
  return getRuleContext<TParser::TypeElementContext>(0);
}


size_t TParser::TypeParameterDeclContext::getRuleIndex() const {
  return TParser::RuleTypeParameterDecl;
}

void TParser::TypeParameterDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeParameterDecl(this);
}

void TParser::TypeParameterDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeParameterDecl(this);
}


std::any TParser::TypeParameterDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeParameterDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeParameterDeclContext* TParser::typeParameterDecl() {
  TypeParameterDeclContext *_localctx = _tracker.createInstance<TypeParameterDeclContext>(_ctx, getState());
  enterRule(_localctx, 22, TParser::RuleTypeParameterDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    identifierList();
    setState(235);
    typeElement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeElementContext ------------------------------------------------------------------

TParser::TypeElementContext::TypeElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TParser::TypeTermContext *> TParser::TypeElementContext::typeTerm() {
  return getRuleContexts<TParser::TypeTermContext>();
}

TParser::TypeTermContext* TParser::TypeElementContext::typeTerm(size_t i) {
  return getRuleContext<TParser::TypeTermContext>(i);
}

std::vector<tree::TerminalNode *> TParser::TypeElementContext::OR() {
  return getTokens(TParser::OR);
}

tree::TerminalNode* TParser::TypeElementContext::OR(size_t i) {
  return getToken(TParser::OR, i);
}


size_t TParser::TypeElementContext::getRuleIndex() const {
  return TParser::RuleTypeElement;
}

void TParser::TypeElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeElement(this);
}

void TParser::TypeElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeElement(this);
}


std::any TParser::TypeElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeElement(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeElementContext* TParser::typeElement() {
  TypeElementContext *_localctx = _tracker.createInstance<TypeElementContext>(_ctx, getState());
  enterRule(_localctx, 24, TParser::RuleTypeElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(237);
    typeTerm();
    setState(242);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::OR) {
      setState(238);
      match(TParser::OR);
      setState(239);
      typeTerm();
      setState(244);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeTermContext ------------------------------------------------------------------

TParser::TypeTermContext::TypeTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::Type_Context* TParser::TypeTermContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

tree::TerminalNode* TParser::TypeTermContext::UNDERLYING() {
  return getToken(TParser::UNDERLYING, 0);
}


size_t TParser::TypeTermContext::getRuleIndex() const {
  return TParser::RuleTypeTerm;
}

void TParser::TypeTermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeTerm(this);
}

void TParser::TypeTermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeTerm(this);
}


std::any TParser::TypeTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeTerm(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeTermContext* TParser::typeTerm() {
  TypeTermContext *_localctx = _tracker.createInstance<TypeTermContext>(_ctx, getState());
  enterRule(_localctx, 26, TParser::RuleTypeTerm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::UNDERLYING) {
      setState(245);
      match(TParser::UNDERLYING);
    }
    setState(248);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDeclContext ------------------------------------------------------------------

TParser::FunctionDeclContext::FunctionDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::FunctionDeclContext::FUNC() {
  return getToken(TParser::FUNC, 0);
}

tree::TerminalNode* TParser::FunctionDeclContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}

TParser::SignatureContext* TParser::FunctionDeclContext::signature() {
  return getRuleContext<TParser::SignatureContext>(0);
}

TParser::TypeParametersContext* TParser::FunctionDeclContext::typeParameters() {
  return getRuleContext<TParser::TypeParametersContext>(0);
}

TParser::BlockContext* TParser::FunctionDeclContext::block() {
  return getRuleContext<TParser::BlockContext>(0);
}


size_t TParser::FunctionDeclContext::getRuleIndex() const {
  return TParser::RuleFunctionDecl;
}

void TParser::FunctionDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionDecl(this);
}

void TParser::FunctionDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionDecl(this);
}


std::any TParser::FunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::FunctionDeclContext* TParser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 28, TParser::RuleFunctionDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(250);
    match(TParser::FUNC);
    setState(251);
    match(TParser::IDENTIFIER);
    setState(253);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::L_BRACKET) {
      setState(252);
      typeParameters();
    }
    setState(255);
    signature();
    setState(257);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::L_CURLY) {
      setState(256);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

TParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::VarDeclContext::VAR() {
  return getToken(TParser::VAR, 0);
}

std::vector<TParser::VarSpecContext *> TParser::VarDeclContext::varSpec() {
  return getRuleContexts<TParser::VarSpecContext>();
}

TParser::VarSpecContext* TParser::VarDeclContext::varSpec(size_t i) {
  return getRuleContext<TParser::VarSpecContext>(i);
}

tree::TerminalNode* TParser::VarDeclContext::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

tree::TerminalNode* TParser::VarDeclContext::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}

std::vector<TParser::EosContext *> TParser::VarDeclContext::eos() {
  return getRuleContexts<TParser::EosContext>();
}

TParser::EosContext* TParser::VarDeclContext::eos(size_t i) {
  return getRuleContext<TParser::EosContext>(i);
}


size_t TParser::VarDeclContext::getRuleIndex() const {
  return TParser::RuleVarDecl;
}

void TParser::VarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarDecl(this);
}

void TParser::VarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarDecl(this);
}


std::any TParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::VarDeclContext* TParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 30, TParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(259);
    match(TParser::VAR);
    setState(271);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::IDENTIFIER: {
        setState(260);
        varSpec();
        break;
      }

      case TParser::L_PAREN: {
        setState(261);
        match(TParser::L_PAREN);
        setState(267);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == TParser::IDENTIFIER) {
          setState(262);
          varSpec();
          setState(263);
          eos();
          setState(269);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(270);
        match(TParser::R_PAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarSpecContext ------------------------------------------------------------------

TParser::VarSpecContext::VarSpecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::IdentifierListContext* TParser::VarSpecContext::identifierList() {
  return getRuleContext<TParser::IdentifierListContext>(0);
}

TParser::Type_Context* TParser::VarSpecContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

tree::TerminalNode* TParser::VarSpecContext::ASSIGN() {
  return getToken(TParser::ASSIGN, 0);
}

TParser::ExpressionListContext* TParser::VarSpecContext::expressionList() {
  return getRuleContext<TParser::ExpressionListContext>(0);
}


size_t TParser::VarSpecContext::getRuleIndex() const {
  return TParser::RuleVarSpec;
}

void TParser::VarSpecContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVarSpec(this);
}

void TParser::VarSpecContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVarSpec(this);
}


std::any TParser::VarSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitVarSpec(this);
  else
    return visitor->visitChildren(this);
}

TParser::VarSpecContext* TParser::varSpec() {
  VarSpecContext *_localctx = _tracker.createInstance<VarSpecContext>(_ctx, getState());
  enterRule(_localctx, 32, TParser::RuleVarSpec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(273);
    identifierList();
    setState(281);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::ASYNC:
      case TParser::FUNC:
      case TParser::SYNC:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET: {
        setState(274);
        type_();
        setState(277);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TParser::ASSIGN) {
          setState(275);
          match(TParser::ASSIGN);
          setState(276);
          expressionList();
        }
        break;
      }

      case TParser::ASSIGN: {
        setState(279);
        match(TParser::ASSIGN);
        setState(280);
        expressionList();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

TParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::BlockContext::L_CURLY() {
  return getToken(TParser::L_CURLY, 0);
}

TParser::StatementListContext* TParser::BlockContext::statementList() {
  return getRuleContext<TParser::StatementListContext>(0);
}

tree::TerminalNode* TParser::BlockContext::R_CURLY() {
  return getToken(TParser::R_CURLY, 0);
}


size_t TParser::BlockContext::getRuleIndex() const {
  return TParser::RuleBlock;
}

void TParser::BlockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlock(this);
}

void TParser::BlockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlock(this);
}


std::any TParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

TParser::BlockContext* TParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 34, TParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(283);
    match(TParser::L_CURLY);
    setState(284);
    statementList();
    setState(285);
    match(TParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementListContext ------------------------------------------------------------------

TParser::StatementListContext::StatementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TParser::StatementContext *> TParser::StatementListContext::statement() {
  return getRuleContexts<TParser::StatementContext>();
}

TParser::StatementContext* TParser::StatementListContext::statement(size_t i) {
  return getRuleContext<TParser::StatementContext>(i);
}

std::vector<TParser::EosContext *> TParser::StatementListContext::eos() {
  return getRuleContexts<TParser::EosContext>();
}

TParser::EosContext* TParser::StatementListContext::eos(size_t i) {
  return getRuleContext<TParser::EosContext>(i);
}

std::vector<tree::TerminalNode *> TParser::StatementListContext::SEMI() {
  return getTokens(TParser::SEMI);
}

tree::TerminalNode* TParser::StatementListContext::SEMI(size_t i) {
  return getToken(TParser::SEMI, i);
}

std::vector<tree::TerminalNode *> TParser::StatementListContext::EOS() {
  return getTokens(TParser::EOS);
}

tree::TerminalNode* TParser::StatementListContext::EOS(size_t i) {
  return getToken(TParser::EOS, i);
}


size_t TParser::StatementListContext::getRuleIndex() const {
  return TParser::RuleStatementList;
}

void TParser::StatementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementList(this);
}

void TParser::StatementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementList(this);
}


std::any TParser::StatementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitStatementList(this);
  else
    return visitor->visitChildren(this);
}

TParser::StatementListContext* TParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 36, TParser::RuleStatementList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7480408612391058792) != 0) || ((((_la - 68) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 68)) & 515) != 0)) {
      setState(290);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case TParser::SEMI: {
          setState(287);
          match(TParser::SEMI);
          break;
        }

        case TParser::EOS: {
          setState(288);
          match(TParser::EOS);
          break;
        }

        case TParser::BREAK:
        case TParser::CONST:
        case TParser::CONTINUE:
        case TParser::FOR:
        case TParser::FUNC:
        case TParser::JOIN:
        case TParser::IF:
        case TParser::NIL_LIT:
        case TParser::RETURN:
        case TParser::VAR:
        case TParser::IDENTIFIER:
        case TParser::L_PAREN:
        case TParser::L_CURLY:
        case TParser::L_BRACKET:
        case TParser::EXCLAMATION:
        case TParser::PLUS:
        case TParser::MINUS:
        case TParser::CARET:
        case TParser::STAR:
        case TParser::AMPERSAND:
        case TParser::DECIMAL_LIT:
        case TParser::BINARY_LIT:
        case TParser::OCTAL_LIT:
        case TParser::HEX_LIT:
        case TParser::FLOAT_LIT:
        case TParser::IMAGINARY_LIT:
        case TParser::RUNE_LIT:
        case TParser::RAW_STRING_LIT:
        case TParser::INTERPRETED_STRING_LIT: {
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(292);
      statement();
      setState(293);
      eos();
      setState(299);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

TParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::DeclarationContext* TParser::StatementContext::declaration() {
  return getRuleContext<TParser::DeclarationContext>(0);
}

TParser::SimpleStmtContext* TParser::StatementContext::simpleStmt() {
  return getRuleContext<TParser::SimpleStmtContext>(0);
}

TParser::ReturnStmtContext* TParser::StatementContext::returnStmt() {
  return getRuleContext<TParser::ReturnStmtContext>(0);
}

TParser::BreakStmtContext* TParser::StatementContext::breakStmt() {
  return getRuleContext<TParser::BreakStmtContext>(0);
}

TParser::ContinueStmtContext* TParser::StatementContext::continueStmt() {
  return getRuleContext<TParser::ContinueStmtContext>(0);
}

TParser::BlockContext* TParser::StatementContext::block() {
  return getRuleContext<TParser::BlockContext>(0);
}

TParser::IfStmtContext* TParser::StatementContext::ifStmt() {
  return getRuleContext<TParser::IfStmtContext>(0);
}

TParser::JoinStmtContext* TParser::StatementContext::joinStmt() {
  return getRuleContext<TParser::JoinStmtContext>(0);
}

TParser::ForStmtContext* TParser::StatementContext::forStmt() {
  return getRuleContext<TParser::ForStmtContext>(0);
}


size_t TParser::StatementContext::getRuleIndex() const {
  return TParser::RuleStatement;
}

void TParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void TParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any TParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

TParser::StatementContext* TParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 38, TParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(309);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::CONST:
      case TParser::VAR: {
        enterOuterAlt(_localctx, 1);
        setState(300);
        declaration();
        break;
      }

      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET:
      case TParser::EXCLAMATION:
      case TParser::PLUS:
      case TParser::MINUS:
      case TParser::CARET:
      case TParser::STAR:
      case TParser::AMPERSAND:
      case TParser::DECIMAL_LIT:
      case TParser::BINARY_LIT:
      case TParser::OCTAL_LIT:
      case TParser::HEX_LIT:
      case TParser::FLOAT_LIT:
      case TParser::IMAGINARY_LIT:
      case TParser::RUNE_LIT:
      case TParser::RAW_STRING_LIT:
      case TParser::INTERPRETED_STRING_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(301);
        simpleStmt();
        break;
      }

      case TParser::RETURN: {
        enterOuterAlt(_localctx, 3);
        setState(302);
        returnStmt();
        break;
      }

      case TParser::BREAK: {
        enterOuterAlt(_localctx, 4);
        setState(303);
        breakStmt();
        break;
      }

      case TParser::CONTINUE: {
        enterOuterAlt(_localctx, 5);
        setState(304);
        continueStmt();
        break;
      }

      case TParser::L_CURLY: {
        enterOuterAlt(_localctx, 6);
        setState(305);
        block();
        break;
      }

      case TParser::IF: {
        enterOuterAlt(_localctx, 7);
        setState(306);
        ifStmt();
        break;
      }

      case TParser::JOIN: {
        enterOuterAlt(_localctx, 8);
        setState(307);
        joinStmt();
        break;
      }

      case TParser::FOR: {
        enterOuterAlt(_localctx, 9);
        setState(308);
        forStmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SimpleStmtContext ------------------------------------------------------------------

TParser::SimpleStmtContext::SimpleStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::EmitStmtContext* TParser::SimpleStmtContext::emitStmt() {
  return getRuleContext<TParser::EmitStmtContext>(0);
}

TParser::SyncReturnStmtContext* TParser::SimpleStmtContext::syncReturnStmt() {
  return getRuleContext<TParser::SyncReturnStmtContext>(0);
}

TParser::IncDecStmtContext* TParser::SimpleStmtContext::incDecStmt() {
  return getRuleContext<TParser::IncDecStmtContext>(0);
}

TParser::AssignmentContext* TParser::SimpleStmtContext::assignment() {
  return getRuleContext<TParser::AssignmentContext>(0);
}

TParser::ExpressionStmtContext* TParser::SimpleStmtContext::expressionStmt() {
  return getRuleContext<TParser::ExpressionStmtContext>(0);
}

TParser::ShortVarDeclContext* TParser::SimpleStmtContext::shortVarDecl() {
  return getRuleContext<TParser::ShortVarDeclContext>(0);
}


size_t TParser::SimpleStmtContext::getRuleIndex() const {
  return TParser::RuleSimpleStmt;
}

void TParser::SimpleStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimpleStmt(this);
}

void TParser::SimpleStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimpleStmt(this);
}


std::any TParser::SimpleStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSimpleStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::SimpleStmtContext* TParser::simpleStmt() {
  SimpleStmtContext *_localctx = _tracker.createInstance<SimpleStmtContext>(_ctx, getState());
  enterRule(_localctx, 40, TParser::RuleSimpleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(317);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(311);
      emitStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(312);
      syncReturnStmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(313);
      incDecStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(314);
      assignment();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(315);
      expressionStmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(316);
      shortVarDecl();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionStmtContext ------------------------------------------------------------------

TParser::ExpressionStmtContext::ExpressionStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ExpressionContext* TParser::ExpressionStmtContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}


size_t TParser::ExpressionStmtContext::getRuleIndex() const {
  return TParser::RuleExpressionStmt;
}

void TParser::ExpressionStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionStmt(this);
}

void TParser::ExpressionStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionStmt(this);
}


std::any TParser::ExpressionStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitExpressionStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ExpressionStmtContext* TParser::expressionStmt() {
  ExpressionStmtContext *_localctx = _tracker.createInstance<ExpressionStmtContext>(_ctx, getState());
  enterRule(_localctx, 42, TParser::RuleExpressionStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(319);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SyncReturnStmtContext ------------------------------------------------------------------

TParser::SyncReturnStmtContext::SyncReturnStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::SyncReturnStmtContext::SYNC_RETURN() {
  return getToken(TParser::SYNC_RETURN, 0);
}

std::vector<TParser::ExpressionContext *> TParser::SyncReturnStmtContext::expression() {
  return getRuleContexts<TParser::ExpressionContext>();
}

TParser::ExpressionContext* TParser::SyncReturnStmtContext::expression(size_t i) {
  return getRuleContext<TParser::ExpressionContext>(i);
}


size_t TParser::SyncReturnStmtContext::getRuleIndex() const {
  return TParser::RuleSyncReturnStmt;
}

void TParser::SyncReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSyncReturnStmt(this);
}

void TParser::SyncReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSyncReturnStmt(this);
}


std::any TParser::SyncReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSyncReturnStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::SyncReturnStmtContext* TParser::syncReturnStmt() {
  SyncReturnStmtContext *_localctx = _tracker.createInstance<SyncReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 44, TParser::RuleSyncReturnStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    antlrcpp::downCast<SyncReturnStmtContext *>(_localctx)->channel = expression(0);
    setState(322);
    match(TParser::SYNC_RETURN);
    setState(323);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EmitStmtContext ------------------------------------------------------------------

TParser::EmitStmtContext::EmitStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::EmitStmtContext::EMIT() {
  return getToken(TParser::EMIT, 0);
}

std::vector<TParser::ExpressionContext *> TParser::EmitStmtContext::expression() {
  return getRuleContexts<TParser::ExpressionContext>();
}

TParser::ExpressionContext* TParser::EmitStmtContext::expression(size_t i) {
  return getRuleContext<TParser::ExpressionContext>(i);
}


size_t TParser::EmitStmtContext::getRuleIndex() const {
  return TParser::RuleEmitStmt;
}

void TParser::EmitStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmitStmt(this);
}

void TParser::EmitStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmitStmt(this);
}


std::any TParser::EmitStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitEmitStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::EmitStmtContext* TParser::emitStmt() {
  EmitStmtContext *_localctx = _tracker.createInstance<EmitStmtContext>(_ctx, getState());
  enterRule(_localctx, 46, TParser::RuleEmitStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    antlrcpp::downCast<EmitStmtContext *>(_localctx)->channel = expression(0);
    setState(326);
    match(TParser::EMIT);
    setState(327);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IncDecStmtContext ------------------------------------------------------------------

TParser::IncDecStmtContext::IncDecStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ExpressionContext* TParser::IncDecStmtContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

tree::TerminalNode* TParser::IncDecStmtContext::PLUS_PLUS() {
  return getToken(TParser::PLUS_PLUS, 0);
}

tree::TerminalNode* TParser::IncDecStmtContext::MINUS_MINUS() {
  return getToken(TParser::MINUS_MINUS, 0);
}


size_t TParser::IncDecStmtContext::getRuleIndex() const {
  return TParser::RuleIncDecStmt;
}

void TParser::IncDecStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIncDecStmt(this);
}

void TParser::IncDecStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIncDecStmt(this);
}


std::any TParser::IncDecStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIncDecStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::IncDecStmtContext* TParser::incDecStmt() {
  IncDecStmtContext *_localctx = _tracker.createInstance<IncDecStmtContext>(_ctx, getState());
  enterRule(_localctx, 48, TParser::RuleIncDecStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    expression(0);
    setState(330);
    _la = _input->LA(1);
    if (!(_la == TParser::PLUS_PLUS

    || _la == TParser::MINUS_MINUS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

TParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TParser::ExpressionListContext *> TParser::AssignmentContext::expressionList() {
  return getRuleContexts<TParser::ExpressionListContext>();
}

TParser::ExpressionListContext* TParser::AssignmentContext::expressionList(size_t i) {
  return getRuleContext<TParser::ExpressionListContext>(i);
}

TParser::Assign_opContext* TParser::AssignmentContext::assign_op() {
  return getRuleContext<TParser::Assign_opContext>(0);
}


size_t TParser::AssignmentContext::getRuleIndex() const {
  return TParser::RuleAssignment;
}

void TParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void TParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any TParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

TParser::AssignmentContext* TParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 50, TParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(332);
    expressionList();
    setState(333);
    assign_op();
    setState(334);
    expressionList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assign_opContext ------------------------------------------------------------------

TParser::Assign_opContext::Assign_opContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::Assign_opContext::ASSIGN() {
  return getToken(TParser::ASSIGN, 0);
}

tree::TerminalNode* TParser::Assign_opContext::PLUS() {
  return getToken(TParser::PLUS, 0);
}

tree::TerminalNode* TParser::Assign_opContext::MINUS() {
  return getToken(TParser::MINUS, 0);
}

tree::TerminalNode* TParser::Assign_opContext::OR() {
  return getToken(TParser::OR, 0);
}

tree::TerminalNode* TParser::Assign_opContext::CARET() {
  return getToken(TParser::CARET, 0);
}

tree::TerminalNode* TParser::Assign_opContext::STAR() {
  return getToken(TParser::STAR, 0);
}

tree::TerminalNode* TParser::Assign_opContext::DIV() {
  return getToken(TParser::DIV, 0);
}

tree::TerminalNode* TParser::Assign_opContext::MOD() {
  return getToken(TParser::MOD, 0);
}

tree::TerminalNode* TParser::Assign_opContext::LSHIFT() {
  return getToken(TParser::LSHIFT, 0);
}

tree::TerminalNode* TParser::Assign_opContext::RSHIFT() {
  return getToken(TParser::RSHIFT, 0);
}

tree::TerminalNode* TParser::Assign_opContext::AMPERSAND() {
  return getToken(TParser::AMPERSAND, 0);
}

tree::TerminalNode* TParser::Assign_opContext::BIT_CLEAR() {
  return getToken(TParser::BIT_CLEAR, 0);
}


size_t TParser::Assign_opContext::getRuleIndex() const {
  return TParser::RuleAssign_op;
}

void TParser::Assign_opContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssign_op(this);
}

void TParser::Assign_opContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssign_op(this);
}


std::any TParser::Assign_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAssign_op(this);
  else
    return visitor->visitChildren(this);
}

TParser::Assign_opContext* TParser::assign_op() {
  Assign_opContext *_localctx = _tracker.createInstance<Assign_opContext>(_ctx, getState());
  enterRule(_localctx, 52, TParser::RuleAssign_op);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4397496755290112) != 0)) {
      setState(336);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 4397496755290112) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(339);
    match(TParser::ASSIGN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ShortVarDeclContext ------------------------------------------------------------------

TParser::ShortVarDeclContext::ShortVarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::IdentifierListContext* TParser::ShortVarDeclContext::identifierList() {
  return getRuleContext<TParser::IdentifierListContext>(0);
}

tree::TerminalNode* TParser::ShortVarDeclContext::DECLARE_ASSIGN() {
  return getToken(TParser::DECLARE_ASSIGN, 0);
}

TParser::ExpressionListContext* TParser::ShortVarDeclContext::expressionList() {
  return getRuleContext<TParser::ExpressionListContext>(0);
}


size_t TParser::ShortVarDeclContext::getRuleIndex() const {
  return TParser::RuleShortVarDecl;
}

void TParser::ShortVarDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShortVarDecl(this);
}

void TParser::ShortVarDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShortVarDecl(this);
}


std::any TParser::ShortVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitShortVarDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::ShortVarDeclContext* TParser::shortVarDecl() {
  ShortVarDeclContext *_localctx = _tracker.createInstance<ShortVarDeclContext>(_ctx, getState());
  enterRule(_localctx, 54, TParser::RuleShortVarDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    identifierList();
    setState(342);
    match(TParser::DECLARE_ASSIGN);
    setState(343);
    expressionList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStmtContext ------------------------------------------------------------------

TParser::ReturnStmtContext::ReturnStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ReturnStmtContext::RETURN() {
  return getToken(TParser::RETURN, 0);
}

TParser::ExpressionListContext* TParser::ReturnStmtContext::expressionList() {
  return getRuleContext<TParser::ExpressionListContext>(0);
}


size_t TParser::ReturnStmtContext::getRuleIndex() const {
  return TParser::RuleReturnStmt;
}

void TParser::ReturnStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStmt(this);
}

void TParser::ReturnStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStmt(this);
}


std::any TParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ReturnStmtContext* TParser::returnStmt() {
  ReturnStmtContext *_localctx = _tracker.createInstance<ReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 56, TParser::RuleReturnStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    match(TParser::RETURN);
    setState(347);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 871996214990606729) != 0)) {
      setState(346);
      expressionList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BreakStmtContext ------------------------------------------------------------------

TParser::BreakStmtContext::BreakStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::BreakStmtContext::BREAK() {
  return getToken(TParser::BREAK, 0);
}

tree::TerminalNode* TParser::BreakStmtContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}


size_t TParser::BreakStmtContext::getRuleIndex() const {
  return TParser::RuleBreakStmt;
}

void TParser::BreakStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBreakStmt(this);
}

void TParser::BreakStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBreakStmt(this);
}


std::any TParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::BreakStmtContext* TParser::breakStmt() {
  BreakStmtContext *_localctx = _tracker.createInstance<BreakStmtContext>(_ctx, getState());
  enterRule(_localctx, 58, TParser::RuleBreakStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    match(TParser::BREAK);
    setState(351);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::IDENTIFIER) {
      setState(350);
      match(TParser::IDENTIFIER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContinueStmtContext ------------------------------------------------------------------

TParser::ContinueStmtContext::ContinueStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ContinueStmtContext::CONTINUE() {
  return getToken(TParser::CONTINUE, 0);
}

tree::TerminalNode* TParser::ContinueStmtContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}


size_t TParser::ContinueStmtContext::getRuleIndex() const {
  return TParser::RuleContinueStmt;
}

void TParser::ContinueStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContinueStmt(this);
}

void TParser::ContinueStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContinueStmt(this);
}


std::any TParser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ContinueStmtContext* TParser::continueStmt() {
  ContinueStmtContext *_localctx = _tracker.createInstance<ContinueStmtContext>(_ctx, getState());
  enterRule(_localctx, 60, TParser::RuleContinueStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(353);
    match(TParser::CONTINUE);
    setState(355);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::IDENTIFIER) {
      setState(354);
      match(TParser::IDENTIFIER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStmtContext ------------------------------------------------------------------

TParser::IfStmtContext::IfStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::IfStmtContext::IF() {
  return getToken(TParser::IF, 0);
}

std::vector<TParser::BlockContext *> TParser::IfStmtContext::block() {
  return getRuleContexts<TParser::BlockContext>();
}

TParser::BlockContext* TParser::IfStmtContext::block(size_t i) {
  return getRuleContext<TParser::BlockContext>(i);
}

TParser::ExpressionContext* TParser::IfStmtContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

TParser::SimpleStmtContext* TParser::IfStmtContext::simpleStmt() {
  return getRuleContext<TParser::SimpleStmtContext>(0);
}

tree::TerminalNode* TParser::IfStmtContext::SEMI() {
  return getToken(TParser::SEMI, 0);
}

tree::TerminalNode* TParser::IfStmtContext::EOS() {
  return getToken(TParser::EOS, 0);
}

tree::TerminalNode* TParser::IfStmtContext::ELSE() {
  return getToken(TParser::ELSE, 0);
}

TParser::IfStmtContext* TParser::IfStmtContext::ifStmt() {
  return getRuleContext<TParser::IfStmtContext>(0);
}


size_t TParser::IfStmtContext::getRuleIndex() const {
  return TParser::RuleIfStmt;
}

void TParser::IfStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIfStmt(this);
}

void TParser::IfStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIfStmt(this);
}


std::any TParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::IfStmtContext* TParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 62, TParser::RuleIfStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(357);
    match(TParser::IF);
    setState(365);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      setState(358);
      expression(0);
      break;
    }

    case 2: {
      setState(359);
      _la = _input->LA(1);
      if (!(_la == TParser::SEMI

      || _la == TParser::EOS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(360);
      expression(0);
      break;
    }

    case 3: {
      setState(361);
      simpleStmt();
      setState(362);
      _la = _input->LA(1);
      if (!(_la == TParser::SEMI

      || _la == TParser::EOS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(363);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(367);
    block();
    setState(373);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::ELSE) {
      setState(368);
      match(TParser::ELSE);
      setState(371);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case TParser::IF: {
          setState(369);
          ifStmt();
          break;
        }

        case TParser::L_CURLY: {
          setState(370);
          block();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeListContext ------------------------------------------------------------------

TParser::TypeListContext::TypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TParser::Type_Context *> TParser::TypeListContext::type_() {
  return getRuleContexts<TParser::Type_Context>();
}

TParser::Type_Context* TParser::TypeListContext::type_(size_t i) {
  return getRuleContext<TParser::Type_Context>(i);
}

std::vector<tree::TerminalNode *> TParser::TypeListContext::NIL_LIT() {
  return getTokens(TParser::NIL_LIT);
}

tree::TerminalNode* TParser::TypeListContext::NIL_LIT(size_t i) {
  return getToken(TParser::NIL_LIT, i);
}

std::vector<tree::TerminalNode *> TParser::TypeListContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::TypeListContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::TypeListContext::getRuleIndex() const {
  return TParser::RuleTypeList;
}

void TParser::TypeListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeList(this);
}

void TParser::TypeListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeList(this);
}


std::any TParser::TypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeList(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeListContext* TParser::typeList() {
  TypeListContext *_localctx = _tracker.createInstance<TypeListContext>(_ctx, getState());
  enterRule(_localctx, 64, TParser::RuleTypeList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(377);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::ASYNC:
      case TParser::FUNC:
      case TParser::SYNC:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET: {
        setState(375);
        type_();
        break;
      }

      case TParser::NIL_LIT: {
        setState(376);
        match(TParser::NIL_LIT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(386);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(379);
        match(TParser::COMMA);
        setState(382);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case TParser::ASYNC:
          case TParser::FUNC:
          case TParser::SYNC:
          case TParser::IDENTIFIER:
          case TParser::L_PAREN:
          case TParser::L_BRACKET: {
            setState(380);
            type_();
            break;
          }

          case TParser::NIL_LIT: {
            setState(381);
            match(TParser::NIL_LIT);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(388);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JoinStmtContext ------------------------------------------------------------------

TParser::JoinStmtContext::JoinStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::JoinStmtContext::JOIN() {
  return getToken(TParser::JOIN, 0);
}

tree::TerminalNode* TParser::JoinStmtContext::L_CURLY() {
  return getToken(TParser::L_CURLY, 0);
}

tree::TerminalNode* TParser::JoinStmtContext::R_CURLY() {
  return getToken(TParser::R_CURLY, 0);
}

std::vector<TParser::MatchClauseContext *> TParser::JoinStmtContext::matchClause() {
  return getRuleContexts<TParser::MatchClauseContext>();
}

TParser::MatchClauseContext* TParser::JoinStmtContext::matchClause(size_t i) {
  return getRuleContext<TParser::MatchClauseContext>(i);
}


size_t TParser::JoinStmtContext::getRuleIndex() const {
  return TParser::RuleJoinStmt;
}

void TParser::JoinStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinStmt(this);
}

void TParser::JoinStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinStmt(this);
}


std::any TParser::JoinStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitJoinStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::JoinStmtContext* TParser::joinStmt() {
  JoinStmtContext *_localctx = _tracker.createInstance<JoinStmtContext>(_ctx, getState());
  enterRule(_localctx, 66, TParser::RuleJoinStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(389);
    match(TParser::JOIN);
    setState(390);
    match(TParser::L_CURLY);
    setState(394);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::CASE) {
      setState(391);
      matchClause();
      setState(396);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(397);
    match(TParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchClauseContext ------------------------------------------------------------------

TParser::MatchClauseContext::MatchClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::MatchCaseContext* TParser::MatchClauseContext::matchCase() {
  return getRuleContext<TParser::MatchCaseContext>(0);
}

tree::TerminalNode* TParser::MatchClauseContext::COLON() {
  return getToken(TParser::COLON, 0);
}

TParser::StatementListContext* TParser::MatchClauseContext::statementList() {
  return getRuleContext<TParser::StatementListContext>(0);
}


size_t TParser::MatchClauseContext::getRuleIndex() const {
  return TParser::RuleMatchClause;
}

void TParser::MatchClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMatchClause(this);
}

void TParser::MatchClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMatchClause(this);
}


std::any TParser::MatchClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitMatchClause(this);
  else
    return visitor->visitChildren(this);
}

TParser::MatchClauseContext* TParser::matchClause() {
  MatchClauseContext *_localctx = _tracker.createInstance<MatchClauseContext>(_ctx, getState());
  enterRule(_localctx, 68, TParser::RuleMatchClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(399);
    matchCase();
    setState(400);
    match(TParser::COLON);
    setState(401);
    statementList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MatchCaseContext ------------------------------------------------------------------

TParser::MatchCaseContext::MatchCaseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::MatchCaseContext::CASE() {
  return getToken(TParser::CASE, 0);
}

std::vector<TParser::FromChanAsContext *> TParser::MatchCaseContext::fromChanAs() {
  return getRuleContexts<TParser::FromChanAsContext>();
}

TParser::FromChanAsContext* TParser::MatchCaseContext::fromChanAs(size_t i) {
  return getRuleContext<TParser::FromChanAsContext>(i);
}

std::vector<tree::TerminalNode *> TParser::MatchCaseContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::MatchCaseContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::MatchCaseContext::getRuleIndex() const {
  return TParser::RuleMatchCase;
}

void TParser::MatchCaseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMatchCase(this);
}

void TParser::MatchCaseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMatchCase(this);
}


std::any TParser::MatchCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitMatchCase(this);
  else
    return visitor->visitChildren(this);
}

TParser::MatchCaseContext* TParser::matchCase() {
  MatchCaseContext *_localctx = _tracker.createInstance<MatchCaseContext>(_ctx, getState());
  enterRule(_localctx, 70, TParser::RuleMatchCase);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(403);
    match(TParser::CASE);
    setState(409);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(404);
        fromChanAs();
        setState(405);
        match(TParser::COMMA); 
      }
      setState(411);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    }
    setState(412);
    fromChanAs();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FromChanAsContext ------------------------------------------------------------------

TParser::FromChanAsContext::FromChanAsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::FromChanAsContext::FROM() {
  return getToken(TParser::FROM, 0);
}

std::vector<tree::TerminalNode *> TParser::FromChanAsContext::IDENTIFIER() {
  return getTokens(TParser::IDENTIFIER);
}

tree::TerminalNode* TParser::FromChanAsContext::IDENTIFIER(size_t i) {
  return getToken(TParser::IDENTIFIER, i);
}

tree::TerminalNode* TParser::FromChanAsContext::AS() {
  return getToken(TParser::AS, 0);
}


size_t TParser::FromChanAsContext::getRuleIndex() const {
  return TParser::RuleFromChanAs;
}

void TParser::FromChanAsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFromChanAs(this);
}

void TParser::FromChanAsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFromChanAs(this);
}


std::any TParser::FromChanAsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFromChanAs(this);
  else
    return visitor->visitChildren(this);
}

TParser::FromChanAsContext* TParser::fromChanAs() {
  FromChanAsContext *_localctx = _tracker.createInstance<FromChanAsContext>(_ctx, getState());
  enterRule(_localctx, 72, TParser::RuleFromChanAs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(414);
    match(TParser::FROM);
    setState(415);
    match(TParser::IDENTIFIER);
    setState(418);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::AS) {
      setState(416);
      match(TParser::AS);
      setState(417);
      match(TParser::IDENTIFIER);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForStmtContext ------------------------------------------------------------------

TParser::ForStmtContext::ForStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ForStmtContext::FOR() {
  return getToken(TParser::FOR, 0);
}

TParser::BlockContext* TParser::ForStmtContext::block() {
  return getRuleContext<TParser::BlockContext>(0);
}

TParser::ConditionContext* TParser::ForStmtContext::condition() {
  return getRuleContext<TParser::ConditionContext>(0);
}

TParser::ForClauseContext* TParser::ForStmtContext::forClause() {
  return getRuleContext<TParser::ForClauseContext>(0);
}


size_t TParser::ForStmtContext::getRuleIndex() const {
  return TParser::RuleForStmt;
}

void TParser::ForStmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForStmt(this);
}

void TParser::ForStmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForStmt(this);
}


std::any TParser::ForStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitForStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ForStmtContext* TParser::forStmt() {
  ForStmtContext *_localctx = _tracker.createInstance<ForStmtContext>(_ctx, getState());
  enterRule(_localctx, 74, TParser::RuleForStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(420);
    match(TParser::FOR);
    setState(423);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      setState(421);
      condition();
      break;
    }

    case 2: {
      setState(422);
      forClause();
      break;
    }

    default:
      break;
    }
    setState(425);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

TParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ExpressionContext* TParser::ConditionContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}


size_t TParser::ConditionContext::getRuleIndex() const {
  return TParser::RuleCondition;
}

void TParser::ConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCondition(this);
}

void TParser::ConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCondition(this);
}


std::any TParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

TParser::ConditionContext* TParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 76, TParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(427);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ForClauseContext ------------------------------------------------------------------

TParser::ForClauseContext::ForClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TParser::EosContext *> TParser::ForClauseContext::eos() {
  return getRuleContexts<TParser::EosContext>();
}

TParser::EosContext* TParser::ForClauseContext::eos(size_t i) {
  return getRuleContext<TParser::EosContext>(i);
}

TParser::ExpressionContext* TParser::ForClauseContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

std::vector<TParser::SimpleStmtContext *> TParser::ForClauseContext::simpleStmt() {
  return getRuleContexts<TParser::SimpleStmtContext>();
}

TParser::SimpleStmtContext* TParser::ForClauseContext::simpleStmt(size_t i) {
  return getRuleContext<TParser::SimpleStmtContext>(i);
}


size_t TParser::ForClauseContext::getRuleIndex() const {
  return TParser::RuleForClause;
}

void TParser::ForClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterForClause(this);
}

void TParser::ForClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitForClause(this);
}


std::any TParser::ForClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitForClause(this);
  else
    return visitor->visitChildren(this);
}

TParser::ForClauseContext* TParser::forClause() {
  ForClauseContext *_localctx = _tracker.createInstance<ForClauseContext>(_ctx, getState());
  enterRule(_localctx, 78, TParser::RuleForClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(430);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 871996214990606729) != 0)) {
      setState(429);
      antlrcpp::downCast<ForClauseContext *>(_localctx)->initStmt = simpleStmt();
    }
    setState(432);
    eos();
    setState(434);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 871996214990606729) != 0)) {
      setState(433);
      expression(0);
    }
    setState(436);
    eos();
    setState(438);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 871996214990606729) != 0)) {
      setState(437);
      antlrcpp::downCast<ForClauseContext *>(_localctx)->postStmt = simpleStmt();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_Context ------------------------------------------------------------------

TParser::Type_Context::Type_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::TypeNameContext* TParser::Type_Context::typeName() {
  return getRuleContext<TParser::TypeNameContext>(0);
}

TParser::TypeArgsContext* TParser::Type_Context::typeArgs() {
  return getRuleContext<TParser::TypeArgsContext>(0);
}

TParser::TypeLitContext* TParser::Type_Context::typeLit() {
  return getRuleContext<TParser::TypeLitContext>(0);
}

tree::TerminalNode* TParser::Type_Context::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

TParser::Type_Context* TParser::Type_Context::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

tree::TerminalNode* TParser::Type_Context::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}


size_t TParser::Type_Context::getRuleIndex() const {
  return TParser::RuleType_;
}

void TParser::Type_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_(this);
}

void TParser::Type_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_(this);
}


std::any TParser::Type_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitType_(this);
  else
    return visitor->visitChildren(this);
}

TParser::Type_Context* TParser::type_() {
  Type_Context *_localctx = _tracker.createInstance<Type_Context>(_ctx, getState());
  enterRule(_localctx, 80, TParser::RuleType_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(449);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(440);
        typeName();
        setState(442);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TParser::L_BRACKET) {
          setState(441);
          typeArgs();
        }
        break;
      }

      case TParser::ASYNC:
      case TParser::FUNC:
      case TParser::SYNC:
      case TParser::L_BRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(444);
        typeLit();
        break;
      }

      case TParser::L_PAREN: {
        enterOuterAlt(_localctx, 3);
        setState(445);
        match(TParser::L_PAREN);
        setState(446);
        type_();
        setState(447);
        match(TParser::R_PAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeArgsContext ------------------------------------------------------------------

TParser::TypeArgsContext::TypeArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::TypeArgsContext::L_BRACKET() {
  return getToken(TParser::L_BRACKET, 0);
}

TParser::TypeListContext* TParser::TypeArgsContext::typeList() {
  return getRuleContext<TParser::TypeListContext>(0);
}

tree::TerminalNode* TParser::TypeArgsContext::R_BRACKET() {
  return getToken(TParser::R_BRACKET, 0);
}

tree::TerminalNode* TParser::TypeArgsContext::COMMA() {
  return getToken(TParser::COMMA, 0);
}


size_t TParser::TypeArgsContext::getRuleIndex() const {
  return TParser::RuleTypeArgs;
}

void TParser::TypeArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeArgs(this);
}

void TParser::TypeArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeArgs(this);
}


std::any TParser::TypeArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeArgs(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeArgsContext* TParser::typeArgs() {
  TypeArgsContext *_localctx = _tracker.createInstance<TypeArgsContext>(_ctx, getState());
  enterRule(_localctx, 82, TParser::RuleTypeArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(451);
    match(TParser::L_BRACKET);
    setState(452);
    typeList();
    setState(454);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::COMMA) {
      setState(453);
      match(TParser::COMMA);
    }
    setState(456);
    match(TParser::R_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeNameContext ------------------------------------------------------------------

TParser::TypeNameContext::TypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::TypeNameContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}


size_t TParser::TypeNameContext::getRuleIndex() const {
  return TParser::RuleTypeName;
}

void TParser::TypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeName(this);
}

void TParser::TypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeName(this);
}


std::any TParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeNameContext* TParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 84, TParser::RuleTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(458);
    match(TParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeLitContext ------------------------------------------------------------------

TParser::TypeLitContext::TypeLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ArrayTypeContext* TParser::TypeLitContext::arrayType() {
  return getRuleContext<TParser::ArrayTypeContext>(0);
}

TParser::FunctionTypeContext* TParser::TypeLitContext::functionType() {
  return getRuleContext<TParser::FunctionTypeContext>(0);
}

TParser::SyncChannelTypeContext* TParser::TypeLitContext::syncChannelType() {
  return getRuleContext<TParser::SyncChannelTypeContext>(0);
}

TParser::AsyncChannelTypeContext* TParser::TypeLitContext::asyncChannelType() {
  return getRuleContext<TParser::AsyncChannelTypeContext>(0);
}


size_t TParser::TypeLitContext::getRuleIndex() const {
  return TParser::RuleTypeLit;
}

void TParser::TypeLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeLit(this);
}

void TParser::TypeLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeLit(this);
}


std::any TParser::TypeLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeLitContext* TParser::typeLit() {
  TypeLitContext *_localctx = _tracker.createInstance<TypeLitContext>(_ctx, getState());
  enterRule(_localctx, 86, TParser::RuleTypeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(464);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::L_BRACKET: {
        enterOuterAlt(_localctx, 1);
        setState(460);
        arrayType();
        break;
      }

      case TParser::FUNC: {
        enterOuterAlt(_localctx, 2);
        setState(461);
        functionType();
        break;
      }

      case TParser::SYNC: {
        enterOuterAlt(_localctx, 3);
        setState(462);
        syncChannelType();
        break;
      }

      case TParser::ASYNC: {
        enterOuterAlt(_localctx, 4);
        setState(463);
        asyncChannelType();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayTypeContext ------------------------------------------------------------------

TParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ArrayTypeContext::L_BRACKET() {
  return getToken(TParser::L_BRACKET, 0);
}

TParser::ArrayLengthContext* TParser::ArrayTypeContext::arrayLength() {
  return getRuleContext<TParser::ArrayLengthContext>(0);
}

tree::TerminalNode* TParser::ArrayTypeContext::R_BRACKET() {
  return getToken(TParser::R_BRACKET, 0);
}

TParser::ElementTypeContext* TParser::ArrayTypeContext::elementType() {
  return getRuleContext<TParser::ElementTypeContext>(0);
}


size_t TParser::ArrayTypeContext::getRuleIndex() const {
  return TParser::RuleArrayType;
}

void TParser::ArrayTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayType(this);
}

void TParser::ArrayTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayType(this);
}


std::any TParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

TParser::ArrayTypeContext* TParser::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 88, TParser::RuleArrayType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(466);
    match(TParser::L_BRACKET);
    setState(467);
    arrayLength();
    setState(468);
    match(TParser::R_BRACKET);
    setState(469);
    elementType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayLengthContext ------------------------------------------------------------------

TParser::ArrayLengthContext::ArrayLengthContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ExpressionContext* TParser::ArrayLengthContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}


size_t TParser::ArrayLengthContext::getRuleIndex() const {
  return TParser::RuleArrayLength;
}

void TParser::ArrayLengthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayLength(this);
}

void TParser::ArrayLengthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayLength(this);
}


std::any TParser::ArrayLengthContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitArrayLength(this);
  else
    return visitor->visitChildren(this);
}

TParser::ArrayLengthContext* TParser::arrayLength() {
  ArrayLengthContext *_localctx = _tracker.createInstance<ArrayLengthContext>(_ctx, getState());
  enterRule(_localctx, 90, TParser::RuleArrayLength);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(471);
    expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementTypeContext ------------------------------------------------------------------

TParser::ElementTypeContext::ElementTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::Type_Context* TParser::ElementTypeContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}


size_t TParser::ElementTypeContext::getRuleIndex() const {
  return TParser::RuleElementType;
}

void TParser::ElementTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementType(this);
}

void TParser::ElementTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementType(this);
}


std::any TParser::ElementTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitElementType(this);
  else
    return visitor->visitChildren(this);
}

TParser::ElementTypeContext* TParser::elementType() {
  ElementTypeContext *_localctx = _tracker.createInstance<ElementTypeContext>(_ctx, getState());
  enterRule(_localctx, 92, TParser::RuleElementType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(473);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AsyncChannelTypeContext ------------------------------------------------------------------

TParser::AsyncChannelTypeContext::AsyncChannelTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::AsyncChannelTypeContext::ASYNC() {
  return getToken(TParser::ASYNC, 0);
}

TParser::ElementTypeContext* TParser::AsyncChannelTypeContext::elementType() {
  return getRuleContext<TParser::ElementTypeContext>(0);
}


size_t TParser::AsyncChannelTypeContext::getRuleIndex() const {
  return TParser::RuleAsyncChannelType;
}

void TParser::AsyncChannelTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAsyncChannelType(this);
}

void TParser::AsyncChannelTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAsyncChannelType(this);
}


std::any TParser::AsyncChannelTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAsyncChannelType(this);
  else
    return visitor->visitChildren(this);
}

TParser::AsyncChannelTypeContext* TParser::asyncChannelType() {
  AsyncChannelTypeContext *_localctx = _tracker.createInstance<AsyncChannelTypeContext>(_ctx, getState());
  enterRule(_localctx, 94, TParser::RuleAsyncChannelType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(475);
    match(TParser::ASYNC);
    setState(476);
    elementType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SyncChannelTypeContext ------------------------------------------------------------------

TParser::SyncChannelTypeContext::SyncChannelTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::SyncChannelTypeContext::SYNC() {
  return getToken(TParser::SYNC, 0);
}

TParser::SignatureContext* TParser::SyncChannelTypeContext::signature() {
  return getRuleContext<TParser::SignatureContext>(0);
}


size_t TParser::SyncChannelTypeContext::getRuleIndex() const {
  return TParser::RuleSyncChannelType;
}

void TParser::SyncChannelTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSyncChannelType(this);
}

void TParser::SyncChannelTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSyncChannelType(this);
}


std::any TParser::SyncChannelTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSyncChannelType(this);
  else
    return visitor->visitChildren(this);
}

TParser::SyncChannelTypeContext* TParser::syncChannelType() {
  SyncChannelTypeContext *_localctx = _tracker.createInstance<SyncChannelTypeContext>(_ctx, getState());
  enterRule(_localctx, 96, TParser::RuleSyncChannelType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(478);
    match(TParser::SYNC);
    setState(479);
    signature();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionTypeContext ------------------------------------------------------------------

TParser::FunctionTypeContext::FunctionTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::FunctionTypeContext::FUNC() {
  return getToken(TParser::FUNC, 0);
}

TParser::SignatureContext* TParser::FunctionTypeContext::signature() {
  return getRuleContext<TParser::SignatureContext>(0);
}


size_t TParser::FunctionTypeContext::getRuleIndex() const {
  return TParser::RuleFunctionType;
}

void TParser::FunctionTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionType(this);
}

void TParser::FunctionTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionType(this);
}


std::any TParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

TParser::FunctionTypeContext* TParser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 98, TParser::RuleFunctionType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(481);
    match(TParser::FUNC);
    setState(482);
    signature();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SignatureContext ------------------------------------------------------------------

TParser::SignatureContext::SignatureContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ParametersContext* TParser::SignatureContext::parameters() {
  return getRuleContext<TParser::ParametersContext>(0);
}

TParser::ResultContext* TParser::SignatureContext::result() {
  return getRuleContext<TParser::ResultContext>(0);
}


size_t TParser::SignatureContext::getRuleIndex() const {
  return TParser::RuleSignature;
}

void TParser::SignatureContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignature(this);
}

void TParser::SignatureContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignature(this);
}


std::any TParser::SignatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSignature(this);
  else
    return visitor->visitChildren(this);
}

TParser::SignatureContext* TParser::signature() {
  SignatureContext *_localctx = _tracker.createInstance<SignatureContext>(_ctx, getState());
  enterRule(_localctx, 100, TParser::RuleSignature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(484);
    parameters();
    setState(486);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      setState(485);
      result();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ResultContext ------------------------------------------------------------------

TParser::ResultContext::ResultContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ParametersContext* TParser::ResultContext::parameters() {
  return getRuleContext<TParser::ParametersContext>(0);
}

TParser::Type_Context* TParser::ResultContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}


size_t TParser::ResultContext::getRuleIndex() const {
  return TParser::RuleResult;
}

void TParser::ResultContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterResult(this);
}

void TParser::ResultContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitResult(this);
}


std::any TParser::ResultContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitResult(this);
  else
    return visitor->visitChildren(this);
}

TParser::ResultContext* TParser::result() {
  ResultContext *_localctx = _tracker.createInstance<ResultContext>(_ctx, getState());
  enterRule(_localctx, 102, TParser::RuleResult);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(490);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(488);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(489);
      type_();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParametersContext ------------------------------------------------------------------

TParser::ParametersContext::ParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ParametersContext::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

tree::TerminalNode* TParser::ParametersContext::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}

std::vector<TParser::ParameterDeclContext *> TParser::ParametersContext::parameterDecl() {
  return getRuleContexts<TParser::ParameterDeclContext>();
}

TParser::ParameterDeclContext* TParser::ParametersContext::parameterDecl(size_t i) {
  return getRuleContext<TParser::ParameterDeclContext>(i);
}

std::vector<tree::TerminalNode *> TParser::ParametersContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::ParametersContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::ParametersContext::getRuleIndex() const {
  return TParser::RuleParameters;
}

void TParser::ParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameters(this);
}

void TParser::ParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameters(this);
}


std::any TParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

TParser::ParametersContext* TParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 104, TParser::RuleParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(492);
    match(TParser::L_PAREN);
    setState(504);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4621316) != 0)) {
      setState(493);
      parameterDecl();
      setState(498);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(494);
          match(TParser::COMMA);
          setState(495);
          parameterDecl(); 
        }
        setState(500);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
      }
      setState(502);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TParser::COMMA) {
        setState(501);
        match(TParser::COMMA);
      }
    }
    setState(506);
    match(TParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterDeclContext ------------------------------------------------------------------

TParser::ParameterDeclContext::ParameterDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::Type_Context* TParser::ParameterDeclContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

TParser::IdentifierListContext* TParser::ParameterDeclContext::identifierList() {
  return getRuleContext<TParser::IdentifierListContext>(0);
}


size_t TParser::ParameterDeclContext::getRuleIndex() const {
  return TParser::RuleParameterDecl;
}

void TParser::ParameterDeclContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterDecl(this);
}

void TParser::ParameterDeclContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterDecl(this);
}


std::any TParser::ParameterDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitParameterDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::ParameterDeclContext* TParser::parameterDecl() {
  ParameterDeclContext *_localctx = _tracker.createInstance<ParameterDeclContext>(_ctx, getState());
  enterRule(_localctx, 106, TParser::RuleParameterDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(509);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      setState(508);
      identifierList();
      break;
    }

    default:
      break;
    }
    setState(511);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

TParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::PrimaryExprContext* TParser::ExpressionContext::primaryExpr() {
  return getRuleContext<TParser::PrimaryExprContext>(0);
}

std::vector<TParser::ExpressionContext *> TParser::ExpressionContext::expression() {
  return getRuleContexts<TParser::ExpressionContext>();
}

TParser::ExpressionContext* TParser::ExpressionContext::expression(size_t i) {
  return getRuleContext<TParser::ExpressionContext>(i);
}

tree::TerminalNode* TParser::ExpressionContext::PLUS() {
  return getToken(TParser::PLUS, 0);
}

tree::TerminalNode* TParser::ExpressionContext::MINUS() {
  return getToken(TParser::MINUS, 0);
}

tree::TerminalNode* TParser::ExpressionContext::EXCLAMATION() {
  return getToken(TParser::EXCLAMATION, 0);
}

tree::TerminalNode* TParser::ExpressionContext::CARET() {
  return getToken(TParser::CARET, 0);
}

tree::TerminalNode* TParser::ExpressionContext::STAR() {
  return getToken(TParser::STAR, 0);
}

tree::TerminalNode* TParser::ExpressionContext::AMPERSAND() {
  return getToken(TParser::AMPERSAND, 0);
}

tree::TerminalNode* TParser::ExpressionContext::DIV() {
  return getToken(TParser::DIV, 0);
}

tree::TerminalNode* TParser::ExpressionContext::MOD() {
  return getToken(TParser::MOD, 0);
}

tree::TerminalNode* TParser::ExpressionContext::LSHIFT() {
  return getToken(TParser::LSHIFT, 0);
}

tree::TerminalNode* TParser::ExpressionContext::RSHIFT() {
  return getToken(TParser::RSHIFT, 0);
}

tree::TerminalNode* TParser::ExpressionContext::BIT_CLEAR() {
  return getToken(TParser::BIT_CLEAR, 0);
}

tree::TerminalNode* TParser::ExpressionContext::OR() {
  return getToken(TParser::OR, 0);
}

tree::TerminalNode* TParser::ExpressionContext::EQUALS() {
  return getToken(TParser::EQUALS, 0);
}

tree::TerminalNode* TParser::ExpressionContext::NOT_EQUALS() {
  return getToken(TParser::NOT_EQUALS, 0);
}

tree::TerminalNode* TParser::ExpressionContext::LESS() {
  return getToken(TParser::LESS, 0);
}

tree::TerminalNode* TParser::ExpressionContext::LESS_OR_EQUALS() {
  return getToken(TParser::LESS_OR_EQUALS, 0);
}

tree::TerminalNode* TParser::ExpressionContext::GREATER() {
  return getToken(TParser::GREATER, 0);
}

tree::TerminalNode* TParser::ExpressionContext::GREATER_OR_EQUALS() {
  return getToken(TParser::GREATER_OR_EQUALS, 0);
}

tree::TerminalNode* TParser::ExpressionContext::LOGICAL_AND() {
  return getToken(TParser::LOGICAL_AND, 0);
}

tree::TerminalNode* TParser::ExpressionContext::LOGICAL_OR() {
  return getToken(TParser::LOGICAL_OR, 0);
}


size_t TParser::ExpressionContext::getRuleIndex() const {
  return TParser::RuleExpression;
}

void TParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void TParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any TParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}


TParser::ExpressionContext* TParser::expression() {
   return expression(0);
}

TParser::ExpressionContext* TParser::expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  TParser::ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, parentState);
  TParser::ExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 108;
  enterRecursionRule(_localctx, 108, TParser::RuleExpression, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(517);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET:
      case TParser::DECIMAL_LIT:
      case TParser::BINARY_LIT:
      case TParser::OCTAL_LIT:
      case TParser::HEX_LIT:
      case TParser::FLOAT_LIT:
      case TParser::IMAGINARY_LIT:
      case TParser::RUNE_LIT:
      case TParser::RAW_STRING_LIT:
      case TParser::INTERPRETED_STRING_LIT: {
        setState(514);
        primaryExpr();
        break;
      }

      case TParser::EXCLAMATION:
      case TParser::PLUS:
      case TParser::MINUS:
      case TParser::CARET:
      case TParser::STAR:
      case TParser::AMPERSAND: {
        setState(515);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 4433230883192832) != 0))) {
          antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(516);
        expression(6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(536);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(534);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(519);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(520);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 3411784580988928) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(521);
          expression(6);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(522);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(523);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 985712174301184) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(524);
          expression(5);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(525);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(526);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 541165879296) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(527);
          expression(4);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(528);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(529);
          match(TParser::LOGICAL_AND);
          setState(530);
          expression(3);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(531);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(532);
          match(TParser::LOGICAL_OR);
          setState(533);
          expression(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(538);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryExprContext ------------------------------------------------------------------

TParser::PrimaryExprContext::PrimaryExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::OperandContext* TParser::PrimaryExprContext::operand() {
  return getRuleContext<TParser::OperandContext>(0);
}

std::vector<TParser::ArgumentsContext *> TParser::PrimaryExprContext::arguments() {
  return getRuleContexts<TParser::ArgumentsContext>();
}

TParser::ArgumentsContext* TParser::PrimaryExprContext::arguments(size_t i) {
  return getRuleContext<TParser::ArgumentsContext>(i);
}


size_t TParser::PrimaryExprContext::getRuleIndex() const {
  return TParser::RulePrimaryExpr;
}

void TParser::PrimaryExprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrimaryExpr(this);
}

void TParser::PrimaryExprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrimaryExpr(this);
}


std::any TParser::PrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}

TParser::PrimaryExprContext* TParser::primaryExpr() {
  PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, getState());
  enterRule(_localctx, 110, TParser::RulePrimaryExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(539);
    operand();
    setState(543);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(540);
        arguments(); 
      }
      setState(545);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConversionContext ------------------------------------------------------------------

TParser::ConversionContext::ConversionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::Type_Context* TParser::ConversionContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

tree::TerminalNode* TParser::ConversionContext::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

TParser::ExpressionContext* TParser::ConversionContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

tree::TerminalNode* TParser::ConversionContext::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}

tree::TerminalNode* TParser::ConversionContext::COMMA() {
  return getToken(TParser::COMMA, 0);
}


size_t TParser::ConversionContext::getRuleIndex() const {
  return TParser::RuleConversion;
}

void TParser::ConversionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConversion(this);
}

void TParser::ConversionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConversion(this);
}


std::any TParser::ConversionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitConversion(this);
  else
    return visitor->visitChildren(this);
}

TParser::ConversionContext* TParser::conversion() {
  ConversionContext *_localctx = _tracker.createInstance<ConversionContext>(_ctx, getState());
  enterRule(_localctx, 112, TParser::RuleConversion);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(546);
    type_();
    setState(547);
    match(TParser::L_PAREN);
    setState(548);
    expression(0);
    setState(550);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::COMMA) {
      setState(549);
      match(TParser::COMMA);
    }
    setState(552);
    match(TParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandContext ------------------------------------------------------------------

TParser::OperandContext::OperandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::LiteralContext* TParser::OperandContext::literal() {
  return getRuleContext<TParser::LiteralContext>(0);
}

TParser::OperandNameContext* TParser::OperandContext::operandName() {
  return getRuleContext<TParser::OperandNameContext>(0);
}

TParser::TypeArgsContext* TParser::OperandContext::typeArgs() {
  return getRuleContext<TParser::TypeArgsContext>(0);
}

tree::TerminalNode* TParser::OperandContext::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

TParser::ExpressionContext* TParser::OperandContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

tree::TerminalNode* TParser::OperandContext::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}


size_t TParser::OperandContext::getRuleIndex() const {
  return TParser::RuleOperand;
}

void TParser::OperandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperand(this);
}

void TParser::OperandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperand(this);
}


std::any TParser::OperandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitOperand(this);
  else
    return visitor->visitChildren(this);
}

TParser::OperandContext* TParser::operand() {
  OperandContext *_localctx = _tracker.createInstance<OperandContext>(_ctx, getState());
  enterRule(_localctx, 114, TParser::RuleOperand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(563);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(554);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(555);
      operandName();
      setState(557);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
      case 1: {
        setState(556);
        typeArgs();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(559);
      match(TParser::L_PAREN);
      setState(560);
      expression(0);
      setState(561);
      match(TParser::R_PAREN);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

TParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::BasicLitContext* TParser::LiteralContext::basicLit() {
  return getRuleContext<TParser::BasicLitContext>(0);
}

TParser::CompositeLitContext* TParser::LiteralContext::compositeLit() {
  return getRuleContext<TParser::CompositeLitContext>(0);
}

TParser::FunctionLitContext* TParser::LiteralContext::functionLit() {
  return getRuleContext<TParser::FunctionLitContext>(0);
}


size_t TParser::LiteralContext::getRuleIndex() const {
  return TParser::RuleLiteral;
}

void TParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void TParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any TParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

TParser::LiteralContext* TParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 116, TParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(568);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::NIL_LIT:
      case TParser::DECIMAL_LIT:
      case TParser::BINARY_LIT:
      case TParser::OCTAL_LIT:
      case TParser::HEX_LIT:
      case TParser::FLOAT_LIT:
      case TParser::IMAGINARY_LIT:
      case TParser::RUNE_LIT:
      case TParser::RAW_STRING_LIT:
      case TParser::INTERPRETED_STRING_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(565);
        basicLit();
        break;
      }

      case TParser::IDENTIFIER:
      case TParser::L_BRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(566);
        compositeLit();
        break;
      }

      case TParser::FUNC: {
        enterOuterAlt(_localctx, 3);
        setState(567);
        functionLit();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BasicLitContext ------------------------------------------------------------------

TParser::BasicLitContext::BasicLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::BasicLitContext::NIL_LIT() {
  return getToken(TParser::NIL_LIT, 0);
}

TParser::IntegerContext* TParser::BasicLitContext::integer() {
  return getRuleContext<TParser::IntegerContext>(0);
}

TParser::String_Context* TParser::BasicLitContext::string_() {
  return getRuleContext<TParser::String_Context>(0);
}

tree::TerminalNode* TParser::BasicLitContext::FLOAT_LIT() {
  return getToken(TParser::FLOAT_LIT, 0);
}


size_t TParser::BasicLitContext::getRuleIndex() const {
  return TParser::RuleBasicLit;
}

void TParser::BasicLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBasicLit(this);
}

void TParser::BasicLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBasicLit(this);
}


std::any TParser::BasicLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitBasicLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::BasicLitContext* TParser::basicLit() {
  BasicLitContext *_localctx = _tracker.createInstance<BasicLitContext>(_ctx, getState());
  enterRule(_localctx, 118, TParser::RuleBasicLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(574);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::NIL_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(570);
        match(TParser::NIL_LIT);
        break;
      }

      case TParser::DECIMAL_LIT:
      case TParser::BINARY_LIT:
      case TParser::OCTAL_LIT:
      case TParser::HEX_LIT:
      case TParser::IMAGINARY_LIT:
      case TParser::RUNE_LIT: {
        enterOuterAlt(_localctx, 2);
        setState(571);
        integer();
        break;
      }

      case TParser::RAW_STRING_LIT:
      case TParser::INTERPRETED_STRING_LIT: {
        enterOuterAlt(_localctx, 3);
        setState(572);
        string_();
        break;
      }

      case TParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 4);
        setState(573);
        match(TParser::FLOAT_LIT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerContext ------------------------------------------------------------------

TParser::IntegerContext::IntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::IntegerContext::DECIMAL_LIT() {
  return getToken(TParser::DECIMAL_LIT, 0);
}

tree::TerminalNode* TParser::IntegerContext::BINARY_LIT() {
  return getToken(TParser::BINARY_LIT, 0);
}

tree::TerminalNode* TParser::IntegerContext::OCTAL_LIT() {
  return getToken(TParser::OCTAL_LIT, 0);
}

tree::TerminalNode* TParser::IntegerContext::HEX_LIT() {
  return getToken(TParser::HEX_LIT, 0);
}

tree::TerminalNode* TParser::IntegerContext::IMAGINARY_LIT() {
  return getToken(TParser::IMAGINARY_LIT, 0);
}

tree::TerminalNode* TParser::IntegerContext::RUNE_LIT() {
  return getToken(TParser::RUNE_LIT, 0);
}


size_t TParser::IntegerContext::getRuleIndex() const {
  return TParser::RuleInteger;
}

void TParser::IntegerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInteger(this);
}

void TParser::IntegerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInteger(this);
}


std::any TParser::IntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitInteger(this);
  else
    return visitor->visitChildren(this);
}

TParser::IntegerContext* TParser::integer() {
  IntegerContext *_localctx = _tracker.createInstance<IntegerContext>(_ctx, getState());
  enterRule(_localctx, 120, TParser::RuleInteger);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(576);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7187745005283311616) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandNameContext ------------------------------------------------------------------

TParser::OperandNameContext::OperandNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::OperandNameContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}


size_t TParser::OperandNameContext::getRuleIndex() const {
  return TParser::RuleOperandName;
}

void TParser::OperandNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperandName(this);
}

void TParser::OperandNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperandName(this);
}


std::any TParser::OperandNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitOperandName(this);
  else
    return visitor->visitChildren(this);
}

TParser::OperandNameContext* TParser::operandName() {
  OperandNameContext *_localctx = _tracker.createInstance<OperandNameContext>(_ctx, getState());
  enterRule(_localctx, 122, TParser::RuleOperandName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(578);
    match(TParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CompositeLitContext ------------------------------------------------------------------

TParser::CompositeLitContext::CompositeLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::LiteralTypeContext* TParser::CompositeLitContext::literalType() {
  return getRuleContext<TParser::LiteralTypeContext>(0);
}

TParser::LiteralValueContext* TParser::CompositeLitContext::literalValue() {
  return getRuleContext<TParser::LiteralValueContext>(0);
}


size_t TParser::CompositeLitContext::getRuleIndex() const {
  return TParser::RuleCompositeLit;
}

void TParser::CompositeLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompositeLit(this);
}

void TParser::CompositeLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompositeLit(this);
}


std::any TParser::CompositeLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitCompositeLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::CompositeLitContext* TParser::compositeLit() {
  CompositeLitContext *_localctx = _tracker.createInstance<CompositeLitContext>(_ctx, getState());
  enterRule(_localctx, 124, TParser::RuleCompositeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(580);
    literalType();
    setState(581);
    literalValue();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralTypeContext ------------------------------------------------------------------

TParser::LiteralTypeContext::LiteralTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ArrayTypeContext* TParser::LiteralTypeContext::arrayType() {
  return getRuleContext<TParser::ArrayTypeContext>(0);
}

TParser::TypeNameContext* TParser::LiteralTypeContext::typeName() {
  return getRuleContext<TParser::TypeNameContext>(0);
}

TParser::TypeArgsContext* TParser::LiteralTypeContext::typeArgs() {
  return getRuleContext<TParser::TypeArgsContext>(0);
}


size_t TParser::LiteralTypeContext::getRuleIndex() const {
  return TParser::RuleLiteralType;
}

void TParser::LiteralTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralType(this);
}

void TParser::LiteralTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralType(this);
}


std::any TParser::LiteralTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitLiteralType(this);
  else
    return visitor->visitChildren(this);
}

TParser::LiteralTypeContext* TParser::literalType() {
  LiteralTypeContext *_localctx = _tracker.createInstance<LiteralTypeContext>(_ctx, getState());
  enterRule(_localctx, 126, TParser::RuleLiteralType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(588);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::L_BRACKET: {
        enterOuterAlt(_localctx, 1);
        setState(583);
        arrayType();
        break;
      }

      case TParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 2);
        setState(584);
        typeName();
        setState(586);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TParser::L_BRACKET) {
          setState(585);
          typeArgs();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralValueContext ------------------------------------------------------------------

TParser::LiteralValueContext::LiteralValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::LiteralValueContext::L_CURLY() {
  return getToken(TParser::L_CURLY, 0);
}

tree::TerminalNode* TParser::LiteralValueContext::R_CURLY() {
  return getToken(TParser::R_CURLY, 0);
}

TParser::ElementListContext* TParser::LiteralValueContext::elementList() {
  return getRuleContext<TParser::ElementListContext>(0);
}

tree::TerminalNode* TParser::LiteralValueContext::COMMA() {
  return getToken(TParser::COMMA, 0);
}


size_t TParser::LiteralValueContext::getRuleIndex() const {
  return TParser::RuleLiteralValue;
}

void TParser::LiteralValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteralValue(this);
}

void TParser::LiteralValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteralValue(this);
}


std::any TParser::LiteralValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitLiteralValue(this);
  else
    return visitor->visitChildren(this);
}

TParser::LiteralValueContext* TParser::literalValue() {
  LiteralValueContext *_localctx = _tracker.createInstance<LiteralValueContext>(_ctx, getState());
  enterRule(_localctx, 128, TParser::RuleLiteralValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(590);
    match(TParser::L_CURLY);
    setState(595);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 871996214990607753) != 0)) {
      setState(591);
      elementList();
      setState(593);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TParser::COMMA) {
        setState(592);
        match(TParser::COMMA);
      }
    }
    setState(597);
    match(TParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementListContext ------------------------------------------------------------------

TParser::ElementListContext::ElementListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<TParser::KeyedElementContext *> TParser::ElementListContext::keyedElement() {
  return getRuleContexts<TParser::KeyedElementContext>();
}

TParser::KeyedElementContext* TParser::ElementListContext::keyedElement(size_t i) {
  return getRuleContext<TParser::KeyedElementContext>(i);
}

std::vector<tree::TerminalNode *> TParser::ElementListContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::ElementListContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::ElementListContext::getRuleIndex() const {
  return TParser::RuleElementList;
}

void TParser::ElementListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementList(this);
}

void TParser::ElementListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementList(this);
}


std::any TParser::ElementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitElementList(this);
  else
    return visitor->visitChildren(this);
}

TParser::ElementListContext* TParser::elementList() {
  ElementListContext *_localctx = _tracker.createInstance<ElementListContext>(_ctx, getState());
  enterRule(_localctx, 130, TParser::RuleElementList);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(599);
    keyedElement();
    setState(604);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(600);
        match(TParser::COMMA);
        setState(601);
        keyedElement(); 
      }
      setState(606);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 65, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyedElementContext ------------------------------------------------------------------

TParser::KeyedElementContext::KeyedElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ElementContext* TParser::KeyedElementContext::element() {
  return getRuleContext<TParser::ElementContext>(0);
}

TParser::KeyContext* TParser::KeyedElementContext::key() {
  return getRuleContext<TParser::KeyContext>(0);
}

tree::TerminalNode* TParser::KeyedElementContext::COLON() {
  return getToken(TParser::COLON, 0);
}


size_t TParser::KeyedElementContext::getRuleIndex() const {
  return TParser::RuleKeyedElement;
}

void TParser::KeyedElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKeyedElement(this);
}

void TParser::KeyedElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKeyedElement(this);
}


std::any TParser::KeyedElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitKeyedElement(this);
  else
    return visitor->visitChildren(this);
}

TParser::KeyedElementContext* TParser::keyedElement() {
  KeyedElementContext *_localctx = _tracker.createInstance<KeyedElementContext>(_ctx, getState());
  enterRule(_localctx, 132, TParser::RuleKeyedElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(610);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      setState(607);
      key();
      setState(608);
      match(TParser::COLON);
      break;
    }

    default:
      break;
    }
    setState(612);
    element();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyContext ------------------------------------------------------------------

TParser::KeyContext::KeyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ExpressionContext* TParser::KeyContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

TParser::LiteralValueContext* TParser::KeyContext::literalValue() {
  return getRuleContext<TParser::LiteralValueContext>(0);
}


size_t TParser::KeyContext::getRuleIndex() const {
  return TParser::RuleKey;
}

void TParser::KeyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKey(this);
}

void TParser::KeyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKey(this);
}


std::any TParser::KeyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitKey(this);
  else
    return visitor->visitChildren(this);
}

TParser::KeyContext* TParser::key() {
  KeyContext *_localctx = _tracker.createInstance<KeyContext>(_ctx, getState());
  enterRule(_localctx, 134, TParser::RuleKey);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(616);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET:
      case TParser::EXCLAMATION:
      case TParser::PLUS:
      case TParser::MINUS:
      case TParser::CARET:
      case TParser::STAR:
      case TParser::AMPERSAND:
      case TParser::DECIMAL_LIT:
      case TParser::BINARY_LIT:
      case TParser::OCTAL_LIT:
      case TParser::HEX_LIT:
      case TParser::FLOAT_LIT:
      case TParser::IMAGINARY_LIT:
      case TParser::RUNE_LIT:
      case TParser::RAW_STRING_LIT:
      case TParser::INTERPRETED_STRING_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(614);
        expression(0);
        break;
      }

      case TParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(615);
        literalValue();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContext ------------------------------------------------------------------

TParser::ElementContext::ElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ExpressionContext* TParser::ElementContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

TParser::LiteralValueContext* TParser::ElementContext::literalValue() {
  return getRuleContext<TParser::LiteralValueContext>(0);
}


size_t TParser::ElementContext::getRuleIndex() const {
  return TParser::RuleElement;
}

void TParser::ElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElement(this);
}

void TParser::ElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElement(this);
}


std::any TParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

TParser::ElementContext* TParser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 136, TParser::RuleElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(620);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET:
      case TParser::EXCLAMATION:
      case TParser::PLUS:
      case TParser::MINUS:
      case TParser::CARET:
      case TParser::STAR:
      case TParser::AMPERSAND:
      case TParser::DECIMAL_LIT:
      case TParser::BINARY_LIT:
      case TParser::OCTAL_LIT:
      case TParser::HEX_LIT:
      case TParser::FLOAT_LIT:
      case TParser::IMAGINARY_LIT:
      case TParser::RUNE_LIT:
      case TParser::RAW_STRING_LIT:
      case TParser::INTERPRETED_STRING_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(618);
        expression(0);
        break;
      }

      case TParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(619);
        literalValue();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- String_Context ------------------------------------------------------------------

TParser::String_Context::String_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::String_Context::RAW_STRING_LIT() {
  return getToken(TParser::RAW_STRING_LIT, 0);
}

tree::TerminalNode* TParser::String_Context::INTERPRETED_STRING_LIT() {
  return getToken(TParser::INTERPRETED_STRING_LIT, 0);
}


size_t TParser::String_Context::getRuleIndex() const {
  return TParser::RuleString_;
}

void TParser::String_Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterString_(this);
}

void TParser::String_Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitString_(this);
}


std::any TParser::String_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitString_(this);
  else
    return visitor->visitChildren(this);
}

TParser::String_Context* TParser::string_() {
  String_Context *_localctx = _tracker.createInstance<String_Context>(_ctx, getState());
  enterRule(_localctx, 138, TParser::RuleString_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(622);
    _la = _input->LA(1);
    if (!(_la == TParser::RAW_STRING_LIT

    || _la == TParser::INTERPRETED_STRING_LIT)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionLitContext ------------------------------------------------------------------

TParser::FunctionLitContext::FunctionLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::FunctionLitContext::FUNC() {
  return getToken(TParser::FUNC, 0);
}

TParser::SignatureContext* TParser::FunctionLitContext::signature() {
  return getRuleContext<TParser::SignatureContext>(0);
}

TParser::BlockContext* TParser::FunctionLitContext::block() {
  return getRuleContext<TParser::BlockContext>(0);
}


size_t TParser::FunctionLitContext::getRuleIndex() const {
  return TParser::RuleFunctionLit;
}

void TParser::FunctionLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionLit(this);
}

void TParser::FunctionLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionLit(this);
}


std::any TParser::FunctionLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFunctionLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::FunctionLitContext* TParser::functionLit() {
  FunctionLitContext *_localctx = _tracker.createInstance<FunctionLitContext>(_ctx, getState());
  enterRule(_localctx, 140, TParser::RuleFunctionLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(624);
    match(TParser::FUNC);
    setState(625);
    signature();
    setState(626);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IndexContext ------------------------------------------------------------------

TParser::IndexContext::IndexContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::IndexContext::L_BRACKET() {
  return getToken(TParser::L_BRACKET, 0);
}

TParser::ExpressionContext* TParser::IndexContext::expression() {
  return getRuleContext<TParser::ExpressionContext>(0);
}

tree::TerminalNode* TParser::IndexContext::R_BRACKET() {
  return getToken(TParser::R_BRACKET, 0);
}


size_t TParser::IndexContext::getRuleIndex() const {
  return TParser::RuleIndex;
}

void TParser::IndexContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIndex(this);
}

void TParser::IndexContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIndex(this);
}


std::any TParser::IndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIndex(this);
  else
    return visitor->visitChildren(this);
}

TParser::IndexContext* TParser::index() {
  IndexContext *_localctx = _tracker.createInstance<IndexContext>(_ctx, getState());
  enterRule(_localctx, 142, TParser::RuleIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(628);
    match(TParser::L_BRACKET);
    setState(629);
    expression(0);
    setState(630);
    match(TParser::R_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentsContext ------------------------------------------------------------------

TParser::ArgumentsContext::ArgumentsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ArgumentsContext::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

tree::TerminalNode* TParser::ArgumentsContext::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}

TParser::ExpressionListContext* TParser::ArgumentsContext::expressionList() {
  return getRuleContext<TParser::ExpressionListContext>(0);
}

TParser::Type_Context* TParser::ArgumentsContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

std::vector<tree::TerminalNode *> TParser::ArgumentsContext::COMMA() {
  return getTokens(TParser::COMMA);
}

tree::TerminalNode* TParser::ArgumentsContext::COMMA(size_t i) {
  return getToken(TParser::COMMA, i);
}


size_t TParser::ArgumentsContext::getRuleIndex() const {
  return TParser::RuleArguments;
}

void TParser::ArgumentsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArguments(this);
}

void TParser::ArgumentsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArguments(this);
}


std::any TParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

TParser::ArgumentsContext* TParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 144, TParser::RuleArguments);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(632);
    match(TParser::L_PAREN);
    setState(644);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7480408612322845700) != 0) || _la == TParser::RAW_STRING_LIT

    || _la == TParser::INTERPRETED_STRING_LIT) {
      setState(639);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 70, _ctx)) {
      case 1: {
        setState(633);
        expressionList();
        break;
      }

      case 2: {
        setState(634);
        type_();
        setState(637);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
        case 1: {
          setState(635);
          match(TParser::COMMA);
          setState(636);
          expressionList();
          break;
        }

        default:
          break;
        }
        break;
      }

      default:
        break;
      }
      setState(642);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TParser::COMMA) {
        setState(641);
        match(TParser::COMMA);
      }
    }
    setState(646);
    match(TParser::R_PAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EosContext ------------------------------------------------------------------

TParser::EosContext::EosContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::EosContext::SEMI() {
  return getToken(TParser::SEMI, 0);
}

tree::TerminalNode* TParser::EosContext::EOS() {
  return getToken(TParser::EOS, 0);
}


size_t TParser::EosContext::getRuleIndex() const {
  return TParser::RuleEos;
}

void TParser::EosContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEos(this);
}

void TParser::EosContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<TParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEos(this);
}


std::any TParser::EosContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitEos(this);
  else
    return visitor->visitChildren(this);
}

TParser::EosContext* TParser::eos() {
  EosContext *_localctx = _tracker.createInstance<EosContext>(_ctx, getState());
  enterRule(_localctx, 146, TParser::RuleEos);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(648);
    _la = _input->LA(1);
    if (!(_la == TParser::SEMI

    || _la == TParser::EOS)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool TParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 54: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool TParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 5);
    case 1: return precpred(_ctx, 4);
    case 2: return precpred(_ctx, 3);
    case 3: return precpred(_ctx, 2);
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void TParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  tparserParserInitialize();
#else
  ::antlr4::internal::call_once(tparserParserOnceFlag, tparserParserInitialize);
#endif
}
