#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "redblack.h"

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

//IMPLEMENTE AS DEMAIS FUNÇÕES AQUI
struct nodo *cria_nodo (struct nodo **raiz){
    struct nodo *novo = malloc (sizeof (struct nodo));
    
    if (!novo) return NULL;

    novo->fd = (*raiz)->pai;
    novo->fe = (*raiz)->pai;
    novo->pai = NULL;
    novo->cor = "R";

    return novo;
}

void rotacaoEsquerda (struct nodo** raiz, struct nodo *nodo){
    if (!raiz || !nodo) return ;

    struct nodo *y = nodo->fd;
    nodo->fd = y->fe;

    if (y->fe != (*raiz)->pai) y->fe->pai = nodo;

    y->pai = nodo->pai;

    if (nodo->pai == (*raiz)->pai) (*raiz) = y;
    else{
        if (nodo == nodo->pai->fe) nodo->pai->fe = y;

        else nodo->pai->fd = y;
    }

    y->fe = nodo;
    nodo->pai = y;
}

void rotacaoDireita (struct nodo** raiz, struct nodo *nodo){
    if (!raiz || !nodo) return ;

    struct nodo *y = nodo->fe;
    nodo->fe = y->fd;

    if (y->fd != (*raiz)->pai) y->fd->pai = nodo;

    y->pai = nodo->pai;

    if (nodo->pai == (*raiz)->pai) (*raiz) = y;
    else{
        if (nodo == nodo->pai->fd) nodo->pai->fd = y;

        else nodo->pai->fe = y;
    }

    y->fd = nodo;
    nodo->pai = y;
}


void arrumaArvore (struct nodo** raiz, struct nodo *nodo){
    if (!raiz || !nodo) return ;

    while (nodo->pai->cor == "R"){
        if (nodo->pai == nodo->pai->pai->fe){
            struct nodo *y = nodo->pai->pai->fd;
            if (y->cor == "R"){
                nodo->pai->cor = "B";
                y->cor = "B";
                nodo->pai->pai->cor = "R";
                nodo = nodo->pai->pai;
            }
            else{
                if (nodo == nodo->pai->fd){
                    nodo = nodo->pai;
                    rotacaoEsquerda (raiz, nodo);
                }
                nodo->pai->cor = "B";
                nodo->pai->pai->cor = "R";
                rotacaoDireita (raiz, nodo->pai->pai);
            }
        }
        else{
            struct nodo *y = nodo->pai->pai->fe;
            if (y->cor == "R"){
                nodo->pai->cor = "B";
                y->cor = "B";
                nodo->pai->pai->cor = "R";
                nodo = nodo->pai->pai;
            }
            else{
                if (nodo == nodo->pai->fe){
                    nodo = nodo->pai;
                    rotacaoDireita (raiz, nodo);
                }
                nodo->pai->cor = "B";
                nodo->pai->pai->cor = "R";
                rotacaoEsquerda (raiz, nodo->pai->pai);
            }
        }
    }
    (*raiz)->cor = "B";
}

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave){
    if (!raiz || chave == -1) return (*raiz)->pai;

    if (buscar ((*raiz), chave) != (*raiz)->pai) return (*raiz)->pai; // Chave já existe

    struct nodo *novo = cria_nodo (raiz);
    if (!novo) return (*raiz)->pai;

    novo->chave = chave;
    struct nodo *x = (*raiz);
    struct nodo *y = (*raiz)->pai;
    
    while (x != (*raiz)->pai){
        y = x;
        if (novo->chave < x->chave) x = x->fe;
        else x = x->fd;
    }

    novo->pai = y;
    if (y == (*raiz)->pai) (*raiz) = novo; // Árvore vazia
    else{
        if (novo->chave < y->chave) y->fe = novo;
        else y->fd = novo;
    }

    arrumaArvore (raiz, novo);

    return novo;
}

void transplantar (struct nodo** raiz, struct nodo *u, struct nodo *v){
    if (!raiz || !u || !v) return ;

    if (u->pai == (*raiz)->pai) (*raiz) = v;
    else{
        if (u == u->pai->fe) u->pai->fe = v;
        else u->pai->fd = v;
    }
    v->pai = u->pai;
}

void arrumaExcluir (struct nodo **raiz, struct nodo *x){
    if (!raiz || !x) return ;

    while (x != (*raiz) && x->cor == "B"){
        if (x == x->pai->fe){
            struct nodo *w = x->pai->fd;
            if (w->cor == "R"){
                w->cor = "B";
                x->pai->cor = "R";
                rotacaoEsquerda (raiz, x->pai);
                w = x->pai->fd;
            }
            if (w->fe->cor == "B" && w->fd->cor == "B"){
                w->cor = "R";
                x = x->pai;
            }
            else{
                if (w->fd->cor == "B"){
                    w->fe->cor = "B";
                    w->cor = "R";
                    rotacaoDireita (raiz, w);
                    w = x->pai->fd;
                }
                w->cor = x->pai->cor;
                x->pai->cor = "B";
                w->fd->cor = "B";
                rotacaoEsquerda (raiz, x->pai);
                x = (*raiz);
            }
        }
        else{
            struct nodo *w = x->pai->fe;
            if (w->cor == "R"){
                w->cor = "B";
                x->pai->cor = "R";
                rotacaoEsquerda (raiz, x->pai);
                w = x->pai->fd;
            }
            if (w->fd->cor == "B" && w->fe->cor == "B"){
                w->cor = "R";
                x = x->pai;
            }
            else{
                if (w->fe->cor == "B"){
                    w->fd->cor = "B";
                    w->cor = "R";
                    rotacaoEsquerda (raiz, w);
                    w = x->pai->fd;
                }
                w->cor = x->pai->cor;
                x->pai->cor = "B";
                w->fe->cor = "B";
                rotacaoDireita (raiz, x->pai);
                x = (*raiz);
            }
        }
    }  
}   

struct nodo *minimo (struct nodo **raiz, struct nodo *n){
    if (!raiz || !n) return NULL;

    struct nodo *min = n;
    struct nodo *aux = n->fe;

    while (aux != (*raiz)->pai){
        min = aux;
        aux = min->fe;
    }

    return min;
}

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave){
    if (!raiz) return 0;

    struct nodo *z = buscar ((*raiz), chave);
    if (z == (*raiz)->pai) return 0; //não existe a chave na árvore

    struct nodo *y = z;
    struct nodo *x;
    char *cor_original = y->cor;

    if (z->fe == (*raiz)->pai){
        x = z->fd;
        transplantar (raiz, z, z->fd);
    }
    else{
        if (z->fd == (*raiz)->pai){
            x = z->fe;
            transplantar (raiz, z, z->fe);
        }
        else{
            y = minimo (raiz, z->fd);
            cor_original = y->cor;
            x = y->fd;
            if (y != z->fd){
                transplantar (raiz, y, y->fd);
                y->fd = z->fd;
                y->fd->pai = y;
            }
            else x->pai = y;

            transplantar (raiz, z, y);
            y->fe = z->fe;
            y->fe->pai = y;
            y->cor = z->cor;
        }
    }

    if (cor_original == "B") arrumaExcluir (raiz, x);
    free (z);
    return 1;
}

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* raiz, int chave){
    if (raiz->chave == -1 || raiz->chave == chave) return raiz;

    if (chave < raiz->chave) return buscar (raiz->fe, chave);

    return buscar (raiz->fd, chave);
}

void imprimirEmOrdem(struct nodo* nodo){
    if (nodo->chave != -1){
        imprimirEmOrdem (nodo->fe);
        printf ("(%s)%d ", nodo->cor, nodo->chave);
        imprimirEmOrdem (nodo->fd);
    }
}

void imprimirEmLargura(struct nodo* raiz){
    if (!raiz || raiz->chave == -1) return ; //árvore vazia
    
    struct nodo **fila;
    int tam = 0;
    int prim = 0;

    fila[tam] = raiz;
    tam += 1;
    while (tam > 0){
        struct nodo *n = fila[prim];
        printf ("(%s)%d ", n->cor, n->chave);

        if (n->fe != raiz->pai){
            fila[tam] = n->fe;
            tam += 1;
        }
        if (n->fd != raiz->pai){
            fila[tam] = n->fd;
            tam += 1;
        }
        tam -= 1;
        prim += 1;
    }


    
}