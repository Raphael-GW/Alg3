#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"


int main(){
	//ATENÇÃO, ESSE É APENAS UM EXEMPLO DE IMPLEMENTAÇÃO DO MAIN.
	//MODIFIQUE DE ACORDO COM SUAS NECESSIDADES E DE ACORDO COM AS ESPECIFICAÇÕES.
	struct tree *t = malloc (sizeof (struct tree));
	int n;
	if (!t) return 1;
	t->raiz = NULL;

	imprimirDadosAluno();

	scanf ("%d", &n);
	scanf ("%d", &t->num_dims);
	int val[t->num_dims];
	
	if (n % t->num_dims != 0) return 1;		// num de nodos não é múltiplo do num de dimensões

	printf ("Insere:\n");
	for (size_t i = 0; i < n; i + t->num_dims){
		for (size_t j = 0; j < t->num_dims; j++){
			scanf("%d", &val[j]);
		}
		if(inserir(t, val) == NULL)
		fprintf(stderr,"Falha ao inserir.\n");
	}

	char op;
	scanf(" %c", &op);
	while(op != 'f'){
		switch (op) {
			case 'l':
				imprimirEmLargura(t);
				break;
			case 'b':
			 	for (size_t i = 0; i < t->num_dims; i++){
					scanf("%d", &val[i]);
				}
				struct nodo* valB = buscar(t->raiz, val, 0, t->num_dims);
				if(valB != NULL){
					printf("Encontrado (%d", val[0]);
					for (size_t i = 1; i < t->num_dims; i++){
						printf(" %d", val[i]);
					}
					printf (")\n");
				}
				else
					printf("Nao encontrado (%d %d)\n", val[0], val[1]);
				break;
			case 'z':
			default:
				fprintf(stderr,"Opcao Invalida %d", (int)op);
		}
		scanf(" %c", &op);
	}

	return 0;
}