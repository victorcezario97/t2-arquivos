#ifndef _IMPRESSAO_H_
#define _IMPRESSAO_H_

#include <stdio.h>

void imprimeNomeCampo(int n);
void imprimeRegistro(REGISTRO registro, int quais);
void imprimeArquivoFixo(FILE *arquivo);
void imprimeArquivoDelimitador(FILE *arquivo);
void imprimeArquivoTamanho(FILE *arquivo);

#endif