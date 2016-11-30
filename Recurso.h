#ifndef RECURSO_H
#define RECURSO_H

#include <stdio.h>
#include <stdlib.h>
#include "Processo.h"
#include "pthread.h"

void alocaRecursos(processo *processo);
void liberaRecursos(processo *processo);

#endif