#ifndef TOKEN_H
#define TOKEN_H

/* Tamanho máximo do lexema (string reconhecida) */
#define MAX_LEXEMA 256

/**
 * Enumeração de todos os tipos de tokens da linguagem.
 * 
 * Categorias:
 * - Palavras-chave: T_VOID, T_INT, T_CHAR, T_FLOAT, T_MAIN, T_IF, T_THEN,
 *                   T_ELSIF, T_ELSE, T_WHILE, T_DO, T_FOR
 * - Operadores: T_OP (aritméticos), T_RELOP (relacionais), T_ATRIB (atribuição)
 * - Delimitadores: T_ABREPAR, T_FECHAPAR, T_ABREBLOCO, T_FECHABLOCO, T_VIRG, T_PV
 * - Identificadores e Constantes: T_ID, T_NUM_INT, T_NUM_FLOAT, T_CHAR_CONST
 * - Especiais: T_EOF (fim de arquivo), T_ERROR (erro léxico), T_WS (whitespace)
 */

typedef enum {
    /* =========================================
     * PALAVRAS RESERVADAS (KEYWORDS)
     * ========================================= */
    T_VOID,         /* void   - tipo de retorno vazio */
    T_INT,          /* int    - tipo inteiro */
    T_CHAR,         /* char   - tipo caractere */
    T_FLOAT,        /* float  - tipo ponto flutuante */
    T_MAIN,         /* main   - função principal */
    T_IF,           /* if     - condicional */
    T_THEN,         /* then   - parte do if */
    T_ELSIF,        /* elsif  - else if */
    T_ELSE,         /* else   - alternativa do if */
    T_WHILE,        /* while  - laço de repetição */
    T_DO,           /* do     - parte do while */
    T_FOR,          /* for    - laço de repetição */
    /* =========================================
     * OPERADORES
     * ========================================= */
    T_OP,           /* Operadores aritméticos: +, -, *, /, ** */
    T_RELOP,        /* Operadores relacionais: ==, !=, <, >, <=, >= */
    T_ATRIB,        /* Operador de atribuição: := */
    /* =========================================
     * DELIMITADORES
     * ========================================= */
    T_ABREPAR,      /* ( - abre parênteses */
    T_FECHAPAR,     /* ) - fecha parênteses */
    T_ABREBLOCO,    /* [ - abre bloco */
    T_FECHABLOCO,   /* ] - fecha bloco */
    T_VIRG,         /* , - vírgula */
    T_PV,           /* ; - ponto e vírgula */
    T_COMENT,       /* Comentário {% ... %} */
    /* =========================================
     * IDENTIFICADORES E CONSTANTES
     * ========================================= */
    T_ID,           /* Identificador (nome de variável/função) */
    T_NUM_INT,      /* Constante inteira (ex: 123) */
    T_NUM_FLOAT,    /* Constante float (ex: 3.14, 0.1E-2) */
    T_CHAR_CONST,   /* Constante de caractere (ex: 'A') */
    /* =========================================
     * TOKENS ESPECIAIS
     * ========================================= */
    T_WS,            /* Whitespace (espaços, tabs, novas linhas) */
    T_EOF,          /* Fim de arquivo */
    T_ERROR        /* Erro léxico */
} TipoToken;

/**
 * Estrutura auxiliar para associar palavras reservadas aos seus tipos.
 */
typedef struct {
    const char* lexema;
    TipoToken tipo;
} PalavraReservada;

/**
 * Lista de todas as palavras reservadas da linguagem.
 * Usada para pré-popular a tabela de símbolos na inicialização.
 */
static const PalavraReservada PALAVRAS_RESERVADAS[];

/* Número total de palavras reservadas */
extern const int NUM_PALAVRAS_RESERVADAS;

/**
 * Estrutura que representa um token reconhecido pelo analisador léxico.
 * 
 * Campos:
 * - tipo: Tipo do token (enum TipoToken)
 * - lexema: String exata encontrada no código fonte
 * - linha: Número da linha onde o token inicia (1-based)
 * - coluna: Número da coluna onde o token inicia (1-based)
 * - atributo: String com o valor do atributo ou "none" se não aplicável
 * 
 * Atributos por tipo de token:
 * - T_NUM_INT: valor numérico inteiro (ex: "123")
 * - T_NUM_FLOAT: valor numérico float (ex: "3.14")
 * - T_CHAR_CONST: caractere (ex: "A")
 * - T_OP: operador específico (ex: "+", "-", "*", "/", "**")
 * - T_RELOP: operador relacional (ex: "==", "!=", "<", ">", "<=", ">=")
 * - Outros: "none"
 */
typedef struct {
    TipoToken tipo;                   /* Tipo do token (enum) */
    int linha;                        /* Linha onde o lexema inicia */
    int coluna;                       /* Coluna onde o lexema inicia */
    char *atributo;                   /* Atributo do token ou "none" */
} Token;

/**
 * Cria um novo token com os valores especificados.
 * 
 * @param tipo Tipo do token
 * @param linha Linha onde o token foi encontrado
 * @param coluna Coluna onde o token foi encontrado
 * @param atributo Atributo do token ou none
 * @return Token inicializado com os valores fornecidos
 */
Token criar_token(TipoToken tipo, int linha, int coluna, const char* atributo);

/**
 * Retorna o tipo do token correspondente ao lexema, se for uma palavra reservada.
 * Caso contrário, retorna NULL.
 * 
 * @param lexema String a ser verificada
 * @return Tipo do token correspondente ou NULL se não for reservado
 */
TipoToken get_token(const char* lexema);

/**
 * Converte um TipoToken para sua representação em string.
 * 
 * @param tipo Tipo do token
 * @return String correspondente ao nome do tipo de token
 */
const char* str_token(TipoToken tipo);

/**
 * Imprime as informações de um token de forma formatada.
 * Formato: <TIPO, "lexema", linha:coluna, atributo>
 * 
 * @param token Ponteiro para o token a ser impresso
 */
void imprimir_token(const Token* token);

#endif /* TOKEN_H */
