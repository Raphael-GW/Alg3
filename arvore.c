#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TAM_EXP 100

struct nodo {
    char ope;
    int valor;
    struct nodo *pai;
    struct nodo *fe;
    struct nodo *fd;
};

struct arvore {
    struct nodo *raiz;
    short int tam;
};

struct nodo *cria_nodo (){
    struct nodo *new_nodo = malloc (sizeof (struct nodo));

    if (!new_nodo) return NULL;

    new_nodo->pai = NULL;
    new_nodo->fe = NULL;
    new_nodo->fd = NULL;

    return new_nodo;
}


void insere_nodo (struct arvore *tree, char *token, char *operacoes){
    if (!tree || !token || operacoes) return NULL;

    struct nodo *novo = cria_nodo ();
    short int inserido = 0;

    if (token >= 42 && token <= 47) novo->ope = token;
    else novo->valor = atoi (token);

    tree->tam += 1;
    //arvore vazia
    if (!tree->raiz){
        tree->raiz = novo;
        return ;
    }

    struct nodo *aux = tree->raiz;

    while (aux->fe != NULL) aux = aux->fe;

    if (aux->ope){
        aux->fe = novo;
        novo->pai = aux;
    }
    else{
        aux = aux->pai;
        while (!inserido){
            if (!aux->fd){
                aux->fd = novo;
                novo->pai = aux;
                inserido = 1;
            }
        }
    }






    

    


    
}

void imprime_preordem (){
    return ;
}

int main (){
    char expressao[TAM_EXP + 1];
    const char *delim = ' ';
    char *token;
    char *operacoes = '* + / -';
    struct arvore *tree = malloc (sizeof (struct arvore));

    if (fgets(expressao, TAM_EXP, stdin) != NULL) {
        // Remove o '\n' que o fgets guarda no final
        size_t len = strlen(expressao);
        if (len > 0 && expressao[len - 1] == '\n') {
            expressao[len - 1] = '\0';
        }
    }
    token = strtok (expressao, delim);

    
    while(token != NULL) {
        insere_nodo (tree, token, operacoes);
    
        token = strtok(NULL, delim);
    }
    
    

    
    return 0;
}

