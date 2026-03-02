#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_PESSOAS 100
#define CPF 11

typedef struct pessoa {
    char *cpf;
    Pessoa *pai;
    Pessoa *fd;
    Pessoa *fe;
} Pessoa;

typedef struct tree {
    Pessoa *raiz;
    int tam;
} Tree;

Pessoa *cria_pessoa (char *cpf){
    Pessoa *nova_p = malloc (sizeof (Pessoa));

    nova_p->cpf = cpf;
    nova_p->pai = NULL;
    nova_p->fd = NULL;
    nova_p->fe = NULL;

    return nova_p;
}

struct Pessoa *busca_pessoa (Tree *t, char *cpf) {
    if (!t || !cpf)
        return NULL;

    // árvore vazia
    if (t->raiz == NULL)
        return NULL;

    //cpf inválido
    if (strlen (cpf) < 11){
        printf ("CPF %s inválido!!\n", cpf);
        return NULL;
    }

    Pessoa *nodo = t->raiz;
    
    while (!nodo) {
        int result = strcmp (nodo->cpf, cpf);
        
        if (result == 0)
            return nodo;
        else if (result > 0){
            nodo = nodo->fe;
        }
        else
            nodo = nodo->fd;
    }

    return NULL;
}

void *insere_pessoa (Tree *t, Pessoa *p){
    if (!t || !p){
        print ("Input Nulo\n");
        return ;
    }
    
    //arvore vazia
    if (t->raiz == NULL){
        t->raiz = p;
        print("Inserido com sucesso!\n");
        return ;
    }

    Pessoa *pai = t->raiz;
    Pessoa *aux = t->raiz;
    while (!aux) {
        int result = strcmp (aux, p->cpf);
        
        if (result == 0){
            t->tam += 1;
            print ("Erro: essa pessoa já está cadastrada!\n");
            return ;
        }
        // aux > p
        else if (result > 0){
            pai = aux;
            aux = aux->fe;
        }
        // aux < p
        else
            pai = aux;
            aux = aux->fd;
    }

    p->pai = pai;
    if (strcmp (pai->cpf, p->cpf) > 0)
        pai->fe = p;
    else
        pai->fd = p;

    printf ("Inserido com sucesso!\n");
    t->tam += 1;
    return ;
}

Pessoa *excluir_pessoa (Tree *t, char *cpf){
    if (!t || !cpf)
        return NULL;
    
    //arvore vazia
    if (t->raiz == NULL)
        return NULL;

    //arvore com 1 pessoa
    if (t->tam == 1){
        int result = strcmp (t->raiz->cpf, cpf);

        if (result == 0){
            Pessoa *aux = t->raiz;
            free (t->raiz);
            t->tam = 0;
            return aux;
        }
        else
            return NULL;
    }

    Pessoa *nodo = busca_pessoa (t, cpf);

    // nodo não encontrado
    if (!nodo)
        return NULL;
    
    //nodo é folha
    if (nodo->fd == NULL && nodo->fe == NULL){
        Pessoa *au
    }
}