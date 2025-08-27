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


void insere_nodo (char *token){
    if (!token) return NULL;

    struct nodo *novo = cria_nodo ();

    char *operacoes = "/ * - +";
    char *tk_op = strtok (operacoes, " ");
    short int inserido = 0;

    while (tk_op != NULL){
        if (strcmp (tk_op, token) == 1){
            novo->ope = token;
            inserido = 1;
            break;
        }

        tk_op = strtok (NULL, " ");
    }

    if (!inserido) novo->valor = token - '0';
    

    


    
}

void imprime_preordem (){
    return ;
}

int main (){
    char expressao[TAM_EXP + 1];
    const char *delim = " ";
    char *token;

    if (fgets(expressao, TAM_EXP, stdin) != NULL) {
        // Remove o '\n' que o fgets guarda no final
        size_t len = strlen(expressao);
        if (len > 0 && expressao[len - 1] == '\n') {
            expressao[len - 1] = '\0';
        }
    }
    token = strtok (expressao, delim);

    while(token != NULL) {
      printf("%s\n", token);
    
      token = strtok(NULL, delim);
    }
    
    

    
    return 0;
}

