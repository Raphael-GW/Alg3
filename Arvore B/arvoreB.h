#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdint.h>
#include <stdbool.h> // inclusão não precisaria ser feita com o padrão std=c23

struct nodo {
  int32_t nchave;
  int32_t *chaves;
  struct nodo **filhos;
  char folha;
};

struct arvoreB {
  struct nodo* raiz;
  int32_t t_arvore;
};

struct arvoreB* criarArvoreB(int32_t t_arvore);
void inserirArvoreB(struct arvoreB* arvore, int32_t chave);
void imprimirArvoreB(struct arvoreB* arvore);
void imprimirEmOrdem(struct arvoreB* arvore);
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                          int32_t* idxEncontrado);
bool removerChaveArvoreB (struct arvoreB* arvore, int32_t chave);
void deletarArvore(struct arvoreB* arvore);

#endif
