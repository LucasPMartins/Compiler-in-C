/**
 * =============================================================================
 * ANALISADOR LÉXICO - Construção de Compiladores - UFU
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "syntax.h"

/**
 * Imprime o cabeçalho do programa.
 */
void imprimir_cabecalho(void)
{
    printf("\n");
    printf("===========================================================================================\n");
    printf("                                    Compilador - UFU                                       \n");
    printf("===========================================================================================\n");
    printf("\n");
}

/**
 * Imprime informações de uso do programa.
 */
void imprimir_uso(const char *nome_programa)
{
    printf("Uso: %s <arquivo_fonte>\n", nome_programa);
    printf("\n");
    printf("Argumentos:\n");
    printf("  arquivo_fonte    Caminho para o arquivo de codigo fonte a ser analisado\n");
    printf("\n");
    printf("Exemplo:\n");
    printf("  %s testes/teste1.txt\n", nome_programa);
    printf("\n");
}

char *token_to_str(const Token *token) {
    char *str = malloc(128 * sizeof(char));
    if (!str) return NULL;

    snprintf(str, 128,
             "<%s, %d:%d, %s>",
             str_token(token->tipo),
             token->linha,
             token->coluna,
             token->atributo ? token->atributo : "NULL");

    return str;
}

/**
 * Imprime a lista de tokens reconhecidos pelo analisador léxico.
 */
void imprimir_lista_tokens(char *file)
{
    int num_tokens = 0;
    int num_erros = 0;
    int i = 0;
    EntradaTabela *tabela[TABELA_SIMBOLOS_SIZE];
    Lexer *lexer = NULL;
    Token token;

    char *str_tokens[3];

    /* Inicializa o analisador léxico */
    lexer = inicializar_lexer(file, tabela);
    if (lexer == NULL)
    {
        printf("Erro: Falha ao inicializar analisador lexico.\n");
        destruir_tabela(tabela);
        return;
    }

    /* Inicializa a tabela de símbolos */
    inicializar_tabela(tabela);
    if (tabela == NULL)
    {
        printf("Erro: Falha ao inicializar tabela de simbolos.\n");
        return;
    }

    /* Imprime cabeçalho da lista de tokens */
    printf("===========================================================================================\n");
    printf("                                    ANALISADOR LEXICO                                      \n");
    printf("===========================================================================================\n");
    printf("\n");
    /* Loop principal: processa todos os tokens */
    do
    {
        token = proximo_token(lexer);
        num_tokens++;


        /* Imprime o token */
        if(num_tokens % 3 == 0) {
            str_tokens[i] = token_to_str(&token);
            printf("| %-27s | %-27s | %-27s |\n", str_tokens[0], str_tokens[1], str_tokens[2]);
            i = 0;
        }else{
            str_tokens[i] = token_to_str(&token);
            i++;
        }

        /* Conta erros */
        if (token.tipo == T_ERROR)
        {
            num_erros++;
        }

    } while (token.tipo != T_EOF);

    printf("\n");
    printf("===========================================================================================\n");
    printf("                                   RESUMO DA ANALISE                                       \n");
    printf("===========================================================================================\n");
    printf("Total de tokens reconhecidos: %d\n", num_tokens);
    printf("Total de erros lexicos: %d\n", num_erros);
    printf("===========================================================================================\n\n");

    /* Imprime a tabela de símbolos final */
    imprimir_tabela(tabela);

    printf("Analise lexica concluida com sucesso!\n\n");

    /* Limpa recursos */
    destruir_lexer(lexer);
    destruir_tabela(tabela);
}

void imprimir_arvore_derivacao(No *no, int nivel)
{
    if (no == NULL)
        return;

    /* Indentação para visualização hierárquica */
    for (int i = 0; i < nivel; i++)
        printf("  ");

    /* Imprime o símbolo do nó */
    if (no->simbolo.classe == SIMBOLO_TERMINAL)
    {
        printf("Terminal: %s\n", str_token(no->simbolo.valor));
    }
    else
    {
        printf("Nao-Terminal: %s\n", NOME_NAO_TERMINAIS[no->simbolo.valor]);
    }

    /* Recursão para os filhos */
    for (int i = 0; i < no->num_filhos; i++)
    {
        imprimir_arvore_derivacao(no->filhos[i], nivel + 1);
    }
}

/**
 * Função principal do programa.
 */
int main(int argc, char *argv[])
{
    EntradaTabela *tabela[TABELA_SIMBOLOS_SIZE];
    ArvoreDerivacao *arvore = NULL;
    Lexer *lexer = NULL;
    Token token;
    int opcao = 0;

    /* Imprime cabeçalho */
    imprimir_cabecalho();

    /* Verifica argumentos */
    if (argc < 2)
    {
        fprintf(stderr, "Erro: Arquivo fonte nao especificado.\n\n");
        imprimir_uso(argv[0]);
        return 1;
    }

    printf("Arquivo fonte: %s\n", argv[1]);
    printf("\n");

    printf("===========================================================================================\n\n");
    do
    {
        printf("Selecine a opcao de analise:\n");
        printf("1 - Analise Lexica\n");
        printf("2 - Analise Sintatica\n");
        printf("3 - Compilar\n");
        printf("4 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        switch (opcao)
        {
        case 1:
            imprimir_lista_tokens(argv[1]);
            break;
        case 2:
            inicializar_tabela(tabela);
            if (tabela == NULL)
            {
                fprintf(stderr, "Erro: Falha ao inicializar tabela de simbolos.\n\n");
                return 1;
            }
            lexer = inicializar_lexer(argv[1], tabela);
            if (lexer == NULL)
            {
                fprintf(stderr, "Erro: Falha ao inicializar analisador lexico.\n\n");
                destruir_tabela(tabela);
                return 1;
            }
            arvore = parser(lexer);
            if (arvore != NULL)
            {
                printf("Analise sintatica concluida com sucesso!\n\n");
                //imprimir_arvore_derivacao(arvore->raiz, 0);
            }
            else
            {
                printf("Analise sintatica falhou.\n\n");
            }
            break;
        case 3:
            break;
        case 4:
            opcao = 4; // Sair
            break;
        default:
            opcao = 0;
            printf("Opcao invalida. Tente novamente.\n\n");
            break;
        }
    } while (opcao != 4);

    printf("Saindo do programa.\n");
    destruir_lexer(lexer);
    destruir_tabela(tabela);
    return 0;
}
