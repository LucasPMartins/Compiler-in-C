#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "token.h"
#include "tabela_simbolos.h"

/* ============================================================================
 * FUNÇÕES AUXILIARES INTERNAS
 * ============================================================================ */

static void avancar(Lexer* lexer) {
    if (lexer == NULL || lexer->eof_alcancado) {
        return;
    }
    
    /* Atualiza posição antes de ler o próximo */
    if (lexer->atual == '\n') {
        lexer->linha++;
        lexer->coluna = 1;
    } else if (lexer->atual != EOF) {
        lexer->coluna++;
    }
    
    /* Lê o próximo caractere */
    int c = fgetc(lexer->arquivo);
    
    if (c == EOF) {
        lexer->atual = '\0';
        lexer->eof_alcancado = 1;
    } else {
        lexer->atual = (char) c;
    }
}

static void limpar_buffer(Lexer* lexer) {
    lexer->buf_pos = 0;
    lexer->buffer[0] = '\0';
}

static void adicionar_ao_buffer(Lexer* lexer, char c) {
    if (lexer->buf_pos < TAM_BUFFER_LEXEMA - 1) {
        lexer->buffer[lexer->buf_pos++] = c;
        lexer->buffer[lexer->buf_pos] = '\0';
    }
}

/* ============================================================================
 * FUNÇÕES DE VERIFICAÇÃO DE CARACTERES
 * ============================================================================ */

int eh_letra(char c) {
    return (c >= 'a' && c <= 'z') || 
           (c >= 'A' && c <= 'Z') || 
           c == '_';
}

int eh_digito(char c) {
    return c >= '0' && c <= '9';
}

int eh_alfanumerico(char c) {
    return eh_letra(c) || eh_digito(c);
}

int eh_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

/* ============================================================================
 * FUNÇÕES PÚBLICAS
 * ============================================================================ */

char peek(Lexer* lexer) {
    if (lexer == NULL) {
        return '\0';
    }
    return lexer->atual;
}

Lexer* inicializar_lexer(const char* nome_arquivo, EntradaTabela* tabela[]) {
    Lexer* lexer;
    
    if (nome_arquivo == NULL || tabela == NULL) {
        fprintf(stderr, "Erro: Parametros invalidos para inicializar o lexer\n");
        return NULL;
    }
    
    /* Aloca a estrutura do Lexer */
    lexer = (Lexer*) malloc(sizeof(Lexer));
    if (lexer == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memoria para o Lexer\n");
        return NULL;
    }
    
    /* Abre o arquivo fonte */
    lexer->arquivo = fopen(nome_arquivo, "r");
    if (lexer->arquivo == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel abrir o arquivo '%s'\n", nome_arquivo);
        free(lexer);
        return NULL;
    }
    
    /* Inicializa os campos */
    lexer->linha = 1;
    lexer->coluna = 0;  /* Será incrementado na primeira leitura */
    lexer->buf_pos = 0;
    lexer->buffer[0] = '\0';
    lexer->tabela = tabela;
    lexer->eof_alcancado = 0;
    
    /* Lê o primeiro caractere */
    int c = fgetc(lexer->arquivo);
    if (c == EOF) {
        lexer->atual = '\0';
        lexer->eof_alcancado = 1;
    } else {
        lexer->atual = (char) c;
        lexer->coluna = 1;
    }
    
    return lexer;
}

void destruir_lexer(Lexer* lexer) {
    if (lexer == NULL) {
        return;
    }

    if (lexer->arquivo != NULL) {
        fclose(lexer->arquivo);
    }

    free(lexer);
}

Token proximo_token(Lexer* lexer) {
    int linha_inicio, coluna_inicio, indice;
    int state = 0;
    char caracter_lido;
    char str_indice[12]; /* Buffer para armazenar o índice como string */
    
    if (lexer == NULL) {
        return criar_token(T_ERROR, 0, 0, "Lexer nulo");
    }

    limpar_buffer(lexer);

    /* Salva posição inicial do token */
    linha_inicio = lexer->linha;
    coluna_inicio = lexer->coluna;

    /* Reconhecimento de tokens via AFD */
    while (1) {
        if (lexer->eof_alcancado)state = 45;
        switch (state)
        { // Cada caso representa um estado do AFD (Total: 43)
        case 0:
            caracter_lido = peek(lexer);
            if (caracter_lido == ';') state = 1;
            else if (caracter_lido == '(') state = 2;
            else if (caracter_lido == ')') state = 3;
            else if (caracter_lido == '[') state = 4;
            else if (caracter_lido == ']') state = 5;
            else if (caracter_lido == ',') state = 6;
            else if (eh_whitespace(caracter_lido)) state = 7;
            else if (caracter_lido == '{') state = 8;
            else if (caracter_lido == ':') state = 20;
            else if (caracter_lido == '\'') state = 22;
            else if (caracter_lido == '*') state = 44;
            else if (caracter_lido == '+') state = 35;
            else if (caracter_lido == '-') state = 38;
            else if (caracter_lido == '/') state = 39;
            else if (caracter_lido == '>') state = 27;
            else if (caracter_lido == '<') state = 28;
            else if (caracter_lido == '=') state = 25;
            else if (caracter_lido == '!') state = 26;
            else if (caracter_lido == '_') state = 36;
            else if (eh_letra(caracter_lido)) state = 42;
            else if (eh_digito(caracter_lido)) state = 12;
            else if (lexer->eof_alcancado) state = 45;
            /* Estado de erro para caracteres inválidos */
            else {
                char msgbuf[64];
                snprintf(msgbuf, sizeof(msgbuf), "Caractere invalido: %c", caracter_lido);
                char lexbuf[2] = { caracter_lido, '\0' };
                avancar(lexer);
                caracter_lido = peek(lexer);
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, msgbuf);
            }
            break;
        case 1:
            avancar(lexer);
            return criar_token(T_PV, lexer->linha, lexer->coluna, "none");
        case 2:
            avancar(lexer);
            return criar_token(T_ABREPAR, lexer->linha, lexer->coluna, "none");
        case 3:
            avancar(lexer);
            return criar_token(T_FECHAPAR, lexer->linha, lexer->coluna, "none");
        case 4:
            avancar(lexer);
            return criar_token(T_ABREBLOCO, lexer->linha, lexer->coluna, "none");  
        case 5:
            avancar(lexer);
            return criar_token(T_FECHABLOCO, lexer->linha, lexer->coluna, "none");
        case 6:
            avancar(lexer);
            return criar_token(T_VIRG, lexer->linha, lexer->coluna, "none");
        case 7:
        {
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (eh_whitespace(caracter_lido)) state = 7;
            else return criar_token(T_WS, lexer->linha, lexer->coluna, "none");
            break;
        }
        case 8:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (caracter_lido == '%') {
                adicionar_ao_buffer(lexer, caracter_lido);
                state = 9;
            }
            /* Estado de erro para '{' inválido */
            else return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Caractere '{' invalido"); 
            break;
        case 9:
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (caracter_lido == '%') state = 10;
            else state = 9;
            break;
        case 10:
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (caracter_lido == '}') {
                adicionar_ao_buffer(lexer, '%');
                state = 11;
            }
            else state = 9;
            break;
        case 11:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            return criar_token(T_COMENT, lexer->linha, lexer->coluna, "none");
        case 12:
            if (eh_digito(caracter_lido)) {
                adicionar_ao_buffer(lexer, caracter_lido);
                avancar(lexer);
                caracter_lido = peek(lexer);
                state = 12;
            } else if (caracter_lido == '.') state = 13;
            else state = 18;
            break;
        case 13:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if(eh_digito(caracter_lido)) state = 14;
            else {
                /* Estado de erro para ponto decimal sem dígitos seguintes */
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Ponto decimal sem digitos seguintes");
            }
            break;
        case 14:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if(eh_digito(caracter_lido)) state = 14;
            else if (caracter_lido == 'E') state = 15;
            else state = 19;
            break;
        case 15:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if(caracter_lido == '+' || caracter_lido == '-' || eh_digito(caracter_lido)) state = 16;
            else {
                /* Estado de erro para 'E' sem expoente válido */
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Expoente invalido apos 'E'");
            }
            break;
        case 16:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if(eh_digito(caracter_lido)) state = 16; 
            else state = 17;
            break;
        case 17:
            indice = inserir_simbolo(lexer->tabela, lexer->buffer, T_NUM_FLOAT, "float");
            sprintf(str_indice, "%d", indice);
            return criar_token(T_NUM_FLOAT, lexer->linha, lexer->coluna, str_indice);
        case 18:
            indice = inserir_simbolo(lexer->tabela, lexer->buffer, T_NUM_INT, "int");
            sprintf(str_indice, "%d", indice);
            return criar_token(T_NUM_INT, lexer->linha, lexer->coluna, str_indice);
        case 19:
            indice = inserir_simbolo(lexer->tabela, lexer->buffer, T_NUM_FLOAT, "float");
            sprintf(str_indice, "%d", indice);
            return criar_token(T_NUM_FLOAT, lexer->linha, lexer->coluna, str_indice);
        case 20:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if(caracter_lido == '=') {
                state = 21;
            } else {
                /* Estado de erro para ':' isolado */
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Caractere ':' isolado invalido, expectando ':='");
            }
            break;
        case 21:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            return criar_token(T_ATRIB, lexer->linha, lexer->coluna, "none");
        case 22:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if(caracter_lido != '\n' && caracter_lido != '\'' && caracter_lido != EOF) state = 23;
            else {
                /* Estado de erro para constante de caractere vazia */
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Constante de caractere vazia ou invalida");
            }
            break;
        case 23:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (caracter_lido == '\'') state = 24;
            else {
                /* Estado de erro para constante de caractere mal formada */
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Constante de caractere mal formada, expectando fechamento com \'");
            }
        case 24:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            indice = inserir_simbolo(lexer->tabela, lexer->buffer, T_CHAR_CONST, "char");
            sprintf(str_indice, "%d", indice);
            return criar_token(T_CHAR_CONST, lexer->linha, lexer->coluna, str_indice);
        case 25:
            if(caracter_lido == '=') {
                adicionar_ao_buffer(lexer, caracter_lido);
                avancar(lexer);
                caracter_lido = peek(lexer);
                state = 29;
            } else {
                /* Estado de erro para '=' isolado */
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Caractere '=' isolado invalido, expectando '=='");
            }
            break;
        case 26:
            if(caracter_lido == '!') {
                adicionar_ao_buffer(lexer, caracter_lido);
                avancar(lexer);
                caracter_lido = peek(lexer);
                state = 30;
            } else {
                /* Estado de erro para '!' isolado */
                return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Caractere '!' isolado invalido, expectando '!='");
            }
            break;
        case 27:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (caracter_lido == '=') state = 31;
            else state = 32;
            break;
        case 28:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (caracter_lido == '=') state = 33;
            else state = 34;
            break;
        case 29:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            return criar_token(T_RELOP, lexer->linha, lexer->coluna, lexer->buffer);
        case 30:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            return criar_token(T_RELOP, lexer->linha, lexer->coluna, lexer->buffer);
        case 31:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            return criar_token(T_RELOP, lexer->linha, lexer->coluna, lexer->buffer);
        case 32:
            avancar(lexer);
            return criar_token(T_RELOP, lexer->linha, lexer->coluna, lexer->buffer);
        case 33:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            return criar_token(T_RELOP, lexer->linha, lexer->coluna, lexer->buffer);
        case 34:
            avancar(lexer);
            return criar_token(T_RELOP, lexer->linha, lexer->coluna, lexer->buffer);
        case 35:
            avancar(lexer);
            return criar_token(T_OP, lexer->linha, lexer->coluna, lexer->buffer);
        case 36:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (eh_alfanumerico(caracter_lido)) state = 36;
            else state = 37;
            break;
        case 37:
            avancar(lexer);
            indice = inserir_simbolo(lexer->tabela, lexer->buffer, T_ID, "none");
            sprintf(str_indice, "%d", indice);
            return criar_token(T_ID, lexer->linha, lexer->coluna, str_indice);
        case 38:
            avancar(lexer);
            return criar_token(T_OP, lexer->linha, lexer->coluna, lexer->buffer);
        case 39:
            avancar(lexer);
            return criar_token(T_OP, lexer->linha, lexer->coluna, lexer->buffer);
        case 40:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            return criar_token(T_OP, lexer->linha, lexer->coluna, lexer->buffer);
        case 41:
            avancar(lexer);
            return criar_token(T_OP, lexer->linha, lexer->coluna, lexer->buffer);
        case 42:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if(eh_letra(caracter_lido)) state = 42;
            else if(eh_digito(caracter_lido) || caracter_lido == '_') state = 36;
            else state = 43;
            break;
        case 43: {
            avancar(lexer);
            TipoToken tipo_tk = get_token(lexer->buffer);
            if(tipo_tk == NUM_PALAVRAS_RESERVADAS){
                indice = inserir_simbolo(lexer->tabela, lexer->buffer, T_ID, "none");
                sprintf(str_indice, "%d", indice);
                return criar_token(T_ID, lexer->linha, lexer->coluna, str_indice);
            } else {
                return criar_token(tipo_tk, lexer->linha, lexer->coluna, "none");
            }
        }
        case 44:
            adicionar_ao_buffer(lexer, caracter_lido);
            avancar(lexer);
            caracter_lido = peek(lexer);
            if (caracter_lido == '*') state = 40;
            else state = 41;
            break;
        case 45:
            avancar(lexer);
            return criar_token(T_EOF, lexer->linha, lexer->coluna, "none");
        default:
            /* Estado de erro desconhecido */
            return criar_token(T_ERROR, lexer->linha, lexer->coluna, "Estado desconhecido no AFD");
            break;
        }
    }
}
