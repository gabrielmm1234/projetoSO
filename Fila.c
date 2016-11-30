/*
Universidade de Brasília
Sistemas Operacionais

Alunos: Gabriel Mesquita(130009121), Carlos Joel Tavares(130007293), Leandro Bergmann(140149007)

Trabalho Final de implementação da matéria 	de sistemas operacionais

Módulo responsável por todas as operações sobre a fila de processos.
*/

#include "Fila.h"

Fila* initFila(){
	Fila* fila = (Fila*) malloc(sizeof(Fila));
	fila->principal = NULL;
	fila->final = NULL;
	fila->tamanho = 0;

	return fila;
}

void insere(Fila *fila, processo *processo){
    Nodo *atual = (Nodo*) malloc(sizeof(Nodo));
    atual->processo = processo;
    atual->proximo = NULL;
  
    if(fila->principal == NULL){
        fila->principal = fila->final = atual;
    } else{
        fila->final->proximo = atual;
        fila->final = atual;
    }
    fila->tamanho++;
}

void exclui(Fila *fila){
    Nodo *auxiliar;

    auxiliar = fila->principal->proximo;
    free(fila->principal);
    fila->principal = auxiliar;
    fila->tamanho--;
}

Nodo* frente(Fila *fila){
    return fila->principal;
}

int isEmpty(Fila *fila){
	return fila->tamanho;
}

void insereProcessoNaFila(processo *processo){
	if(processo->prioridadeDoProcesso == 0){
		insere(filaProcessoTempoReal, processo);
	} else if(processo->prioridadeDoProcesso == 1){
		insere(filaProcessoUsuario, processo);
	} else if(processo->prioridadeDoProcesso == 2){
		insere(filaProcessoUsuario2, processo);
	} else if(processo->prioridadeDoProcesso == 3){
		insere(filaProcessoUsuario3, processo);
	}
}