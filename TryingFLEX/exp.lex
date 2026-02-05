/* ===== Arquivo exp.lex ===== */

%option noyywrap
%option nodefault
%option outfile="lexer.c" header-file="lexer.h"
%{
#include "exp.h"
%}


INT    [0-9]+
EXP    [Ee][\+\-]?{INT}
floatA {INT}"."{INT}?{EXP}?
floatB "."{INT}{EXP}?
floatC {INT}{EXP}
FLOAT  {floatA}|{floatB}|{floatC}
ID     [a-zA-Z_][a-zA-Z0-9_]*
RELOP  (<=)|(>=)|(!=)|(==)|(<)|(>) 
IF     [iI][fF]
THEN   [tT][hH][eE][nN]
ELSE   [eE][lL][sS][eE]
WHILE  [wW][hH][iI][lL][eE]
REPEAT [rR][eE][pP][eE][aA][tT]
UNTIL  [uU][nN][tT][iI][lL]
COMMENT   "/*"([^*]|\*+[^*/])*\*+"/"



%%
{IF} { return token(TOK_IF, "none"); }
{THEN} { return token(TOK_THEN, "none"); }
{ELSE} { return token(TOK_ELSE, "none"); }
{WHILE} { return token(TOK_WHILE, "none"); }
{REPEAT} { return token(TOK_REPEAT, "none"); }
{UNTIL} { return token(TOK_UNTIL, "none"); }
{COMMENT} { return token(TOK_COMMT, "none"); }
{RELOP} { return token(TOK_RELOP, strdup(yytext)); }
[\+\-\*\/] { return token(TOK_OP, "none"); }
[\(\)] { return token(TOK_PONT, "none"); }
":=" { return token(TOK_ATRIB, "none"); }
[ \t\n] { return token(TOK_SEP, "none"); }
{FLOAT} { return token(TOK_FLOAT,strdup(yytext)); }
{INT} { return token(TOK_INT, strdup(yytext)); }
{ID} { return token(TOK_ID, strdup(yytext)); }
<<EOF>> { return token(TOK_EOF, "none"); }
. { return token(TOK_ERRO, "none"); }
%%

// variavel global para um token
Token tok;
Token * token (int tipo, char* valor) {
    tok.tipo = tipo;
    tok.atributo = valor;
    return &tok;
}