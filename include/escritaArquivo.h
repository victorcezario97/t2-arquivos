#ifndef _ESCRITAARQUIVO_H_
#define _ESCRITAARQUIVO_H_

#include <defines.h>

void gravarArquivoComNumeroFixo(FILE *arquivo, REGISTRO *registro);
void gravarArquivoComTamanho(FILE *arquivo, REGISTRO *registro);
void gravarArquivoComSeparador(FILE *arquivo, REGISTRO *registro);

#endif