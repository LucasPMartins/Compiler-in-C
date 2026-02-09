#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

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
    printf("<%s, %d:%d, %s>",
           str_token(token->tipo),
           token->linha,
           token->coluna,
           token->atributo);
}


