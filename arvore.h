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

// Protótipos das funções
Gerenciador* criar_gerenciador();
Produto* criar_produto(int id, const char *nome, float preco);
No* inserir_por_id(No *raiz, Produto *p);
No* inserir_por_preco(No *raiz, Produto *p);
void inserir_produto_completo(Gerenciador *g, int id, const char *nome, float preco);

// Funções auxiliares para visualização (opcional para teste)
void exibir_em_ordem_id(No *raiz);
void exibir_em_ordem_preco(No *raiz);

// FunĂ§Ăµes para liberar memĂłria
void liberar_arvore(No *raiz, int liberar_produto);
void finalizar_gerenciador(Gerenciador *g);

#endif // ARVORE_H
