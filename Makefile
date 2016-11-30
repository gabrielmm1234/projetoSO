all: pseudoSo clean

pseudoSo: Leitor.o Fila.o Processador.o Processo.o Memoria.o
	gcc pseudoSo.c Leitor.o Fila.o Processador.o Processo.o Memoria.o -std=c99 -pthread -o pseudoSo

Leitor.o: Leitor.c Leitor.h 
	gcc Leitor.c -std=c99 -c -pthread 

Fila.o: Fila.c Fila.h
	gcc Fila.c -std=c99 -c -pthread

Processador.o: Processador.c Processador.h
	gcc Processador.c -std=c99 -c -pthread

Processo.o: Processo.c Processo.h
	gcc Processo.c -std=c99 -c -pthread

Memoria.o: Memoria.c Memoria.h
	gcc Memoria.c -std=c99 -c -pthread

clean:
	rm -f *.o 