#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvore.h"

Gerenciador* criar_gerenciador() {
    Gerenciador *g = (Gerenciador*) malloc(sizeof(Gerenciador));
    if (g) {
        g->raizID = NULL;
        g->raizPreco = NULL;
    }
    return g;
}

Produto* criar_produto(int id, const char *nome, float preco) {
    Produto *p = (Produto*) malloc(sizeof(Produto));
    if (p) {
        p->id = id;
        strncpy(p->nome, nome, 99);
        p->nome[99] = '\0';
        p->preco = preco;
    }
    return p;
}

No* criar_no(Produto *p) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo) {
        novo->conteudo = p;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

No* inserir_por_id(No *raiz, Produto *p) {
    if (raiz == NULL) {
        return criar_no(p);
    }
    if (p->id < raiz->conteudo->id) {
        raiz->esq = inserir_por_id(raiz->esq, p);
    } else if (p->id > raiz->conteudo->id) {
        raiz->dir = inserir_por_id(raiz->dir, p);
    }
    return raiz;
}

No* inserir_por_preco(No *raiz, Produto *p) {
    if (raiz == NULL) {
        return criar_no(p);
    }
    if (p->preco < raiz->conteudo->preco) {
        raiz->esq = inserir_por_preco(raiz->esq, p);
    } else {
        raiz->dir = inserir_por_preco(raiz->dir, p);
    }
    return raiz;
}

void inserir_produto_completo(Gerenciador *g, int id, const char *nome, float preco) {
    if (!g) return;
    Produto *p = criar_produto(id, nome, preco);
    if (p) {
        g->raizID = inserir_por_id(g->raizID, p);
        g->raizPreco = inserir_por_preco(g->raizPreco, p);
    }
}

void exibir_em_ordem_id(No *raiz) {
    if (raiz) {
        exibir_em_ordem_id(raiz->esq);
        printf("ID: %d | Nome: %s | Preco: %.2f\n", raiz->conteudo->id, raiz->conteudo->nome, raiz->conteudo->preco);
        exibir_em_ordem_id(raiz->dir);
    }
}

void exibir_em_ordem_preco(No *raiz) {
    if (raiz) {
        exibir_em_ordem_preco(raiz->esq);
        printf("Preco: %.2f | ID: %d | Nome: %s\n", raiz->conteudo->preco, raiz->conteudo->id, raiz->conteudo->nome);
        exibir_em_ordem_preco(raiz->dir);
    }
}

void liberar_arvore(No *raiz, int liberar_produto) {
    if (raiz) {
        liberar_arvore(raiz->esq, liberar_produto);
        liberar_arvore(raiz->dir, liberar_produto);
        if (liberar_produto && raiz->conteudo) {
            free(raiz->conteudo);
        }
        free(raiz);
    }
}

void finalizar_gerenciador(Gerenciador *g) {
    if (g) {
        // Liberamos os produtos apenas em uma das árvores para não dar free duplo
        liberar_arvore(g->raizID, 1);
        // Na outra árvore, liberamos apenas os nós (que apontavam para os mesmos produtos)
        liberar_arvore(g->raizPreco, 0);
        free(g);
    }
}
