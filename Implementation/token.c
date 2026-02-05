#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

/**
 * Array de strings correspondentes aos nomes dos tipos de tokens.
 * A ordem deve corresponder exatamente à ordem do enum TipoToken.
 */
static const char* NOMES_TOKENS[] = {
    /* Palavras reservadas */
    "T_VOID",
    "T_INT",
    "T_CHAR",
    "T_FLOAT",
    "T_MAIN",
    "T_IF",
    "T_THEN",
    "T_ELSIF",
    "T_ELSE",
    "T_WHILE",
    "T_DO",
    "T_FOR",
    /* Operadores */
    "T_OP",
    "T_RELOP",
    "T_ATRIB",
    /* Delimitadores */
    "T_ABREPAR",
    "T_FECHAPAR",
    "T_ABREBLOCO",
    "T_FECHABLOCO",
    "T_VIRG",
    "T_PV",
    "T_COMENT",
    /* Identificadores e constantes */
    "T_ID",
    "T_NUM_INT",
    "T_NUM_FLOAT",
    "T_CHAR_CONST",
    /* Especiais */
    "T_WS",
    "T_EOF",
    "T_ERROR"
};

/**
 * Lista de todas as palavras reservadas da linguagem.
 * Usada para pré-popular a tabela de símbolos na inicialização.
 */
static const PalavraReservada PALAVRAS_RESERVADAS[] = {
    {"void",    T_VOID},
    {"int",     T_INT},
    {"char",    T_CHAR},
    {"float",   T_FLOAT},
    {"main",    T_MAIN},
    {"if",      T_IF},
    {"then",    T_THEN},
    {"elsif",   T_ELSIF},
    {"else",    T_ELSE},
    {"while",   T_WHILE},
    {"do",      T_DO},
    {"for",     T_FOR}
};

/* Número total de palavras reservadas */
const int NUM_PALAVRAS_RESERVADAS = sizeof(PALAVRAS_RESERVADAS) / sizeof(PALAVRAS_RESERVADAS[0]);

Token criar_token(TipoToken tipo, int linha, int coluna, const char* atributo) {
    Token token;
    
    /* Inicializa os campos do token */
    token.tipo = tipo;
    token.linha = linha;
    token.coluna = coluna;

    int  len_atributo = strlen(atributo);
    /* Copia o atributo */
    if(atributo != NULL) {
        token.atributo = (char*)malloc(len_atributo + 1);
        strncpy(token.atributo, atributo, len_atributo );
        token.atributo[len_atributo] = '\0'; /* Garante terminação */
    } else {
        token.atributo = (char*)malloc(5 * sizeof(char));
        strcpy(token.atributo, "none");
    }
    
    return token;
}

TipoToken get_token(const char* lexema) {
    for (int i = 0; i < NUM_PALAVRAS_RESERVADAS; i++) {
        if (strcmp(lexema, PALAVRAS_RESERVADAS[i].lexema) == 0) {
            return PALAVRAS_RESERVADAS[i].tipo;
        }
    }
    return NUM_PALAVRAS_RESERVADAS;
}

const char* str_token(TipoToken tipo) {
    /* Verifica se o tipo está dentro do range válido */
    if (tipo >= T_VOID && tipo <= T_ERROR) {
        return NOMES_TOKENS[tipo];
    }
    return "T_DESCONHECIDO";
}

void imprimir_token(const Token* token) {
    if (token == NULL) {
        printf("<NULL TOKEN>\n");
        return;
    }
    
    /* Formato: <TIPO, linha:coluna, atributo> */
    printf("<%s, %d:%d, %s>\n",
           str_token(token->tipo),
           token->linha,
           token->coluna,
           token->atributo);
}