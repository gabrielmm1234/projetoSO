/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(), Leandro Santos Bergmann(140149007)

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

processo retiraProcessoDaFilaDeUsuario(){
	processo processo = filaProcessoUsuario[topoFilaUsuario];
	topoFilaUsuario++;
	return processo;
}

int existeProcessoTempoRealPendente(){
	if(tamanhoFilaTempoReal != topoFilaTempoReal)
		return 1;
	else
		return 0;
}

int existeProcessoUsuarioPendente(){
	if(tamanhoFilaUsuario != topoFilaUsuario)
		return 1;
	else
		return 0;
}

int naoExisteProcessosPendentes(){
	if(tamanhoFilaTempoReal == topoFilaTempoReal && tamanhoFilaUsuario == topoFilaUsuario)
		return 1;
	else
		return 0;
}

void dumpFilaTempoReal(){
	printf("--------- Fila tempo real ---------\n");
	for(int i = 0; i < tamanhoFilaTempoReal; i++){
		printf("Processo Tempo Real %d\n",filaProcessoTempoReal[i].pID);
	}
	printf("--------- Fila tempo real ---------\n\n");
}

void dumpFilaUsuario(){
	printf("--------- Fila Usuário ---------\n");
	for(int i = 0; i < tamanhoFilaUsuario; i++){
		printf("Processo Usuário %d\n",filaProcessoUsuario[i].pID);
	}
	printf("--------- Fila Usuário ---------\n\n");
}