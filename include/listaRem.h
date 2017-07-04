#ifndef _LISTAREM_H_
#define _LISTAREM_H_

int encontraPos(int n, FILE *arquivo);
void ordenaBest(FILE *arquivo, int rrn, int tam, int pos);
void ordenaWorst(FILE *arquivo, int rrn, int tam, int pos);
void ordenaFirst(FILE *arquivo, int rrn, int pos);
void ordenaListaRem(FILE *arquivo, int tipo, int rrn, int tam);
void imprimeListaRem(FILE *arquivo);

#endif