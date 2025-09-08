#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "redblack.h"

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
struct nodo *cria_nodo (){
    struct nodo *novo = malloc (sizeof (struct nodo));
    
    if (!novo) return NULL;

    novo->fd = NULL;
    novo->fe = NULL;
    novo->pai = NULL;
    novo->cor = "vermelho";

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

    while (nodo->pai->cor == "vermelho"){
        if (nodo->pai == nodo->pai->pai->fe){
            struct nodo *y = nodo->pai->pai->fd;
            if (y->cor == "vermelho"){
                nodo->pai->cor = "preto";
                y->cor = "preto";
                nodo->pai->pai->cor = "vermelho";
                nodo = nodo->pai->pai;
            }
            else{
                if (nodo == nodo->pai->fd){
                    nodo = nodo->pai;
                    rotacaoEsquerda (raiz, nodo);
                }
                nodo->pai->cor = "preto";
                nodo->pai->pai->cor = "vermelho";
                rotacaoDireita (raiz, nodo->pai->pai);
            }
        }
        else{
            struct nodo *y = nodo->pai->pai->fe;
            if (y->cor == "vermelho"){
                nodo->pai->cor = "preto";
                y->cor = "preto";
                nodo->pai->pai->cor = "vermelho";
                nodo = nodo->pai->pai;
            }
            else{
                if (nodo == nodo->pai->fe){
                    nodo = nodo->pai;
                    rotacaoDireita (raiz, nodo);
                }
                nodo->pai->cor = "preto";
                nodo->pai->pai->cor = "vermelho";
                rotacaoEsquerda (raiz, nodo->pai->pai);
            }
        }
    }
    (*raiz)->cor = "preto";
}

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave){
    if (!raiz || chave == -1) return (*raiz)->pai;

    if (buscar ((*raiz), chave) != (*raiz)->pai) return (*raiz)->pai; // Chave já existe

    struct nodo *novo = cria_nodo ();
    if (!novo) return (*raiz)->pai;

    novo->chave = chave;
    raiz[0]
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

    while (x != (*raiz) && x->cor == "preto"){
        if (x == x->pai->fe){
            struct nodo *w = x->pai->fd;
            if (w->cor == "vermelho"){
                w->cor = "preto";
                x->pai->cor = "vermelho";
                rotacaoEsquerda (raiz, x->pai);
                w = x->pai->fd;
            }
            if (w->fe->cor == "preto" && w->fd->cor == "preto"){
                w->cor = "vermelho";
                x = x->pai;
            }
            else{
                if (w->fd->cor == "preto"){
                    w->fe->cor = "preto";
                    w->cor = "vermelho";
                    rotacaoDireita (raiz, w);
                    w = x->pai->fd;
                }
                w->cor = x->pai->cor;
                x->pai->cor = "preto";
                w->fd->cor = "preto";
                rotacaoEsquerda (raiz, x->pai);
                x = (*raiz);
            }
        }
        else{
            struct nodo *w = x->pai->fe;
            if (w->cor == "vermelho"){
                w->cor = "preto";
                x->pai->cor = "vermelho";
                rotacaoEsquerda (raiz, x->pai);
                w = x->pai->fd;
            }
            if (w->fd->cor == "preto" && w->fe->cor == "preto"){
                w->cor = "vermelho";
                x = x->pai;
            }
            else{
                if (w->fe->cor == "preto"){
                    w->fd->cor = "preto";
                    w->cor = "vermelho";
                    rotacaoEsquerda (raiz, w);
                    w = x->pai->fd;
                }
                w->cor = x->pai->cor;
                x->pai->cor = "preto";
                w->fe->cor = "preto";
                rotacaoDireita (raiz, x->pai);
                x = (*raiz);
            }
        }
    }  
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
            y = minimo (z->fd);
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
            y.cor = z.cor;
        }
    }

    if (cor_original == "preto") arrumaExcluir (raiz, x);

    return 1;
}

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* raiz, int chave){
    if (raiz->chave == -1 || raiz->chave == chave) return raiz;

    if (chave < raiz->chave) return buscar (raiz->fe, chave);

    return buscar (raiz->fd, chave);
}

void imprimirEmOrdem(struct nodo* nodo){
    return ;
}

void imprimirEmLargura(struct nodo* raiz){
    return ;
}