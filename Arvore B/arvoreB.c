#include <stdio.h>
#include <stdlib.h>

#include "arvoreB.h"


struct arvoreB* criarArvoreB(int32_t t_arvore){
    struct arvoreB* arvore = malloc (sizeof (struct arvoreB));
    if (!arvore)
        return NULL;

    arvore->n = 0;
    arvore->chaves = malloc (sizeof(int32_t) * (2*t_arvore - 1));
    arvore->filhos = malloc(sizeof (int32_t) * 2*t_arvore);
    arvore->folha = true;

    return arvore;
}

void divide_filho (struct arvoreB* arvore, int32_t idx){

}

void inserirArvoreB(struct arvoreB* arvore, int32_t chave){
    if (!arvore)
        return ;

    struct arvoreB* nodo = arv
}