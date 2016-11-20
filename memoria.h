#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"
#include "Fila.h"

int totalProcessos;

//Flag para o ultimo bloco ocupado de processo Tempo Real
int static ultimoBlocoTR = 0;
//Flag para o ultimo bloco ocupado de processo de Usuário.
int static ultimoBlocoUS = 0;

//Abstração da memória com tamanho de 1024 blocos
//Os blocos ocupados pelo processo são marcados na memória com seu PID.
int* memoria;

void alocaMemoria(processo processo);
void desalocaMemoria(processo processo);
void dumpMem();

#endif