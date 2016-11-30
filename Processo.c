/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(130007293), Leandro Bergmann()

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo responsável por todas as operações do processo bem como a definição da estrutura de um processo.
*/

#include "Processo.h"

int totalProcessos;

/*
Função que recebe o array de processos montado a partir do arquivo e mostra na tela informações de cada processo.
*/
void exibidorDispatcher(processo* processo){
	for(int j = 0; j < totalProcessos; j++){
		printf("dispatcher => \n");
		printf("Pid: %d\n",processo[j].pID);
		printf("Offset: %d\n",calculaOffset(processo,j));
		printf("Blocks: %d\n",processo[j].blocosEmMemoria);
		printf("Priority: %d\n",processo[j].prioridadeDoProcesso);
		printf("Time: %d\n",processo[j].tempoDeProcessador);
		printf("Printers: %d\n",processo[j].numeroCodigoImpressora);
		printf("Scanners: %d\n",processo[j].utilizacaoDoScanner);
		printf("Modems: %d\n",processo[j].utilizacaoDoModem);
		printf("Drivers: %d\n",processo[j].numeroCodigoDriver);
		printf("\n\n");
	}
}

/*
Função auxiliar utilizada para calcular e armazenar o ofsset na memória de cada processo.
*/
int calculaOffset(processo* processo, int j){
	if(j == 0 || ajustaOffset(processo,j)){
		processo[j].offset = 0;
		return 0;
	}
	else{
		processo[j].offset = processo[j - 1].offset + processo[j - 1].blocosEmMemoria + 1;
		return processo[j - 1].offset + processo[j - 1].blocosEmMemoria + 1;
	}
}

int ajustaOffset(processo* processo, int j){
	if(processo[j].prioridadeDoProcesso == 0)
		return processo[j].blocosEmMemoria > 64 - (processo[j - 1].offset + processo[j - 1].blocosEmMemoria);
	else
		return processo[j].blocosEmMemoria > 1024 - (processo[j - 1].offset + processo[j - 1].blocosEmMemoria);
}	