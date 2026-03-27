#include <stdio.h>
#include <stdlib.h>

#include "arvoreB.h"


struct arvoreB* criarArvoreB(int32_t t_arvore){
    struct arvoreB* arvore = malloc (sizeof (struct arvoreB));
    if (!arvore)
        return NULL;

    arvore->raiz = NULL;
    arvore->t = t_arvore;

    return arvore;
}

struct nodo* criarnodo(int32_t t_arvore){
    struct nodo* arvore = malloc (sizeof (struct nodo));
    if (!arvore)
        return NULL;

    arvore->n = 0;
    arvore->chaves = malloc (sizeof(int32_t) * (2*t_arvore - 1));
    arvore->filhos = malloc(sizeof (int32_t) * 2*t_arvore);
    arvore->folha = true;

    return arvore;
}

void divide_filho (struct nodo* x, int32_t idx){
    if (!x)
        return ;
    
    int32_t t_arvore = sizeof (x->filhos) / (sizeof(int32_t) * 2);
    struct nodo* z = criarnodo (t_arvore);
    struct nodo* y = 
}

void inserirArvoreB(struct arvoreB* arvore, int32_t chave){
    if (!arvore)
        return ;

    
}