#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

int main(void) {
    Gerenciador *g = criar_gerenciador();

    if (!g) {
        printf("Erro ao criar gerenciador!\n");
        return 1;
    }

    printf("--- Inserindo produtos --\n");
    inserir_produto_completo(g, 50, "Mouse", 100);
    inserir_produto_completo(g, 30, "Teclado", 150);
    inserir_produto_completo(g, 70, "Monitor", 900);
    inserir_produto_completo(g, 20, "Mousepad", 50);
    inserir_produto_completo(g, 40, "Headset", 250);
    inserir_produto_completo(g, 60, "Webcam", 300);
    inserir_produto_completo(g, 80, "Notebook", 3500);

    printf("\n--- Lista por ID ---\n");
    exibir_em_ordem_id(g->raizID);

    printf("\n--- Busca por ID (70) ---\n");
    Produto *p = buscar_por_id(g->raizID, 70);
    if (p) printf("Encontrado: %s (Preco: %.2f)\n", p->nome, p->preco);

    printf("\n--- Busca por Faixa de Preco (200 a 800) ---\n");
    buscar_por_faixa_preco(g->raizPreco, 200, 800);

    printf("\n--- Busca de Vizinho Mais Proximo (Preco alvo: 280) ---\n");
    Produto *v = buscar_vizinho_proximo(g->raizPreco, 280);
    if (v) printf("Mais proximo de 280.00: %s (Preco: %.2f)\n", v->nome, v->preco);

    printf("\n--- Remocao Sincronizada (ID 30 - Teclado) ---\n");
    remover_produto_completo(g, 30);

    printf("\n--- Verificando remocao na lista por Preco ---\n");
    exibir_em_ordem_preco(g->raizPreco);

    finalizar_gerenciador(g);
    
    return 0;
}
