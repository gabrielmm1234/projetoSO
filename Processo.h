#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>

extern int totalProcessos;

typedef struct processo
{
	int pID;
	int offset;
	int tempoDeInicializacao;
	int prioridadeDoProcesso;
	int tempoDeProcessador;
	int blocosEmMemoria;
	int numeroCodigoImpressora;
	int utilizacaoDoScanner;
	int utilizacaoDoModem;
	int numeroCodigoDriver;
}processo; 

void exibidorDispatcher(processo* processo);

#endif