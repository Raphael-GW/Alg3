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

// Auxiliar para verificar se é operador
int eh_operador(char *s) {
    return (strcmp(s, "+") == 0 || strcmp(s, "-") == 0 || 
            strcmp(s, "*") == 0 || strcmp(s, "/") == 0);
}

struct nodo *cria_nodo(char *token) {
    struct nodo *new_nodo = malloc(sizeof(struct nodo));
    if (!new_nodo) return NULL;
    
    new_nodo->key = strdup(token); // Copia a string do token
    new_nodo->fe = NULL;
    new_nodo->fd = NULL;
    return new_nodo;
}

// FUNÇÃO CHAVE: Constrói a árvore recursivamente
struct nodo* constroi_arvore_prefixa() {
    char *token = strtok(NULL, " ");
    if (!token) return NULL;

    struct nodo *n = cria_nodo(token);

    // Se for operador, ele obrigatoriamente terá dois filhos
    if (eh_operador(token)) {
        n->fe = constroi_arvore_prefixa();
        n->fd = constroi_arvore_prefixa();
    }
    // Se for número, a recursão para aqui e retorna o nó folha
    return n;
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
        free(nodo->key);
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

    printf ("%.2f %.2f\n", num1, num2);
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
    struct arvore tree = {NULL};

    printf("Digite a expressão em Notação Polonesa (ex: + 5 * 3 2): ");
    if (fgets(expressao, TAM_EXP, stdin)) {
        expressao[strcspn(expressao, "\n")] = 0; // Remove o \n
        
        // Inicializa o strtok com a string
        char *primeiro_token = strtok(expressao, " ");
        if (primeiro_token) {
            tree.raiz = cria_nodo(primeiro_token);
            
            // Se o primeiro for operador, começa a recursão para os filhos
            if (eh_operador(primeiro_token)) {
                tree.raiz->fe = constroi_arvore_prefixa();
                tree.raiz->fd = constroi_arvore_prefixa();
            }
        }
    }

    if (tree.raiz) {
        printf("\nPre-ordem: ");
        imprime_preordem(tree.raiz);
        printf("\nResultado: %.2f\n", resolve_esquacao(tree.raiz));
        destroi_arvore(tree.raiz);
    }
    return 0;
}

