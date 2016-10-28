#include "Leitor.h"
#include "Processo.h"

int totalProcessos;

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
		j++;
		totalProcessos++;
	}

	fclose(file);
	free(line);

	return processo;
}
