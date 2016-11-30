/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(130007293), Leandro Bergmann(140149007)

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo responsável por todas as operações sobre a memória bem como a definição da estrutura da memória.
*/
#include "Memoria.h"
#include "pthread.h"

//Lock para acesso exclusivo a memória.
pthread_mutex_t lock_memoria = PTHREAD_MUTEX_INITIALIZER;

//TODO -> Refatorar essa alocação.
//Função que aloca espaço na memória dependendo do tipo do processo recebido.
void alocaMemoria(processo *processo){
	pthread_mutex_lock(&lock_memoria);
	//Se for processo de tempo real
	if(processo->prioridadeDoProcesso == 0){
		//Se não está cheio a memória de tempo real.
		if(ultimoBlocoTR != 64){
			//preencho a quantidade de blocos na memoria com o pid
			for(int i = 0; i < processo->blocosEmMemoria; i++){
				//Se está livre o espaço coloca o pid
				if(memoria[processo->offset + i] == 0){
					memoria[processo->offset + i] = processo->pID;
				}else{
					printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo->pID);
					insereProcessoNaFila(processo);
					return;
				}
			}
			//Atualiza qual o ultimo bloco alocado;
			ultimoBlocoTR = processo->blocosEmMemoria + processo->offset;
			printf("Memória alocada para o processo de Tempo Real: %d\n",processo->pID);
			insereProcessoNaFila(processo);
		}else{
			printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo->pID);
			insereProcessoNaFila(processo);
		}
	}else{
		if(ultimoBlocoUS != 1024){
			//preencho a quantidade de blocos na memoria com o pid
			for(int i = 0; i < processo->blocosEmMemoria; i++){
				//Se está livre o espaço coloca o pid
				if(memoria[processo->offset + i] == 0){
					memoria[processo->offset + i] = processo->pID;
				}else{
					printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo->pID);
					insereProcessoNaFila(processo);
					return;
				}
			}
			//Atualiza qual o ultimo bloco alocado;
			ultimoBlocoUS = processo->blocosEmMemoria + processo->offset;
			printf("Memória alocada para o processo de Usuário: %d\n",processo->pID);
			insereProcessoNaFila(processo);
		}else{
			printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo->pID);
			insereProcessoNaFila(processo);
		}
	}
	pthread_mutex_unlock(&lock_memoria);
}

//Função que desaloca o espaço de memória assim que o processo termina a execução.
void desalocaMemoria(processo *processo){
	//preencho a quantidade de blocos na memoria com o pid
	for(int i = 0; i < processo->blocosEmMemoria; i++){
		//Se está livre o espaço coloca o pid
		if(memoria[processo->offset + i] == processo->pID){
			memoria[processo->offset + i] = 0;
		}
	}
	ultimoBlocoTR = 0;
	printf("Memória desalocada para o processo: %d\n\n",processo->pID);
}