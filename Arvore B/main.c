#include <stdio.h>
#include <stdlib.h>

#include "arvoreB.h"


int main (){

    int32_t t;
    scanf ("%d", &t);

    struct arvoreB* arvore = criarArvoreB (t);
    if (!arvore)
        exit(1);

    
    printf ("SELECIONE UMA OPCAO: 1 - Inserir  2 - Buscar  3 - Imprimir  \n4 - Imprime Ordem  5 - Excluir chave  6 - Sair\n");

    int op = 0;
    scanf ("%d", &op);

    int32_t chave = 0;
    int32_t idx = -1;
    while (op != 6){
        switch (op){
            case 1:
                scanf ("%d", &chave);
                inserirArvoreB (arvore, chave);
                break;
            
            case 2:
                scanf ("%d", &chave);
                struct nodo* n = buscarArvoreB (arvore, chave , &idx);
                if (n)
                    printf ("Chave encontrada no índice %d\n", idx);
                else
                    printf ("Chave não encontrada!!\n");
                break;

            case 3:
                imprimirArvoreB (arvore);
                break;

            case 4:
                imprimirEmOrdem (arvore);
                break;

            case 5:
                scanf ("%d", &chave);
                bool remove = removerChaveArvoreB (arvore, chave);
                if (remove)
                    printf ("Chave removida com sucesso!!\n");
                else
                    printf ("Chave não encontrada\n");
                break;

            default:
                printf ("Opcao invalida!!\n");
                break;
        }
        printf ("SELECIONE UMA OPCAO: 1 - Inserir  2 - Buscar  3 - Imprimir  \n4 - Imprime Ordem  5 - Excluir chave  6 - Sair\n");
        scanf ("%d", &op);
    }

    deletarArvore (arvore);
    return 0;
}