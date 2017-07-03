#ifndef _LEITURAARQUIVO_H_
#define _LEITURAARQUIVO_H_

#include <defines.h>

REGISTRO leRegistro(FILE *arquivo);
char *leCampoVariavel(FILE *arquivo, int *tamanho);
void leEntradaGeraSaida(char *entrada, REGISTRO *registro);

#endif