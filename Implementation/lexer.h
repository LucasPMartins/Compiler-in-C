#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "tabela_simbolos.h"

/* Tamanho máximo do buffer para construção de lexemas */
#define TAM_BUFFER_LEXEMA 1024

/**
 * Estrutura principal do Analisador Léxico.
 * 
 * Mantém o estado atual da análise, incluindo:
 * - Ponteiro para o arquivo fonte
 * - Caractere atual sendo analisado
 * - Posição atual (linha e coluna)
 * - Buffer para construção de lexemas
 * - Referência para a tabela de símbolos
 */
typedef struct {
    FILE* arquivo;                      /* Arquivo fonte sendo analisado */
    char atual;                         /* Caractere atual (lookahead) */
    int linha;                          /* Linha atual (1-based) */
    int coluna;                         /* Coluna atual (1-based) */
    char buffer[TAM_BUFFER_LEXEMA];     /* Buffer para construção de lexemas */
    int buf_pos;                        /* Posição atual no buffer */
    EntradaTabela** tabela;             /* Ponteiro para tabela de símbolos */
    int eof_alcancado;                  /* Flag indicando fim de arquivo */
} Lexer;

/**
 * Inicializa o analisador léxico para processar um arquivo.
 * 
 * @param nome_arquivo Caminho para o arquivo fonte
 * @param tabela Ponteiro para a tabela de símbolos inicializada
 * @return Ponteiro para o Lexer inicializado, ou NULL em caso de erro
 */
Lexer* inicializar_lexer(const char* nome_arquivo, EntradaTabela* tabela[]);

/**
 * Libera os recursos alocados pelo analisador léxico.
 * Fecha o arquivo e libera a memória do Lexer.
 * 
 * @param lexer Ponteiro para o Lexer a ser destruído
 */
void destruir_lexer(Lexer* lexer);

/**
 * Função principal do analisador léxico.
 * Retorna o próximo token encontrado no arquivo fonte.
 * 
 * Esta função implementa o Autômato Finito Determinístico que:
 * - Ignora whitespace e comentários
 * - Reconhece identificadores e palavras reservadas
 * - Reconhece constantes numéricas (int e float)
 * - Reconhece constantes de caractere
 * - Reconhece operadores e delimitadores
 * - Reporta erros léxicos
 * 
 * @param lexer Ponteiro para o Lexer
 * @return Token reconhecido (incluindo T_EOF ou T_ERROR)
 */
Token proximo_token(Lexer* lexer);

/**
 * Retorna o caractere atual sem consumi-lo.
 * Útil para verificar o próximo caractere (lookahead).
 * 
 * @param lexer Ponteiro para o Lexer
 * @return Caractere atual
 */
char peek(Lexer* lexer);

/**
 * Adiciona um caractere ao buffer de lexema.
 */
static void adicionar_ao_buffer(Lexer* lexer, char c);

/**
 * Inicializa o buffer de lexema (limpa e reseta posição).
 */
static void limpar_buffer(Lexer* lexer);

/**
 * Avança para o próximo caractere do arquivo.
 * Atualiza a posição (linha/coluna) conforme necessário.
 */
static void avancar(Lexer* lexer);

/**
 * Verifica se um caractere é uma letra (a-z, A-Z, _).
 * 
 * @param c Caractere a verificar
 * @return 1 se for letra ou underscore, 0 caso contrário
 */
int eh_letra(char c);

/**
 * Verifica se um caractere é um dígito (0-9).
 * 
 * @param c Caractere a verificar
 * @return 1 se for dígito, 0 caso contrário
 */
int eh_digito(char c);

/**
 * Verifica se um caractere é alfanumérico (letra ou dígito).
 * 
 * @param c Caractere a verificar
 * @return 1 se for alfanumérico, 0 caso contrário
 */
int eh_alfanumerico(char c);

/**
 * Verifica se um caractere é whitespace (espaço, tab, newline, CR).
 * 
 * @param c Caractere a verificar
 * @return 1 se for whitespace, 0 caso contrário
 */
int eh_whitespace(char c);

#endif /* LEXER_H */

