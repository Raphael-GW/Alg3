#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"


void destroi_tree(struct nodo* r){
	if (!r) return ;
	destroi_tree(r->fe);
	destroi_tree(r->fd);
	free(r->vetchave);
	free(r);
}

int main(){
	//ATENÇÃO, ESSE É APENAS UM EXEMPLO DE IMPLEMENTAÇÃO DO MAIN.
	//MODIFIQUE DE ACORDO COM SUAS NECESSIDADES E DE ACORDO COM AS ESPECIFICAÇÕES.
	struct tree *t = malloc (sizeof (struct tree));
	int n;
	int classe = 0;
	
	if (!t){
		printf ("Falha ao alocar memória\n");
		exit (1);
	}
	t->raiz = NULL;

	imprimirDadosAluno();

	printf ("Insira N e K:\n");
	scanf ("%d", &n);
	scanf ("%d", &t->num_dims);
	float val[t->num_dims];
	

	printf ("Insere:\n");
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < t->num_dims; j++){
			scanf("%e", &val[j]);
		}
		scanf ("%d", &classe);
		if(inserir(t, val, classe) == NULL)
		fprintf(stderr,"Falha ao inserir.\n");
	}

	printf ("Arvore Construida\n");

	int z;
	float busca[t->num_dims];
	char op;
	scanf(" %c", &op);
	while(op != 'f'){
		switch (op) {
			case 'l':
				imprimirEmLargura(t);
				break;
			case 'b':
			 	for (size_t i = 0; i < t->num_dims; i++){
					scanf("%e", &busca[i]);
				}
				struct nodo* valB = buscar(t->raiz, busca, 0, t->num_dims);
				if(valB != NULL){
					printf("Encontrado. Classe %d\n", valB->classe);
				}
				else printf("Nao encontrado.\n");
				break;
			case 'z':
				scanf ("%d", &z);
				for (size_t j = 0; j < t->num_dims; j++){
					scanf("%e", &val[j]);
				}
				struct fprio *f = cria_fprio();
				if (!f){
					printf ("Falha ao alocar memória\n");
					exit (1);
				}
				struct melhor_vizinho *melhor = cria_melhor(1000.0);
				z_vizinhos_prox(t->raiz, 0, val, t->num_dims, z, melhor, f);
				printf ("Vizinhos mais proximos:\n");
				struct melhor_vizinho *atual = f->prim;
				for (size_t i = 0; i < z; i++){
					if (!atual) break;
					for (size_t j = 0; j < (t->num_dims - 1); j++){
						printf ("%.1f, ", atual->n->vetchave[j]);
					}
					printf ("%.1f ", atual->n->vetchave[t->num_dims - 1]);
					printf ("(classe %d), dist = %.4f\n", atual->n->classe, atual->distancia);
					atual = atual->prox;
				}
				destroi_fprio(f);
				free(melhor);
				break;
			default:
				fprintf(stderr,"Opcao Invalida %d", (int)op);
		}
		scanf(" %c", &op);
	}

	destroi_tree(t->raiz);
	free(t);

	return 0;
}