#ifndef _WRITEFILE_H_
#define _WRITEFILE_H_

#include <defines.h>

void leEntradaGeraSaida(char *entrada, char *saida, REGISTRO *registro, int modo);
void gravarArquivoComNumeroFixo(FILE *arquivo, REGISTRO *registro);
void gravarArquivoComTamanho(FILE *arquivo, REGISTRO *registro);
void gravarArquivoComSeparador(FILE *arquivo, REGISTRO *registro);

#endif