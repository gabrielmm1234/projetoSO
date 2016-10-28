#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"
#include "Leitor.h"


int main(int argc, char *argv[]){
	processo* processo;

	FILE* file = fopen("processes.txt", "r");
	processo = leProcessos(file);
	exibidorDispatcher(processo);
}