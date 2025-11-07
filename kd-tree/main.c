#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"


void destroi_tree(struct tree* t){
	if (!t) return ;
}

void em_ordem (struct nodo* n, int k){
	if (n){
		em_ordem (n->fe, k);
		printf ("[");
		for (size_t j = 0; j < k; j++){
			printf(" %.1f", n->vetchave[j]);
		}
		printf ("]\n");
		em_ordem (n->fd, k);
	}
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

	em_ordem (t->raiz, t->num_dims);

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
				vizinhos_prox (t, val, z);
			default:
				fprintf(stderr,"Opcao Invalida %d", (int)op);
		}
		scanf(" %c", &op);
	}

	return 0;
}