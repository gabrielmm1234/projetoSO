#define _GNU_SOURCE
#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Processo.h"

int static pid = 0;

processo* leProcessos(FILE*);

#endif