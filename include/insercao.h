#ifndef _INSERCAO_H_
#define _INSERCAO_H_

#include <defines.h>

int recebeCampo(char **campo, boolean fixo, boolean nulo);
REGISTRO recebeRegistro();
void escreve(REGISTRO reg, FILE *arquivo, int tipo);
int inserir();

#endif