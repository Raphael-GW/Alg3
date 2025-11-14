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

struct melhor_vizinho {
    struct nodo *n;
    struct melhor_vizinho *prox;
    float distancia;
};

struct fprio{
    struct melhor_vizinho *prim;
    int tam;
};

struct fprio* cria_fprio();


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
void z_vizinhos_prox(struct nodo *r, int coord, float *vetchave, int k, int z, struct melhor_vizinho *melhor, struct fprio* f);

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo *r, float *vetchave, int coord, int k);

void imprimirEmLargura(struct tree *t);

struct melhor_vizinho* cria_melhor(float d);

#endif