#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"

int static tamanhoFilaTempoReal = 0;
int static topoFilaTempoReal = 0;
extern processo* filaProcessoTempoReal;

int static tamanhoFilaUsuario = 0;
extern processo* filaProcessoUsuario;

void insereProcessoNaFila(processo processo);
void dumpFilaTempoReal();
void dumpFilaUsuario();
processo retiraProcessoDaFilaDeTempoReal();

#endif