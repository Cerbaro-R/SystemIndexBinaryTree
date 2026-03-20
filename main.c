#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(void) {
    Gerenciador *g = criar_gerenciador();

    if (!g) {
        printf("Erro ao criar gerenciador!\n");
        return 1;
    }

    printf("Inserindo produtos...\n");
    inserir_produto_completo(g, 10, "Produto A", 50.0);
    inserir_produto_completo(g, 5, "Produto B", 20.0);
    inserir_produto_completo(g, 15, "Produto C", 80.0);
    inserir_produto_completo(g, 2, "Produto D", 10.0);
    inserir_produto_completo(g, 8, "Produto E", 30.0);

    printf("\n--- Exibicao em Ordem por ID ---\n");
    exibir_em_ordem_id(g->raizID);

    printf("\n--- Exibicao em Ordem por Preco ---\n");
    exibir_em_ordem_preco(g->raizPreco);

    finalizar_gerenciador(g);
    
    return 0;
}
