#ifndef _READFILE_H_
#define _READFILE_H_

#include <defines.h>

REGISTRO leRegistro(FILE *arquivo);
char *leCampoVariavel(FILE *arquivo, int *tamanho);
void leEntradaGeraSaida(char *entrada, char *saida, REGISTRO *registro, int modo);

#endif