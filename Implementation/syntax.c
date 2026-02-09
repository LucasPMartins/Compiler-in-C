#include "syntax.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *NOME_NAO_TERMINAIS[] = {
    "S", "BLOCO", "LISTA_DECL_LOC", "TIPO", "LISTA_IDS", "LISTA_IDS_LINHA",
    "LISTA_COM", "COMANDO", "POS_ID_COM", "ENTIDADE", "IF", "IF_TAIL",
    "ELSIF", "ELSE", "WHILE", "DO", "FOR", "EXPRESSAO", "EXPR_LINHA",
    "TERMO", "TERMO_LINHA", "POTENCIA", "POTENCIA_LINHA", "FATOR",
    "CONDICAO", "OPERANDO_COND", "OPER_RELAC", "EPSILON"};

/*
 * Matriz de Análise Sintática (Parsing Table)
 * Linhas: 27 (Não-Terminais)
 * Colunas: 29 (Tokens)
 */
int TabelaPreditiva[NUM_NAO_TERMINAIS][NUM_TOKENS] = {
    /* VOID, INT, CHAR, FLOAT, MAIN, IF, THEN, ELSIF, ELSE, WHILE, DO, FOR, OP, RELOP, ATRIB, ( , ) , { , } , , , ; , COMENT, ID, N_INT, N_FLOAT, C_CONST, WS, EOF, ERROR */
    /* [S] */ {0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [BLOCO] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [LISTA_DECL_LOC] */ {2, 2, 2, 2, -1, 3, -1, -1, -1, 3, 3, 3, -1, -1, -1, -1, -1, -1, 3, -1, -1, -1, 3, -1, -1, -1, -1, -1, -1},
    /* [TIPO] */ {4, 5, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [LISTA_IDS] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 8, -1, -1, -1, -1, -1, -1},
    /* [LISTA_IDS_L] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 9, 10, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [LISTA_COM] */ {-1, -1, -1, -1, -1, 11, -1, -1, -1, 11, 11, 11, -1, -1, -1, -1, -1, -1, 12, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1},
    /* [COMANDO] */ {-1, -1, -1, -1, -1, 13, -1, -1, -1, 14, 15, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17, -1, -1, -1, -1, -1, -1},
    /* [POS_ID_COM] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [ENTIDADE] */ {-1, -1, -1, -1, -1, 20, -1, -1, -1, 20, 20, 20, -1, -1, -1, -1, -1, 19, -1, -1, -1, -1, 20, -1, -1, -1, -1, -1, -1},
    /* [IF_STMT] */ {-1, -1, -1, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [IF_TAIL] */ {-1, -1, -1, -1, -1, 24, -1, 22, 23, 24, 24, 24, -1, -1, -1, -1, -1, -1, 24, -1, -1, -1, 24, -1, -1, -1, -1, -1, -1},
    /* [ELSIF_STMT] */ {-1, -1, -1, -1, -1, -1, -1, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [ELSE_STMT] */ {-1, -1, -1, -1, -1, -1, -1, -1, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [WHILE_STMT] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, 27, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [DO_STMT] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [FOR_STMT] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 29, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [EXPR] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30, -1, -1, -1, -1, -1, -1, 30, 30, 30, 30, -1, -1, -1},
    /* [EXPR_L] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 31, -1, -1, -1, 33, -1, 33, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [TERMO] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 34, -1, -1, -1, -1, -1, -1, 34, 34, 34, 34, -1, -1, -1},
    /* [TERMO_L] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 35, -1, -1, -1, 37, -1, 37, -1, 37, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [POTENCIA] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 38, -1, -1, -1, -1, -1, -1, 38, 38, 38, 38, -1, -1, -1},
    /* [POTENCIA_L] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 39, -1, -1, -1, 40, -1, 40, -1, 40, -1, -1, -1, -1, -1, -1, -1, -1},
    /* [FATOR] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 45, -1, -1, -1, -1, -1, -1, 41, 42, 43, 44, -1, -1, -1},
    /* [CONDICAO] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 46, 46, 46, 46, -1, -1, -1},
    /* [OPERANDO_COND] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 47, 48, 49, 50, -1, -1, -1},
    /* [OPER_RELAC] */ {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

static const Simbolo prod0[] = {
    {SIMBOLO_NAO_TERMINAL, TIPO},
    {SIMBOLO_TERMINAL, T_MAIN},
    {SIMBOLO_TERMINAL, T_ABREPAR},
    {SIMBOLO_TERMINAL, T_FECHAPAR},
    {SIMBOLO_NAO_TERMINAL, BLOCO},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod1[] = {
    {SIMBOLO_TERMINAL, T_ABREBLOCO},
    {SIMBOLO_NAO_TERMINAL, LISTA_DECL_LOC},
    {SIMBOLO_NAO_TERMINAL, LISTA_COM},
    {SIMBOLO_TERMINAL, T_FECHABLOCO},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod2[] = {
    {SIMBOLO_NAO_TERMINAL, TIPO},
    {SIMBOLO_NAO_TERMINAL, LISTA_IDS},
    {SIMBOLO_TERMINAL, T_PV},
    {SIMBOLO_NAO_TERMINAL, LISTA_DECL_LOC},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prodEPSILON[] = {{SIMBOLO_TERMINAL, SIMBOLO_FIM}}; /* EPSILON */
static const Simbolo prod4[] = {{SIMBOLO_TERMINAL, T_VOID}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod5[] = {{SIMBOLO_TERMINAL, T_INT}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod6[] = {{SIMBOLO_TERMINAL, T_CHAR}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod7[] = {{SIMBOLO_TERMINAL, T_FLOAT}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod8[] = {
    {SIMBOLO_TERMINAL, T_ID},
    {SIMBOLO_NAO_TERMINAL, LISTA_IDS_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod9[] = {
    {SIMBOLO_TERMINAL, T_VIRG},
    {SIMBOLO_TERMINAL, T_ID},
    {SIMBOLO_NAO_TERMINAL, LISTA_IDS_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod11[] = {
    {SIMBOLO_NAO_TERMINAL, COMANDO},
    {SIMBOLO_NAO_TERMINAL, LISTA_COM},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod13[] = {{SIMBOLO_NAO_TERMINAL, IF}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod14[] = {{SIMBOLO_NAO_TERMINAL, WHILE}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod15[] = {{SIMBOLO_NAO_TERMINAL, DO}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod16[] = {{SIMBOLO_NAO_TERMINAL, FOR}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod17[] = {
    {SIMBOLO_TERMINAL, T_ID},
    {SIMBOLO_NAO_TERMINAL, POS_ID_COM},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod18[] = {
    {SIMBOLO_TERMINAL, T_ATRIB},
    {SIMBOLO_NAO_TERMINAL, EXPRESSAO},
    {SIMBOLO_TERMINAL, T_PV},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod19[] = {{SIMBOLO_NAO_TERMINAL, BLOCO}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod20[] = {{SIMBOLO_NAO_TERMINAL, COMANDO}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod21[] = {
    {SIMBOLO_TERMINAL, T_IF},
    {SIMBOLO_TERMINAL, T_ABREPAR},
    {SIMBOLO_NAO_TERMINAL, CONDICAO},
    {SIMBOLO_TERMINAL, T_FECHAPAR},
    {SIMBOLO_TERMINAL, T_THEN},
    {SIMBOLO_NAO_TERMINAL, ENTIDADE},
    {SIMBOLO_NAO_TERMINAL, IF_TAIL},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod22[] = {
    {SIMBOLO_NAO_TERMINAL, ELSIF},
    {SIMBOLO_NAO_TERMINAL, IF_TAIL},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod23[] = {{SIMBOLO_NAO_TERMINAL, ELSE}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod25[] = {
    {SIMBOLO_TERMINAL, T_ELSIF},
    {SIMBOLO_TERMINAL, T_ABREPAR},
    {SIMBOLO_NAO_TERMINAL, CONDICAO},
    {SIMBOLO_TERMINAL, T_FECHAPAR},
    {SIMBOLO_TERMINAL, T_THEN},
    {SIMBOLO_NAO_TERMINAL, ENTIDADE},
    {SIMBOLO_NAO_TERMINAL, IF_TAIL},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM},
};
static const Simbolo prod26[] = {
    {SIMBOLO_TERMINAL, T_ELSE},
    {SIMBOLO_NAO_TERMINAL, ENTIDADE},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod27[] = {
    {SIMBOLO_TERMINAL, T_WHILE},
    {SIMBOLO_TERMINAL, T_ABREPAR},
    {SIMBOLO_NAO_TERMINAL, CONDICAO},
    {SIMBOLO_TERMINAL, T_FECHAPAR},
    {SIMBOLO_TERMINAL, T_DO},
    {SIMBOLO_NAO_TERMINAL, ENTIDADE},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod28[] = {
    {SIMBOLO_TERMINAL, T_DO},
    {SIMBOLO_NAO_TERMINAL, ENTIDADE},
    {SIMBOLO_TERMINAL, T_WHILE},
    {SIMBOLO_TERMINAL, T_ABREPAR},
    {SIMBOLO_NAO_TERMINAL, CONDICAO},
    {SIMBOLO_TERMINAL, T_FECHAPAR},
    {SIMBOLO_TERMINAL, T_PV},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod29[] = {
    {SIMBOLO_TERMINAL, T_FOR},
    {SIMBOLO_TERMINAL, T_ABREPAR},
    {SIMBOLO_TERMINAL, T_ID},
    {SIMBOLO_TERMINAL, T_PV},
    {SIMBOLO_TERMINAL, T_NUM_INT},
    {SIMBOLO_TERMINAL, T_PV},
    {SIMBOLO_TERMINAL, T_NUM_INT},
    {SIMBOLO_TERMINAL, T_PV},
    {SIMBOLO_NAO_TERMINAL, EXPRESSAO},
    {SIMBOLO_TERMINAL, T_FECHAPAR},
    {SIMBOLO_NAO_TERMINAL, ENTIDADE},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod30[] = {
    {SIMBOLO_NAO_TERMINAL, TERMO},
    {SIMBOLO_NAO_TERMINAL, EXPR_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod31[] = {
    {SIMBOLO_TERMINAL, T_OP}, /* '+' */
    {SIMBOLO_NAO_TERMINAL, TERMO},
    {SIMBOLO_NAO_TERMINAL, EXPR_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod32[] = {
    {SIMBOLO_TERMINAL, T_OP}, /* '-' */
    {SIMBOLO_NAO_TERMINAL, TERMO},
    {SIMBOLO_NAO_TERMINAL, EXPR_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod34[] = {
    {SIMBOLO_NAO_TERMINAL, POTENCIA},
    {SIMBOLO_NAO_TERMINAL, TERMO_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod35[] = {
    {SIMBOLO_TERMINAL, T_OP}, /* '*' */
    {SIMBOLO_NAO_TERMINAL, POTENCIA},
    {SIMBOLO_NAO_TERMINAL, TERMO_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod36[] = {
    {SIMBOLO_TERMINAL, T_OP}, /* '/' */
    {SIMBOLO_NAO_TERMINAL, POTENCIA},
    {SIMBOLO_NAO_TERMINAL, TERMO_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod38[] = {
    {SIMBOLO_NAO_TERMINAL, FATOR},
    {SIMBOLO_NAO_TERMINAL, POTENCIA_LINHA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM},
};
static const Simbolo prod39[] = {
    {SIMBOLO_TERMINAL, T_OP}, /* '**' */
    {SIMBOLO_NAO_TERMINAL, POTENCIA},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM},
};
static const Simbolo prod41[] = {{SIMBOLO_TERMINAL, T_ID}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod42[] = {{SIMBOLO_TERMINAL, T_NUM_INT}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod43[] = {{SIMBOLO_TERMINAL, T_NUM_FLOAT}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod44[] = {{SIMBOLO_TERMINAL, T_CHAR_CONST}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod45[] = {
    {SIMBOLO_TERMINAL, T_ABREPAR},
    {SIMBOLO_NAO_TERMINAL, EXPRESSAO},
    {SIMBOLO_TERMINAL, T_FECHAPAR},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod46[] = {
    {SIMBOLO_NAO_TERMINAL, OPERANDO_COND},
    {SIMBOLO_NAO_TERMINAL, OPER_RELAC},
    {SIMBOLO_NAO_TERMINAL, OPERANDO_COND},
    {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod47[] = {{SIMBOLO_TERMINAL, T_ID}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod48[] = {{SIMBOLO_TERMINAL, T_NUM_INT}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod49[] = {{SIMBOLO_TERMINAL, T_NUM_FLOAT}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod50[] = {{SIMBOLO_TERMINAL, T_CHAR_CONST}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}};
static const Simbolo prod51[] = {{SIMBOLO_TERMINAL, T_RELOP}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}}; /* '==' */
static const Simbolo prod52[] = {{SIMBOLO_TERMINAL, T_RELOP}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}}; /* '!=' */
static const Simbolo prod53[] = {{SIMBOLO_TERMINAL, T_RELOP}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}}; /* '<' */
static const Simbolo prod54[] = {{SIMBOLO_TERMINAL, T_RELOP}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}}; /* '>' */
static const Simbolo prod55[] = {{SIMBOLO_TERMINAL, T_RELOP}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}}; /* '<=' */
static const Simbolo prod56[] = {{SIMBOLO_TERMINAL, T_RELOP}, {SIMBOLO_TERMINAL, SIMBOLO_FIM}}; /* '>=' */

const Simbolo *producoes[] = {
    prod0,
    prod1,
    prod2,
    prodEPSILON,
    prod4,
    prod5,
    prod6,
    prod7,
    prod8,
    prod9,
    prodEPSILON,
    prod11,
    prodEPSILON,
    prod13,
    prod14,
    prod15,
    prod16,
    prod17,
    prod18,
    prod19,
    prod20,
    prod21,
    prod22,
    prod23,
    prodEPSILON,
    prod25,
    prod26,
    prod27,
    prod28,
    prod29,
    prod30,
    prod31,
    prod32,
    prodEPSILON,
    prod34,
    prod35,
    prod36,
    prodEPSILON,
    prod38,
    prod39,
    prodEPSILON,
    prod41,
    prod42,
    prod43,
    prod44,
    prod45,
    prod46,
    prod47,
    prod48,
    prod49,
    prod50,
    prod51,
    prod52,
    prod53,
    prod54,
    prod55,
    prod56,
};

/* =============================================================================
 * Implementação do Analisador Sintático (Parser)
 * =============================================================================
 *
 * Este módulo implementa um analisador sintático preditivo para a linguagem
 * definida pela gramática. Ele utiliza uma tabela preditiva para guiar a
 * construção da árvore de derivação a partir dos tokens fornecidos pelo
 * analisador léxico.
 *
 * A função principal é `parser`, que recebe um ponteiro para o lexer e retorna
 * uma árvore de derivação representando a estrutura sintática do programa
 * fonte. Em caso de erros sintáticos, mensagens de erro detalhadas são
 * impressas indicando a natureza do erro e sua localização no código fonte.
 *
 * O módulo também define as estruturas de dados necessárias para representar
 * os símbolos, a pilha de análise e os nós da árvore de derivação, bem como
 * as funções auxiliares para manipular essas estruturas.
 */

ArvoreDerivacao *parser(Lexer *lexer)
{
    Pilha *pilha = NULL;
    Token token;
    pilha = inicializar_pilha();
    if (pilha == NULL)
    {
        printf("Erro: Falha ao inicializar pilha para analise sintatica.\n");
        return NULL;
    }
    Simbolo simbolo_inicial = {SIMBOLO_NAO_TERMINAL, S};
    ArvoreDerivacao *arvore = (ArvoreDerivacao *)malloc(sizeof(ArvoreDerivacao));
    if (arvore == NULL)
    {
        printf("Erro: Falha ao alocar memoria para arvore de derivacao.\n");
        free(pilha);
        return NULL;
    }
    arvore->raiz = criar_no(simbolo_inicial);
    empilhar(pilha, simbolo_inicial); // Símbolo inicial da gramática
    token = proximo_token(lexer);
    while (token.tipo == T_COMENT || token.tipo == T_WS)
    {
        token = proximo_token(lexer);
    }
    while (!pilha_vazia(pilha))
    {
        Simbolo topo = topo_pilha(pilha);
        if (topo.classe == SIMBOLO_TERMINAL)
        {
            if (topo.valor == token.tipo)
            {
                desempilhar(pilha);
                token = proximo_token(lexer);
                while (token.tipo == T_COMENT || token.tipo == T_WS)
                {
                    token = proximo_token(lexer);
                }
            }
            else
            {
                printf("Erro sintatico: esperado '%s' mas encontrado '%s' na linha %d, coluna %d\n", str_token(topo.valor), str_token(token.tipo), token.linha, token.coluna);
                return NULL;
            }
        }
        else
        {
            if (TabelaPreditiva[topo.valor][token.tipo] == -1)
            {
                printf("Erro sintatico: nenhuma regra para '%s' com token '%s' na linha %d, coluna %d\n", NOME_NAO_TERMINAIS[topo.valor], str_token(token.tipo), token.linha, token.coluna);
                return NULL;
            }
            else
            {
                int tamanho_producao;
                Simbolo *producao = obter_producao(topo, token, &tamanho_producao);
                desempilhar(pilha);
                if (producao == NULL)
                {
                    printf("Erro sintatico: falha ao obter producao para '%s' com token '%s' na linha %d, coluna %d\n", NOME_NAO_TERMINAIS[topo.valor], str_token(token.tipo), token.linha, token.coluna);
                    return NULL;
                }
                else if (tamanho_producao > 0)
                {
                    for (int i = tamanho_producao - 1; i >= 0; i--)
                    {
                        No *no_arvore = criar_no(producao[i]);
                        adicionar_filho(arvore->raiz, no_arvore);
                        empilhar(pilha, producao[i]);
                    }
                }
            }
        }
    }
    if (token.tipo == T_EOF)
    {
        return arvore;
    }
    else
    {
        printf("Erro sintatico: tokens restantes apos o fim da analise na linha %d, coluna %d\n", token.linha, token.coluna);
        destruir_arvore(arvore->raiz);
        free(arvore);
        return NULL;
    }
}

No *criar_no(Simbolo simbolo)
{
    No *no = (No *)malloc(sizeof(No));
    no->simbolo = simbolo;
    no->filhos = NULL;
    no->num_filhos = 0;
    return no;
}

Pilha *inicializar_pilha()
{
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    pilha->proximo = NULL;
    return pilha;
}

int empilhar(Pilha *pilha, Simbolo simbolo)
{
    Pilha *novo = (Pilha *)malloc(sizeof(Pilha));
    if (novo == NULL)
        return -1; // Falha de alocação
    novo->simbolo = simbolo;
    novo->proximo = pilha->proximo;
    pilha->proximo = novo;
    return 0; // Sucesso
}

int desempilhar(Pilha *pilha)
{
    if (pilha->proximo == NULL)
        return -1; // Pilha vazia
    Pilha *temp = pilha->proximo;
    pilha->proximo = temp->proximo;
    free(temp);
    return 0; // Sucesso
}

Simbolo topo_pilha(Pilha *pilha)
{
    if (pilha->proximo == NULL)
        return (Simbolo){SIMBOLO_TERMINAL, -1}; // Pilha vazia
    return pilha->proximo->simbolo;
}

int pilha_vazia(Pilha *pilha)
{
    return pilha->proximo == NULL;
}

void destruir_arvore(No *no)
{
    if (no == NULL)
        return;
    for (int i = 0; i < no->num_filhos; i++)
    {
        destruir_arvore(no->filhos[i]);
    }
    free(no->filhos);
    free(no);
}

void adicionar_filho(No *pai, No *filho)
{
    pai->filhos = (No **)realloc(pai->filhos, sizeof(No *) * (pai->num_filhos + 1));
    pai->filhos[pai->num_filhos] = filho;
    pai->num_filhos++;
}

Simbolo *obter_producao(Simbolo topo, Token token, int *tamanho)
{
    if (topo.valor == -1)
    {
        *tamanho = 0;
        return NULL;
    }
    int indice_producao = TabelaPreditiva[topo.valor][token.tipo];
    switch (indice_producao)
    {
    case 31: // 'EXPR_L -> '+' TERMO EXPR_L' 'EXPR_L -> '-' TERMO EXPR_L'
        if (token.tipo == T_OP && strcmp(token.atributo, "+") == 0) indice_producao = 31;
        else if (token.tipo == T_OP && strcmp(token.atributo, "-") == 0) indice_producao = 32;
        else indice_producao = -1; // Erro: operador inválido
        break;
    case 35: // 'TERMO_L -> '*' POTENCIA TERMO_L' 'TERMO_L -> '/' POTENCIA TERMO_L'
        if (token.tipo == T_OP && strcmp(token.atributo, "*") == 0) indice_producao = 35;
        else if (token.tipo == T_OP && strcmp(token.atributo, "/") == 0) indice_producao = 36;
        else if(token.tipo == T_OP && strcmp(token.atributo, "+") == 0)indice_producao = 37;
        else if(token.tipo == T_OP && strcmp(token.atributo, "-") == 0)indice_producao = 37;
        else indice_producao = -1; // Erro: operador inválido
        break;
    case 39: // 'POTENCIA_L -> '**' POTENCIA POTENCIA_L'
        if (token.tipo == T_OP && strcmp(token.atributo, "**") == 0) indice_producao = 39;
        else if (token.tipo == T_OP) indice_producao = 40; 
        else indice_producao = -1; // Erro: operador inválido
        break;
    case 51:
        if (token.tipo == T_RELOP && strcmp(token.atributo, "==") == 0) indice_producao = 51;
        else if (token.tipo == T_RELOP && strcmp(token.atributo, "!=") == 0) indice_producao = 52;
        else if (token.tipo == T_RELOP && strcmp(token.atributo, "<") == 0) indice_producao = 53;
        else if (token.tipo == T_RELOP && strcmp(token.atributo, ">") == 0) indice_producao = 54;
        else if (token.tipo == T_RELOP && strcmp(token.atributo, "<=") == 0) indice_producao = 55;
        else if (token.tipo == T_RELOP && strcmp(token.atributo, ">=") == 0) indice_producao = 56;
        else indice_producao = -1; // Erro: operador relacional inválido
        break;
    default:
        break;
    }
    if (indice_producao == -1)
    {
        *tamanho = 0;
        return NULL;
    }
    const Simbolo *producao = producoes[indice_producao];
    
    int count = 0;
    while (producao[count].valor != SIMBOLO_FIM)
    {
        count++;
    }
    *tamanho = count;
    return (Simbolo *)producao;
}