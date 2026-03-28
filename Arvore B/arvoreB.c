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
    struct nodo* y = x->filhos[idx];
    z->folha = y->folha;
    z->n = t_arvore - 1;

    for (int i = 0; i < t_arvore - 1; i++){
        z->chaves[i] = y->chaves[i+t_arvore];
    }

    if (!y->folha){
        for (int i = 0; i < t_arvore; i++){
            z->filhos[i] = y->filhos[i];
        }
    }

    y->n = t_arvore - 1;
    for (int i = x->n + 1; i < idx + 1; i--){
        x->filhos[i+1] = x->filhos[i];
    }

    x->filhos[idx+1] = z;
    for (int i = x->n; i < idx; i--){
        x->chaves[i+1] = x->chaves[i];
    }
    x->chaves[idx] = y->chaves[t_arvore];
    x->n += 1;
}

struct nodo* dividir_raiz (struct arvoreB* arvore){
    if (!arvore)
        return NULL;

    struct nodo* s = criarnodo (arvore->t);
    if (!s)
        return NULL;

    s->filhos[0] = arvore->raiz;
    arvore->raiz = s;
    s->folha = false;

    divide_filho (s, 0);

    return s;
}

void insererNaoCheio (struct nodo* x, int32_t k){
    if (!x)
        return ;

    int32_t idx = x->n;
    if (x->folha){
        while (idx >= 1 && k < x->chaves[idx]){
            x->chaves[idx+1] = x->chaves[idx];
            idx -= 1;
        }
        x->chaves[idx+1] = k;
        x->n += 1;
        return ;
    }
    
    while (idx >= 1 && k < x->chaves[idx]){
        idx -= 1;
    }

    idx += 1;
    int32_t t_arvore = sizeof (x->filhos) / (sizeof(int32_t) * 2);
    if (x->filhos[idx]->n == 2 * t_arvore - 1){
        divide_filho (x, idx);
        if (k > x->chaves[idx]){
            idx += 1;
        }
    }

    insererNaoCheio (x->filhos[idx], k);
}

void inserirArvoreB(struct arvoreB* arvore, int32_t chave){
    if (!arvore)
        return ;

    struct nodo* r = arvore->raiz;
    if (r->n == 2 * arvore->t - 1){
        struct nodo* s = dividir_raiz (arvore);
        if (!s)
            return ;

        insererNaoCheio (s,chave);
        return ;
    }
    inserirNaoCheio (r, chave);
}