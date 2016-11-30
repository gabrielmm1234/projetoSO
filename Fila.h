#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"

typedef struct Nodo {
    processo *processo;
    struct Nodo *proximo;
} Nodo;

typedef struct Fila {
	Nodo* principal;
	Nodo* final;
	int tamanho;
} Fila;

extern Fila *filaProcessoTempoReal;
extern Fila *filaProcessoUsuario;
extern Fila *filaProcessoUsuario2;
extern Fila *filaProcessoUsuario3;

void insereProcessoNaFila(processo *processo);
void insere(Fila *fila, processo *processo);
void exclui(Fila *fila);
Nodo* frente(Fila *fila);
Fila* initFila();
int isEmpty(Fila *fila);

#endif