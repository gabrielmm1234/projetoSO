/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(), Leandro Bergmann()

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo main que le um arquivo chamado processes.txt, tal arquivo contém os processos a serem executados,
e inicia o dispatcher e execução do so.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"
#include "Leitor.h"
#include "memoria.h"


int main(int argc, char *argv[]){
	processo* processo;

	memoria = calloc(sizeof(int),1024);

	FILE* file = fopen("processes.txt", "r");
	processo = leProcessos(file);
	exibidorDispatcher(processo);

	alocaMemoria(processo);
	dumpMem();
}