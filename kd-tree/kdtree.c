#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kdtree.h"


struct obj {
    struct nodo *n;
    struct obj *prox;
    int nivel;
};

struct fila {
    struct obj *prim;
    struct obj *last;
    int tam;
};

struct fila *cria_fila (){
    struct fila *f = malloc (sizeof (struct fila));
    if (!f) return NULL;

    f->prim = NULL;
    f->last = NULL;
    f->tam = 0;

    return f;
}

struct obj *cria_obj (struct nodo *nodo, int nivel){
    if (!nodo) return NULL;

    struct obj *o = malloc (sizeof (struct obj));
    if (!o) return NULL;

    o->n = nodo;
    o->nivel = nivel;
    o->prox = NULL;

    return o;
}

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
struct nodo* inserir(struct tree *t, float *vetchave, int c){
    if (!t || !vetchave) return NULL;

    struct nodo *novo = cria_nodo ();
    if (!novo){
        printf ("Falha ao alocar memória\n");
        exit (1);
    }

    novo->vetchave = vetchave;
    novo->classe = c;
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

int compara_vet (float *vet1, float *vet2, int k){
    if (!vet1 || !vet2 || k == 0) return 1;

    for (size_t i = 0; i < k; i++){
        printf ("Valor1: %.1f\n", vet1[i]);
        printf ("Valor2: %.1f\n", vet2[i]);
        if (vet1[i] - vet2[i] != 0.0){
            return 1;
        }
    }

    return 0;
}

struct nodo* buscar(struct nodo *r, float *vetchave, int coord, int k){
    if (r == NULL) return NULL; 

    if (compara_vet(r->vetchave, vetchave, k) == 0) return r;
    
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

void enfileirar (struct fila *f, struct obj *o){
    if (!f || !o) return ;

    if (!f->prim){ // fila vazia
        f->prim = o;
        f->last = o;
        f->tam += 1;
        return ;
    }

    f->last->prox = o;
    f->last = o;
    f->tam += 1;
}

struct obj *desenfileirar (struct fila *f){
    if (!f) return NULL;

    if (!f->prim) return NULL; // fila vazia

    struct obj *aux = f->prim;

    if (f->prim->prox) f->prim = f->prim->prox;
    else f->prim = NULL;

    f->tam -= 1;

    return aux;
}

void imprimirEmLargura(struct tree* t){
    if (!t->raiz || !t->raiz) return ; //árvore vazia
    int nivel_atual = 0;

    struct fila *f = cria_fila ();
    if (!f){
        printf ("Falha ao alocar memória\n");
        exit(1);
    }

    struct obj *novo = cria_obj (t->raiz, nivel_atual);
    if (!novo){
        printf ("Falha ao alocar memória\n");
        exit(1);
    }
    
    enfileirar (f, novo);
    printf ("[%d]   ", nivel_atual);
    while (f->tam > 0){
        struct obj *aux = desenfileirar (f);
        if (aux->nivel > nivel_atual){ // se nivel do nodo for maior vai para linha de baixo
            printf ("\n");
            nivel_atual = aux->nivel;
            printf ("[%d]   ", nivel_atual);
        }

        if (aux->n == t->raiz){
            printf ("[");
            for (size_t j = 0; j < t->num_dims; j++){
			    printf(" %.1f", novo->n->vetchave[j]);
		    }
            printf ("] ");
        }

        if (aux->n == aux->n->pai->fe) {
            printf ("[");
            for (size_t j = 0; j < t->num_dims; j++){
			    printf(" %.1f", novo->n->vetchave[j]);
		    }
            printf ("] ");
        }

        if (aux->n == aux->n->pai->fd) {
            printf ("[");
            for (size_t j = 0; j < t->num_dims; j++){
			    printf(" %.1f", novo->n->vetchave[j]);
		    }
            printf ("] ");
        }

        if (aux->n->fe){
            struct obj *fe = cria_obj (aux->n->fe, aux->nivel + 1);
            enfileirar (f, fe);
        }
        if (aux->n->fd){
            struct obj *fd = cria_obj (aux->n->fd, aux->nivel + 1);
            enfileirar (f, fd);
        }

        free (aux);
    }
    free (f);
    printf ("\n");
}

void vizinhos_prox(struct tree *t, float *vetchave, int num){
    if (!t || !vetchave) return ;
}
