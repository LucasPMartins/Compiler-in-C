#include "syntax.h"

int parser(Lexer* lexer) {
    /* Implementação do analisador sintático (parser) */
    /* Esta função deve consumir os tokens gerados pelo lexer e construir a árvore sintática */
    /* Para esta etapa, o foco é reconhecer a estrutura geral do programa e validar a sintaxe básica */
    Pilha* pilha = NULL;
    Token token;
    inicializar_pilha(pilha); 
    empilhar(pilha, "S"); // Símbolo inicial da gramática
    token = proximo_token(lexer);
    while (!pilha_vazia(pilha)) {
        int topo = topo_pilha(pilha);
        if (eh_terminal(topo)) {
            if (topo == token.tipo) {
                desempilhar(pilha);
                token = proximo_token(lexer);
            } else {
                fprintf(stderr, "Erro sintatico: esperado '%s' mas encontrado '%s' na linha %d, coluna %d\n", str_token(topo), str_token(token.tipo), token.linha, token.coluna);
                return 0;
            }
        } else {
            if(TabelaPreditiva[topo][token.tipo] == -1) {
                fprintf(stderr, "Erro sintatico: nenhuma regra para '%s' com token '%s' na linha %d, coluna %d\n", str_producao(topo), str_token(token.tipo), token.linha, token.coluna);
                return 0;
            } else {
                desempilhar(pilha);
                // Array = Retorna produção invertida
                Producao *producao = obter_producao(TabelaPreditiva[topo][token.tipo]);
                for(int i = 0; i < *producao; i++) {
                    if(eh_terminal(producao[i])){
                        
                    }
                    empilhar(pilha, *(producao + 1 + i));
                }
            }
        }
    }
    if(token.tipo == T_EOF) {
        printf("Analise sintatica concluida com sucesso!\n");
        return 1;
    } else {
        fprintf(stderr, "Erro sintatico: tokens restantes apos o fim da analise na linha %d, coluna %d\n", token.linha, token.coluna);
        return 0;
    }
}