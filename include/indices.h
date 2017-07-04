#ifndef _INDICES_H_
#define _INDICES_H_

#include <defines.h>

void criaIndice (FILE *arquivo, int qtd);
INDICE *lerIndice(FILE *fp, int *n);
void imprimirIndices();
void removeIndice();
void insereIndice(int ticket, int bo, INDICE *indices, int n, int tipo);
int buscaIndice(int x, int n, INDICE *v);

#endif