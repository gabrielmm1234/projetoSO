/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(), Leandro Santos Bergmann(140149007)

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo responsável pelo escalonamento dos processos e simulação de execução no processador.
*/

#include "Processador.h"
#include "pthread.h"

int totalProcessos;
int execucaoProcessador = 0;

//Lock para acesso exclusivo ao processador.
pthread_mutex_t lock_processador = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_escalonador = PTHREAD_MUTEX_INITIALIZER;

//TODO -> adicionar as prioridades para processo de usuário.
//Função responsável por escalonar os processos para execução no processador.
void escalonar(){
	int processosExecutados = 0;
	//Loop infinito de execução do processador.
	while(1){
		//Se ainda existem processos na fila de prontos de tempo real executa primeiro.	
		if(existeProcessoTempoRealPendente()){
			processo processo = retiraProcessoDaFilaDeTempoReal();
			printf("Liberando o processo %d\n",processo.pID);
			//Sinaliza thread para ser executada.
			pthread_cond_signal(&varCondicaoProcesso[processo.pID]);

			pthread_mutex_lock(&lock_escalonador);
			while(!execucaoProcessador)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
			execucaoProcessador = 0;
			processosExecutados++;
			continue;
		}
		else if(existeProcessoUsuarioPendente()){
			processo processo = retiraProcessoDaFilaDeUsuario();
			printf("Liberando o processo %d\n",processo.pID);
			//Sinaliza thread para ser executada.
			pthread_cond_signal(&varCondicaoProcesso[processo.pID]);

			pthread_mutex_lock(&lock_escalonador);
			while(!execucaoProcessador)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
			execucaoProcessador = 0;
			processosExecutados++;
		}
		if(processosExecutados == totalProcessos){
			printf("Todos os processos já foram executados\n\n");
			break;
		}
	}
}

//TODO -> Refatorar para quando houver preempção para processos de usuário.
//Função que simula a execução de um processo no processador.
void executaProcesso(processo processo){
	pthread_mutex_lock(&lock_processador);

	//Simulação da execução.
	printf("process %d =>\n",processo.pID);
	printf("p%d STARTED\n",processo.pID);
	for(int i = 0; i < processo.tempoDeProcessador; i++){
		printf("p%d instruction %d\n",processo.pID,i + 1);
	}
	printf("p%d return SIGINT\n",processo.pID);

	execucaoProcessador = 1;
	desalocaMemoria(processo);

	pthread_cond_signal(&varCondicaoEscalonador);
	pthread_mutex_unlock(&lock_processador);
}