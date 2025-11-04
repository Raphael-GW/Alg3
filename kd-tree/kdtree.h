#ifndef KDTREE_H_
#define KDTREE_H_

struct nodo {
    struct nodo *pai;
    struct nodo *fd;
    struct nodo *fe;
    int *vetchave;
};

struct tree {
    struct nodo *raiz;
    int num_dims;
};

struct nodo *cria_nodo ();

struct aluno{
    char* nome;//nome completo
    char* nomeDinf;//nome de usuário nas servidoras do dinf
    unsigned int grr;
};

struct aluno* getAluno();

void imprimirDadosAluno();

//retorna NULO se não foi possível inserir
struct nodo* inserir(struct tree *t, int *vetchave);

// retorna o número de nodos excluídos
int excluir(struct tree *t, int *vetchave);

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo *r, int *vetchave, int coord, int k);

void imprimirEmOrdem(struct tree *t);

void imprimirEmLargura(struct tree *t);

#endif