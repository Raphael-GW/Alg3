parametrosCompilacao=-std=c2x -Wall
nomePrograma=prova1_20244362

all: $(nomePrograma)

$(nomePrograma): main.o arvoreB.o
	gcc -o $(nomePrograma) main.o arvoreB.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

arvoreB.o: arvoreB.h arvoreB.c
	gcc -c arvoreB.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)