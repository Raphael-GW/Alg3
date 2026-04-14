#include <stdio.h>
#include <stdlib.h>

#include "arvoreB.h"

struct nodo* criarnodo(int32_t t_arvore){
    struct nodo* nodo = malloc (sizeof (struct nodo));
    if (!nodo)
        return NULL;

    nodo->nchave = 0;
    nodo->chaves = malloc (sizeof(int32_t) * (2*t_arvore - 1));
    nodo->filhos = malloc (sizeof (struct nodo) * 2*t_arvore);
    for (int32_t i = 0; i < 2*t_arvore; i++)
        nodo->filhos[i] = NULL;
    nodo->folha = 1;

    return nodo;
}

struct arvoreB* criarArvoreB(int32_t t_arvore){
    struct arvoreB* arvore = malloc (sizeof (struct arvoreB));
    if (!arvore)
        return NULL;

    arvore->raiz = NULL;

    arvore->t_arvore = t_arvore;

    return arvore;
}

void divide_filho (struct nodo* x, int32_t idx, int32_t t){
    if (!x)
        return ;
    
    
    struct nodo* z = criarnodo (t);
    if (!z)
        return ;

    struct nodo* y = x->filhos[idx];
    z->folha = y->folha;
    z->nchave = t - 1;

    for (int32_t i = 0; i < t - 1; i++)
        z->chaves[i] = y->chaves[i+t];
    

    if (!y->folha){
        for (int32_t i = 0; i < t; i++){
            z->filhos[i] = y->filhos[i+t];
        }
    }

    y->nchave = t - 1;
    for (int32_t i = x->nchave + 1; i >= idx + 1; i--)
        x->filhos[i+1] = x->filhos[i];
    
    x->filhos[idx+1] = z;
    for (int32_t i = x->nchave; i >= idx; i--)
        x->chaves[i+1] = x->chaves[i];
    
    x->chaves[idx] = y->chaves[t - 1];
    x->nchave += 1;
}

struct nodo* dividir_raiz (struct arvoreB* arvore){
    if (!arvore)
        return NULL;

    struct nodo* s = criarnodo (arvore->t_arvore);
    if (!s)
        return NULL;

    s->filhos[0] = arvore->raiz;
    arvore->raiz = s;
    s->folha = 0;

    divide_filho (s, 0, arvore->t_arvore);

    return s;
}

void inserirNaoCheio (struct nodo* x, int32_t k, int32_t t){
    if (!x)
        return ;

    int32_t idx = x->nchave - 1;
    if (x->folha){
        while (idx >= 0 && k < x->chaves[idx]){
            x->chaves[idx+1] = x->chaves[idx];
            idx -= 1;
        }
        x->chaves[idx+1] = k;
        x->nchave += 1;
    }
    else{
        while (idx >= 0 && k < x->chaves[idx])
            idx -= 1;
        
        idx += 1;

        if (x->filhos[idx]->nchave == (2*t - 1)){
            divide_filho (x, idx, t);
            if (k > x->chaves[idx])
                idx += 1;
            
        }

        inserirNaoCheio (x->filhos[idx], k, t);
    }
}

void inserirArvoreB(struct arvoreB* arvore, int32_t chave){
    if (!arvore)
        return ;

    if (!arvore->raiz)
        arvore->raiz = criarnodo (arvore->t_arvore);

    struct nodo* r = arvore->raiz;
    int32_t t = arvore->t_arvore;
    if (r->nchave == 2 * t - 1){
        struct nodo* s = dividir_raiz (arvore);
        if (!s)
            return ;

        inserirNaoCheio (s, chave, arvore->t_arvore);
    }
    else
        inserirNaoCheio (r, chave, arvore->t_arvore);
}

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado){
    if (!idxEncontrado)
        return NULL;

    if (!arvore || !arvore->raiz){
        *idxEncontrado = -1;
        return NULL;
    }

    struct nodo* aux = arvore->raiz;
    while (aux){
        int32_t idx = 0;

        while (idx < aux->nchave && chave > aux->chaves[idx])
            idx += 1;
        
        if (idx < aux->nchave && chave == aux->chaves[idx]){
            *idxEncontrado = idx;
            return aux;
        }

        if (aux->folha)
            break;

        aux = aux->filhos[idx];
    }

    *idxEncontrado = -1;
    return NULL;
}

// ---------- Estrutura auxiliar para impressão em ordem -------------
struct item {
    struct nodo* n;
    int32_t f_idx; // index do filho
};

struct pilha {
    struct item** items;
    int32_t topo;
};

//cria pilha vazia
struct pilha* cria_pilha (int32_t t){
    struct pilha* p = malloc (sizeof (struct pilha));
    if (!p)
        return NULL;

    p->items = malloc (sizeof (struct item*) *2*t);
    p->topo = 0;
    return p;
}

// cria o item da pilha com o nodo e o índice do filho
struct item* cria_item (struct nodo* n, int32_t idx){
    struct item* i = malloc (sizeof (struct item));
    if (!i)
        return NULL;

    i->f_idx = idx;
    i->n = n;
    return i;
} 

void empilha (struct pilha* p, struct nodo* n, int32_t idx){
    if (!p || !n)
        return ;

    struct item* i = cria_item (n, idx);
    if (!i)
        return ;

    p->items[p->topo] = i;
    p->topo += 1;
}

struct item* desempilha (struct pilha* p){
    if (!p || p->topo == 0)
        return NULL;

    p->topo -= 1;
    struct item* i = p->items[p->topo];

    return i;
}
// ------------------------------------------------------------


void imprimirEmOrdem(struct arvoreB* arvore){
    if (!arvore)
        return ;

    struct pilha* p = cria_pilha (arvore->t_arvore);
    if (!p)
        return ;

    empilha (p, arvore->raiz, 0);

    printf ("Em ordem: ");

    while (p->topo > 0){
        struct item* i = desempilha (p);
        struct nodo* n = i->n;
        int32_t idx = i->f_idx;

        if (n->folha){
            for (int32_t i = 0; i < n->nchave; i++)
                printf ("%d ", n->chaves[i]);
            
        }

        if (idx > 0 && (idx - 1) < n->nchave)
            printf ("%d ", n->chaves[idx - 1]);
        

        if (idx <= n->nchave){
            if (!n->folha)
                empilha (p, n, idx + 1);
            empilha (p, n->filhos[idx], 0);
        }
        free (i);
    }
    printf ("\n");
    
    free (p->items);
    free (p);
}


// ----------- Estrutura auxiliar para impressão em largura -----------

struct nodo_fila {
    struct nodo* n;
    struct nodo_fila* prox;
};

struct fila {
    struct nodo_fila* prim;
    struct nodo_fila* ult;
};

void enfileirar (struct fila* f, struct nodo* n){
    if (!f || !n)
        return ;

    struct nodo_fila* nf = malloc (sizeof(struct nodo_fila));
    if (!nf)
        return ;
    nf->n = n;
    nf->prox = NULL;
    
    //fila vazia
    if (!f->prim){
        f->prim = nf;
        f->ult = nf;
    }
    else{
        f->ult->prox = nf;
        f->ult = nf;
    }
}

struct nodo* desinfileirar (struct fila* f){
    if (!f || !f->prim)
        return NULL;

    struct nodo_fila* nf = f->prim;
    struct nodo* n = nf->n;

    f->prim = nf->prox;
    free (nf);

    return n;
}

// --------------------------------

void imprimirArvoreB(struct arvoreB* arvore){
    if (!arvore)
        return ;

    struct fila* f = malloc (sizeof(struct fila));
    if (!f)
        return ;
    
    f->prim = NULL;
    f->ult = NULL;
    enfileirar (f, arvore->raiz);

    int nivel = 0;
    while (f->prim){
        int n_no_nivel = 0; // quantidade de nodos no nivel
        struct nodo_fila* temp = f->prim;
        while (temp){
            n_no_nivel++;
            temp = temp->prox;
        }

        printf ("----//----\n");
        printf ("Nivel %d\n", nivel);
        printf ("----//----\n");

        for (int32_t i = 0; i < n_no_nivel; i++){
            struct nodo* n = desinfileirar (f);
            if (!n)
                return ;
            
            if (!n->folha){
                printf ("I ");
                printf ("(n:%d)", n->nchave);
                printf ("[");
                for (int32_t j = 0; j < n->nchave; j++){
                    printf (" %d", n->chaves[j]);
                    enfileirar (f, n->filhos[j]);
                }
                enfileirar (f, n->filhos[n->nchave]);
                printf ("]  ");
            }
            else{   
                printf ("F ");
                printf ("(n:%d)", n->nchave);
                printf ("[");
                for (int32_t j = 0; j < n->nchave; j++)
                    printf (" %d", n->chaves[j]);
                    
                printf ("]  ");
            }
        }
        nivel += 1;
        printf("\n");
    }

    while (f->prim)
        desinfileirar (f);
    free (f);
}

void deletarNodo (struct nodo* n){
    if (!n)
        return ;

    if (!n->folha){
        for (int32_t i = 0; i <= n->nchave; i++)
            deletarNodo (n->filhos[i]);
    }

    free (n->chaves);
    free (n->filhos);
    free(n);
}

void deletarArvore (struct arvoreB* arvore){
    if (!arvore)
        return ;

    if (arvore->raiz)
        deletarNodo (arvore->raiz);
    free (arvore);
}