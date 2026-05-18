/* parser/listener/visitor header section */

// Generated from TParser.g4 by ANTLR 4.13.2

/* parser precinclude section */

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
      "identifierList", "expressionList", "typeDecl", "typeSpec", "aliasDecl", 
      "typeDef", "typeParameters", "typeParameterDecl", "typeElement", "typeTerm", 
      "functionDecl", "varDecl", "varSpec", "block", "statementList", "statement", 
      "simpleStmt", "expressionStmt", "syncReturnStmt", "emitStmt", "incDecStmt", 
      "assignment", "assign_op", "shortVarDecl", "returnStmt", "breakStmt", 
      "continueStmt", "ifStmt", "typeList", "joinStmt", "matchClause", "matchCase", 
      "fromChanAs", "forStmt", "condition", "forClause", "type_", "typeArgs", 
      "typeName", "typeLit", "arrayType", "arrayLength", "elementType", 
      "sliceType", "asyncChannelType", "syncChannelType", "functionType", 
      "signature", "result", "parameters", "parameterDecl", "expression", 
      "primaryExpr", "conversion", "operand", "literal", "basicLit", "integer", 
      "operandName", "qualifiedIdent", "compositeLit", "literalType", "literalValue", 
      "elementList", "keyedElement", "key", "element", "structType", "fieldDecl", 
      "string_", "embeddedField", "functionLit", "index", "slice_", "arguments", 
      "eos"
    },
    std::vector<std::string>{
      "", "'as'", "'async'", "'break'", "'case'", "'const'", "'continue'", 
      "'else'", "'for'", "'from'", "'func'", "'join'", "'if'", "'nil'", 
      "'return'", "'sync'", "'struct'", "'type'", "'var'", "", "'('", "')'", 
      "'{'", "'}'", "'['", "']'", "'='", "','", "';'", "':'", "'.'", "'++'", 
      "'--'", "':='", "'||'", "'&&'", "'<|'", "'=='", "'!='", "'<'", "'<='", 
      "'>'", "'>='", "'|'", "'/'", "'%'", "'<<'", "'>>'", "'&^'", "'~'", 
      "'!'", "'+'", "'-'", "'^'", "'*'", "'&'", "'<-'"
    },
    std::vector<std::string>{
      "", "AS", "ASYNC", "BREAK", "CASE", "CONST", "CONTINUE", "ELSE", "FOR", 
      "FROM", "FUNC", "JOIN", "IF", "NIL_LIT", "RETURN", "SYNC", "STRUCT", 
      "TYPE", "VAR", "IDENTIFIER", "L_PAREN", "R_PAREN", "L_CURLY", "R_CURLY", 
      "L_BRACKET", "R_BRACKET", "ASSIGN", "COMMA", "SEMI", "COLON", "DOT", 
      "PLUS_PLUS", "MINUS_MINUS", "DECLARE_ASSIGN", "LOGICAL_OR", "LOGICAL_AND", 
      "SYNC_RETURN", "EQUALS", "NOT_EQUALS", "LESS", "LESS_OR_EQUALS", "GREATER", 
      "GREATER_OR_EQUALS", "OR", "DIV", "MOD", "LSHIFT", "RSHIFT", "BIT_CLEAR", 
      "UNDERLYING", "EXCLAMATION", "PLUS", "MINUS", "CARET", "STAR", "AMPERSAND", 
      "EMIT", "DECIMAL_LIT", "BINARY_LIT", "OCTAL_LIT", "HEX_LIT", "FLOAT_LIT", 
      "DECIMAL_FLOAT_LIT", "HEX_FLOAT_LIT", "IMAGINARY_LIT", "RUNE_LIT", 
      "BYTE_VALUE", "OCTAL_BYTE_VALUE", "HEX_BYTE_VALUE", "LITTLE_U_VALUE", 
      "BIG_U_VALUE", "RAW_STRING_LIT", "INTERPRETED_STRING_LIT", "WS", "COMMENT", 
      "TERMINATOR", "LINE_COMMENT", "WS_NLSEMI", "COMMENT_NLSEMI", "LINE_COMMENT_NLSEMI", 
      "EOS", "OTHER"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,81,758,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,2,34,7,34,2,35,7,
  	35,2,36,7,36,2,37,7,37,2,38,7,38,2,39,7,39,2,40,7,40,2,41,7,41,2,42,7,
  	42,2,43,7,43,2,44,7,44,2,45,7,45,2,46,7,46,2,47,7,47,2,48,7,48,2,49,7,
  	49,2,50,7,50,2,51,7,51,2,52,7,52,2,53,7,53,2,54,7,54,2,55,7,55,2,56,7,
  	56,2,57,7,57,2,58,7,58,2,59,7,59,2,60,7,60,2,61,7,61,2,62,7,62,2,63,7,
  	63,2,64,7,64,2,65,7,65,2,66,7,66,2,67,7,67,2,68,7,68,2,69,7,69,2,70,7,
  	70,2,71,7,71,2,72,7,72,2,73,7,73,2,74,7,74,2,75,7,75,2,76,7,76,2,77,7,
  	77,2,78,7,78,2,79,7,79,2,80,7,80,1,0,1,0,1,0,3,0,166,8,0,1,0,1,0,5,0,
  	170,8,0,10,0,12,0,173,9,0,1,0,1,0,1,1,1,1,1,2,1,2,1,2,3,2,182,8,2,1,3,
  	1,3,1,3,1,3,1,3,1,3,5,3,190,8,3,10,3,12,3,193,9,3,1,3,3,3,196,8,3,1,4,
  	1,4,3,4,200,8,4,1,4,1,4,3,4,204,8,4,1,5,1,5,1,5,5,5,209,8,5,10,5,12,5,
  	212,9,5,1,6,1,6,1,6,5,6,217,8,6,10,6,12,6,220,9,6,1,7,1,7,1,7,1,7,1,7,
  	1,7,5,7,228,8,7,10,7,12,7,231,9,7,1,7,3,7,234,8,7,1,8,1,8,3,8,238,8,8,
  	1,9,1,9,3,9,242,8,9,1,9,1,9,1,9,1,10,1,10,3,10,249,8,10,1,10,1,10,1,11,
  	1,11,1,11,1,11,5,11,257,8,11,10,11,12,11,260,9,11,1,11,1,11,1,12,1,12,
  	1,12,1,13,1,13,1,13,5,13,270,8,13,10,13,12,13,273,9,13,1,14,3,14,276,
  	8,14,1,14,1,14,1,15,1,15,1,15,3,15,283,8,15,1,15,1,15,3,15,287,8,15,1,
  	16,1,16,1,16,1,16,1,16,1,16,5,16,295,8,16,10,16,12,16,298,9,16,1,16,3,
  	16,301,8,16,1,17,1,17,1,17,1,17,3,17,307,8,17,1,17,1,17,3,17,311,8,17,
  	1,18,1,18,1,18,1,18,1,19,1,19,1,19,3,19,320,8,19,1,19,1,19,1,19,5,19,
  	325,8,19,10,19,12,19,328,9,19,1,20,1,20,1,20,1,20,1,20,1,20,1,20,1,20,
  	1,20,3,20,339,8,20,1,21,1,21,1,21,1,21,1,21,1,21,3,21,347,8,21,1,22,1,
  	22,1,23,1,23,1,23,1,23,1,24,1,24,1,24,1,24,1,25,1,25,1,25,1,26,1,26,1,
  	26,1,26,1,27,3,27,367,8,27,1,27,1,27,1,28,1,28,1,28,1,28,1,29,1,29,3,
  	29,377,8,29,1,30,1,30,3,30,381,8,30,1,31,1,31,3,31,385,8,31,1,32,1,32,
  	1,32,1,32,1,32,1,32,1,32,1,32,3,32,395,8,32,1,32,1,32,1,32,1,32,3,32,
  	401,8,32,3,32,403,8,32,1,33,1,33,3,33,407,8,33,1,33,1,33,1,33,3,33,412,
  	8,33,5,33,414,8,33,10,33,12,33,417,9,33,1,34,1,34,1,34,5,34,422,8,34,
  	10,34,12,34,425,9,34,1,34,1,34,1,35,1,35,1,35,1,35,1,36,1,36,1,36,1,36,
  	5,36,437,8,36,10,36,12,36,440,9,36,1,36,1,36,1,37,1,37,1,37,1,37,3,37,
  	448,8,37,1,38,1,38,1,38,3,38,453,8,38,1,38,1,38,1,39,1,39,1,40,3,40,460,
  	8,40,1,40,1,40,3,40,464,8,40,1,40,1,40,3,40,468,8,40,1,41,1,41,3,41,472,
  	8,41,1,41,1,41,1,41,1,41,1,41,3,41,479,8,41,1,42,1,42,1,42,3,42,484,8,
  	42,1,42,1,42,1,43,1,43,3,43,490,8,43,1,44,1,44,1,44,1,44,1,44,1,44,3,
  	44,498,8,44,1,45,1,45,3,45,502,8,45,1,45,1,45,1,45,1,46,1,46,1,47,1,47,
  	1,48,1,48,1,48,1,48,1,49,1,49,1,49,1,50,1,50,1,50,1,51,1,51,1,51,1,52,
  	1,52,3,52,526,8,52,1,53,1,53,3,53,530,8,53,1,54,1,54,1,54,1,54,5,54,536,
  	8,54,10,54,12,54,539,9,54,1,54,3,54,542,8,54,3,54,544,8,54,1,54,1,54,
  	1,55,3,55,549,8,55,1,55,1,55,1,56,1,56,1,56,1,56,3,56,557,8,56,1,56,1,
  	56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,56,1,
  	56,1,56,1,56,5,56,577,8,56,10,56,12,56,580,9,56,1,57,1,57,1,57,5,57,585,
  	8,57,10,57,12,57,588,9,57,1,57,1,57,1,57,5,57,593,8,57,10,57,12,57,596,
  	9,57,1,58,1,58,1,58,1,58,3,58,602,8,58,1,58,1,58,1,59,1,59,1,59,3,59,
  	609,8,59,1,59,1,59,1,59,1,59,3,59,615,8,59,1,60,1,60,1,60,3,60,620,8,
  	60,1,61,1,61,1,61,1,61,3,61,626,8,61,1,62,1,62,1,63,1,63,3,63,632,8,63,
  	1,64,1,64,1,64,1,64,1,65,1,65,1,65,1,66,1,66,1,66,1,66,1,66,3,66,646,
  	8,66,3,66,648,8,66,1,67,1,67,1,67,3,67,653,8,67,3,67,655,8,67,1,67,1,
  	67,1,68,1,68,1,68,5,68,662,8,68,10,68,12,68,665,9,68,1,69,1,69,1,69,3,
  	69,670,8,69,1,69,1,69,1,70,1,70,3,70,676,8,70,1,71,1,71,3,71,680,8,71,
  	1,72,1,72,1,72,1,72,1,72,5,72,687,8,72,10,72,12,72,690,9,72,1,72,1,72,
  	1,73,1,73,1,73,1,73,3,73,698,8,73,1,73,3,73,701,8,73,1,74,1,74,1,75,3,
  	75,706,8,75,1,75,1,75,3,75,710,8,75,1,76,1,76,1,76,1,76,1,77,1,77,1,77,
  	1,77,1,78,1,78,3,78,722,8,78,1,78,1,78,3,78,726,8,78,1,78,3,78,729,8,
  	78,1,78,1,78,1,78,1,78,1,78,3,78,736,8,78,1,78,1,78,1,79,1,79,1,79,1,
  	79,1,79,3,79,745,8,79,3,79,747,8,79,1,79,3,79,750,8,79,3,79,752,8,79,
  	1,79,1,79,1,80,1,80,1,80,0,1,112,81,0,2,4,6,8,10,12,14,16,18,20,22,24,
  	26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70,
  	72,74,76,78,80,82,84,86,88,90,92,94,96,98,100,102,104,106,108,110,112,
  	114,116,118,120,122,124,126,128,130,132,134,136,138,140,142,144,146,148,
  	150,152,154,156,158,160,0,10,1,0,31,32,2,0,43,48,51,55,2,0,28,28,80,80,
  	1,0,50,55,2,0,44,48,54,55,2,0,43,43,51,53,1,0,37,42,2,0,57,60,64,65,1,
  	0,71,72,2,1,28,28,80,80,798,0,171,1,0,0,0,2,176,1,0,0,0,4,181,1,0,0,0,
  	6,183,1,0,0,0,8,197,1,0,0,0,10,205,1,0,0,0,12,213,1,0,0,0,14,221,1,0,
  	0,0,16,237,1,0,0,0,18,239,1,0,0,0,20,246,1,0,0,0,22,252,1,0,0,0,24,263,
  	1,0,0,0,26,266,1,0,0,0,28,275,1,0,0,0,30,279,1,0,0,0,32,288,1,0,0,0,34,
  	302,1,0,0,0,36,312,1,0,0,0,38,326,1,0,0,0,40,338,1,0,0,0,42,346,1,0,0,
  	0,44,348,1,0,0,0,46,350,1,0,0,0,48,354,1,0,0,0,50,358,1,0,0,0,52,361,
  	1,0,0,0,54,366,1,0,0,0,56,370,1,0,0,0,58,374,1,0,0,0,60,378,1,0,0,0,62,
  	382,1,0,0,0,64,386,1,0,0,0,66,406,1,0,0,0,68,418,1,0,0,0,70,428,1,0,0,
  	0,72,432,1,0,0,0,74,443,1,0,0,0,76,449,1,0,0,0,78,456,1,0,0,0,80,459,
  	1,0,0,0,82,478,1,0,0,0,84,480,1,0,0,0,86,489,1,0,0,0,88,497,1,0,0,0,90,
  	499,1,0,0,0,92,506,1,0,0,0,94,508,1,0,0,0,96,510,1,0,0,0,98,514,1,0,0,
  	0,100,517,1,0,0,0,102,520,1,0,0,0,104,523,1,0,0,0,106,529,1,0,0,0,108,
  	531,1,0,0,0,110,548,1,0,0,0,112,556,1,0,0,0,114,581,1,0,0,0,116,597,1,
  	0,0,0,118,614,1,0,0,0,120,619,1,0,0,0,122,625,1,0,0,0,124,627,1,0,0,0,
  	126,631,1,0,0,0,128,633,1,0,0,0,130,637,1,0,0,0,132,647,1,0,0,0,134,649,
  	1,0,0,0,136,658,1,0,0,0,138,669,1,0,0,0,140,675,1,0,0,0,142,679,1,0,0,
  	0,144,681,1,0,0,0,146,697,1,0,0,0,148,702,1,0,0,0,150,705,1,0,0,0,152,
  	711,1,0,0,0,154,715,1,0,0,0,156,719,1,0,0,0,158,739,1,0,0,0,160,755,1,
  	0,0,0,162,166,3,30,15,0,163,166,3,4,2,0,164,166,3,40,20,0,165,162,1,0,
  	0,0,165,163,1,0,0,0,165,164,1,0,0,0,166,167,1,0,0,0,167,168,3,160,80,
  	0,168,170,1,0,0,0,169,165,1,0,0,0,170,173,1,0,0,0,171,169,1,0,0,0,171,
  	172,1,0,0,0,172,174,1,0,0,0,173,171,1,0,0,0,174,175,5,0,0,1,175,1,1,0,
  	0,0,176,177,5,19,0,0,177,3,1,0,0,0,178,182,3,6,3,0,179,182,3,14,7,0,180,
  	182,3,32,16,0,181,178,1,0,0,0,181,179,1,0,0,0,181,180,1,0,0,0,182,5,1,
  	0,0,0,183,195,5,5,0,0,184,196,3,8,4,0,185,191,5,20,0,0,186,187,3,8,4,
  	0,187,188,3,160,80,0,188,190,1,0,0,0,189,186,1,0,0,0,190,193,1,0,0,0,
  	191,189,1,0,0,0,191,192,1,0,0,0,192,194,1,0,0,0,193,191,1,0,0,0,194,196,
  	5,21,0,0,195,184,1,0,0,0,195,185,1,0,0,0,196,7,1,0,0,0,197,203,3,10,5,
  	0,198,200,3,82,41,0,199,198,1,0,0,0,199,200,1,0,0,0,200,201,1,0,0,0,201,
  	202,5,26,0,0,202,204,3,12,6,0,203,199,1,0,0,0,203,204,1,0,0,0,204,9,1,
  	0,0,0,205,210,5,19,0,0,206,207,5,27,0,0,207,209,5,19,0,0,208,206,1,0,
  	0,0,209,212,1,0,0,0,210,208,1,0,0,0,210,211,1,0,0,0,211,11,1,0,0,0,212,
  	210,1,0,0,0,213,218,3,112,56,0,214,215,5,27,0,0,215,217,3,112,56,0,216,
  	214,1,0,0,0,217,220,1,0,0,0,218,216,1,0,0,0,218,219,1,0,0,0,219,13,1,
  	0,0,0,220,218,1,0,0,0,221,233,5,17,0,0,222,234,3,16,8,0,223,229,5,20,
  	0,0,224,225,3,16,8,0,225,226,3,160,80,0,226,228,1,0,0,0,227,224,1,0,0,
  	0,228,231,1,0,0,0,229,227,1,0,0,0,229,230,1,0,0,0,230,232,1,0,0,0,231,
  	229,1,0,0,0,232,234,5,21,0,0,233,222,1,0,0,0,233,223,1,0,0,0,234,15,1,
  	0,0,0,235,238,3,18,9,0,236,238,3,20,10,0,237,235,1,0,0,0,237,236,1,0,
  	0,0,238,17,1,0,0,0,239,241,5,19,0,0,240,242,3,22,11,0,241,240,1,0,0,0,
  	241,242,1,0,0,0,242,243,1,0,0,0,243,244,5,26,0,0,244,245,3,82,41,0,245,
  	19,1,0,0,0,246,248,5,19,0,0,247,249,3,22,11,0,248,247,1,0,0,0,248,249,
  	1,0,0,0,249,250,1,0,0,0,250,251,3,82,41,0,251,21,1,0,0,0,252,253,5,24,
  	0,0,253,258,3,24,12,0,254,255,5,27,0,0,255,257,3,24,12,0,256,254,1,0,
  	0,0,257,260,1,0,0,0,258,256,1,0,0,0,258,259,1,0,0,0,259,261,1,0,0,0,260,
  	258,1,0,0,0,261,262,5,25,0,0,262,23,1,0,0,0,263,264,3,10,5,0,264,265,
  	3,26,13,0,265,25,1,0,0,0,266,271,3,28,14,0,267,268,5,43,0,0,268,270,3,
  	28,14,0,269,267,1,0,0,0,270,273,1,0,0,0,271,269,1,0,0,0,271,272,1,0,0,
  	0,272,27,1,0,0,0,273,271,1,0,0,0,274,276,5,49,0,0,275,274,1,0,0,0,275,
  	276,1,0,0,0,276,277,1,0,0,0,277,278,3,82,41,0,278,29,1,0,0,0,279,280,
  	5,10,0,0,280,282,5,19,0,0,281,283,3,22,11,0,282,281,1,0,0,0,282,283,1,
  	0,0,0,283,284,1,0,0,0,284,286,3,104,52,0,285,287,3,36,18,0,286,285,1,
  	0,0,0,286,287,1,0,0,0,287,31,1,0,0,0,288,300,5,18,0,0,289,301,3,34,17,
  	0,290,296,5,20,0,0,291,292,3,34,17,0,292,293,3,160,80,0,293,295,1,0,0,
  	0,294,291,1,0,0,0,295,298,1,0,0,0,296,294,1,0,0,0,296,297,1,0,0,0,297,
  	299,1,0,0,0,298,296,1,0,0,0,299,301,5,21,0,0,300,289,1,0,0,0,300,290,
  	1,0,0,0,301,33,1,0,0,0,302,310,3,10,5,0,303,306,3,82,41,0,304,305,5,26,
  	0,0,305,307,3,12,6,0,306,304,1,0,0,0,306,307,1,0,0,0,307,311,1,0,0,0,
  	308,309,5,26,0,0,309,311,3,12,6,0,310,303,1,0,0,0,310,308,1,0,0,0,311,
  	35,1,0,0,0,312,313,5,22,0,0,313,314,3,38,19,0,314,315,5,23,0,0,315,37,
  	1,0,0,0,316,320,5,28,0,0,317,320,5,80,0,0,318,320,1,0,0,0,319,316,1,0,
  	0,0,319,317,1,0,0,0,319,318,1,0,0,0,320,321,1,0,0,0,321,322,3,40,20,0,
  	322,323,3,160,80,0,323,325,1,0,0,0,324,319,1,0,0,0,325,328,1,0,0,0,326,
  	324,1,0,0,0,326,327,1,0,0,0,327,39,1,0,0,0,328,326,1,0,0,0,329,339,3,
  	4,2,0,330,339,3,42,21,0,331,339,3,58,29,0,332,339,3,60,30,0,333,339,3,
  	62,31,0,334,339,3,36,18,0,335,339,3,64,32,0,336,339,3,68,34,0,337,339,
  	3,76,38,0,338,329,1,0,0,0,338,330,1,0,0,0,338,331,1,0,0,0,338,332,1,0,
  	0,0,338,333,1,0,0,0,338,334,1,0,0,0,338,335,1,0,0,0,338,336,1,0,0,0,338,
  	337,1,0,0,0,339,41,1,0,0,0,340,347,3,48,24,0,341,347,3,46,23,0,342,347,
  	3,50,25,0,343,347,3,52,26,0,344,347,3,44,22,0,345,347,3,56,28,0,346,340,
  	1,0,0,0,346,341,1,0,0,0,346,342,1,0,0,0,346,343,1,0,0,0,346,344,1,0,0,
  	0,346,345,1,0,0,0,347,43,1,0,0,0,348,349,3,112,56,0,349,45,1,0,0,0,350,
  	351,3,112,56,0,351,352,5,36,0,0,352,353,3,112,56,0,353,47,1,0,0,0,354,
  	355,3,112,56,0,355,356,5,56,0,0,356,357,3,112,56,0,357,49,1,0,0,0,358,
  	359,3,112,56,0,359,360,7,0,0,0,360,51,1,0,0,0,361,362,3,12,6,0,362,363,
  	3,54,27,0,363,364,3,12,6,0,364,53,1,0,0,0,365,367,7,1,0,0,366,365,1,0,
  	0,0,366,367,1,0,0,0,367,368,1,0,0,0,368,369,5,26,0,0,369,55,1,0,0,0,370,
  	371,3,10,5,0,371,372,5,33,0,0,372,373,3,12,6,0,373,57,1,0,0,0,374,376,
  	5,14,0,0,375,377,3,12,6,0,376,375,1,0,0,0,376,377,1,0,0,0,377,59,1,0,
  	0,0,378,380,5,3,0,0,379,381,5,19,0,0,380,379,1,0,0,0,380,381,1,0,0,0,
  	381,61,1,0,0,0,382,384,5,6,0,0,383,385,5,19,0,0,384,383,1,0,0,0,384,385,
  	1,0,0,0,385,63,1,0,0,0,386,394,5,12,0,0,387,395,3,112,56,0,388,389,7,
  	2,0,0,389,395,3,112,56,0,390,391,3,42,21,0,391,392,7,2,0,0,392,393,3,
  	112,56,0,393,395,1,0,0,0,394,387,1,0,0,0,394,388,1,0,0,0,394,390,1,0,
  	0,0,395,396,1,0,0,0,396,402,3,36,18,0,397,400,5,7,0,0,398,401,3,64,32,
  	0,399,401,3,36,18,0,400,398,1,0,0,0,400,399,1,0,0,0,401,403,1,0,0,0,402,
  	397,1,0,0,0,402,403,1,0,0,0,403,65,1,0,0,0,404,407,3,82,41,0,405,407,
  	5,13,0,0,406,404,1,0,0,0,406,405,1,0,0,0,407,415,1,0,0,0,408,411,5,27,
  	0,0,409,412,3,82,41,0,410,412,5,13,0,0,411,409,1,0,0,0,411,410,1,0,0,
  	0,412,414,1,0,0,0,413,408,1,0,0,0,414,417,1,0,0,0,415,413,1,0,0,0,415,
  	416,1,0,0,0,416,67,1,0,0,0,417,415,1,0,0,0,418,419,5,11,0,0,419,423,5,
  	22,0,0,420,422,3,70,35,0,421,420,1,0,0,0,422,425,1,0,0,0,423,421,1,0,
  	0,0,423,424,1,0,0,0,424,426,1,0,0,0,425,423,1,0,0,0,426,427,5,23,0,0,
  	427,69,1,0,0,0,428,429,3,72,36,0,429,430,5,29,0,0,430,431,3,38,19,0,431,
  	71,1,0,0,0,432,438,5,4,0,0,433,434,3,74,37,0,434,435,5,27,0,0,435,437,
  	1,0,0,0,436,433,1,0,0,0,437,440,1,0,0,0,438,436,1,0,0,0,438,439,1,0,0,
  	0,439,441,1,0,0,0,440,438,1,0,0,0,441,442,3,74,37,0,442,73,1,0,0,0,443,
  	444,5,9,0,0,444,447,5,19,0,0,445,446,5,1,0,0,446,448,5,19,0,0,447,445,
  	1,0,0,0,447,448,1,0,0,0,448,75,1,0,0,0,449,452,5,8,0,0,450,453,3,78,39,
  	0,451,453,3,80,40,0,452,450,1,0,0,0,452,451,1,0,0,0,452,453,1,0,0,0,453,
  	454,1,0,0,0,454,455,3,36,18,0,455,77,1,0,0,0,456,457,3,112,56,0,457,79,
  	1,0,0,0,458,460,3,42,21,0,459,458,1,0,0,0,459,460,1,0,0,0,460,461,1,0,
  	0,0,461,463,3,160,80,0,462,464,3,112,56,0,463,462,1,0,0,0,463,464,1,0,
  	0,0,464,465,1,0,0,0,465,467,3,160,80,0,466,468,3,42,21,0,467,466,1,0,
  	0,0,467,468,1,0,0,0,468,81,1,0,0,0,469,471,3,86,43,0,470,472,3,84,42,
  	0,471,470,1,0,0,0,471,472,1,0,0,0,472,479,1,0,0,0,473,479,3,88,44,0,474,
  	475,5,20,0,0,475,476,3,82,41,0,476,477,5,21,0,0,477,479,1,0,0,0,478,469,
  	1,0,0,0,478,473,1,0,0,0,478,474,1,0,0,0,479,83,1,0,0,0,480,481,5,24,0,
  	0,481,483,3,66,33,0,482,484,5,27,0,0,483,482,1,0,0,0,483,484,1,0,0,0,
  	484,485,1,0,0,0,485,486,5,25,0,0,486,85,1,0,0,0,487,490,3,128,64,0,488,
  	490,5,19,0,0,489,487,1,0,0,0,489,488,1,0,0,0,490,87,1,0,0,0,491,498,3,
  	90,45,0,492,498,3,144,72,0,493,498,3,102,51,0,494,498,3,96,48,0,495,498,
  	3,100,50,0,496,498,3,98,49,0,497,491,1,0,0,0,497,492,1,0,0,0,497,493,
  	1,0,0,0,497,494,1,0,0,0,497,495,1,0,0,0,497,496,1,0,0,0,498,89,1,0,0,
  	0,499,501,5,24,0,0,500,502,3,92,46,0,501,500,1,0,0,0,501,502,1,0,0,0,
  	502,503,1,0,0,0,503,504,5,25,0,0,504,505,3,94,47,0,505,91,1,0,0,0,506,
  	507,3,112,56,0,507,93,1,0,0,0,508,509,3,82,41,0,509,95,1,0,0,0,510,511,
  	5,24,0,0,511,512,5,25,0,0,512,513,3,94,47,0,513,97,1,0,0,0,514,515,5,
  	2,0,0,515,516,3,94,47,0,516,99,1,0,0,0,517,518,5,15,0,0,518,519,3,104,
  	52,0,519,101,1,0,0,0,520,521,5,10,0,0,521,522,3,104,52,0,522,103,1,0,
  	0,0,523,525,3,108,54,0,524,526,3,106,53,0,525,524,1,0,0,0,525,526,1,0,
  	0,0,526,105,1,0,0,0,527,530,3,108,54,0,528,530,3,82,41,0,529,527,1,0,
  	0,0,529,528,1,0,0,0,530,107,1,0,0,0,531,543,5,20,0,0,532,537,3,110,55,
  	0,533,534,5,27,0,0,534,536,3,110,55,0,535,533,1,0,0,0,536,539,1,0,0,0,
  	537,535,1,0,0,0,537,538,1,0,0,0,538,541,1,0,0,0,539,537,1,0,0,0,540,542,
  	5,27,0,0,541,540,1,0,0,0,541,542,1,0,0,0,542,544,1,0,0,0,543,532,1,0,
  	0,0,543,544,1,0,0,0,544,545,1,0,0,0,545,546,5,21,0,0,546,109,1,0,0,0,
  	547,549,3,10,5,0,548,547,1,0,0,0,548,549,1,0,0,0,549,550,1,0,0,0,550,
  	551,3,82,41,0,551,111,1,0,0,0,552,553,6,56,-1,0,553,557,3,114,57,0,554,
  	555,7,3,0,0,555,557,3,112,56,7,556,552,1,0,0,0,556,554,1,0,0,0,557,578,
  	1,0,0,0,558,559,10,6,0,0,559,560,5,56,0,0,560,577,3,112,56,7,561,562,
  	10,5,0,0,562,563,7,4,0,0,563,577,3,112,56,6,564,565,10,4,0,0,565,566,
  	7,5,0,0,566,577,3,112,56,5,567,568,10,3,0,0,568,569,7,6,0,0,569,577,3,
  	112,56,4,570,571,10,2,0,0,571,572,5,35,0,0,572,577,3,112,56,3,573,574,
  	10,1,0,0,574,575,5,34,0,0,575,577,3,112,56,2,576,558,1,0,0,0,576,561,
  	1,0,0,0,576,564,1,0,0,0,576,567,1,0,0,0,576,570,1,0,0,0,576,573,1,0,0,
  	0,577,580,1,0,0,0,578,576,1,0,0,0,578,579,1,0,0,0,579,113,1,0,0,0,580,
  	578,1,0,0,0,581,594,3,118,59,0,582,586,5,30,0,0,583,585,5,19,0,0,584,
  	583,1,0,0,0,585,588,1,0,0,0,586,584,1,0,0,0,586,587,1,0,0,0,587,593,1,
  	0,0,0,588,586,1,0,0,0,589,593,3,154,77,0,590,593,3,156,78,0,591,593,3,
  	158,79,0,592,582,1,0,0,0,592,589,1,0,0,0,592,590,1,0,0,0,592,591,1,0,
  	0,0,593,596,1,0,0,0,594,592,1,0,0,0,594,595,1,0,0,0,595,115,1,0,0,0,596,
  	594,1,0,0,0,597,598,3,82,41,0,598,599,5,20,0,0,599,601,3,112,56,0,600,
  	602,5,27,0,0,601,600,1,0,0,0,601,602,1,0,0,0,602,603,1,0,0,0,603,604,
  	5,21,0,0,604,117,1,0,0,0,605,615,3,120,60,0,606,608,3,126,63,0,607,609,
  	3,84,42,0,608,607,1,0,0,0,608,609,1,0,0,0,609,615,1,0,0,0,610,611,5,20,
  	0,0,611,612,3,112,56,0,612,613,5,21,0,0,613,615,1,0,0,0,614,605,1,0,0,
  	0,614,606,1,0,0,0,614,610,1,0,0,0,615,119,1,0,0,0,616,620,3,122,61,0,
  	617,620,3,130,65,0,618,620,3,152,76,0,619,616,1,0,0,0,619,617,1,0,0,0,
  	619,618,1,0,0,0,620,121,1,0,0,0,621,626,5,13,0,0,622,626,3,124,62,0,623,
  	626,3,148,74,0,624,626,5,61,0,0,625,621,1,0,0,0,625,622,1,0,0,0,625,623,
  	1,0,0,0,625,624,1,0,0,0,626,123,1,0,0,0,627,628,7,7,0,0,628,125,1,0,0,
  	0,629,632,5,19,0,0,630,632,3,128,64,0,631,629,1,0,0,0,631,630,1,0,0,0,
  	632,127,1,0,0,0,633,634,5,19,0,0,634,635,5,30,0,0,635,636,5,19,0,0,636,
  	129,1,0,0,0,637,638,3,132,66,0,638,639,3,134,67,0,639,131,1,0,0,0,640,
  	648,3,144,72,0,641,648,3,90,45,0,642,648,3,96,48,0,643,645,3,86,43,0,
  	644,646,3,84,42,0,645,644,1,0,0,0,645,646,1,0,0,0,646,648,1,0,0,0,647,
  	640,1,0,0,0,647,641,1,0,0,0,647,642,1,0,0,0,647,643,1,0,0,0,648,133,1,
  	0,0,0,649,654,5,22,0,0,650,652,3,136,68,0,651,653,5,27,0,0,652,651,1,
  	0,0,0,652,653,1,0,0,0,653,655,1,0,0,0,654,650,1,0,0,0,654,655,1,0,0,0,
  	655,656,1,0,0,0,656,657,5,23,0,0,657,135,1,0,0,0,658,663,3,138,69,0,659,
  	660,5,27,0,0,660,662,3,138,69,0,661,659,1,0,0,0,662,665,1,0,0,0,663,661,
  	1,0,0,0,663,664,1,0,0,0,664,137,1,0,0,0,665,663,1,0,0,0,666,667,3,140,
  	70,0,667,668,5,29,0,0,668,670,1,0,0,0,669,666,1,0,0,0,669,670,1,0,0,0,
  	670,671,1,0,0,0,671,672,3,142,71,0,672,139,1,0,0,0,673,676,3,112,56,0,
  	674,676,3,134,67,0,675,673,1,0,0,0,675,674,1,0,0,0,676,141,1,0,0,0,677,
  	680,3,112,56,0,678,680,3,134,67,0,679,677,1,0,0,0,679,678,1,0,0,0,680,
  	143,1,0,0,0,681,682,5,16,0,0,682,688,5,22,0,0,683,684,3,146,73,0,684,
  	685,3,160,80,0,685,687,1,0,0,0,686,683,1,0,0,0,687,690,1,0,0,0,688,686,
  	1,0,0,0,688,689,1,0,0,0,689,691,1,0,0,0,690,688,1,0,0,0,691,692,5,23,
  	0,0,692,145,1,0,0,0,693,694,3,10,5,0,694,695,3,82,41,0,695,698,1,0,0,
  	0,696,698,3,150,75,0,697,693,1,0,0,0,697,696,1,0,0,0,698,700,1,0,0,0,
  	699,701,3,148,74,0,700,699,1,0,0,0,700,701,1,0,0,0,701,147,1,0,0,0,702,
  	703,7,8,0,0,703,149,1,0,0,0,704,706,5,54,0,0,705,704,1,0,0,0,705,706,
  	1,0,0,0,706,707,1,0,0,0,707,709,3,86,43,0,708,710,3,84,42,0,709,708,1,
  	0,0,0,709,710,1,0,0,0,710,151,1,0,0,0,711,712,5,10,0,0,712,713,3,104,
  	52,0,713,714,3,36,18,0,714,153,1,0,0,0,715,716,5,24,0,0,716,717,3,112,
  	56,0,717,718,5,25,0,0,718,155,1,0,0,0,719,735,5,24,0,0,720,722,3,112,
  	56,0,721,720,1,0,0,0,721,722,1,0,0,0,722,723,1,0,0,0,723,725,5,29,0,0,
  	724,726,3,112,56,0,725,724,1,0,0,0,725,726,1,0,0,0,726,736,1,0,0,0,727,
  	729,3,112,56,0,728,727,1,0,0,0,728,729,1,0,0,0,729,730,1,0,0,0,730,731,
  	5,29,0,0,731,732,3,112,56,0,732,733,5,29,0,0,733,734,3,112,56,0,734,736,
  	1,0,0,0,735,721,1,0,0,0,735,728,1,0,0,0,736,737,1,0,0,0,737,738,5,25,
  	0,0,738,157,1,0,0,0,739,751,5,20,0,0,740,747,3,12,6,0,741,744,3,82,41,
  	0,742,743,5,27,0,0,743,745,3,12,6,0,744,742,1,0,0,0,744,745,1,0,0,0,745,
  	747,1,0,0,0,746,740,1,0,0,0,746,741,1,0,0,0,747,749,1,0,0,0,748,750,5,
  	27,0,0,749,748,1,0,0,0,749,750,1,0,0,0,750,752,1,0,0,0,751,746,1,0,0,
  	0,751,752,1,0,0,0,752,753,1,0,0,0,753,754,5,21,0,0,754,159,1,0,0,0,755,
  	756,7,9,0,0,756,161,1,0,0,0,89,165,171,181,191,195,199,203,210,218,229,
  	233,237,241,248,258,271,275,282,286,296,300,306,310,319,326,338,346,366,
  	376,380,384,394,400,402,406,411,415,423,438,447,452,459,463,467,471,478,
  	483,489,497,501,525,529,537,541,543,548,556,576,578,586,592,594,601,608,
  	614,619,625,631,645,647,652,654,663,669,675,679,688,697,700,705,709,721,
  	725,728,735,744,746,749,751
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
    setState(171);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4538502524505652584) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 387) != 0)) {
      setState(165);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(162);
        functionDecl();
        break;
      }

      case 2: {
        setState(163);
        declaration();
        break;
      }

      case 3: {
        setState(164);
        statement();
        break;
      }

      default:
        break;
      }
      setState(167);
      eos();
      setState(173);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(174);
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
    setState(176);
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

TParser::TypeDeclContext* TParser::DeclarationContext::typeDecl() {
  return getRuleContext<TParser::TypeDeclContext>(0);
}

TParser::VarDeclContext* TParser::DeclarationContext::varDecl() {
  return getRuleContext<TParser::VarDeclContext>(0);
}


size_t TParser::DeclarationContext::getRuleIndex() const {
  return TParser::RuleDeclaration;
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
    setState(181);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(178);
        constDecl();
        break;
      }

      case TParser::TYPE: {
        enterOuterAlt(_localctx, 2);
        setState(179);
        typeDecl();
        break;
      }

      case TParser::VAR: {
        enterOuterAlt(_localctx, 3);
        setState(180);
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
    setState(183);
    match(TParser::CONST);
    setState(195);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::IDENTIFIER: {
        setState(184);
        constSpec();
        break;
      }

      case TParser::L_PAREN: {
        setState(185);
        match(TParser::L_PAREN);
        setState(191);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == TParser::IDENTIFIER) {
          setState(186);
          constSpec();
          setState(187);
          eos();
          setState(193);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(194);
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
    setState(197);
    identifierList();
    setState(203);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 85558276) != 0)) {
      setState(199);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 18449412) != 0)) {
        setState(198);
        type_();
      }
      setState(201);
      match(TParser::ASSIGN);
      setState(202);
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
    setState(205);
    match(TParser::IDENTIFIER);
    setState(210);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::COMMA) {
      setState(206);
      match(TParser::COMMA);
      setState(207);
      match(TParser::IDENTIFIER);
      setState(212);
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
    setState(213);
    expression(0);
    setState(218);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(214);
        match(TParser::COMMA);
        setState(215);
        expression(0); 
      }
      setState(220);
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

//----------------- TypeDeclContext ------------------------------------------------------------------

TParser::TypeDeclContext::TypeDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::TypeDeclContext::TYPE() {
  return getToken(TParser::TYPE, 0);
}

std::vector<TParser::TypeSpecContext *> TParser::TypeDeclContext::typeSpec() {
  return getRuleContexts<TParser::TypeSpecContext>();
}

TParser::TypeSpecContext* TParser::TypeDeclContext::typeSpec(size_t i) {
  return getRuleContext<TParser::TypeSpecContext>(i);
}

tree::TerminalNode* TParser::TypeDeclContext::L_PAREN() {
  return getToken(TParser::L_PAREN, 0);
}

tree::TerminalNode* TParser::TypeDeclContext::R_PAREN() {
  return getToken(TParser::R_PAREN, 0);
}

std::vector<TParser::EosContext *> TParser::TypeDeclContext::eos() {
  return getRuleContexts<TParser::EosContext>();
}

TParser::EosContext* TParser::TypeDeclContext::eos(size_t i) {
  return getRuleContext<TParser::EosContext>(i);
}


size_t TParser::TypeDeclContext::getRuleIndex() const {
  return TParser::RuleTypeDecl;
}


std::any TParser::TypeDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeDeclContext* TParser::typeDecl() {
  TypeDeclContext *_localctx = _tracker.createInstance<TypeDeclContext>(_ctx, getState());
  enterRule(_localctx, 14, TParser::RuleTypeDecl);
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
    setState(221);
    match(TParser::TYPE);
    setState(233);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::IDENTIFIER: {
        setState(222);
        typeSpec();
        break;
      }

      case TParser::L_PAREN: {
        setState(223);
        match(TParser::L_PAREN);
        setState(229);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == TParser::IDENTIFIER) {
          setState(224);
          typeSpec();
          setState(225);
          eos();
          setState(231);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(232);
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


std::any TParser::TypeSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeSpec(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeSpecContext* TParser::typeSpec() {
  TypeSpecContext *_localctx = _tracker.createInstance<TypeSpecContext>(_ctx, getState());
  enterRule(_localctx, 16, TParser::RuleTypeSpec);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(237);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(235);
      aliasDecl();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(236);
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


std::any TParser::AliasDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAliasDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::AliasDeclContext* TParser::aliasDecl() {
  AliasDeclContext *_localctx = _tracker.createInstance<AliasDeclContext>(_ctx, getState());
  enterRule(_localctx, 18, TParser::RuleAliasDecl);
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
    setState(239);
    match(TParser::IDENTIFIER);
    setState(241);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::L_BRACKET) {
      setState(240);
      typeParameters();
    }
    setState(243);
    match(TParser::ASSIGN);
    setState(244);
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


std::any TParser::TypeDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeDef(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeDefContext* TParser::typeDef() {
  TypeDefContext *_localctx = _tracker.createInstance<TypeDefContext>(_ctx, getState());
  enterRule(_localctx, 20, TParser::RuleTypeDef);

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
    match(TParser::IDENTIFIER);
    setState(248);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(247);
      typeParameters();
      break;
    }

    default:
      break;
    }
    setState(250);
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


std::any TParser::TypeParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeParameters(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeParametersContext* TParser::typeParameters() {
  TypeParametersContext *_localctx = _tracker.createInstance<TypeParametersContext>(_ctx, getState());
  enterRule(_localctx, 22, TParser::RuleTypeParameters);
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
    setState(252);
    match(TParser::L_BRACKET);
    setState(253);
    typeParameterDecl();
    setState(258);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::COMMA) {
      setState(254);
      match(TParser::COMMA);
      setState(255);
      typeParameterDecl();
      setState(260);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(261);
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


std::any TParser::TypeParameterDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeParameterDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeParameterDeclContext* TParser::typeParameterDecl() {
  TypeParameterDeclContext *_localctx = _tracker.createInstance<TypeParameterDeclContext>(_ctx, getState());
  enterRule(_localctx, 24, TParser::RuleTypeParameterDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    identifierList();
    setState(264);
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


std::any TParser::TypeElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeElement(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeElementContext* TParser::typeElement() {
  TypeElementContext *_localctx = _tracker.createInstance<TypeElementContext>(_ctx, getState());
  enterRule(_localctx, 26, TParser::RuleTypeElement);
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
    setState(266);
    typeTerm();
    setState(271);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::OR) {
      setState(267);
      match(TParser::OR);
      setState(268);
      typeTerm();
      setState(273);
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


std::any TParser::TypeTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeTerm(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeTermContext* TParser::typeTerm() {
  TypeTermContext *_localctx = _tracker.createInstance<TypeTermContext>(_ctx, getState());
  enterRule(_localctx, 28, TParser::RuleTypeTerm);
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
    setState(275);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::UNDERLYING) {
      setState(274);
      match(TParser::UNDERLYING);
    }
    setState(277);
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


std::any TParser::FunctionDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFunctionDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::FunctionDeclContext* TParser::functionDecl() {
  FunctionDeclContext *_localctx = _tracker.createInstance<FunctionDeclContext>(_ctx, getState());
  enterRule(_localctx, 30, TParser::RuleFunctionDecl);
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
    setState(279);
    match(TParser::FUNC);
    setState(280);
    match(TParser::IDENTIFIER);
    setState(282);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::L_BRACKET) {
      setState(281);
      typeParameters();
    }
    setState(284);
    signature();
    setState(286);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::L_CURLY) {
      setState(285);
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


std::any TParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::VarDeclContext* TParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 32, TParser::RuleVarDecl);
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
    setState(288);
    match(TParser::VAR);
    setState(300);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::IDENTIFIER: {
        setState(289);
        varSpec();
        break;
      }

      case TParser::L_PAREN: {
        setState(290);
        match(TParser::L_PAREN);
        setState(296);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == TParser::IDENTIFIER) {
          setState(291);
          varSpec();
          setState(292);
          eos();
          setState(298);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(299);
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


std::any TParser::VarSpecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitVarSpec(this);
  else
    return visitor->visitChildren(this);
}

TParser::VarSpecContext* TParser::varSpec() {
  VarSpecContext *_localctx = _tracker.createInstance<VarSpecContext>(_ctx, getState());
  enterRule(_localctx, 34, TParser::RuleVarSpec);
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
    setState(302);
    identifierList();
    setState(310);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::ASYNC:
      case TParser::FUNC:
      case TParser::SYNC:
      case TParser::STRUCT:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET: {
        setState(303);
        type_();
        setState(306);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TParser::ASSIGN) {
          setState(304);
          match(TParser::ASSIGN);
          setState(305);
          expressionList();
        }
        break;
      }

      case TParser::ASSIGN: {
        setState(308);
        match(TParser::ASSIGN);
        setState(309);
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


std::any TParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

TParser::BlockContext* TParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 36, TParser::RuleBlock);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    match(TParser::L_CURLY);
    setState(313);
    statementList();
    setState(314);
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


std::any TParser::StatementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitStatementList(this);
  else
    return visitor->visitChildren(this);
}

TParser::StatementListContext* TParser::statementList() {
  StatementListContext *_localctx = _tracker.createInstance<StatementListContext>(_ctx, getState());
  enterRule(_localctx, 38, TParser::RuleStatementList);
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
    setState(326);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4538502524774088040) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 65923) != 0)) {
      setState(319);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case TParser::SEMI: {
          setState(316);
          match(TParser::SEMI);
          break;
        }

        case TParser::EOS: {
          setState(317);
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
        case TParser::STRUCT:
        case TParser::TYPE:
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
      setState(321);
      statement();
      setState(322);
      eos();
      setState(328);
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


std::any TParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

TParser::StatementContext* TParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 40, TParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(338);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::CONST:
      case TParser::TYPE:
      case TParser::VAR: {
        enterOuterAlt(_localctx, 1);
        setState(329);
        declaration();
        break;
      }

      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::STRUCT:
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
        setState(330);
        simpleStmt();
        break;
      }

      case TParser::RETURN: {
        enterOuterAlt(_localctx, 3);
        setState(331);
        returnStmt();
        break;
      }

      case TParser::BREAK: {
        enterOuterAlt(_localctx, 4);
        setState(332);
        breakStmt();
        break;
      }

      case TParser::CONTINUE: {
        enterOuterAlt(_localctx, 5);
        setState(333);
        continueStmt();
        break;
      }

      case TParser::L_CURLY: {
        enterOuterAlt(_localctx, 6);
        setState(334);
        block();
        break;
      }

      case TParser::IF: {
        enterOuterAlt(_localctx, 7);
        setState(335);
        ifStmt();
        break;
      }

      case TParser::JOIN: {
        enterOuterAlt(_localctx, 8);
        setState(336);
        joinStmt();
        break;
      }

      case TParser::FOR: {
        enterOuterAlt(_localctx, 9);
        setState(337);
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


std::any TParser::SimpleStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSimpleStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::SimpleStmtContext* TParser::simpleStmt() {
  SimpleStmtContext *_localctx = _tracker.createInstance<SimpleStmtContext>(_ctx, getState());
  enterRule(_localctx, 42, TParser::RuleSimpleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(346);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(340);
      emitStmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(341);
      syncReturnStmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(342);
      incDecStmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(343);
      assignment();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(344);
      expressionStmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(345);
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


std::any TParser::ExpressionStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitExpressionStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ExpressionStmtContext* TParser::expressionStmt() {
  ExpressionStmtContext *_localctx = _tracker.createInstance<ExpressionStmtContext>(_ctx, getState());
  enterRule(_localctx, 44, TParser::RuleExpressionStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(348);
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


std::any TParser::SyncReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSyncReturnStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::SyncReturnStmtContext* TParser::syncReturnStmt() {
  SyncReturnStmtContext *_localctx = _tracker.createInstance<SyncReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 46, TParser::RuleSyncReturnStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(350);
    antlrcpp::downCast<SyncReturnStmtContext *>(_localctx)->channel = expression(0);
    setState(351);
    match(TParser::SYNC_RETURN);
    setState(352);
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


std::any TParser::EmitStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitEmitStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::EmitStmtContext* TParser::emitStmt() {
  EmitStmtContext *_localctx = _tracker.createInstance<EmitStmtContext>(_ctx, getState());
  enterRule(_localctx, 48, TParser::RuleEmitStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    antlrcpp::downCast<EmitStmtContext *>(_localctx)->channel = expression(0);
    setState(355);
    match(TParser::EMIT);
    setState(356);
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


std::any TParser::IncDecStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIncDecStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::IncDecStmtContext* TParser::incDecStmt() {
  IncDecStmtContext *_localctx = _tracker.createInstance<IncDecStmtContext>(_ctx, getState());
  enterRule(_localctx, 50, TParser::RuleIncDecStmt);
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
    setState(358);
    expression(0);
    setState(359);
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


std::any TParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

TParser::AssignmentContext* TParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 52, TParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(361);
    expressionList();
    setState(362);
    assign_op();
    setState(363);
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


std::any TParser::Assign_opContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAssign_op(this);
  else
    return visitor->visitChildren(this);
}

TParser::Assign_opContext* TParser::assign_op() {
  Assign_opContext *_localctx = _tracker.createInstance<Assign_opContext>(_ctx, getState());
  enterRule(_localctx, 54, TParser::RuleAssign_op);
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
    setState(366);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 70359948084641792) != 0)) {
      setState(365);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 70359948084641792) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(368);
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


std::any TParser::ShortVarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitShortVarDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::ShortVarDeclContext* TParser::shortVarDecl() {
  ShortVarDeclContext *_localctx = _tracker.createInstance<ShortVarDeclContext>(_ctx, getState());
  enterRule(_localctx, 56, TParser::RuleShortVarDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(370);
    identifierList();
    setState(371);
    match(TParser::DECLARE_ASSIGN);
    setState(372);
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


std::any TParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ReturnStmtContext* TParser::returnStmt() {
  ReturnStmtContext *_localctx = _tracker.createInstance<ReturnStmtContext>(_ctx, getState());
  enterRule(_localctx, 58, TParser::RuleReturnStmt);
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
    setState(374);
    match(TParser::RETURN);
    setState(376);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
      setState(375);
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


std::any TParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::BreakStmtContext* TParser::breakStmt() {
  BreakStmtContext *_localctx = _tracker.createInstance<BreakStmtContext>(_ctx, getState());
  enterRule(_localctx, 60, TParser::RuleBreakStmt);
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
    setState(378);
    match(TParser::BREAK);
    setState(380);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::IDENTIFIER) {
      setState(379);
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


std::any TParser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ContinueStmtContext* TParser::continueStmt() {
  ContinueStmtContext *_localctx = _tracker.createInstance<ContinueStmtContext>(_ctx, getState());
  enterRule(_localctx, 62, TParser::RuleContinueStmt);
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
    setState(382);
    match(TParser::CONTINUE);
    setState(384);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::IDENTIFIER) {
      setState(383);
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


std::any TParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::IfStmtContext* TParser::ifStmt() {
  IfStmtContext *_localctx = _tracker.createInstance<IfStmtContext>(_ctx, getState());
  enterRule(_localctx, 64, TParser::RuleIfStmt);
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
    setState(386);
    match(TParser::IF);
    setState(394);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(387);
      expression(0);
      break;
    }

    case 2: {
      setState(388);
      _la = _input->LA(1);
      if (!(_la == TParser::SEMI

      || _la == TParser::EOS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(389);
      expression(0);
      break;
    }

    case 3: {
      setState(390);
      simpleStmt();
      setState(391);
      _la = _input->LA(1);
      if (!(_la == TParser::SEMI

      || _la == TParser::EOS)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(392);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(396);
    block();
    setState(402);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::ELSE) {
      setState(397);
      match(TParser::ELSE);
      setState(400);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case TParser::IF: {
          setState(398);
          ifStmt();
          break;
        }

        case TParser::L_CURLY: {
          setState(399);
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


std::any TParser::TypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeList(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeListContext* TParser::typeList() {
  TypeListContext *_localctx = _tracker.createInstance<TypeListContext>(_ctx, getState());
  enterRule(_localctx, 66, TParser::RuleTypeList);

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
    setState(406);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::ASYNC:
      case TParser::FUNC:
      case TParser::SYNC:
      case TParser::STRUCT:
      case TParser::IDENTIFIER:
      case TParser::L_PAREN:
      case TParser::L_BRACKET: {
        setState(404);
        type_();
        break;
      }

      case TParser::NIL_LIT: {
        setState(405);
        match(TParser::NIL_LIT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(415);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(408);
        match(TParser::COMMA);
        setState(411);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case TParser::ASYNC:
          case TParser::FUNC:
          case TParser::SYNC:
          case TParser::STRUCT:
          case TParser::IDENTIFIER:
          case TParser::L_PAREN:
          case TParser::L_BRACKET: {
            setState(409);
            type_();
            break;
          }

          case TParser::NIL_LIT: {
            setState(410);
            match(TParser::NIL_LIT);
            break;
          }

        default:
          throw NoViableAltException(this);
        } 
      }
      setState(417);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
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


std::any TParser::JoinStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitJoinStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::JoinStmtContext* TParser::joinStmt() {
  JoinStmtContext *_localctx = _tracker.createInstance<JoinStmtContext>(_ctx, getState());
  enterRule(_localctx, 68, TParser::RuleJoinStmt);
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
    setState(418);
    match(TParser::JOIN);
    setState(419);
    match(TParser::L_CURLY);
    setState(423);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::CASE) {
      setState(420);
      matchClause();
      setState(425);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(426);
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


std::any TParser::MatchClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitMatchClause(this);
  else
    return visitor->visitChildren(this);
}

TParser::MatchClauseContext* TParser::matchClause() {
  MatchClauseContext *_localctx = _tracker.createInstance<MatchClauseContext>(_ctx, getState());
  enterRule(_localctx, 70, TParser::RuleMatchClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(428);
    matchCase();
    setState(429);
    match(TParser::COLON);
    setState(430);
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


std::any TParser::MatchCaseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitMatchCase(this);
  else
    return visitor->visitChildren(this);
}

TParser::MatchCaseContext* TParser::matchCase() {
  MatchCaseContext *_localctx = _tracker.createInstance<MatchCaseContext>(_ctx, getState());
  enterRule(_localctx, 72, TParser::RuleMatchCase);

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
    setState(432);
    match(TParser::CASE);
    setState(438);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(433);
        fromChanAs();
        setState(434);
        match(TParser::COMMA); 
      }
      setState(440);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx);
    }
    setState(441);
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


std::any TParser::FromChanAsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFromChanAs(this);
  else
    return visitor->visitChildren(this);
}

TParser::FromChanAsContext* TParser::fromChanAs() {
  FromChanAsContext *_localctx = _tracker.createInstance<FromChanAsContext>(_ctx, getState());
  enterRule(_localctx, 74, TParser::RuleFromChanAs);
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
    setState(443);
    match(TParser::FROM);
    setState(444);
    antlrcpp::downCast<FromChanAsContext *>(_localctx)->chanName = match(TParser::IDENTIFIER);
    setState(447);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::AS) {
      setState(445);
      match(TParser::AS);
      setState(446);
      antlrcpp::downCast<FromChanAsContext *>(_localctx)->varName = match(TParser::IDENTIFIER);
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


std::any TParser::ForStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitForStmt(this);
  else
    return visitor->visitChildren(this);
}

TParser::ForStmtContext* TParser::forStmt() {
  ForStmtContext *_localctx = _tracker.createInstance<ForStmtContext>(_ctx, getState());
  enterRule(_localctx, 76, TParser::RuleForStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(449);
    match(TParser::FOR);
    setState(452);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      setState(450);
      condition();
      break;
    }

    case 2: {
      setState(451);
      forClause();
      break;
    }

    default:
      break;
    }
    setState(454);
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


std::any TParser::ConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitCondition(this);
  else
    return visitor->visitChildren(this);
}

TParser::ConditionContext* TParser::condition() {
  ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, getState());
  enterRule(_localctx, 78, TParser::RuleCondition);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(456);
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


std::any TParser::ForClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitForClause(this);
  else
    return visitor->visitChildren(this);
}

TParser::ForClauseContext* TParser::forClause() {
  ForClauseContext *_localctx = _tracker.createInstance<ForClauseContext>(_ctx, getState());
  enterRule(_localctx, 80, TParser::RuleForClause);
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
    setState(459);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
      setState(458);
      antlrcpp::downCast<ForClauseContext *>(_localctx)->initStmt = simpleStmt();
    }
    setState(461);
    eos();
    setState(463);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
      setState(462);
      expression(0);
    }
    setState(465);
    eos();
    setState(467);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
      setState(466);
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


std::any TParser::Type_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitType_(this);
  else
    return visitor->visitChildren(this);
}

TParser::Type_Context* TParser::type_() {
  Type_Context *_localctx = _tracker.createInstance<Type_Context>(_ctx, getState());
  enterRule(_localctx, 82, TParser::RuleType_);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(478);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::IDENTIFIER: {
        enterOuterAlt(_localctx, 1);
        setState(469);
        typeName();
        setState(471);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == TParser::L_BRACKET) {
          setState(470);
          typeArgs();
        }
        break;
      }

      case TParser::ASYNC:
      case TParser::FUNC:
      case TParser::SYNC:
      case TParser::STRUCT:
      case TParser::L_BRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(473);
        typeLit();
        break;
      }

      case TParser::L_PAREN: {
        enterOuterAlt(_localctx, 3);
        setState(474);
        match(TParser::L_PAREN);
        setState(475);
        type_();
        setState(476);
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


std::any TParser::TypeArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeArgs(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeArgsContext* TParser::typeArgs() {
  TypeArgsContext *_localctx = _tracker.createInstance<TypeArgsContext>(_ctx, getState());
  enterRule(_localctx, 84, TParser::RuleTypeArgs);
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
    setState(480);
    match(TParser::L_BRACKET);
    setState(481);
    typeList();
    setState(483);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::COMMA) {
      setState(482);
      match(TParser::COMMA);
    }
    setState(485);
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

TParser::QualifiedIdentContext* TParser::TypeNameContext::qualifiedIdent() {
  return getRuleContext<TParser::QualifiedIdentContext>(0);
}

tree::TerminalNode* TParser::TypeNameContext::IDENTIFIER() {
  return getToken(TParser::IDENTIFIER, 0);
}


size_t TParser::TypeNameContext::getRuleIndex() const {
  return TParser::RuleTypeName;
}


std::any TParser::TypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeName(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeNameContext* TParser::typeName() {
  TypeNameContext *_localctx = _tracker.createInstance<TypeNameContext>(_ctx, getState());
  enterRule(_localctx, 86, TParser::RuleTypeName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(489);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(487);
      qualifiedIdent();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(488);
      match(TParser::IDENTIFIER);
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

//----------------- TypeLitContext ------------------------------------------------------------------

TParser::TypeLitContext::TypeLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::ArrayTypeContext* TParser::TypeLitContext::arrayType() {
  return getRuleContext<TParser::ArrayTypeContext>(0);
}

TParser::StructTypeContext* TParser::TypeLitContext::structType() {
  return getRuleContext<TParser::StructTypeContext>(0);
}

TParser::FunctionTypeContext* TParser::TypeLitContext::functionType() {
  return getRuleContext<TParser::FunctionTypeContext>(0);
}

TParser::SliceTypeContext* TParser::TypeLitContext::sliceType() {
  return getRuleContext<TParser::SliceTypeContext>(0);
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


std::any TParser::TypeLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitTypeLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::TypeLitContext* TParser::typeLit() {
  TypeLitContext *_localctx = _tracker.createInstance<TypeLitContext>(_ctx, getState());
  enterRule(_localctx, 88, TParser::RuleTypeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(497);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(491);
      arrayType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(492);
      structType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(493);
      functionType();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(494);
      sliceType();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(495);
      syncChannelType();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(496);
      asyncChannelType();
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

//----------------- ArrayTypeContext ------------------------------------------------------------------

TParser::ArrayTypeContext::ArrayTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::ArrayTypeContext::L_BRACKET() {
  return getToken(TParser::L_BRACKET, 0);
}

tree::TerminalNode* TParser::ArrayTypeContext::R_BRACKET() {
  return getToken(TParser::R_BRACKET, 0);
}

TParser::ElementTypeContext* TParser::ArrayTypeContext::elementType() {
  return getRuleContext<TParser::ElementTypeContext>(0);
}

TParser::ArrayLengthContext* TParser::ArrayTypeContext::arrayLength() {
  return getRuleContext<TParser::ArrayLengthContext>(0);
}


size_t TParser::ArrayTypeContext::getRuleIndex() const {
  return TParser::RuleArrayType;
}


std::any TParser::ArrayTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitArrayType(this);
  else
    return visitor->visitChildren(this);
}

TParser::ArrayTypeContext* TParser::arrayType() {
  ArrayTypeContext *_localctx = _tracker.createInstance<ArrayTypeContext>(_ctx, getState());
  enterRule(_localctx, 90, TParser::RuleArrayType);
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
    setState(499);
    match(TParser::L_BRACKET);
    setState(501);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
      setState(500);
      arrayLength();
    }
    setState(503);
    match(TParser::R_BRACKET);
    setState(504);
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


std::any TParser::ArrayLengthContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitArrayLength(this);
  else
    return visitor->visitChildren(this);
}

TParser::ArrayLengthContext* TParser::arrayLength() {
  ArrayLengthContext *_localctx = _tracker.createInstance<ArrayLengthContext>(_ctx, getState());
  enterRule(_localctx, 92, TParser::RuleArrayLength);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(506);
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


std::any TParser::ElementTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitElementType(this);
  else
    return visitor->visitChildren(this);
}

TParser::ElementTypeContext* TParser::elementType() {
  ElementTypeContext *_localctx = _tracker.createInstance<ElementTypeContext>(_ctx, getState());
  enterRule(_localctx, 94, TParser::RuleElementType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(508);
    type_();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SliceTypeContext ------------------------------------------------------------------

TParser::SliceTypeContext::SliceTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::SliceTypeContext::L_BRACKET() {
  return getToken(TParser::L_BRACKET, 0);
}

tree::TerminalNode* TParser::SliceTypeContext::R_BRACKET() {
  return getToken(TParser::R_BRACKET, 0);
}

TParser::ElementTypeContext* TParser::SliceTypeContext::elementType() {
  return getRuleContext<TParser::ElementTypeContext>(0);
}


size_t TParser::SliceTypeContext::getRuleIndex() const {
  return TParser::RuleSliceType;
}


std::any TParser::SliceTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSliceType(this);
  else
    return visitor->visitChildren(this);
}

TParser::SliceTypeContext* TParser::sliceType() {
  SliceTypeContext *_localctx = _tracker.createInstance<SliceTypeContext>(_ctx, getState());
  enterRule(_localctx, 96, TParser::RuleSliceType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(510);
    match(TParser::L_BRACKET);
    setState(511);
    match(TParser::R_BRACKET);
    setState(512);
    elementType();
   
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


std::any TParser::AsyncChannelTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitAsyncChannelType(this);
  else
    return visitor->visitChildren(this);
}

TParser::AsyncChannelTypeContext* TParser::asyncChannelType() {
  AsyncChannelTypeContext *_localctx = _tracker.createInstance<AsyncChannelTypeContext>(_ctx, getState());
  enterRule(_localctx, 98, TParser::RuleAsyncChannelType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(514);
    match(TParser::ASYNC);
    setState(515);
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


std::any TParser::SyncChannelTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSyncChannelType(this);
  else
    return visitor->visitChildren(this);
}

TParser::SyncChannelTypeContext* TParser::syncChannelType() {
  SyncChannelTypeContext *_localctx = _tracker.createInstance<SyncChannelTypeContext>(_ctx, getState());
  enterRule(_localctx, 100, TParser::RuleSyncChannelType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(517);
    match(TParser::SYNC);
    setState(518);
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


std::any TParser::FunctionTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFunctionType(this);
  else
    return visitor->visitChildren(this);
}

TParser::FunctionTypeContext* TParser::functionType() {
  FunctionTypeContext *_localctx = _tracker.createInstance<FunctionTypeContext>(_ctx, getState());
  enterRule(_localctx, 102, TParser::RuleFunctionType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(520);
    match(TParser::FUNC);
    setState(521);
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


std::any TParser::SignatureContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSignature(this);
  else
    return visitor->visitChildren(this);
}

TParser::SignatureContext* TParser::signature() {
  SignatureContext *_localctx = _tracker.createInstance<SignatureContext>(_ctx, getState());
  enterRule(_localctx, 104, TParser::RuleSignature);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(523);
    parameters();
    setState(525);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      setState(524);
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


std::any TParser::ResultContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitResult(this);
  else
    return visitor->visitChildren(this);
}

TParser::ResultContext* TParser::result() {
  ResultContext *_localctx = _tracker.createInstance<ResultContext>(_ctx, getState());
  enterRule(_localctx, 106, TParser::RuleResult);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(529);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(527);
      parameters();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(528);
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


std::any TParser::ParametersContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitParameters(this);
  else
    return visitor->visitChildren(this);
}

TParser::ParametersContext* TParser::parameters() {
  ParametersContext *_localctx = _tracker.createInstance<ParametersContext>(_ctx, getState());
  enterRule(_localctx, 108, TParser::RuleParameters);
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
    setState(531);
    match(TParser::L_PAREN);
    setState(543);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 18449412) != 0)) {
      setState(532);
      parameterDecl();
      setState(537);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(533);
          match(TParser::COMMA);
          setState(534);
          parameterDecl(); 
        }
        setState(539);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
      }
      setState(541);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TParser::COMMA) {
        setState(540);
        match(TParser::COMMA);
      }
    }
    setState(545);
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


std::any TParser::ParameterDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitParameterDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::ParameterDeclContext* TParser::parameterDecl() {
  ParameterDeclContext *_localctx = _tracker.createInstance<ParameterDeclContext>(_ctx, getState());
  enterRule(_localctx, 110, TParser::RuleParameterDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(548);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
    case 1: {
      setState(547);
      identifierList();
      break;
    }

    default:
      break;
    }
    setState(550);
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

tree::TerminalNode* TParser::ExpressionContext::EMIT() {
  return getToken(TParser::EMIT, 0);
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
  size_t startState = 112;
  enterRecursionRule(_localctx, 112, TParser::RuleExpression, precedence);

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
    setState(556);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::STRUCT:
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
        setState(553);
        primaryExpr();
        break;
      }

      case TParser::EXCLAMATION:
      case TParser::PLUS:
      case TParser::MINUS:
      case TParser::CARET:
      case TParser::STAR:
      case TParser::AMPERSAND: {
        setState(554);
        antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 70931694131085312) != 0))) {
          antlrcpp::downCast<ExpressionContext *>(_localctx)->unary_op = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(555);
        expression(7);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(578);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(576);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(558);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(559);
          match(TParser::EMIT);
          setState(560);
          expression(7);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(561);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(562);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 54588553295822848) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->mul_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(563);
          expression(6);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(564);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(565);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 15771394788818944) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->add_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(566);
          expression(5);
          break;
        }

        case 4: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(567);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(568);
          antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8658654068736) != 0))) {
            antlrcpp::downCast<ExpressionContext *>(_localctx)->rel_op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(569);
          expression(4);
          break;
        }

        case 5: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(570);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(571);
          match(TParser::LOGICAL_AND);
          setState(572);
          expression(3);
          break;
        }

        case 6: {
          _localctx = _tracker.createInstance<ExpressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpression);
          setState(573);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(574);
          match(TParser::LOGICAL_OR);
          setState(575);
          expression(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(580);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx);
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

std::vector<tree::TerminalNode *> TParser::PrimaryExprContext::DOT() {
  return getTokens(TParser::DOT);
}

tree::TerminalNode* TParser::PrimaryExprContext::DOT(size_t i) {
  return getToken(TParser::DOT, i);
}

std::vector<TParser::IndexContext *> TParser::PrimaryExprContext::index() {
  return getRuleContexts<TParser::IndexContext>();
}

TParser::IndexContext* TParser::PrimaryExprContext::index(size_t i) {
  return getRuleContext<TParser::IndexContext>(i);
}

std::vector<TParser::Slice_Context *> TParser::PrimaryExprContext::slice_() {
  return getRuleContexts<TParser::Slice_Context>();
}

TParser::Slice_Context* TParser::PrimaryExprContext::slice_(size_t i) {
  return getRuleContext<TParser::Slice_Context>(i);
}

std::vector<TParser::ArgumentsContext *> TParser::PrimaryExprContext::arguments() {
  return getRuleContexts<TParser::ArgumentsContext>();
}

TParser::ArgumentsContext* TParser::PrimaryExprContext::arguments(size_t i) {
  return getRuleContext<TParser::ArgumentsContext>(i);
}

std::vector<tree::TerminalNode *> TParser::PrimaryExprContext::IDENTIFIER() {
  return getTokens(TParser::IDENTIFIER);
}

tree::TerminalNode* TParser::PrimaryExprContext::IDENTIFIER(size_t i) {
  return getToken(TParser::IDENTIFIER, i);
}


size_t TParser::PrimaryExprContext::getRuleIndex() const {
  return TParser::RulePrimaryExpr;
}


std::any TParser::PrimaryExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpr(this);
  else
    return visitor->visitChildren(this);
}

TParser::PrimaryExprContext* TParser::primaryExpr() {
  PrimaryExprContext *_localctx = _tracker.createInstance<PrimaryExprContext>(_ctx, getState());
  enterRule(_localctx, 114, TParser::RulePrimaryExpr);

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
    setState(581);
    operand();
    setState(594);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(592);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
        case 1: {
          setState(582);
          match(TParser::DOT);
          setState(586);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
          while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
              setState(583);
              match(TParser::IDENTIFIER); 
            }
            setState(588);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx);
          }
          break;
        }

        case 2: {
          setState(589);
          index();
          break;
        }

        case 3: {
          setState(590);
          slice_();
          break;
        }

        case 4: {
          setState(591);
          arguments();
          break;
        }

        default:
          break;
        } 
      }
      setState(596);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx);
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


std::any TParser::ConversionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitConversion(this);
  else
    return visitor->visitChildren(this);
}

TParser::ConversionContext* TParser::conversion() {
  ConversionContext *_localctx = _tracker.createInstance<ConversionContext>(_ctx, getState());
  enterRule(_localctx, 116, TParser::RuleConversion);
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
    setState(597);
    type_();
    setState(598);
    match(TParser::L_PAREN);
    setState(599);
    expression(0);
    setState(601);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::COMMA) {
      setState(600);
      match(TParser::COMMA);
    }
    setState(603);
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


std::any TParser::OperandContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitOperand(this);
  else
    return visitor->visitChildren(this);
}

TParser::OperandContext* TParser::operand() {
  OperandContext *_localctx = _tracker.createInstance<OperandContext>(_ctx, getState());
  enterRule(_localctx, 118, TParser::RuleOperand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(614);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 64, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(605);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(606);
      operandName();
      setState(608);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
      case 1: {
        setState(607);
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
      setState(610);
      match(TParser::L_PAREN);
      setState(611);
      expression(0);
      setState(612);
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


std::any TParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

TParser::LiteralContext* TParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 120, TParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(619);
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
        setState(616);
        basicLit();
        break;
      }

      case TParser::STRUCT:
      case TParser::IDENTIFIER:
      case TParser::L_BRACKET: {
        enterOuterAlt(_localctx, 2);
        setState(617);
        compositeLit();
        break;
      }

      case TParser::FUNC: {
        enterOuterAlt(_localctx, 3);
        setState(618);
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


std::any TParser::BasicLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitBasicLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::BasicLitContext* TParser::basicLit() {
  BasicLitContext *_localctx = _tracker.createInstance<BasicLitContext>(_ctx, getState());
  enterRule(_localctx, 122, TParser::RuleBasicLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(625);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::NIL_LIT: {
        enterOuterAlt(_localctx, 1);
        setState(621);
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
        setState(622);
        integer();
        break;
      }

      case TParser::RAW_STRING_LIT:
      case TParser::INTERPRETED_STRING_LIT: {
        enterOuterAlt(_localctx, 3);
        setState(623);
        string_();
        break;
      }

      case TParser::FLOAT_LIT: {
        enterOuterAlt(_localctx, 4);
        setState(624);
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


std::any TParser::IntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitInteger(this);
  else
    return visitor->visitChildren(this);
}

TParser::IntegerContext* TParser::integer() {
  IntegerContext *_localctx = _tracker.createInstance<IntegerContext>(_ctx, getState());
  enterRule(_localctx, 124, TParser::RuleInteger);
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
    setState(627);
    _la = _input->LA(1);
    if (!(((((_la - 57) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 57)) & 399) != 0))) {
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

TParser::QualifiedIdentContext* TParser::OperandNameContext::qualifiedIdent() {
  return getRuleContext<TParser::QualifiedIdentContext>(0);
}


size_t TParser::OperandNameContext::getRuleIndex() const {
  return TParser::RuleOperandName;
}


std::any TParser::OperandNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitOperandName(this);
  else
    return visitor->visitChildren(this);
}

TParser::OperandNameContext* TParser::operandName() {
  OperandNameContext *_localctx = _tracker.createInstance<OperandNameContext>(_ctx, getState());
  enterRule(_localctx, 126, TParser::RuleOperandName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(631);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 67, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(629);
      match(TParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(630);
      qualifiedIdent();
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

//----------------- QualifiedIdentContext ------------------------------------------------------------------

TParser::QualifiedIdentContext::QualifiedIdentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> TParser::QualifiedIdentContext::IDENTIFIER() {
  return getTokens(TParser::IDENTIFIER);
}

tree::TerminalNode* TParser::QualifiedIdentContext::IDENTIFIER(size_t i) {
  return getToken(TParser::IDENTIFIER, i);
}

tree::TerminalNode* TParser::QualifiedIdentContext::DOT() {
  return getToken(TParser::DOT, 0);
}


size_t TParser::QualifiedIdentContext::getRuleIndex() const {
  return TParser::RuleQualifiedIdent;
}


std::any TParser::QualifiedIdentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitQualifiedIdent(this);
  else
    return visitor->visitChildren(this);
}

TParser::QualifiedIdentContext* TParser::qualifiedIdent() {
  QualifiedIdentContext *_localctx = _tracker.createInstance<QualifiedIdentContext>(_ctx, getState());
  enterRule(_localctx, 128, TParser::RuleQualifiedIdent);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(633);
    match(TParser::IDENTIFIER);
    setState(634);
    match(TParser::DOT);
    setState(635);
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


std::any TParser::CompositeLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitCompositeLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::CompositeLitContext* TParser::compositeLit() {
  CompositeLitContext *_localctx = _tracker.createInstance<CompositeLitContext>(_ctx, getState());
  enterRule(_localctx, 130, TParser::RuleCompositeLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(637);
    literalType();
    setState(638);
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

TParser::StructTypeContext* TParser::LiteralTypeContext::structType() {
  return getRuleContext<TParser::StructTypeContext>(0);
}

TParser::ArrayTypeContext* TParser::LiteralTypeContext::arrayType() {
  return getRuleContext<TParser::ArrayTypeContext>(0);
}

TParser::SliceTypeContext* TParser::LiteralTypeContext::sliceType() {
  return getRuleContext<TParser::SliceTypeContext>(0);
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


std::any TParser::LiteralTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitLiteralType(this);
  else
    return visitor->visitChildren(this);
}

TParser::LiteralTypeContext* TParser::literalType() {
  LiteralTypeContext *_localctx = _tracker.createInstance<LiteralTypeContext>(_ctx, getState());
  enterRule(_localctx, 132, TParser::RuleLiteralType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(647);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(640);
      structType();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(641);
      arrayType();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(642);
      sliceType();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(643);
      typeName();
      setState(645);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TParser::L_BRACKET) {
        setState(644);
        typeArgs();
      }
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


std::any TParser::LiteralValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitLiteralValue(this);
  else
    return visitor->visitChildren(this);
}

TParser::LiteralValueContext* TParser::literalValue() {
  LiteralValueContext *_localctx = _tracker.createInstance<LiteralValueContext>(_ctx, getState());
  enterRule(_localctx, 134, TParser::RuleLiteralValue);
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
    setState(649);
    match(TParser::L_CURLY);
    setState(654);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 10) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 10)) & 6976004354541114953) != 0)) {
      setState(650);
      elementList();
      setState(652);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TParser::COMMA) {
        setState(651);
        match(TParser::COMMA);
      }
    }
    setState(656);
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


std::any TParser::ElementListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitElementList(this);
  else
    return visitor->visitChildren(this);
}

TParser::ElementListContext* TParser::elementList() {
  ElementListContext *_localctx = _tracker.createInstance<ElementListContext>(_ctx, getState());
  enterRule(_localctx, 136, TParser::RuleElementList);

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
    setState(658);
    keyedElement();
    setState(663);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(659);
        match(TParser::COMMA);
        setState(660);
        keyedElement(); 
      }
      setState(665);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx);
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


std::any TParser::KeyedElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitKeyedElement(this);
  else
    return visitor->visitChildren(this);
}

TParser::KeyedElementContext* TParser::keyedElement() {
  KeyedElementContext *_localctx = _tracker.createInstance<KeyedElementContext>(_ctx, getState());
  enterRule(_localctx, 138, TParser::RuleKeyedElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(669);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      setState(666);
      key();
      setState(667);
      match(TParser::COLON);
      break;
    }

    default:
      break;
    }
    setState(671);
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


std::any TParser::KeyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitKey(this);
  else
    return visitor->visitChildren(this);
}

TParser::KeyContext* TParser::key() {
  KeyContext *_localctx = _tracker.createInstance<KeyContext>(_ctx, getState());
  enterRule(_localctx, 140, TParser::RuleKey);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(675);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::STRUCT:
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
        setState(673);
        expression(0);
        break;
      }

      case TParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(674);
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


std::any TParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

TParser::ElementContext* TParser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 142, TParser::RuleElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(679);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case TParser::FUNC:
      case TParser::NIL_LIT:
      case TParser::STRUCT:
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
        setState(677);
        expression(0);
        break;
      }

      case TParser::L_CURLY: {
        enterOuterAlt(_localctx, 2);
        setState(678);
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

//----------------- StructTypeContext ------------------------------------------------------------------

TParser::StructTypeContext::StructTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::StructTypeContext::STRUCT() {
  return getToken(TParser::STRUCT, 0);
}

tree::TerminalNode* TParser::StructTypeContext::L_CURLY() {
  return getToken(TParser::L_CURLY, 0);
}

tree::TerminalNode* TParser::StructTypeContext::R_CURLY() {
  return getToken(TParser::R_CURLY, 0);
}

std::vector<TParser::FieldDeclContext *> TParser::StructTypeContext::fieldDecl() {
  return getRuleContexts<TParser::FieldDeclContext>();
}

TParser::FieldDeclContext* TParser::StructTypeContext::fieldDecl(size_t i) {
  return getRuleContext<TParser::FieldDeclContext>(i);
}

std::vector<TParser::EosContext *> TParser::StructTypeContext::eos() {
  return getRuleContexts<TParser::EosContext>();
}

TParser::EosContext* TParser::StructTypeContext::eos(size_t i) {
  return getRuleContext<TParser::EosContext>(i);
}


size_t TParser::StructTypeContext::getRuleIndex() const {
  return TParser::RuleStructType;
}


std::any TParser::StructTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitStructType(this);
  else
    return visitor->visitChildren(this);
}

TParser::StructTypeContext* TParser::structType() {
  StructTypeContext *_localctx = _tracker.createInstance<StructTypeContext>(_ctx, getState());
  enterRule(_localctx, 144, TParser::RuleStructType);
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
    setState(681);
    match(TParser::STRUCT);
    setState(682);
    match(TParser::L_CURLY);
    setState(688);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == TParser::IDENTIFIER

    || _la == TParser::STAR) {
      setState(683);
      fieldDecl();
      setState(684);
      eos();
      setState(690);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(691);
    match(TParser::R_CURLY);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FieldDeclContext ------------------------------------------------------------------

TParser::FieldDeclContext::FieldDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::IdentifierListContext* TParser::FieldDeclContext::identifierList() {
  return getRuleContext<TParser::IdentifierListContext>(0);
}

TParser::Type_Context* TParser::FieldDeclContext::type_() {
  return getRuleContext<TParser::Type_Context>(0);
}

TParser::EmbeddedFieldContext* TParser::FieldDeclContext::embeddedField() {
  return getRuleContext<TParser::EmbeddedFieldContext>(0);
}

TParser::String_Context* TParser::FieldDeclContext::string_() {
  return getRuleContext<TParser::String_Context>(0);
}


size_t TParser::FieldDeclContext::getRuleIndex() const {
  return TParser::RuleFieldDecl;
}


std::any TParser::FieldDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFieldDecl(this);
  else
    return visitor->visitChildren(this);
}

TParser::FieldDeclContext* TParser::fieldDecl() {
  FieldDeclContext *_localctx = _tracker.createInstance<FieldDeclContext>(_ctx, getState());
  enterRule(_localctx, 146, TParser::RuleFieldDecl);
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
    setState(697);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      setState(693);
      identifierList();
      setState(694);
      type_();
      break;
    }

    case 2: {
      setState(696);
      embeddedField();
      break;
    }

    default:
      break;
    }
    setState(700);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::RAW_STRING_LIT

    || _la == TParser::INTERPRETED_STRING_LIT) {
      setState(699);
      antlrcpp::downCast<FieldDeclContext *>(_localctx)->tag = string_();
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


std::any TParser::String_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitString_(this);
  else
    return visitor->visitChildren(this);
}

TParser::String_Context* TParser::string_() {
  String_Context *_localctx = _tracker.createInstance<String_Context>(_ctx, getState());
  enterRule(_localctx, 148, TParser::RuleString_);
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
    setState(702);
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

//----------------- EmbeddedFieldContext ------------------------------------------------------------------

TParser::EmbeddedFieldContext::EmbeddedFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

TParser::TypeNameContext* TParser::EmbeddedFieldContext::typeName() {
  return getRuleContext<TParser::TypeNameContext>(0);
}

tree::TerminalNode* TParser::EmbeddedFieldContext::STAR() {
  return getToken(TParser::STAR, 0);
}

TParser::TypeArgsContext* TParser::EmbeddedFieldContext::typeArgs() {
  return getRuleContext<TParser::TypeArgsContext>(0);
}


size_t TParser::EmbeddedFieldContext::getRuleIndex() const {
  return TParser::RuleEmbeddedField;
}


std::any TParser::EmbeddedFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitEmbeddedField(this);
  else
    return visitor->visitChildren(this);
}

TParser::EmbeddedFieldContext* TParser::embeddedField() {
  EmbeddedFieldContext *_localctx = _tracker.createInstance<EmbeddedFieldContext>(_ctx, getState());
  enterRule(_localctx, 150, TParser::RuleEmbeddedField);
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
    setState(705);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::STAR) {
      setState(704);
      match(TParser::STAR);
    }
    setState(707);
    typeName();
    setState(709);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == TParser::L_BRACKET) {
      setState(708);
      typeArgs();
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


std::any TParser::FunctionLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitFunctionLit(this);
  else
    return visitor->visitChildren(this);
}

TParser::FunctionLitContext* TParser::functionLit() {
  FunctionLitContext *_localctx = _tracker.createInstance<FunctionLitContext>(_ctx, getState());
  enterRule(_localctx, 152, TParser::RuleFunctionLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(711);
    match(TParser::FUNC);
    setState(712);
    signature();
    setState(713);
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


std::any TParser::IndexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitIndex(this);
  else
    return visitor->visitChildren(this);
}

TParser::IndexContext* TParser::index() {
  IndexContext *_localctx = _tracker.createInstance<IndexContext>(_ctx, getState());
  enterRule(_localctx, 154, TParser::RuleIndex);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(715);
    match(TParser::L_BRACKET);
    setState(716);
    expression(0);
    setState(717);
    match(TParser::R_BRACKET);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Slice_Context ------------------------------------------------------------------

TParser::Slice_Context::Slice_Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* TParser::Slice_Context::L_BRACKET() {
  return getToken(TParser::L_BRACKET, 0);
}

tree::TerminalNode* TParser::Slice_Context::R_BRACKET() {
  return getToken(TParser::R_BRACKET, 0);
}

std::vector<tree::TerminalNode *> TParser::Slice_Context::COLON() {
  return getTokens(TParser::COLON);
}

tree::TerminalNode* TParser::Slice_Context::COLON(size_t i) {
  return getToken(TParser::COLON, i);
}

std::vector<TParser::ExpressionContext *> TParser::Slice_Context::expression() {
  return getRuleContexts<TParser::ExpressionContext>();
}

TParser::ExpressionContext* TParser::Slice_Context::expression(size_t i) {
  return getRuleContext<TParser::ExpressionContext>(i);
}


size_t TParser::Slice_Context::getRuleIndex() const {
  return TParser::RuleSlice_;
}


std::any TParser::Slice_Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitSlice_(this);
  else
    return visitor->visitChildren(this);
}

TParser::Slice_Context* TParser::slice_() {
  Slice_Context *_localctx = _tracker.createInstance<Slice_Context>(_ctx, getState());
  enterRule(_localctx, 156, TParser::RuleSlice_);
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
    setState(719);
    match(TParser::L_BRACKET);
    setState(735);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx)) {
    case 1: {
      setState(721);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 10) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
        setState(720);
        expression(0);
      }
      setState(723);
      match(TParser::COLON);
      setState(725);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 10) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
        setState(724);
        expression(0);
      }
      break;
    }

    case 2: {
      setState(728);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 10) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 10)) & 6976004354541110857) != 0)) {
        setState(727);
        expression(0);
      }
      setState(730);
      match(TParser::COLON);
      setState(731);
      expression(0);
      setState(732);
      match(TParser::COLON);
      setState(733);
      expression(0);
      break;
    }

    default:
      break;
    }
    setState(737);
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


std::any TParser::ArgumentsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitArguments(this);
  else
    return visitor->visitChildren(this);
}

TParser::ArgumentsContext* TParser::arguments() {
  ArgumentsContext *_localctx = _tracker.createInstance<ArgumentsContext>(_ctx, getState());
  enterRule(_localctx, 158, TParser::RuleArguments);
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
    setState(739);
    match(TParser::L_PAREN);
    setState(751);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 4538502524501074948) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & 387) != 0)) {
      setState(746);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
      case 1: {
        setState(740);
        expressionList();
        break;
      }

      case 2: {
        setState(741);
        type_();
        setState(744);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
        case 1: {
          setState(742);
          match(TParser::COMMA);
          setState(743);
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
      setState(749);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == TParser::COMMA) {
        setState(748);
        match(TParser::COMMA);
      }
    }
    setState(753);
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

tree::TerminalNode* TParser::EosContext::EOF() {
  return getToken(TParser::EOF, 0);
}


size_t TParser::EosContext::getRuleIndex() const {
  return TParser::RuleEos;
}


std::any TParser::EosContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<TParserVisitor*>(visitor))
    return parserVisitor->visitEos(this);
  else
    return visitor->visitChildren(this);
}

TParser::EosContext* TParser::eos() {
  EosContext *_localctx = _tracker.createInstance<EosContext>(_ctx, getState());
  enterRule(_localctx, 160, TParser::RuleEos);
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
    setState(755);
    _la = _input->LA(1);
    if (!(_la == TParser::EOF

    || _la == TParser::SEMI || _la == TParser::EOS)) {
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
    case 56: return expressionSempred(antlrcpp::downCast<ExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool TParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 5);
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);
    case 4: return precpred(_ctx, 2);
    case 5: return precpred(_ctx, 1);

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
