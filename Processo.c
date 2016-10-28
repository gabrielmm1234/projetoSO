#include "Processo.h"

int totalProcessos;

void exibidorDispatcher(processo* processo){
	for(int j = 0; j < totalProcessos; j++){
		printf("dispatcher => \n");
		printf("Pid: %d\n",processo[j].pID);
		printf("Offset: \n");
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