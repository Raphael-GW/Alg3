#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM_EXP 100

struct nodo {
    char ope;
    float valor;
    struct nodo *fe;
    struct nodo *fd;
};

struct nodo *cria_nodo (){
    struct nodo *new_nodo = malloc (sizeof (struct nodo));

    if (!new_nodo)
        return NULL;

    new_nodo->fe = NULL;
    new_nodo->fd = NULL;

    return new_nodo;
}

struct nodo *cria_arvore (char *token){
    struct nodo *arvore = cria_nodo ();
    char *ope = "/ * - +";
    char *tk_ope = strtok (ope, " ");

    if (!token || !arvore)
        return NULL;

    // verificar se equação é válida
    int valido = 0;
    while (tk_ope != NULL){
        if (strcmp (token, tk_ope) == 1)
            valido = 1;

        tk_ope = strtok(NULL, " ");
    }

    if (!valido){
        return NULL;
    }

    arvore->ope = *token;
    token = strtok(NULL, " ");


    



    return NULL;
}

void imprime_preordem (){
    return ;
}

int main (){
    char expressao[TAM_EXP];
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

