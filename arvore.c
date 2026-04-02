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

// --- Busca por ID ---
Produto* buscar_por_id(No *raiz, int id) {
    if (!raiz) return NULL;
    if (id == raiz->conteudo->id) return raiz->conteudo;
    if (id < raiz->conteudo->id) return buscar_por_id(raiz->esq, id);
    return buscar_por_id(raiz->dir, id);
}

// --- Busca por Faixa de Preço ---
void buscar_por_faixa_preco(No *raiz, float min, float max) {
    if (!raiz) return;
    // Se o preço atual for maior que o mínimo, pode haver resultados à esquerda
    if (raiz->conteudo->preco > min) {
        buscar_por_faixa_preco(raiz->esq, min, max);
    }
    // Se o preço atual estiver na faixa, exibe
    if (raiz->conteudo->preco >= min && raiz->conteudo->preco <= max) {
        printf("ID: %d | Nome: %s | Preco: %.2f\n", raiz->conteudo->id, raiz->conteudo->nome, raiz->conteudo->preco);
    }
    // Se o preço atual for menor que o máximo, pode haver resultados à direita
    if (raiz->conteudo->preco < max) {
        buscar_por_faixa_preco(raiz->dir, min, max);
    }
}

// --- Vizinho Mais Próximo por Preço ---
Produto* buscar_vizinho_proximo(No *raiz, float preco_alvo) {
    if (!raiz) return NULL;

    Produto *melhor = raiz->conteudo;
    float dif_min = abs(preco_alvo - raiz->conteudo->preco);

    No *atual = raiz;
    while (atual) {
        float dif_atual = abs(preco_alvo - atual->conteudo->preco);
        if (dif_atual < dif_min) {
            dif_min = dif_atual;
            melhor = atual->conteudo;
        }

        if (preco_alvo < atual->conteudo->preco) {
            atual = atual->esq;
        } else if (preco_alvo > atual->conteudo->preco) {
            atual = atual->dir;
        } else {
            return atual->conteudo; // Diferença zero, é o próprio preço
        }
    }
    return melhor;
}

// --- Funções Auxiliares de Remoção ---
No* encontrar_minimo(No *raiz) {
    No *atual = raiz;
    while (atual && atual->esq) atual = atual->esq;
    return atual;
}

No* remover_por_id(No *raiz, int id, int *sucesso) {
    if (!raiz) return NULL;

    if (id < raiz->conteudo->id) {
        raiz->esq = remover_por_id(raiz->esq, id, sucesso);
    } else if (id > raiz->conteudo->id) {
        raiz->dir = remover_por_id(raiz->dir, id, sucesso);
    } else {
        *sucesso = 1;
        if (!raiz->esq) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (!raiz->dir) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        No *temp = encontrar_minimo(raiz->dir);
        raiz->conteudo = temp->conteudo;
        raiz->dir = remover_por_id(raiz->dir, temp->conteudo->id, sucesso);
    }
    return raiz;
}

No* remover_por_preco(No *raiz, float preco, int id, int *sucesso) {
    if (!raiz) return NULL;

    if (preco < raiz->conteudo->preco) {
        raiz->esq = remover_por_preco(raiz->esq, preco, id, sucesso);
    } else if (preco > raiz->conteudo->preco) {
        raiz->dir = remover_por_preco(raiz->dir, preco, id, sucesso);
    } else {
        // Se o preço é igual, precisamos verificar se o ID também é (pois pode haver preços repetidos)
        if (id == raiz->conteudo->id) {
            *sucesso = 1;
            if (!raiz->esq) {
                No *temp = raiz->dir;
                free(raiz);
                return temp;
            } else if (!raiz->dir) {
                No *temp = raiz->esq;
                free(raiz);
                return temp;
            }
            No *temp = encontrar_minimo(raiz->dir);
            raiz->conteudo = temp->conteudo;
            raiz->dir = remover_por_preco(raiz->dir, temp->conteudo->preco, temp->conteudo->id, sucesso);
        } else {
            // Em caso de preços iguais mas IDs diferentes, continua a busca à direita (ou esquerda conforme sua lógica de inserção)
            // Nossa lógica de inserção põe iguais à direita.
            raiz->dir = remover_por_preco(raiz->dir, preco, id, sucesso);
        }
    }
    return raiz;
}

void remover_produto_completo(Gerenciador *g, int id) {
    if (!g) return;

        Produto *p = buscar_por_id(g->raizID, id);
    if (!p) {
        printf("Erro: Produto ID %d nao encontrado para remocao.\n", id);
        return;
    }

    float preco_para_remover = p->preco;
    int sucessoID = 0, sucessoPreco = 0;

    g->raizPreco = remover_por_preco(g->raizPreco, preco_para_remover, id, &sucessoPreco);

    g->raizID = remover_por_id(g->raizID, id, &sucessoID);

    if (sucessoID && sucessoPreco) {
        free(p);
        printf("Produto ID %d removido com sucesso de ambas as arvores.\n", id);
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
