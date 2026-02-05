/**
 * =============================================================================
 * ANALISADOR LÉXICO - Construção de Compiladores - UFU
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "tabela_simbolos.h"
#include "lexer.h"
#include "syntax.h"

/**
 * Imprime o cabeçalho do programa.
 */
void imprimir_cabecalho(void) {
    printf("\n");
    printf("================================================================================\n");
    printf("                                Compilador - UFU                                \n");
    printf("================================================================================\n");
    printf("\n");
}

/**
 * Imprime informações de uso do programa.
 */
void imprimir_uso(const char* nome_programa) {
    printf("Uso: %s <arquivo_fonte>\n", nome_programa);
    printf("\n");
    printf("Argumentos:\n");
    printf("  arquivo_fonte    Caminho para o arquivo de codigo fonte a ser analisado\n");
    printf("\n");
    printf("Exemplo:\n");
    printf("  %s testes/teste1.txt\n", nome_programa);
    printf("\n");
}

/**
 * Imprime a lista de tokens reconhecidos pelo analisador léxico.
 */
void imprimir_lista_tokens(char* file) {
    int num_tokens = 0;
    int num_erros = 0;
    EntradaTabela * tabela[TABELA_SIMBOLOS_SIZE];
    Lexer* lexer = NULL;
    Token token;

    /* Inicializa o analisador léxico */
    printf("Inicializando analisador lexico...\n");
    lexer = inicializar_lexer(file, tabela);
    if (lexer == NULL) {
        fprintf(stderr, "Erro: Falha ao inicializar analisador lexico.\n");
        destruir_tabela(tabela);
        return 1;
    }

    /* Inicializa a tabela de símbolos */
    printf("Inicializando tabela de simbolos...\n");
    inicializar_tabela(tabela);
    if (tabela == NULL) {
        fprintf(stderr, "Erro: Falha ao inicializar tabela de simbolos.\n");
        return 1;
    }
    printf("Tabela de simbolos inicializada.\n");

    /* Imprime cabeçalho da lista de tokens */
    printf("================================================================================\n");
    printf("                      ANALISADOR LEXICO - LISTA DE TOKENS                       \n");
    printf("================================================================================\n");
    printf("\n");
    /* Loop principal: processa todos os tokens */
    do {
        token = proximo_token(lexer);
        
        /* Imprime o token */
        imprimir_token(&token);
        num_tokens++;
        
        /* Conta erros */
        if (token.tipo == T_ERROR) {
            num_erros++;
        }
        
    } while (token.tipo != T_EOF);
    
    printf("\n");
    printf("================================================================================\n");
    printf("                              RESUMO DA ANALISE                                 \n");
    printf("================================================================================\n");
    printf("Total de tokens reconhecidos: %d\n", num_tokens);
    printf("Total de erros lexicos: %d\n", num_erros);
    printf("================================================================================\n\n");

    printf("Analise lexica concluida com sucesso!\n\n");

    /* Limpa recursos */
    destruir_lexer(lexer);
    destruir_tabela(tabela);
}

/**
 * Função principal do programa.
 */
int main(int argc, char* argv[]) {
    EntradaTabela * tabela[TABELA_SIMBOLOS_SIZE];
    Lexer* lexer = NULL;
    Token token;
    
    /* Imprime cabeçalho */
    imprimir_cabecalho();
    
    /* Verifica argumentos */
    if (argc < 2) {
        fprintf(stderr, "Erro: Arquivo fonte nao especificado.\n\n");
        imprimir_uso(argv[0]);
        return 1;
    }
    
    printf("Arquivo fonte: %s\n", argv[1]);
    printf("\n");
    
    /* Inicializa a tabela de símbolos */
    printf("Inicializando tabela de simbolos...\n");
    inicializar_tabela(tabela);
    if (tabela == NULL) {
        fprintf(stderr, "Erro: Falha ao inicializar tabela de simbolos.\n");
        return 1;
    }
    printf("Tabela de simbolos inicializada.\n");

    /* Inicializa o analisador léxico */
    printf("Inicializando analisador lexico...\n");
    lexer = inicializar_lexer(argv[1], tabela);
    if (lexer == NULL) {
        fprintf(stderr, "Erro: Falha ao inicializar analisador lexico.\n");
        destruir_tabela(tabela);
        return 1;
    }
    printf("Analisador lexico inicializado.\n");
    printf("\n");

    /* Imprime a tabela de símbolos final */
    imprimir_tabela(tabela);
    
    /* Limpa recursos */
    destruir_lexer(lexer);
    destruir_tabela(tabela);

    return 0;
}

