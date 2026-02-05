/* ===== Arquivo exp.c ===== */
#include "lexer.h"
#include "exp.h"
#include <stdio.h>
#include <string.h>

const char* TOKEN_NAMES[] = {
    "TOKEN_INTEGER",               // 0
    "TOKEN_OPERATOR",              // 1
    "TOKEN_PUNCTUATION",           // 2
    "TOKEN_ERROR",                 // 3
    "TOKEN_IDENTIFIER",            // 4
    "TOKEN_RELATIONAL_OPERATOR",   // 5
    "TOKEN_SEPARATOR",             // 6
    "TOKEN_FLOAT",                 // 7
    "TOKEN_END_OF_FILE",           // 8
    "TOKEN_ASSIGNMENT",            // 9
    "TOKEN_IF",                    // 10
    "TOKEN_THEN",                  // 11
    "TOKEN_ELSE",                  // 12
    "TOKEN_WHILE",                 // 13
    "TOKEN_REPEAT",                // 14
    "TOKEN_UNTIL",                 // 15
    "TOKEN_COMMENT"                // 16
};

/* Carrega arquivo */
int inicializa(char *str)
{
    FILE *f = fopen(str, "r");
    if (f == NULL)
        return FALSE;

    yyin = f;
    return TRUE;
}

Token *proximo_token()
{
    return yylex();
}

void imprime_token(Token *tok)
{
    if (tok != NULL)
    {
        printf("<%s, \"%s\">\n", TOKEN_NAMES[tok->tipo], tok->atributo);
    }
}

int main()
{
    Token *tok;
    char entrada[200];
    int opcao = 1;

    printf("\n----======* Analisador Lexico *======----\n");

    do
    {
        printf("Digite o nome do arquivo com o codigo fonte a ser analisado: ");
        scanf("%s", entrada);

        if (!inicializa(entrada))
        {
            printf("Erro ao abrir o arquivo %s\n", entrada);
            continue;
        }else
        {
            printf("\nTokens reconhecidos:\n");
            while ((tok = proximo_token())->tipo != TOK_EOF)
            {
                imprime_token(tok);
                free(tok->atributo);
                free(tok);
            }
            // Imprime o token EOF
            imprime_token(tok);
            free(tok);

            fclose(yyin);
        }

        printf("\nAnalise concluida.\n");
        printf("Deseja analisar outro arquivo? (1-Sim / 0-Nao): ");
        scanf("%d", &opcao);
    } while (opcao == 1);

    return 0;
}
