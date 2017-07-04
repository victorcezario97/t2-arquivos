#ifndef _LISTAREM_H_
#define _LISTAREM_H_

#include <utils.h>

void removeLista(int bo, FILE *arquivo);
int encontraPos(int n, FILE *arquivo, boolean op, int *end, boolean *reordena);
void ordenaBest(FILE *arquivo, int rrn, int tam, int pos);
void ordenaWorst(FILE *arquivo, int rrn, int tam, int pos);
void ordenaFirst(FILE *arquivo, int rrn, int pos);
void ordenaListaRem(FILE *arquivo, int tipo, int rrn, int tam);
void imprimeListaRem(FILE *arquivo);

#endif