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
#include "pthread.h"
#include "Processo.h"
#include "Leitor.h"
#include "memoria.h"
#include "Fila.h"

#define N 1000

int totalProcessos;

processo* filaProcessoTempoReal;
processo* filaProcessoUsuario;

//Thread que representa um processo lido do arquivo processes.txt
void* threadProcesso(void* arg){
	processo* processo = arg; 
    printf("Criou um pthread com id = %d \n",processo->pID);
    //Tenta alocar memória.
    alocaMemoria(*processo);
    //TODO -> execute();
    pthread_exit(0);    
}


int main(int argc, char *argv[]){
	pthread_t threads[N];

	processo* processo;

	//Aloca espaço para as estruturas de dados iniciais.
	filaProcessoTempoReal = malloc(1000 * sizeof(processo));
	filaProcessoUsuario = malloc(1000 * sizeof(processo));
	memoria = calloc(sizeof(int),1024);

	//Abre o arquivo e lê preenchendo o vetor de processos. Depois exibe as características de cada processo.
	FILE* file = fopen("processes.txt", "r");
	processo = leProcessos(file);
	exibidorDispatcher(processo);

	//Cria uma thread para cada processo alocar sua memória e começar a executar.
	for (int i = 0; i < totalProcessos ; i++) {
        pthread_create(&threads[i], NULL, threadProcesso, &processo[i]);
   	}

   	//Espera o termino de todas as threads.
   	for (int i = 0; i < totalProcessos ; i++) {
      pthread_join(threads[i],NULL);
  	}

  	//Dumps do estado da memória e das filas de espera -> DEBUG.
	dumpMem();
	dumpFilaTempoReal();
	dumpFilaUsuario();
}