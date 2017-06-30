#ifndef _IMPRESSAO_H_
#define _IMPRESSAO_H_

void imprimeNomeCampo(int n);
void imprimeRegistro(REGISTRO registro, int quais);
void imprimeArquivoFixo(FILE *arquivo);
void ImprimeArquivoDelimitador(FILE *arquivo);
void ImprimeArquivoTamanho(FILE *arquivo);

#endif