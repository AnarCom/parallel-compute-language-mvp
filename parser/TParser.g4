parser grammar TParser;

options {
	tokenVocab = TLexer;
}

// These are all supported parser sections:

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.
@parser::header {/* parser/listener/visitor header section */}

// Appears before any #include in h + cpp files.
@parser::preinclude {/* parser precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@parser::postinclude {
/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
/* public parser declarations/members section */
bool myAction() { return true; }
bool doesItBlend() { return true; }
void cleanUp() {}
void doInit() {}
void doAfter() {}
}

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}

// Actual grammar start.

sourceFile
    : /*packageClause eos (importDecl eos)**/ ((functionDecl | /*methodDecl |*/ declaration | statement) eos)* EOF
    ;
/*
packageClause
    : PACKAGE packageName {this.myreset();}
    ;*/
/*
packageName
    : identifier
    ;*/

identifier : IDENTIFIER ;
/* 
importDecl
    : IMPORT (importSpec | L_PAREN (importSpec eos)* R_PAREN)
    ;

importSpec
    : (DOT | packageName)? importPath {this.addImportSpec();}
    ;

importPath
    : string_
    ;*/

declaration
    : constDecl
    //| typeDecl
    | varDecl
    ;

constDecl
    : CONST (constSpec | L_PAREN (constSpec eos)* R_PAREN)
    ;

constSpec
    : identifierList (type_? ASSIGN expressionList)?
    ;

identifierList
    : IDENTIFIER (COMMA IDENTIFIER)*
    ;

expressionList
    : expression (COMMA expression)*
    ;
/*
typeDecl
    : TYPE (typeSpec | L_PAREN (typeSpec eos)* R_PAREN)
    ;*/

typeSpec
    : aliasDecl
    | typeDef
    ;

aliasDecl
    : IDENTIFIER typeParameters? ASSIGN type_
    ;

typeDef
    : IDENTIFIER typeParameters? type_
    ;

typeParameters
    : L_BRACKET typeParameterDecl (COMMA typeParameterDecl)* R_BRACKET
    ;

typeParameterDecl
    : identifierList typeElement
    ;

typeElement
    : typeTerm (OR typeTerm)*
    ;

typeTerm
    : UNDERLYING? type_
    ;

// Function declarations

functionDecl
    : FUNC IDENTIFIER typeParameters? signature block?
    ;
/*
methodDecl
    : FUNC receiver IDENTIFIER signature block?
    ;

receiver
    : parameters
    ;*/

varDecl
    : VAR (varSpec | L_PAREN (varSpec eos)* R_PAREN)
    ;

varSpec
    : identifierList (type_ (ASSIGN expressionList)? | ASSIGN expressionList)
    ;

block
    : L_CURLY statementList R_CURLY
    ;

statementList
    : ( (SEMI | EOS | /* {this.closingBracket()}? */ ) statement eos)*
    ;

statement
    : declaration
//    | labeledStmt
    | simpleStmt
//    | goStmt
    | returnStmt
    | breakStmt
    | continueStmt
//    | gotoStmt
//    | fallthroughStmt
    | block
    | ifStmt
//    | switchStmt
//    | selectStmt
    | joinStmt
    | forStmt
//    | deferStmt
    ;

simpleStmt
    //: sendStmt
    : emitStmt
    | syncReturnStmt
    | incDecStmt
    | assignment
    | expressionStmt
    | shortVarDecl
    ;

expressionStmt
    : expression
    ;
/*
sendStmt
    : channel = expression RECEIVE expression
    ;*/

syncReturnStmt
    : channel = expression SYNC_RETURN expression
    ;

emitStmt
    : channel = expression EMIT expression
    ;

incDecStmt
    : expression (PLUS_PLUS | MINUS_MINUS)
    ;

assignment
    : expressionList assign_op expressionList
    ;

assign_op
    : (PLUS | MINUS | OR | CARET | STAR | DIV | MOD | LSHIFT | RSHIFT | AMPERSAND | BIT_CLEAR)? ASSIGN
    ;

shortVarDecl
    : identifierList DECLARE_ASSIGN expressionList
    ;
/*
labeledStmt
    : IDENTIFIER COLON statement?
    ;*/

returnStmt
    : RETURN expressionList?
    ;

breakStmt
    : BREAK IDENTIFIER?
    ;

continueStmt
    : CONTINUE IDENTIFIER?
    ;
/*
gotoStmt
    : GOTO IDENTIFIER
    ;

fallthroughStmt
    : FALLTHROUGH
    ;

deferStmt
    : DEFER expression
    ;*/

ifStmt
    : IF (expression | (SEMI | EOS) expression | simpleStmt (SEMI | EOS) expression) block (ELSE (ifStmt | block))?
    ;
/*
switchStmt
    : exprSwitchStmt
    | typeSwitchStmt
    ;

exprSwitchStmt
    : SWITCH (expression? | simpleStmt? eos expression?) L_CURLY exprCaseClause* R_CURLY
    ;

exprCaseClause
    : exprSwitchCase COLON statementList
    ;

exprSwitchCase
    : CASE expressionList
    | DEFAULT
    ;

typeSwitchStmt
    : SWITCH (typeSwitchGuard | eos typeSwitchGuard | simpleStmt eos typeSwitchGuard) L_CURLY typeCaseClause* R_CURLY
    ;

typeSwitchGuard
    : (IDENTIFIER DECLARE_ASSIGN)? primaryExpr DOT L_PAREN TYPE R_PAREN
    ;

typeCaseClause
    : typeSwitchCase COLON statementList
    ;

typeSwitchCase
    : CASE typeList
    | DEFAULT
    ;*/

typeList
    : (type_ | NIL_LIT) (COMMA (type_ | NIL_LIT))*
    ;
/*
selectStmt
    : SELECT L_CURLY commClause* R_CURLY
    ;

commClause
    : commCase COLON statementList
    ;

commCase
    : CASE (sendStmt | recvStmt)
    | DEFAULT
    ;

recvStmt
    : (expressionList ASSIGN | identifierList DECLARE_ASSIGN)? recvExpr = expression
    ;*/

joinStmt
   : JOIN L_CURLY matchClause* R_CURLY
   ;

matchClause
   : matchCase COLON statementList
   ;

matchCase
   : CASE (fromChanAs COMMA)* fromChanAs
   ;

fromChanAs
   : FROM IDENTIFIER (AS IDENTIFIER)?
   ;

forStmt
    : FOR (condition | forClause /*| rangeClause*/)? block
    ;

condition
    : expression
    ;

forClause
    : initStmt = simpleStmt? eos expression? eos postStmt = simpleStmt?
    ;
/*
rangeClause
    : (expressionList ASSIGN | identifierList DECLARE_ASSIGN)? RANGE expression
    ;*/
/*
goStmt
    : GO expression
    ;*/

type_
    : typeName typeArgs?
    | typeLit
    | L_PAREN type_ R_PAREN
    ;

typeArgs
    : L_BRACKET typeList COMMA? R_BRACKET
    ;

typeName
    //: qualifiedIdent
    : IDENTIFIER
    ;

typeLit
    : arrayType
    //| structType
    //| pointerType
    | functionType
    //| interfaceType
    //| sliceType
    //| mapType
    | syncChannelType
    | asyncChannelType
    ;

arrayType
    : L_BRACKET arrayLength R_BRACKET elementType
    ;

arrayLength
    : expression
    ;

elementType
    : type_
    ;
/*
pointerType
    : STAR type_
    ;

interfaceType
    : INTERFACE L_CURLY ((methodSpec | typeElement) eos)* R_CURLY
    ;

sliceType
    : L_BRACKET R_BRACKET elementType
    ;

// It's possible to replace `type` with more restricted typeLit list and also pay attention to nil maps
mapType
    : MAP L_BRACKET type_ R_BRACKET elementType
    ;

channelType
    : ({this.isNotReceive()}? CHAN | CHAN RECEIVE | RECEIVE CHAN) elementType
    ;

methodSpec
    : IDENTIFIER parameters result
    | IDENTIFIER parameters
    ;*/

asyncChannelType
    : ASYNC elementType
    ;

syncChannelType
    : SYNC signature
    ;

functionType
    : FUNC signature
    ;

signature
    : parameters result?
    ;

result
    : parameters
    | type_
    ;

parameters
    : L_PAREN (parameterDecl (COMMA parameterDecl)* COMMA?)? R_PAREN
    ;

parameterDecl
    : identifierList? /*ELLIPSIS?*/ type_
    ;

expression
    : primaryExpr
    | unary_op = (PLUS | MINUS | EXCLAMATION | CARET | STAR | AMPERSAND /*| RECEIVE*/) expression
    | expression mul_op = (STAR | DIV | MOD | LSHIFT | RSHIFT | AMPERSAND | BIT_CLEAR) expression
    | expression add_op = (PLUS | MINUS | OR | CARET) expression
    | expression rel_op = (
        EQUALS
        | NOT_EQUALS
        | LESS
        | LESS_OR_EQUALS
        | GREATER
        | GREATER_OR_EQUALS
    ) expression
    | expression LOGICAL_AND expression
    | expression LOGICAL_OR expression
    ;

primaryExpr :
    operand
    /*( {this->isOperand()}? operand
    | {this->isConversion()}? conversion
    | {this.isMethodExpr()}? methodExpr )*/
    ( /*DOT IDENTIFIER* | index | /*slice_ | typeAssertion |*/ arguments )*
    ;

conversion
    : type_ L_PAREN expression COMMA? R_PAREN
    ;

operand
    : literal
    | operandName typeArgs?
    | L_PAREN expression R_PAREN
    ;

literal
    : basicLit
    | compositeLit
    | functionLit
    ;

basicLit
    : NIL_LIT
    | integer
    | string_
    | FLOAT_LIT
    ;

integer
    : DECIMAL_LIT
    | BINARY_LIT
    | OCTAL_LIT
    | HEX_LIT
    | IMAGINARY_LIT
    | RUNE_LIT
    ;

operandName
    : IDENTIFIER
   // | qualifiedIdent
    ;
/*
qualifiedIdent
    : IDENTIFIER DOT IDENTIFIER
    ;*/

compositeLit
    : literalType literalValue
    ;

literalType
    //: structType
    : arrayType
    //| L_BRACKET ELLIPSIS R_BRACKET elementType
    //| sliceType
    //| mapType
    | typeName typeArgs?
    ;

literalValue
    : L_CURLY (elementList COMMA?)? R_CURLY
    ;

elementList
    : keyedElement (COMMA keyedElement)*
    ;

keyedElement
    : (key COLON)? element
    ;

key
    : expression
    | literalValue
    ;

element
    : expression
    | literalValue
    ;
/*
structType
    : STRUCT L_CURLY (fieldDecl eos)* R_CURLY
    ;

fieldDecl
    : (identifierList type_ | embeddedField) tag = string_?
    ;*/

string_
    : RAW_STRING_LIT
    | INTERPRETED_STRING_LIT
    ;
/*
embeddedField
    : STAR? typeName typeArgs?
    ;*/

functionLit
    : FUNC signature block
    ; // function

index
    : L_BRACKET expression R_BRACKET
    ;
/*
slice_
    : L_BRACKET (expression? COLON expression? | expression? COLON expression COLON expression) R_BRACKET
    ;*/
/*
typeAssertion
    : DOT L_PAREN type_ R_PAREN
    ;*/

arguments
    : L_PAREN ((expressionList | type_ (COMMA expressionList)?) /*ELLIPSIS?*/ COMMA?)? R_PAREN
    ;
/*
methodExpr
    : type_ DOT IDENTIFIER
    ;*/

eos
    : SEMI
    | EOS
    //| {this->closingBracket()}?
    ;