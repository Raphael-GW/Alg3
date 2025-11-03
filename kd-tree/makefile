parametrosCompilacao=-Wall #-Wshadow
nomePrograma=antesprova3_20244362

all: $(nomePrograma)

$(nomePrograma): main.o kdtree.o
	gcc -o $(nomePrograma) main.o kdtree.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: kdtree.h kdtree.c
	gcc -c kdtree.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)