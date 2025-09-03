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

    if (y->fe != raiz[0]->pai) y->fe->pai = nodo;

    y->pai = nodo->pai;

    if (nodo->pai == raiz[0]->pai) raiz[0] = y;
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

    if (y->fd != raiz[0]->pai) y->fd->pai = nodo;

    y->pai = nodo->pai;

    if (nodo->pai == raiz[0]->pai) raiz[0] = y;
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
    raiz[0]->cor = "preto";
}

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave){
    if (!raiz || chave == -1) return raiz[0]->pai;

    if (buscar (raiz[0], chave) != raiz[0]->pai) return raiz[0]->pai; // Chave já existe

    struct nodo *novo = cria_nodo ();
    if (!novo) return raiz[0]->pai;

    novo->chave = chave;

    struct nodo *x = raiz[0];
    struct nodo *y = raiz[0]->pai;
    
    while (x != raiz[0]->pai){
        y = x;
        if (novo->chave < x->chave) x = x->fe;
        else x = x->fd;
    }

    novo->pai = y;
    if (y == raiz[0]->pai) raiz[0] = novo; // Árvore vazia
    else{
        if (novo->chave < y->chave) y->fe = novo;
        else y->fd = novo;
    }

    arrumaArvore (raiz, novo);

    return novo;
}

void transplantar (struct nodo** raiz, struct nodo *u, struct nodo *v){

}

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave){
    return 0;
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