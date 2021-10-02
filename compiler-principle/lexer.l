%{
#include "AbsSyntaxTree.h"
#include "parser.hpp"
#include <stdio.h>
#include <string>
using namespace std;
extern "C" int yywrap() {return 1;}
%}

%%
[ \t\n]                                             { }

"("                                                 { return LP; }
")"                                                 { return RP; }
"["                                                 { return LB; }
"]"                                                 { return RB; }
"."                                                 { return DOT; }
","                                                 { return COMMA; }
":"                                                 { return COLON; }
"*"                                                 { return MUL; }
"/"                                                 { return DIV; }
"<>"                                                { return UNEQUAL; }
"NOT"                                               { return NOT; }
"+"                                                 { return PLUS; }
"-"                                                 { return MINUS; }
">="                                                { return GE; }
">"                                                 { return GT; }
"<="                                                { return LE; }
"<"                                                 { return LT; }
"="                                                 { return EQUAL; }
":="                                                { return ASSIGN; }
"MOD"                                               { return MOD; }
".."                                                { return DOTDOT; }
";"                                                 { return SEMI; }
"and"                                               { return AND; }
"array"                                             { return ARRAY; }
"begin"                                             { return _BEGIN; }
"case"                                              { return CASE; }
"const"                                             { return CONST; }
"div"                                               { return DIV; }
"do"                                                { return DO; }
"downto"                                            { return DOWNTO; }
"else"                                              { return ELSE; }
"end"                                               { return END; }
"for"                                               { return FOR; }
"function"                                          { return FUNCTION; }
"goto"                                              { return GOTO; }
"if"                                                { return IF; }
"mod"                                               { return MOD; }
"not"                                               { return NOT; }
"of"                                                { return OF; }
"or"                                                { return OR; }
"packed"                                            { return PACKED; }
"procedure"                                         { return PROCEDURE; }
"program"                                           { return PROGRAM; }
"record"                                            { return RECORD; }
"repeat"                                            { return REPEAT; }
"then"                                              { return THEN; }
"to"                                                { return TO; }
"type"                                              { return TYPE; }
"until"                                             { return UNTIL; }
"var"                                               { return VAR; }
"while"                                             { return WHILE; }
"false"|"maxint"|"true"                             {
                                                        yylval.stringValue = new string(yytext); 
                                                        return SYS_CONST; 
                                                    }
"abs"|"chr"|"odd"|"ord"|"pred"|"sqr"|"sqrt"|"succ"  {
                                                        yylval.stringValue = new string(yytext); 
                                                        return SYS_FUNC; 
                                                    }
"write"|"writeln"                                   {
                                                        yylval.stringValue = new string(yytext);
                                                        return SYS_PROC; 
                                                    }
"boolean"|"char"|"integer"|"real"                   {
                                                        yylval.stringValue = new string(yytext); 
                                                        return SYS_TYPE; 
                                                    }
"read"                                              {
                                                        yylval.stringValue = new string(yytext);
                                                        return READ; 
                                                    }
[0-9]+                                              {
                                                        yylval.intValue = atoi(yytext); 
                                                        return INTEGER; 
                                                    }
[0-9]+\.[0-9]+                                      {
                                                        yylval.doubleValue = atof(yytext);
                                                        return REAL; 
                                                    }
\'.\'                                               { 
                                                        yylval.charValue = yytext[1];
                                                        return CHAR; 
                                                    }

[a-zA-Z][_a-zA-Z0-9]*                               {
                                                        yylval.stringValue = new string(yytext);
                                                        return ID;
                                                    }

%%