#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"

int main(){
	//ATENÇÃO, ESSE É APENAS UM EXEMPLO DE IMPLEMENTAÇÃO DO MAIN.
	//MODIFIQUE DE ACORDO COM SUAS NECESSIDADES E DE ACORDO COM AS ESPECIFICAÇÕES.
	struct tree *t = malloc (sizeof (struct tree));
	if (!t) return 1;
	
	t->raiz = NULL;

	imprimirDadosAluno();

	char op;
	scanf(" %c", &op);
	scanf ("%d", &t->num_dims);
	int val[t->num_dims];
	
	while(op != 'f'){
		switch (op) {
			case 'i':
				printf ("Insere:\n");
				for (size_t i = 0; i < t->num_dims; i++){
					scanf("%d", &val[i]);
				}
				if(inserir(t, val) == NULL)
					fprintf(stderr,"Falha ao inserir.\n");
				break;
			case 'r':
				for (size_t i = 0; i < t->num_dims; i++){
					scanf("%d", &val[i]);
				}
				if(!excluir(t, val)){
					fprintf(stderr,"Falha ao remover (");
					for (size_t i = 0; i < t->num_dims; i++){
						printf(" %d", val[i]);
					}
					printf (")\n");
				}
				break;
			case 'e':
				imprimirEmOrdem(t);
				puts("\n");
				break;
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
			default:
				fprintf(stderr,"Opcao Invalida %d", (int)op);
		}
		scanf(" %c", &op);
	}

	return 0;
}