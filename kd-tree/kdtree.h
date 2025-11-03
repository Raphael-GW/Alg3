#ifndef KDTREE_H_
#define KDTREE_H_

struct nodo {
    struct nodo *pai;
    struct nodo *fd;
    struct nodo *fe;
    int *vetchave;
};

struct nodo *cria_nodo ();

struct aluno{
    char* nome;//nome completo
    char* nomeDinf;//nome de usuário nas servidoras do dinf
    unsigned int grr;
};

struct aluno* getAluno();

void imprimirDadosAluno();

//retorna SENTINELA se não foi possível inserir
struct nodo* inserir(struct nodo** raiz, int chave);

// retorna o número de nodos excluídos
int excluir(struct nodo** raiz, int chave);

//retorna SENTINELA se não existe
struct nodo* buscar(struct nodo* raiz, int chave);

void imprimirEmOrdem(struct nodo* nodo);

void imprimirEmLargura(struct nodo* raiz);

#endif