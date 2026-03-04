#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


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
        if ((int)aux->key < 48) aux = aux->fe;
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

void destroi_arvore (struct nodo *nodo){
    if (!nodo) return ;
    if (nodo){
        destroi_arvore (nodo->fe);
        destroi_arvore (nodo->fd);
        free (nodo);
    }
}

float resolve_esquacao (struct nodo *n){
    if (!n)
        return 0;

    // Se for uma folha retorna o número
    if (isdigit(n->key[0])){
        return atof(n->key);
    }

    float num1 = resolve_esquacao (n->fe);
    float num2 = resolve_esquacao (n->fd);

    switch (n->key[0]){
        case '*':
            printf ("multiplica %.2f * %.2f\n", num1, num2);
            return num1 * num2;

        case '/':
            if (num2 != 0)
                return num1 / num2;
            else
                return 0;

        case '+':
            return num1 + num2;

        case '-':
            printf ("subtrai %.2f - %2.f\n", num1, num2);
            return num1 - num2;
        default:
            return 0;
    }
}

int main (){
    char expressao[TAM_EXP + 1];
    const char *delim = " ";
    char *token;
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

    printf ("Resultado: %.2f\n", resolve_esquacao (tree->raiz));

    destroi_arvore (tree->raiz);
    free (tree);
    

    
    return 0;
}

