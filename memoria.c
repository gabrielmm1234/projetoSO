/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(), Leandro Bergmann()

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo responsável por todas as operações sobre a memória bem como a definição da estrutura da memória.
*/
#include "memoria.h"

//TODO -> refatorar para receber somente um processo em vez de percorrer tudo.
//Função que percorre o array de processos e aloca espaço na memória dependendo do tipo do processo.
void alocaMemoria(processo* processo){

	int flagAlocado = 0;

	for(int j = 0; j < totalProcessos; j++){
		//Se for processo de tempo real
		if(processo[j].prioridadeDoProcesso == 0){
			//Se não está cheio a memória de tempo real.
			if(ultimoBlocoTR != 64){
				//preencho a quantidade de blocos na memoria com o pid
				for(int i = 0; i < processo[j].blocosEmMemoria; i++){
					//Se está livre o espaço coloca o pid
					if(memoria[processo[j].offset + i] == 0){
						memoria[processo[j].offset + i] = processo[j].pID;
					}else{
						printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo[j].pID);
						insereProcessoNaFila(processo[j]);
						flagAlocado = 1;
						break;
					}
				}
				//Se não foi alocado passa para o próximo processo -> TODO colocar na fila de processos.
				if(flagAlocado == 1){
					flagAlocado = 0;
					continue;
				}
				//Atualiza qual o ultimo bloco alocado;
				ultimoBlocoTR = processo[j].blocosEmMemoria + processo[j].offset;
				printf("Memória alocada para o processo de Tempo Real: %d\n",processo[j].pID);
			}else{
				printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo[j].pID);
				insereProcessoNaFila(processo[j]);
			}
		}else{
			if(ultimoBlocoUS != 1024){
				//preencho a quantidade de blocos na memoria com o pid
				for(int i = 0; i < processo[j].blocosEmMemoria; i++){
					//Se está livre o espaço coloca o pid
					if(memoria[processo[j].offset + i] == 0){
						memoria[processo[j].offset + i] = processo[j].pID;
					}else{
						printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo[j].pID);
						insereProcessoNaFila(processo[j]);
						flagAlocado = 1;
						break;
					}
				}
				//Se não foi alocado passa para o próximo processo -> TODO colocar na fila de processos.
				if(flagAlocado == 1){
					flagAlocado = 0;
					continue;
				}
				//Atualiza qual o ultimo bloco alocado;
				ultimoBlocoUS = processo[j].blocosEmMemoria + processo[j].offset;
				printf("Memória alocada para o processo de Usuário: %d\n",processo[j].pID);
			}else{
				printf("Memória ocupada, não foi possível alocar memória para o processo: %d\n",processo[j].pID);
				insereProcessoNaFila(processo[j]);
			}
		}
	}
}

void dumpMem(){
	for(int i = 0; i < 1024; i++){
		printf("%d ",memoria[i]);
	}
	printf("\n");
}