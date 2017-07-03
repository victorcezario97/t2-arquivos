#ifndef _INDICES_H_
#define _INDICES_H_

#include <defines.h>

void criaIndice (FILE *arquivo, int qtd);
INDICE *lerIndice(FILE *fp, int *n);
void imprimirIndices();

#endif