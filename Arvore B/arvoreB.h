#ifndef BTREE_H_
#define BTREE_H_

#include <stdint.h>
#include <stdbool.h> //com o padrao c23 não era necessário a inclusão dessa lib

struct nodo {
    int32_t n;
    int32_t *chaves;
    struct arvoreB **filhos;
    bool folha;
};

struct arvoreB {
    struct nodo* raiz;
    int
};

struct arvoreB* criarArvoreB(int32_t t_arvore);
void inserirArvoreB(struct arvoreB* arvore, int32_t chave);
void imprimirArvoreB(struct arvoreB* arvore);
void imprimirEmOrdem(struct arvoreB* arvore);
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado);
void deletarArvore(struct arvoreB* arvore);

#endif