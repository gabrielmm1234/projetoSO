/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(130007293), Leandro Bergmann(140149007)

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo responsável pelo escalonamento dos processos e simulação de execução no processador.
*/

#include "Processador.h"
#include "pthread.h"

int totalProcessos;
int execucaoProcessador = 0;
static int quantum = 1;
int tempo = 0;

//Lock para acesso exclusivo ao processador.
pthread_mutex_t lock_processador = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_escalonador = PTHREAD_MUTEX_INITIALIZER;
extern pthread_mutex_t processoMutex;

//TODO -> adicionar as prioridades para processo de usuário.
//Função responsável por escalonar os processos para execução no processador.
void escalonar(){
	int processosExecutados = 0;
	//Loop infinito de execução do processador.
	while(1){
		//Se ainda existem processos na fila de prontos de tempo real executa primeiro.	
		if(isEmpty(filaProcessoTempoReal)){
			processo *processo = frente(filaProcessoTempoReal)->processo;
			processo->vezesEmProcessador++;
			//Sinaliza thread para ser executada.
			pthread_mutex_lock(&processoMutex);
			if(processo->pronto){
				pthread_cond_signal(&varCondicaoProcesso[processo->pID]);
			} else{
				pthread_mutex_unlock(&processoMutex);
				continue;
			}
			pthread_mutex_unlock(&processoMutex);

			pthread_mutex_lock(&lock_escalonador);
			while(!execucaoProcessador)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);

			if(processo->instrucao == processo->tempoDeProcessador){
				processosExecutados++;
				exclui(filaProcessoTempoReal);
			}

			execucaoProcessador = 0;
		} else if(isEmpty(filaProcessoUsuario)){
			processo *processo = frente(filaProcessoUsuario)->processo;
			processo->vezesEmProcessador++;
			printf("Liberando o processo %d\n",processo->pID);
			//Sinaliza thread para ser executada.
			pthread_mutex_lock(&processoMutex);
			if(processo->pronto){
				pthread_cond_signal(&varCondicaoProcesso[processo->pID]);
			} else{
				pthread_mutex_unlock(&processoMutex);
				continue;
			}
			pthread_mutex_unlock(&processoMutex);

			pthread_mutex_lock(&lock_escalonador);
			while(!execucaoProcessador)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
			execucaoProcessador = 0;

			if(processo->instrucao == processo->tempoDeProcessador){
				processosExecutados++;
				exclui(filaProcessoUsuario);
			} else{
				if(processo->vezesEmProcessador > 10){
					processo->vezesEmProcessador = 0;
					insere(filaProcessoUsuario2, processo);
					exclui(filaProcessoUsuario);
				} else{
					insere(filaProcessoUsuario, processo);
					exclui(filaProcessoUsuario);
				}
			}
			
		} else if(isEmpty(filaProcessoUsuario2)){
			processo *processo = frente(filaProcessoUsuario2)->processo;
			processo->vezesEmProcessador++;
			printf("Liberando o processo %d\n",processo->pID);
			//Sinaliza thread para ser executada.
			pthread_mutex_lock(&processoMutex);
			if(processo->pronto){
				pthread_cond_signal(&varCondicaoProcesso[processo->pID]);
			} else{
				pthread_mutex_unlock(&processoMutex);
				continue;
			}
			pthread_mutex_unlock(&processoMutex);

			pthread_mutex_lock(&lock_escalonador);
			while(!execucaoProcessador)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
			execucaoProcessador = 0;

			if(processo->instrucao == processo->tempoDeProcessador){
				processosExecutados++;
				exclui(filaProcessoUsuario2);
			} else{
				if(processo->vezesEmProcessador > 10){
					processo->vezesEmProcessador = 0;
					insere(filaProcessoUsuario3, processo);
					exclui(filaProcessoUsuario2);
				} else{
					insere(filaProcessoUsuario2, processo);
					exclui(filaProcessoUsuario2);
				}
			}
		} else if(isEmpty(filaProcessoUsuario3)){
			processo *processo = frente(filaProcessoUsuario3)->processo;
			printf("Liberando o processo %d\n",processo->pID);
			//Sinaliza thread para ser executada.
			pthread_mutex_lock(&processoMutex);
			if(processo->pronto){
				pthread_cond_signal(&varCondicaoProcesso[processo->pID]);
			} else{
				pthread_mutex_unlock(&processoMutex);
				continue;
			}
			pthread_mutex_unlock(&processoMutex);

			pthread_mutex_lock(&lock_escalonador);
			while(!execucaoProcessador)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
			execucaoProcessador = 0;

			if(processo->instrucao == processo->tempoDeProcessador){
				processosExecutados++;
				exclui(filaProcessoUsuario3);
			} else{
				insere(filaProcessoUsuario3, processo);
				exclui(filaProcessoUsuario3);
			}
		}
		if(processosExecutados == totalProcessos){
			printf("Todos os processos já foram executados\n\n");
			break;
		}
	}
}

//TODO -> Refatorar para quando houver preempção para processos de usuário.
//Função que simula a execução de um processo no processador.
processo* executaProcesso(processo *processo){
	pthread_mutex_lock(&lock_processador);

	//Simulação da execução.
	if(processo->instrucao == 0 && processo->prioridadeDoProcesso == 0){
		printf("process %d =>\n",processo->pID);
		printf("p%d STARTED\n",processo->pID);
	} else if(processo->prioridadeDoProcesso != 0){
		printf("process %d =>\n",processo->pID);
		printf("p%d STARTED\n",processo->pID);
	}

	while(1){
		printf("p%d instruction %d\n",processo->pID,processo->instrucao + 1);
		processo->instrucao++;
		tempo++;
		if(tempo == quantum){
			tempo = 0;
			break;
		} else if(processo->instrucao == processo->tempoDeProcessador){
			break;
		}
	}

	if(processo->instrucao == processo->tempoDeProcessador){
		printf("p%d return SIGINT\n",processo->pID);
		desalocaMemoria(processo);
	}	

	execucaoProcessador = 1;

	pthread_cond_signal(&varCondicaoEscalonador);
	pthread_mutex_unlock(&lock_processador);

	return processo;
}