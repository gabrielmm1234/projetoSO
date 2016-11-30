#include "Recurso.h"

pthread_mutex_t lock_scanner = PTHREAD_MUTEX_INITIALIZER;
int scannerProcessoId = 0;
pthread_mutex_t lock_impressora1 = PTHREAD_MUTEX_INITIALIZER;
int impressora1ProcessoId = 0;
pthread_mutex_t lock_impressora2 = PTHREAD_MUTEX_INITIALIZER;
int impressora2ProcessoId = 0;
pthread_mutex_t lock_modem = PTHREAD_MUTEX_INITIALIZER;
int modemProcessoId = 0;
pthread_mutex_t lock_sata1 = PTHREAD_MUTEX_INITIALIZER;
int sata1ProcessoId = 0;
pthread_mutex_t lock_sata2 = PTHREAD_MUTEX_INITIALIZER;
int sata2ProcessoId = 0;

void alocaRecursos(processo *processo){
	if(processo->numeroCodigoImpressora != 0){
		if(processo->numeroCodigoImpressora == 1){
			pthread_mutex_lock(&lock_impressora1);
			impressora1ProcessoId = processo->pID;
		} else {
			pthread_mutex_lock(&lock_impressora2);
			impressora2ProcessoId = processo->pID;
		}
	}

	if(processo->utilizacaoDoScanner != 0){
		pthread_mutex_lock(&lock_scanner);
		scannerProcessoId = processo->pID;
	}

	if(processo->utilizacaoDoModem != 0){
		pthread_mutex_lock(&lock_modem);
		modemProcessoId = processo->pID;
	}
	
	if(processo->numeroCodigoDriver != 0){
		if(processo->numeroCodigoDriver == 1){
			pthread_mutex_lock(&lock_sata1);
			sata1ProcessoId = processo->pID;
		} else {
			pthread_mutex_lock(&lock_sata2);
			sata2ProcessoId = processo->pID;
		}
	}
}

void liberaRecursos(processo *processo){
	if(processo->numeroCodigoImpressora != 0){
		if(processo->numeroCodigoImpressora == 1){
			if(impressora1ProcessoId != processo->pID){
				printf("ERRO AO TENTAR DESALOCAR UM RECURSO QUE NAO ERA DO PROCESSO\n");
			} else {
				impressora1ProcessoId = 0;
				pthread_mutex_unlock(&lock_impressora1);
			}
		} else {
			if(impressora2ProcessoId != processo->pID){
				printf("ERRO AO TENTAR DESALOCAR UM RECURSO QUE NAO ERA DO PROCESSO\n");
			} else {
				impressora2ProcessoId = 0;
				pthread_mutex_unlock(&lock_impressora2);
			}
		}
	}

	if(processo->utilizacaoDoScanner != 0){
		if(scannerProcessoId != processo->pID){
			printf("ERRO AO TENTAR DESALOCAR UM RECURSO QUE NAO ERA DO PROCESSO\n");
		} else {
			scannerProcessoId = 0;
			pthread_mutex_unlock(&lock_scanner);
		}
	}

	if(processo->utilizacaoDoModem != 0){
		if(modemProcessoId != processo->pID){
			printf("ERRO AO TENTAR DESALOCAR UM RECURSO QUE NAO ERA DO PROCESSO\n");
		} else {
			modemProcessoId = 0;
			pthread_mutex_unlock(&lock_modem);
		}
	}
	
	if(processo->numeroCodigoDriver != 0){
		if(processo->numeroCodigoDriver == 1){
			if(sata1ProcessoId != processo->pID){
				printf("ERRO AO TENTAR DESALOCAR UM RECURSO QUE NAO ERA DO PROCESSO\n");
			} else {
				sata1ProcessoId = 0;
				pthread_mutex_unlock(&lock_sata1);
			}
		} else {
			if(sata2ProcessoId != processo->pID){
				printf("ERRO AO TENTAR DESALOCAR UM RECURSO QUE NAO ERA DO PROCESSO\n");
			} else {
				sata2ProcessoId = 0;
				pthread_mutex_unlock(&lock_sata2);
			}
		}
	}
}