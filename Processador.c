#include "Processador.h"
#include "pthread.h"

int totalProcessos;
int teste = 0;

//Lock para acesso exclusivo ao processador.
pthread_mutex_t lock_escalonador = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_processador = PTHREAD_MUTEX_INITIALIZER;

//TODO -> adicionar o tempo de chegada de cada processo.
//TODO -> adicionar as prioridades para processo de usuário.
void escalonador(){
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
			while(!teste)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
			teste = 0;
			processosExecutados++;
			continue;
		}
		else if(existeProcessoUsuarioPendente()){
			processo processo = retiraProcessoDaFilaDeUsuario();
			printf("Liberando o processo %d\n",processo.pID);
			//Sinaliza thread para ser executada.
			pthread_cond_signal(&varCondicaoProcesso[processo.pID]);

			pthread_mutex_lock(&lock_escalonador);
			while(!teste)
				//Espera sinal para voltar a escalonar
				pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
			teste = 0;
			processosExecutados++;
		}
		if(processosExecutados == totalProcessos){
			printf("Todos os processos já foram executados\n\n");
			break;
		}
	}
}

void executaProcesso(processo processo){
	pthread_mutex_lock(&lock_processador);
	printf("Executando o processo: %d por %d ciclos\n\n", processo.pID, processo.tempoDeProcessador);
	teste = 1;
	pthread_cond_signal(&varCondicaoEscalonador);
	pthread_mutex_unlock(&lock_processador);
}