#ifndef KDTREE_H_
#define KDTREE_H_

struct nodo {
    struct nodo *pai;
    struct nodo *fd;
    struct nodo *fe;
    int classe;
    float *vetchave;
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
struct nodo* inserir(struct tree *t, float *vetchave, int c);

// retorna o número de nodos excluídos
void vizinhos_prox(struct tree *t, float *vetchave, int num);

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo *r, float *vetchave, int coord, int k);

void imprimirEmLargura(struct tree *t);

#endif