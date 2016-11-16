#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"

int static tamanhoFilaTempoReal = 0;
int static topoFilaTempoReal = 0;
extern processo* filaProcessoTempoReal;

//TODO -> melhorar a fila de processos de usuário para as 3 filas de prioridades.
int static tamanhoFilaUsuario = 0;
int static topoFilaUsuario = 0;
extern processo* filaProcessoUsuario;

void insereProcessoNaFila(processo processo);
void dumpFilaTempoReal();
void dumpFilaUsuario();
processo retiraProcessoDaFilaDeTempoReal();
processo retiraProcessoDaFilaDeUsuario();
int existeProcessoTempoRealPendente();
int naoExisteProcessosPendentes();
int existeProcessoUsuarioPendente();

#endif