/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(), Leandro Bergmann()

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo responsável por todas as operações sobre a fila de processos.
*/

#include "Fila.h"

void insereProcessoNaFila(processo processo){
	if(processo.prioridadeDoProcesso == 0){
		filaProcessoTempoReal[tamanhoFilaTempoReal] = processo;
		tamanhoFilaTempoReal++;
	}
	else{
		filaProcessoUsuario[tamanhoFilaUsuario] = processo;
		tamanhoFilaUsuario++;
	}
}

processo retiraProcessoDaFilaDeTempoReal(){
	processo processo = filaProcessoTempoReal[topoFilaTempoReal];
	topoFilaTempoReal++;
	return processo;
}

void dumpFilaTempoReal(){
	for(int i = 0; i < tamanhoFilaTempoReal; i++){
		printf("Processo Tempo Real %d\n",filaProcessoTempoReal[i].pID);
	}
}

void dumpFilaUsuario(){
	for(int i = 0; i < tamanhoFilaUsuario; i++){
		printf("Processo Usuário %d\n",filaProcessoUsuario[i].pID);
	}
}