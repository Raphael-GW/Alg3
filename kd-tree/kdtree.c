#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"


void matarProgramaFaltaMemoria (){
    fprintf(stderr,"Falha ao alocar memoria.\n");
    exit (1);
}

struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("Raphael Gaias"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("rgw24"));
    if(!retorno->nomeDinf)
        matarProgramaFaltaMemoria();
    
	strcpy(retorno->nome, "Raphael Gaias");
    strcpy(retorno->nomeDinf, "rgw24");
    retorno->grr = 20244362;

	return retorno;
}

void imprimirDadosAluno(){
    struct aluno* aluno = getAluno();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    return;
}

struct nodo *cria_nodo (){
    struct nodo *n = malloc (sizeof (struct nodo));
    if (!n) return NULL;

    n->fd = NULL;
    n->fe = NULL;
    n->pai = NULL;
    return n;
}

//retorna NULO se não foi possível inserir
struct nodo* inserir(struct tree *t, int *vetchave){
    if (!t || !vetchave) return NULL;

    struct nodo *novo = cria_nodo ();
    if (!novo) return NULL;

    novo->vetchave = vetchave;
    size_t coord = 0;

    struct nodo *atual = t->raiz;
    struct nodo *pai = NULL;
    while (atual != NULL){
        pai = atual;

        if (novo->vetchave[coord] < atual->vetchave[coord]){
            atual = atual->fe;
        }
        else atual = atual->fd;

        coord = (coord + 1) % t->num_dims;
    }

    novo->pai = pai;
    if (pai == NULL){
        t->raiz = novo;
    }
    else{
        if (novo->vetchave[coord] < pai->vetchave[coord]){
            pai->fe = novo;
        }
        else pai->fd = novo;
    }

    return novo;
}

int compara_vet (int *vet1, int *vet2, int k){
    if (!vet1 || !vet2 || k == 0) return 1;

    int igual = 0;
    for (size_t i = 0; i < k; i++){
        if (vet1[i] != vet2[i]){
            igual = 1;
        }
    }

    return igual;
}

struct nodo* buscar(struct nodo *r, int *vetchave, int coord, int k){
    if (!r || compara_vet (r->vetchave, vetchave, k) == 0) return r;

    if (vetchave[coord] < r->vetchave[coord]){
        return buscar (r->fe, vetchave, (coord + 1) % k, k);
    }
    return buscar (r->fd, vetchave, (coord + 1) % k, k);
}

// retorna o número de nodos excluídos
int excluir(struct tree *t, int *vetchave){
    if (!t || !vetchave) return 0;

    return 1;
}

void imprimirEmOrdem(struct tree *t){
    if (!t || !t->raiz) return ;
}

void imprimirEmLargura(struct tree *t){
    if (!t || !t->raiz) return ;
}