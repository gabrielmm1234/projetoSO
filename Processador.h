#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include "Fila.h"
#include "pthread.h"
#include "Processo.h"
#include "Memoria.h"

#define N 1000

pthread_cond_t varCondicaoProcesso[N];
pthread_cond_t varCondicaoEscalonador;
extern processo* processos;

void escalonar();
processo* executaProcesso(processo *processo);

#endif