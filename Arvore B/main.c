#include <stdio.h>
#include <stdlib.h>

#include "arvoreB.h"


int main (){

    int32_t t;
    scanf ("%d", &t);

    struct arvoreB* arvore = criarArvoreB (t);
    if (!arvore)
        exit(1);

    printf ("SELECIONE UMA OPÇÃO: 1 - Inserir  2 - Buscar  3 - Imprimir  4 - Imprime Ordem  5 - Sair\n");

    int op = 0;
    scanf ("%d", &op);

    int32_t chave = 0;
    int32_t idx = -1;
    while (op != 5){
        switch (op){
            case 1:
                scanf ("%d", &chave);
                inserirArvoreB (arvore, chave);
                break;
            
            case 2:
                scanf ("%d", &chave);
                buscarArvoreB (arvore, chave , &idx);
                break;

            case 3:
                imprimirArvoreB (arvore);
                break;

            case 4:
                imprimirEmOrdem (arvore);
                break;

            case 5:
                deletarArvore (arvore);
                break;

            default:
                printf ("Opcao invalida!!\n");
                break;
        }
        printf ("SELECIONE UMA OPCAO: 1 - Inserir  2 - Buscar  3 - Imprimir  4 - Imprime Ordem  5 - Sair\n");
        scanf ("%d", &op);
    }

    return 0;
}