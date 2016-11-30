#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdio.h>
#include <stdlib.h>

extern int totalProcessos;

//Estrutura de um processo.
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
	int instrucao;
} processo; 

void exibidorDispatcher(processo* processo);
int calculaOffset(processo* processo, int j);
int ajustaOffset(processo* processo, int j);

#endif