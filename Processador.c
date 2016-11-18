#include "Processador.h"
#include "pthread.h"

int totalProcessos;

//Lock para acesso exclusivo ao processador.
pthread_mutex_t lock_escalonador = PTHREAD_MUTEX_INITIALIZER;

//TODO -> adicionar o tempo de chegada de cada processo.
//TODO -> adicionar as prioridades para processo de usuário.
void escalonador(){
	int processosExecutados = 0;
	//Loop infinito de execução do processador.
	while(1){
		pthread_mutex_lock(&lock_escalonador);
		//Se ainda existem processos na fila de prontos de tempo real executa primeiro.	
		if(existeProcessoTempoRealPendente()){
			processo processo = retiraProcessoDaFilaDeTempoReal();
			printf("Liberando o processo %d\n",processo.pID);
			//Sinaliza thread para ser executada.
			pthread_cond_signal(&varCondicaoProcesso[processo.pID]);

			//Espera sinal para voltar a escalonar
			pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			printf("Escalonador liberado\n\n");
			processosExecutados++;
			pthread_mutex_unlock(&lock_escalonador);
			continue;
		}
		else if(existeProcessoUsuarioPendente()){
			processo processo = retiraProcessoDaFilaDeUsuario();
			printf("Liberando o processo %d\n",processo.pID);
			//Sinaliza thread para ser executada.
			pthread_cond_signal(&varCondicaoProcesso[processo.pID]);

			//Espera sinal para voltar a escalonar
			pthread_cond_wait(&varCondicaoEscalonador, &lock_escalonador);
			pthread_mutex_unlock(&lock_escalonador);
			printf("Escalonador liberado\n\n");
		}
		processosExecutados++;
		printf("processosExecutados: %d\n",processosExecutados);
		printf("totalProcessos: %d\n",totalProcessos);
		if(processosExecutados == totalProcessos){
			printf("Todos os processos já foram executados\n\n");
			break;
		}
	}
}

void executaProcesso(processo processo){
	printf("Executando o processo: %d por %d ciclos\n", processo.pID, processo.tempoDeProcessador);
	pthread_cond_signal(&varCondicaoEscalonador);
}