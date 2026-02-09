#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"
#include "token.h"

/**
 * Cria uma nova entrada para a tabela de símbolos.
 * Função auxiliar interna.
 */
static EntradaTabela* criar_entrada(const char* lexema, TipoToken tipo_token, char *tipo_dado) {
    EntradaTabela* entrada = (EntradaTabela*) malloc(sizeof(EntradaTabela));
    
    if (entrada == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memoria para entrada da tabela\n");
        return NULL;
    }
    
    /* Copia o lexema com proteção contra overflow */
    int len_lexema = strlen(lexema);
    entrada->lexema = (char*)malloc(len_lexema + 1);
    strncpy(entrada->lexema, lexema, len_lexema);
    entrada->lexema[len_lexema] = '\0';

    int len_nome_token = strlen(str_token(tipo_token));
    entrada->nome_token = (char*)malloc(len_nome_token + 1);
    strncpy(entrada->nome_token, str_token(tipo_token), len_nome_token);
    entrada->nome_token[len_nome_token] = '\0';

    int len_tipo_dado = strlen(tipo_dado);
    entrada->tipo_dado = (char*)malloc(len_tipo_dado + 1);
    strncpy(entrada->tipo_dado, tipo_dado, len_tipo_dado);
    entrada->tipo_dado[len_tipo_dado] = '\0';

    return entrada;
}

void inicializar_tabela(EntradaTabela* TabelaSimbolos[]) {
    for(int i = 0; i < TABELA_SIMBOLOS_SIZE; i++) {
        TabelaSimbolos[i] = NULL;
    } 
}

void destruir_tabela(EntradaTabela* TabelaSimbolos[]) {
    if (TabelaSimbolos == NULL) {
        return;
    }

    /* Percorre todas as posições da tabela */
    for (int i = 0; i < TABELA_SIMBOLOS_SIZE; i++) {
        EntradaTabela* entrada = TabelaSimbolos[i];
        /* Libera a entrada se existir */
        if (entrada != NULL) {
            free(entrada->lexema);
            free(entrada->nome_token);
            free(entrada->tipo_dado);
            free(entrada);
        }
    }

    /* Libera a estrutura da tabela */
    free(TabelaSimbolos);
}

int hash(const char* lexema) {
    unsigned long hash = 5381;
    int c;

    while ((c = *lexema++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % TABELA_SIMBOLOS_SIZE;
}

EntradaTabela* buscar_simbolo(EntradaTabela* TabelaSimbolos[], const char* lexema) {

    int indice = hash(lexema);

    if (TabelaSimbolos[indice] != NULL && strcmp(TabelaSimbolos[indice]->lexema, lexema) == 0) {
        return TabelaSimbolos[indice];
    }

    return NULL; /* Símbolo não encontrado */
}

int inserir_simbolo(EntradaTabela* TabelaSimbolos[], const char* lexema, TipoToken tipo_token, char *tipo_dado) {

    if (tipo_dado == NULL || lexema == NULL || strlen(lexema) == 0)  return -1;

    int indice = hash(lexema);

    if(TabelaSimbolos[indice] != NULL) return indice;

    TabelaSimbolos[indice] = criar_entrada(lexema, tipo_token, tipo_dado);

    if (TabelaSimbolos[indice] == NULL) return -1;

    return indice;
}

void imprimir_tabela(EntradaTabela* TabelaSimbolos[]) {

    if (TabelaSimbolos == NULL) {
        printf("Tabela de simbolos: NULL\n");
        return;
    }
    
    printf("\n");
    printf("===========================================================================================\n");
    printf("                                 TABELA DE SIMBOLOS                                        \n");
    printf("===========================================================================================\n");
    printf("| %-27s | %-27s | %-27s |\n", 
           "LEXEMA", "TOKEN", "TIPO DADO");
    printf("|-----------------------------|-----------------------------|-----------------------------|\n");
    
    for (int i = 0; i < TABELA_SIMBOLOS_SIZE; i++) {
        if(TabelaSimbolos[i] != NULL) {
            printf("| %-27s | %-27s | %-27s |\n",
                    TabelaSimbolos[i]->lexema,
                    TabelaSimbolos[i]->nome_token,
                    TabelaSimbolos[i]->tipo_dado
                );
        }
    }
    printf("===========================================================================================\n\n");
}
