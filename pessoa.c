#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CPF 12

typedef struct pessoa {
    char cpf [CPF];
    struct pessoa *pai;
    struct pessoa *fd;
    struct pessoa *fe;
} Pessoa;

typedef struct tree {
    Pessoa *raiz;
    int tam;
} Tree;

Pessoa *cria_pessoa (char *cpf){
    Pessoa *nova_p = malloc (sizeof (Pessoa));
    if (!nova_p)
        return NULL;

    strncpy (nova_p->cpf, cpf, 11);
    nova_p->cpf[11] = '\0';
    nova_p->pai = NULL;
    nova_p->fd = NULL;
    nova_p->fe = NULL;

    return nova_p;
}

Pessoa *busca_pessoa (Tree *t, char *cpf) {
    if (!t || !t->raiz)
        return NULL;

    Pessoa *nodo = t->raiz;
    
    while (nodo) {
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

void insere_pessoa (Tree *t, Pessoa *p){
    if (!t || !p){
        printf ("Input Nulo\n");
        return ;
    }
    
    //arvore vazia
    if (t->raiz == NULL){
        t->raiz = p;
    }
    else {
        Pessoa *pai = NULL;
        Pessoa *aux = t->raiz;
        while (aux) {
            int result = strcmp (aux->cpf, p->cpf);
            pai = aux;

            if (result == 0){
                printf ("Erro: essa pessoa já está cadastrada!\n");
                free (p);
                return ;
            }
            // aux > p
            else if (result > 0){
                aux = aux->fe;
            }
            // aux < p
            else {
                aux = aux->fd;
            }
        }

        p->pai = pai;
        if (strcmp (pai->cpf, p->cpf) > 0)
            pai->fe = p;
        else
            pai->fd = p;
    }
    printf ("Inserido com sucesso!\n");
    t->tam += 1;
}

// Função auxiliar, coloca v no lugar de u
void transplante(Tree *t, Pessoa *u, Pessoa *v) {
    if (u->pai == NULL) 
        t->raiz = v;
    else if (u == u->pai->fe) 
        u->pai->fe = v;
    else 
        u->pai->fd = v;
    if (v != NULL) 
        v->pai = u->pai;
}

Pessoa* minimo(Pessoa* n) {
    while (n->fe != NULL) 
        n = n->fe;
    return n;
}

int excluir_pessoa(Tree *t, char *cpf) {
    Pessoa *p = busca_pessoa(t, cpf);
    if (!p) return 1;

    if (p->fe == NULL) {
        transplante(t, p, p->fd);
    } else if (p->fd == NULL) {
        transplante(t, p, p->fe);
    } else {
        Pessoa *aux = minimo(p->fd);
        if (aux->pai != p) {
            transplante(t, aux, aux->fd);
            aux->fd = p->fd;
            aux->fd->pai = aux;
        }
        transplante(t, p, aux);
        aux->fe = p->fe;
        aux->fe->pai = aux;
    }
    free(p);
    t->tam--;
    return 0;
}

void destroi_arvore (Pessoa *p){
    if (!p)
        return ;
    destroi_arvore (p->fe);
    destroi_arvore (p->fd);
    free (p);
}

void pre_ordem (Pessoa *r){
    if (!r)
        return ;
    
    printf ("CPF: %s | ", r->cpf);
    pre_ordem (r->fe);
    pre_ordem (r->fd);
}

void imprime_ordem (Pessoa *r){
    if (!r)
        return ;
    
    imprime_ordem (r->fe);
    printf ("CPF: %s\n", r->cpf);
    imprime_ordem (r->fd);
}

int main () {
    Tree *t = malloc (sizeof (Tree));
    if (!t)
        return 1;
    
    t->tam = 0;
    t->raiz = NULL;

    int input = 0;
    char cpf [CPF];
    printf ("Digite uma opcao (1 - inserir | 2 - buscar | 3 - excluir | 4 - imprimir | 5 - sair): ");
    scanf ("%d", &input);

    while (input != 5) {
        if (input >= 1 && input <= 3){
            printf ("Digite o cpf (somente numeros): ");
            scanf ("%s", cpf);
        }

        switch (input){
            case 1:{
                Pessoa *novo = cria_pessoa (cpf);
                if (!novo){
                    printf ("Erro ao criar pessoa\n");
                    exit (1);
                }
                insere_pessoa (t, novo);
                break;
            }

            case 2:
                Pessoa *p = busca_pessoa (t, cpf);
                if (p)
                    printf ("Pessoa encontrada!\n");
                else
                    printf ("Pessoa não encontrada\n");
                break;

            case 3:
                int e = excluir_pessoa (t, cpf);
                if (e == 0)
                    printf ("Pessoa excluída com sucesso!\n");
                else
                    printf ("Pessoa não encontrada\n");
                break;

            case 4:
                imprime_ordem (t->raiz);
                break;
            
            case 5:
                break;

            default:
                printf ("Opção inválida!\n");
                break;
        }
        printf ("Digite uma opcao (1 - inserir | 2 - buscar | 3 - excluir | 4 - imprimir |5 - sair): ");
        scanf ("%d", &input);
    }

    destroi_arvore (t->raiz);
    free (t);
    return 0;

}