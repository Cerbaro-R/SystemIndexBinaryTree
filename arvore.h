#ifndef ARVORE_H
#define ARVORE_H

#include "produto.h"

typedef struct No {
    Produto *conteudo;
    struct No *esq;
    struct No *dir;
} No;

typedef struct {
    No *raizID;
    No *raizPreco;
} Gerenciador;

Gerenciador* criar_gerenciador();
Produto* criar_produto(int id, const char *nome, float preco);
No* inserir_por_id(No *raiz, Produto *p);
No* inserir_por_preco(No *raiz, Produto *p);
void inserir_produto_completo(Gerenciador *g, int id, const char *nome, float preco);

Produto* buscar_por_id(No *raiz, int id);
void buscar_por_faixa_preco(No *raiz, float min, float max);
Produto* buscar_vizinho_proximo(No *raiz, float preco_alvo);

No* remover_por_id(No *raiz, int id, int *sucesso);
No* remover_por_preco(No *raiz, float preco, int id, int *sucesso);
void remover_produto_completo(Gerenciador *g, int id);

void exibir_em_ordem_id(No *raiz);
void exibir_em_ordem_preco(No *raiz);

void liberar_arvore(No *raiz, int liberar_produto);
void finalizar_gerenciador(Gerenciador *g);

#endif
