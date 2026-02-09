#ifndef SYNTAX_H
#define SYNTAX_H

#include "lexer.h"

/* ============================================================================
 * DEFINIÇÕES E ESTRUTURAS PARA ANÁLISE SINTÁTICA
 * ============================================================================ */

#define NUM_TOKENS 29

#define SIMBOLO_FIM -1

typedef enum {
    SIMBOLO_TERMINAL,
    SIMBOLO_NAO_TERMINAL
} TipoSimbolo;

typedef struct {
    TipoSimbolo classe;
    int valor;   /* TipoToken ou NaoTerminal */
} Simbolo;

typedef struct Pilha {
    Simbolo simbolo;
    struct Pilha* proximo;
} Pilha;

typedef struct No {
    Simbolo simbolo;
    struct No** filhos;
    int num_filhos;
} No;

typedef struct ArvoreDerivacao {
    No* raiz;
} ArvoreDerivacao;

enum NaoTerminais {
    S, BLOCO, LISTA_DECL_LOC, TIPO, LISTA_IDS, LISTA_IDS_LINHA,
    LISTA_COM, COMANDO, POS_ID_COM, ENTIDADE, IF, IF_TAIL,
    ELSIF, ELSE, WHILE, DO, FOR, EXPRESSAO, EXPR_LINHA,
    TERMO, TERMO_LINHA, POTENCIA, POTENCIA_LINHA, FATOR,
    CONDICAO, OPERANDO_COND, OPER_RELAC, EPSILON, /* EPSILON deve ser o último para facilitar a identificação */
    NUM_NAO_TERMINAIS // Total de linhas: 27
};

extern const char* NOME_NAO_TERMINAIS[NUM_NAO_TERMINAIS];

extern int TabelaPreditiva[NUM_NAO_TERMINAIS][NUM_TOKENS];


/* ============================================================================
 * PROTÓTIPOS DE FUNÇÕES PARA ANÁLISE SINTÁTICA
 * ============================================================================ */

/* Função principal do parser, que recebe um lexer e retorna a árvore de derivação */
ArvoreDerivacao *parser(Lexer *lexer);

/* Função para criar um novo nó na árvore de derivação */
No *criar_no(Simbolo simbolo);

/* Função para inicializar a pilha */
Pilha *inicializar_pilha();

/* Função para empilhar um símbolo na pilha */
int empilhar(Pilha *pilha, Simbolo simbolo);

/* Função para desempilhar um símbolo da pilha */
int desempilhar(Pilha *pilha);

/* Função para obter o símbolo no topo da pilha */
Simbolo topo_pilha(Pilha *pilha);

/* Função para verificar se a pilha está vazia */
int pilha_vazia(Pilha *pilha);

/* Função para liberar a memória alocada para a árvore de derivação */
void destruir_arvore(No *no);

/* Adiciona um filho a um nó pai na árvore de derivação */
void adicionar_filho(No *pai, No *filho);

/* Retorna a produção correspondente ao não-terminal e token, e o tamanho da produção */
Simbolo *obter_producao(Simbolo topo, Token token, int *tamanho);

#endif /* SYNTAX_H */