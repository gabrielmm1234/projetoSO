#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include "Fila.h"
#include "pthread.h"
#include "Processo.h"

#define N 1000

pthread_cond_t varCondicaoProcesso[N];
pthread_cond_t varCondicaoEscalonador;

void escalonar();
void executaProcesso(processo processo);

#endif