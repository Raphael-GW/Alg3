#include <stdio.h>
#include <stdlib.h>

#include "kdtree.h"

int main(){
	//ATENÇÃO, ESSE É APENAS UM EXEMPLO DE IMPLEMENTAÇÃO DO MAIN.
	//MODIFIQUE DE ACORDO COM SUAS NECESSIDADES E DE ACORDO COM AS ESPECIFICAÇÕES.
	struct nodo* raiz = malloc (sizeof (struct nodo));
	if (!raiz) return 0;
	

	imprimirDadosAluno();

	char op;
	int val;
	scanf(" %c", &op);
	while(op != 'f'){
		switch (op) {
			case 'i':
				scanf("%d", &val);
				if(inserir(&raiz, val) == raiz->pai)
					fprintf(stderr,"Falha ao inserir.\n");
				break;
			case 'r':
				scanf("%d", &val);
				if(!excluir(&raiz, val))
					fprintf(stderr,"Falha ao remover %d.\n", val);
				break;
			case 'e':
				imprimirEmOrdem(raiz);
				puts("\n");
				break;
			case 'l':
				imprimirEmLargura(raiz);
				break;
			case 'b':
			 	scanf("%d", &val);
				struct nodo* valB = buscar(raiz, val);
				if(valB != (*raiz).pai)
					printf("Encontrado %d\n", valB->chave);
				else
					printf("Nao encontrado %d\n", val);
				break;
			default:
				fprintf(stderr,"Opcao Invalida %d", (int)op);
		}
		scanf(" %c", &op);
	}

	return 0;
}