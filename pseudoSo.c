/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(130007293), Leandro Santos Bergmann(140149007)

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo main que le um arquivo chamado processes.txt, tal arquivo contém os processos a serem executados,
e inicia o dispatcher e execução do so.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pthread.h"
#include "Processo.h"
#include "Leitor.h"
#include "Memoria.h"
#include "Fila.h"
#include "Processador.h"
#include "Recurso.h"

int totalProcessos;

Fila *filaProcessoTempoReal;
Fila *filaProcessoUsuario;
Fila *filaProcessoUsuario2;
Fila *filaProcessoUsuario3;
processo* processos;

int compare(const void *s1, const void *s2)
{
  processo *p1 = (processo *)s1;
  processo *p2 = (processo *)s2;
  return p1->tempoDeInicializacao >= p2->tempoDeInicializacao;
}

//Lock para a variável de condição dos processos.
pthread_mutex_t processoMutex = PTHREAD_MUTEX_INITIALIZER;

//Thread que representa a execução do processador
void* threadProcessador(void* arg){
	//Processador começa a executar
  	escalonar();

  	//Termina a thread.
    pthread_exit(0);
}

//Thread que representa um processo lido do arquivo processes.txt
void* threadProcesso(void* arg){
	processo* processo = arg; 

	//TODO -> Refatorar -> Simula o tempo de inicialização do processo.
	sleep(processo->tempoDeInicializacao);

    printf("Thread com id: %d chegou no instante %d\n", processo->pID, processo->tempoDeInicializacao);

    //Tenta alocar memória.
    alocaMemoria(processo);

  	//Executa o processo.
  	alocaRecursos(processo);
  	while(processo->instrucao != processo->tempoDeProcessador){
	    //Variável de condição para travar os vários processos. Ficam esperando liberação do escalonador.	
	    pthread_mutex_lock(&processoMutex);
	  	pthread_cond_wait(&varCondicaoProcesso[processo->pID], &processoMutex);
	  	pthread_mutex_unlock(&processoMutex);
	  	
	  	processo = executaProcesso(processo);
  	}
  	liberaRecursos(processo);

    //Termina a thread.
    pthread_exit(0);    
}


int main(int argc, char *argv[]){
	pthread_t threads[N];
	pthread_t processador;
	int i;

	//Aloca espaço para as estruturas de dados iniciais.
	filaProcessoTempoReal = initFila();
	filaProcessoUsuario = initFila();
	filaProcessoUsuario2 = initFila();
	filaProcessoUsuario3 = initFila();
	memoria = calloc(sizeof(int),1024);

	//Inicia as variáveis de condição.
	for(i = 0; i < N; i++)
		pthread_cond_init (&varCondicaoProcesso[i], NULL);
	pthread_cond_init (&varCondicaoEscalonador, NULL);

	//Abre o arquivo e lê preenchendo o vetor de processos. Depois exibe as características de cada processo.
	FILE* file = fopen("processes.txt", "r");
	processos = leProcessos(file);
	qsort(processos, totalProcessos, sizeof(processo), compare);
	exibidorDispatcher(processos);

	//Cria uma thread para cada processo alocar sua memória e começar a executar.
	for (i = 0; i < totalProcessos ; i++) {
        pthread_create(&threads[i], NULL, threadProcesso, &processos[i]);
   	}

   	//Cria a thread de execução do processador.
   	pthread_create(&processador, NULL, threadProcessador, NULL);

   	//Espera o termino de todas as threads.
   	for (int i = 0; i < totalProcessos ; i++) {
      pthread_join(threads[i],NULL);
  	}

  	pthread_join(processador,NULL);

	free(processos);
}