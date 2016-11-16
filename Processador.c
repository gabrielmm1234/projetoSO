#include "Processador.h"

#include "pthread.h"

//Lock para acesso exclusivo ao processador.
pthread_mutex_t lock_processador = PTHREAD_MUTEX_INITIALIZER;

//TODO -> adicionar o tempo de chegada de cada processo.
//TODO -> adicionar as prioridades para processo de usuário.
void execute(){
	pthread_mutex_lock(&lock_processador);
	//Loop infinito de execução do processador.
	while(1){
		//Se ainda existem processos na fila de prontos de tempo real executa primeiro.	
		if(existeProcessoTempoRealPendente()){
			processo processo = retiraProcessoDaFilaDeTempoReal();
			printf("Executando o processo de tempo real: %d por %d ciclos\n", processo.pID, processo.tempoDeProcessador);
			continue;
		}
		else if(existeProcessoUsuarioPendente()){
			processo processo = retiraProcessoDaFilaDeUsuario();
			printf("Executando o processo de usuario: %d por %d ciclos\n", processo.pID, processo.tempoDeProcessador);
		}

		if(naoExisteProcessosPendentes()){
			printf("Todos os processos já foram executados\n\n");
			break;
		}
	}
	pthread_mutex_unlock(&lock_processador);
}