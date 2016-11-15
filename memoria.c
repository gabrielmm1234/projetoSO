/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(), Leandro Bergmann()

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo responsável por todas as operações sobre a memória bem como a definição da estrutura da memória.
*/
#include "memoria.h"
#include "pthread.h"
pthread_mutex_t lock_memoria = PTHREAD_MUTEX_INITIALIZER;

//TODO -> refatorar para receber somente um processo em vez de percorrer tudo.
//Função que percorre o array de processos e aloca espaço na memória dependendo do tipo do processo.
void alocaMemoria(processo processo){
	pthread_mutex_lock(&lock_memoria);
	//Se for processo de tempo real
	if(processo.prioridadeDoProcesso == 0){
		//Se não está cheio a memória de tempo real.
		if(ultimoBlocoTR != 64){
			//preencho a quantidade de blocos na memoria com o pid
			for(int i = 0; i < processo.blocosEmMemoria; i++){
				//Se está livre o espaço coloca o pid
				if(memoria[processo.offset + i] == 0){
					memoria[processo.offset + i] = processo.pID;
				}else{
					printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo.pID);
					insereProcessoNaFila(processo);
					return;
				}
			}
			//Atualiza qual o ultimo bloco alocado;
			ultimoBlocoTR = processo.blocosEmMemoria + processo.offset;
			printf("Memória alocada para o processo de Tempo Real: %d\n",processo.pID);
		}else{
			printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo.pID);
			insereProcessoNaFila(processo);
		}
	}else{
		if(ultimoBlocoUS != 1024){
			//preencho a quantidade de blocos na memoria com o pid
			for(int i = 0; i < processo.blocosEmMemoria; i++){
				//Se está livre o espaço coloca o pid
				if(memoria[processo.offset + i] == 0){
					memoria[processo.offset + i] = processo.pID;
				}else{
					printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo.pID);
					insereProcessoNaFila(processo);
					break;
				}
			}
			//Atualiza qual o ultimo bloco alocado;
			ultimoBlocoUS = processo.blocosEmMemoria + processo.offset;
			printf("Memória alocada para o processo de Usuário: %d\n",processo.pID);
		}else{
			printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo.pID);
			insereProcessoNaFila(processo);
		}
	}
	pthread_mutex_unlock(&lock_memoria);
}

void dumpMem(){
	for(int i = 0; i < 1024; i++){
		printf("%d ",memoria[i]);
	}
	printf("\n\n");
}