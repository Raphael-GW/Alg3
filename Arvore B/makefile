# Adicionado -g para incluir símbolos de depuração, essencial para o Valgrind
parametrosCompilacao=-std=c2x -Wall -g
nomePrograma=prova2_20244362

# Flags recomendadas para uma análise completa de memória
FLAGS_VALGRIND=--leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(nomePrograma)

$(nomePrograma): main.o arvoreB.o
	gcc -o $(nomePrograma) main.o arvoreB.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

arvoreB.o: arvoreB.h arvoreB.c
	gcc -c arvoreB.c $(parametrosCompilacao)

# Nova regra: compila (se necessário) e executa com valgrind
valgrind: $(nomePrograma)
	valgrind $(FLAGS_VALGRIND) ./$(nomePrograma)

clean:
	rm -f *.o *.gch $(nomePrograma)