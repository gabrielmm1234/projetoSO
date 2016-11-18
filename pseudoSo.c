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
#include "Processador.h"

int totalProcessos;

processo* filaProcessoTempoReal;
processo* filaProcessoUsuario;

pthread_mutex_t processoMutex = PTHREAD_MUTEX_INITIALIZER;

//Thread que representa a execução do processador
void* threadProcessador(void* arg){
	//Processador começa a executar
  	//TODO -> adicionar o tempo de chegada de cada processo.
  	escalonador();

  	//Termina a thread.
    pthread_exit(0);
}

//Thread que representa um processo lido do arquivo processes.txt
void* threadProcesso(void* arg){
	processo* processo = arg; 
    printf("Criou um pthread com id = %d \n",processo->pID);
    //Tenta alocar memória.
    alocaMemoria(*processo);
    pthread_mutex_lock(&processoMutex);
    //Variável de condição para travar os vários processos.	
  	pthread_cond_wait(&varCondicaoProcesso[processo->pID], &processoMutex);
  	pthread_mutex_unlock(&processoMutex);
  	printf("Processo %d\n passou\n",processo->pID);
  	//Executa o processo.
  	executaProcesso(*processo);
    //Termina a thread.
    pthread_exit(0);    
}


int main(int argc, char *argv[]){
	pthread_t threads[N];
	pthread_t processador;

	processo* processo;

	//Aloca espaço para as estruturas de dados iniciais.
	filaProcessoTempoReal = malloc(N * sizeof(processo));
	filaProcessoUsuario = malloc(N * sizeof(processo));
	memoria = calloc(sizeof(int),1024);

	for(int i = 0; i < N; i++)
		pthread_cond_init (&varCondicaoProcesso[i], NULL);
	pthread_cond_init (&varCondicaoEscalonador, NULL);

	//Abre o arquivo e lê preenchendo o vetor de processos. Depois exibe as características de cada processo.
	FILE* file = fopen("processes.txt", "r");
	processo = leProcessos(file);
	exibidorDispatcher(processo);

	//Cria uma thread para cada processo alocar sua memória e começar a executar.
	for (int i = 0; i < totalProcessos ; i++) {
        pthread_create(&threads[i], NULL, threadProcesso, &processo[i]);
   	}

   	pthread_create(&processador, NULL, threadProcessador, NULL);

   	//Espera o termino de todas as threads.
   	for (int i = 0; i < totalProcessos ; i++) {
      pthread_join(threads[i],NULL);
  	}

  	pthread_join(processador,NULL);

  	//Dumps do estado da memória e das filas de espera -> DEBUG.
	dumpMem();
	dumpFilaTempoReal();
	dumpFilaUsuario();
}