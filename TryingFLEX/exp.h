#include <stdlib.h>

/* ===== Arquivo exp.h ===== */

// constantes booleanas
#define TRUE 1
#define FALSE 0

// constantes para nome de token
#define TOK_INT 0 // constante numérica inteira
#define TOK_OP 1
#define TOK_PONT 2
#define TOK_ERRO 3
#define TOK_ID 4 // identificadores
#define TOK_RELOP 5 // operadores relacionais
#define TOK_SEP 6 // (espaço, \t e \n)
#define TOK_FLOAT 7 // constante numérica float: com ponto decimal e/ou notação científica
#define TOK_EOF 8 // final de arquivo
#define TOK_ATRIB 9 // atribuição (“:=”)
// palavras reservadas
#define TOK_IF 10
#define TOK_THEN 11
#define TOK_ELSE 12
#define TOK_WHILE 13
#define TOK_REPEAT 14
#define TOK_UNTIL 15
#define TOK_COMMT 16 //  “/* comentário */”

// estrutura de um token
typedef struct {
 int tipo;
 char *atributo;
} Token;

// funcao para criar um token
extern Token *token(int tipo, char *valor);

// funcao do analisador lexico
extern Token *yylex();

extern const char* TOKEN_NAMES[];