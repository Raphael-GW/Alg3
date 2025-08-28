#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define TAM_EXP 100

struct nodo {
    char *key;
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


void insere_nodo (struct arvore *tree, char *token){
    if (!tree || !token) return ;

    struct nodo *novo = cria_nodo ();

    novo->key = token;

    tree->tam += 1;
    //arvore vazia
    if (!tree->raiz){
        tree->raiz = novo;
        return ;
    }

    struct nodo *aux = tree->raiz;
    struct nodo *pai = NULL;

    while (aux != NULL){
        pai = aux;
        if (aux->key < 48) aux = aux->fe;
        else aux = aux->fd;
    }
    novo->pai = pai;
    
    if (pai->fe) pai->fd = novo;
    else pai->fe = novo;
    
}

void imprime_preordem (struct nodo *nodo){
    if (nodo){
        printf ("%s ", nodo->key);
        imprime_preordem (nodo->fe);
        imprime_preordem (nodo->fd);
    }
}

struct arvore *destroi_arvore (struct nodo *nodo){
    if (!nodo) return NULL;
    if (nodo){
        destroi_arvore (nodo->fe);
        destroi_arvore (nodo->fd);
        free (nodo);
    }
}

int main (){
    char expressao[TAM_EXP + 1];
    const char *delim = " ";
    char *token;
    //char *operacoes = '* + / -';
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
        insere_nodo (tree, token);
        token = strtok(NULL, delim);
        printf ("Nodo inserido\n");
    }

    imprime_preordem (tree->raiz);
    printf ("\n");
    printf ("Quantidades de nodos: %d\n", tree->tam);

    destroi_arvore (tree->raiz);
    free (tree);
    

    
    return 0;
}

