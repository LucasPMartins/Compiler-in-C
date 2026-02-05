#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include "token.h"

#define TABELA_SIMBOLOS_SIZE 211  /* Tamanho da tabela de símbolos (número primo para melhor distribuição) */

/**
 * Estrutura que representa uma entrada na tabela de símbolos.
 * 
 * Campos:
 * - lexema: String do identificador ou palavra reservada
 * - nome_token: nome do token associado (T_ID, T_INT, etc.)
 * - tipo_dado: Tipo de dado da variável (int, float, etc.)
 * - proximo: Ponteiro para tratamento de colisões por encadeamento
 */
typedef struct EntradaTabela {
    char *lexema;                   /* Nome do símbolo */
    char *nome_token;               /* Nome do token */
    char *tipo_dado;                /* Tipo de dado  */
} EntradaTabela;

/**
 * Inicializa a tabela de símbolos.
 */
void inicializar_tabela(EntradaTabela* tabela[]);

/**
 * Libera toda a memória alocada pela tabela de símbolos.
 */
void destruir_tabela(EntradaTabela* tabela[]);

/**
 * Função hash simples para mapear lexemas a índices na tabela.
 * 
 * @param lexema String a ser mapeada
 * @return Índice na tabela de símbolos
 */
int hash(const char* lexema);

/**
 * Busca um símbolo na tabela pelo lexema. (lookup)
 * 
 * @param lexema String a ser buscada
 * @return Ponteiro para a entrada encontrada, ou NULL se não existir
 */
EntradaTabela* buscar_simbolo(EntradaTabela* tabela[], const char* lexema);

/**
 * Insere um novo símbolo na tabela.
 * Se o símbolo já existir, retorna -1.
 * 
 * @param lexema String do símbolo a inserir
 * @param tipo_token Tipo do token associado
 * @param tipo_dado Tipo de dado associado
 * @return Índice da entrada inserida ou existente, -1 em caso de erro ou se já existir
 */
int inserir_simbolo(EntradaTabela* tabela[], const char* lexema, TipoToken tipo_token, char *tipo_dado);

/**
 * Imprime todos os símbolos da tabela de forma formatada.
 * Útil para debug e verificação.
 */
void imprimir_tabela(EntradaTabela* tabela[]);

#endif /* TABELA_SIMBOLOS_H */