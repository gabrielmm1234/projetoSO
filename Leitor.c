/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(130007293), Leandro Bergmann(140149007)

Trabalho Final de implementação da matéria de sistemas operacionais

Módulo de leitura do arquivo processes.txt. É responsável por ler o arquivo e montar uma estrutura
de processo definida no módulo de processo.
*/

#include "Leitor.h"
#include "Processo.h"

int totalProcessos;

/*
Função leProcessos que le o processes.txt e monta uma estrutura de processo para o dispatcher.
return: Array de processos.
*/
processo* leProcessos(FILE* file){
	char* pch;
	char* line = NULL;
	size_t len = 0;
	int tokens[500];
	int i = 0, j = 0;
	processo* processo = malloc(1000 * sizeof(processo));

	while((getline(&line,&len,file)) != -1){
		pch = strtok(line,", ");
		pid++;
		processo[j].pID = pid;
		while(pch != NULL){
			if(i == 0){
				processo[j].tempoDeInicializacao = atoi(pch);
			}else if(i == 1){
				processo[j].prioridadeDoProcesso = atoi(pch);
			}else if(i == 2){
				processo[j].tempoDeProcessador = atoi(pch);
			}else if(i == 3){
				processo[j].blocosEmMemoria = atoi(pch);
			}else if(i == 4){
				processo[j].numeroCodigoImpressora = atoi(pch);
			}else if(i == 5){
				processo[j].utilizacaoDoScanner = atoi(pch);
			}else if(i == 6){
				processo[j].utilizacaoDoModem = atoi(pch);
			}else if(i == 7){
				processo[j].numeroCodigoDriver = atoi(pch);
			}
			i++;
			pch = strtok(NULL,", ");
		}
		i = 0;
		processo[j].instrucao = 0;
		j++;
		totalProcessos++;
		if(totalProcessos >= 1000){
			printf("OS processos atingiram seu limite maximo. Caso existam mais processos eles seram ignorados\n");
			return processo;
		}
	}

	fclose(file);
	free(line);

	return processo;
}