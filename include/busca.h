#ifndef _BUSCA_H_
#define _BUSCA_H_

#include <utils.h>

boolean comparaRegistro(REGISTRO registro, CAMPOBUSCA campo);
REGISTRO *buscaPorCampoNFC(CAMPOBUSCA campo, FILE *arquivo, int *n);
REGISTRO buscaRegistroNFC(int regNumber, FILE *arquivo);
REGISTRO *buscaPorCampoTamanho(CAMPOBUSCA campo, FILE *arquivo, int *n);
REGISTRO buscaRegistroTamanho(int regNumber, FILE *arquivo);
REGISTRO *buscaPorCampoDelimitador(CAMPOBUSCA campo, FILE *arquivo, int *n);
REGISTRO buscaRegistroDelimitador(int regNumber, FILE *arquivo);

#endif