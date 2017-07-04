#include <stdlib.h>
#include <stdio.h>
#include <defines.h>
#include <indices.h>
#include <listaRem.h>
#include <utils.h>
#include <leituraArquivo.h>
#include <string.h>

boolean apaga(int ticket, FILE *arquivo, FILE *arquivoIndice, int tipo){
	int n, bo, pos, tamanho;
	char c = '*';

	//Le os indices do arquivo de indices
	INDICE *indices = lerIndice(arquivoIndice, &n);

	//Chama a funcao que remove o indice do arquivo de indices e retorna o byte offset do registro 
	bo = removeIndice(ticket, indices, n, tipo);
	//Caso o registro nao esteja no arquivo
	if(bo == -1){
		fclose(arquivo);
		return FALSE;
	}

	//Le o registro para saber seu tamanho
	fseek(arquivo, bo, SEEK_SET);
	tamanho = tamanhoRegistro(arquivo);

	fseek(arquivo, bo, SEEK_SET);
	//Escreve o byte que indica que o registro foi removido
	fwrite(&c, sizeof(char), 1, arquivo);
	//Escreve o tamanho do espaco "vazio"
	fwrite(&tamanho, sizeof(int), 1, arquivo);


	rewind(arquivo);
	//Le o topo da lista de registros removidos
	fread(&pos, sizeof(int), 1, arquivo);

	//Caso a lista esteja vazia, aponta para o registro removido
	if(pos == -1){
		rewind(arquivo);
		fwrite(&bo, sizeof(int), 1, arquivo);

		fseek(arquivo, bo+5, SEEK_SET);
		fwrite(&pos, sizeof(int), 1, arquivo);
	//Caso nao esteja vazia, chama a funcao correspondente para ordenar a lista com o novo registro
	}else{
		if(tipo == BEST_FIT)
			ordenaBest(arquivo, bo, tamanho, pos);
		if(tipo == WORST_FIT)
			ordenaWorst(arquivo, bo, tamanho, pos);
		if(tipo == FIRST_FIT)
			ordenaFirst(arquivo, bo, pos);
	}

	fclose(arquivo);
	fclose(arquivoIndice);

	return TRUE;
}

void remover(){
	int ticket, b;
	FILE *best = fopen("saidas/saidaBestFit.bin", "r+");
	FILE *worst = fopen("saidas/saidaWorstFit.bin", "r+");
	FILE *first = fopen("saidas/saidaFirstFit.bin", "r+");
	FILE *bestIndice = fopen("indices/indiceBestFit.bin", "r+");
	FILE *worstIndice = fopen("indices/indiceWorstFit.bin", "r+");
	FILE *firstIndice = fopen("indices/indiceFirstFit.bin", "r+");

	printf("Insira o ticket do registro a ser removido: ");
	scanf("%d", &ticket);
	b = apaga(ticket, best, bestIndice, BEST_FIT);
	if(!b){
		printf("Registro nao encontrado.\nA remocao falhou.\n");
	}else{
		apaga(ticket, worst, worstIndice, WORST_FIT);
		apaga(ticket, first, firstIndice, FIRST_FIT);
		printf("Remocao executada com sucesso.\n");
	}
}