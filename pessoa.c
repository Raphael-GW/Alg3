#include <stdio.h>
#include <stdlib.h>

#define MAX_NOME 50
#define MAX_PESSOAS 100

typedef struct pessoa {
    __int8 idade;
    char nome [MAX_NOME];
    __int8 altura;
    float peso;
} Pessoa;

typedef struct dict_pessoas {
    Pessoa pessoa_dict [MAX_PESSOAS];
} Dict_Pessoas;

struct Pessoa *busca_pessoa (Dict_Pessoas lib, Pessoa p) {
    
}