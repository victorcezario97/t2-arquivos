#include <stdlib.h>
#include <defines.h>
#include <utils.h>
#include <impressao.h>
#include <stdio.h>
#include <string.h>
#include <escritaArquivo.h>
#include <indices.h>
#include <listaRem.h>

int recebeCampo(char **campo, boolean fixo, boolean nulo){
	int n = 0;
	while(n == 0){
		(*campo) = leString(&n);

		if(nulo == FALSE && fixo == TRUE){
			if(n == TAMANHO_FIXO-1) break;

			printf("Tamanho invalido para o campo. Digite novamente:\n");
			if(n != 0) free((*campo));
			n = 0;
			continue;
		}else if(nulo == TRUE && fixo == FALSE){
			break;
		}else if(nulo == TRUE && fixo == TRUE){
			if(n == 0 || n == TAMANHO_FIXO-1) break;

			printf("Tamanho invalido para o campo. Digite novamente:\n");
			free((*campo));
			n = 0;
			continue;
		}else{
			if(n != 0) break;

			printf("Tamanho invalido para o campo. Digite novamente:\n");
			n = 0;
		}
	}

	return n;
}

REGISTRO recebeRegistro(){
	REGISTRO reg;
	int n = 0, aux;;

	printf("Insira os dados sobre o registro.\nAo fim de cada dado digite ENTER, e caso o dado seja nulo, digite apenas ENTER.\n");
	printf("DOMINIO: ");
	reg.tamanhoDominio = recebeCampo(&reg.dominio, FALSE, FALSE);
	printf("DOCUMENTO: ");
	while(n != TAMANHO_FIXO-1){
		scanf("%19s", reg.documento);
		n = strlen(reg.documento);
		getchar();
		if(n != TAMANHO_FIXO-1) printf("Tamanho invalido para o campo. Digite novamente:");
	}
	printf("NOME: ");
	reg.tamanhoNome = recebeCampo(&reg.nome, FALSE, FALSE);
	printf("UF: ");
	reg.tamanhoUF = recebeCampo(&reg.uf, FALSE, FALSE);
	printf("CIDADE: ");
	reg.tamanhoCidade = recebeCampo(&reg.cidade, FALSE, TRUE);
	printf("DATA E HORA DO CADASTRO: ");
	aux = recebeCampo(&reg.dataHoraCadastro, TRUE, TRUE);
	if(aux == 0) reg.tamanho = 4;
	else reg.tamanho = TAMANHO_FIXO;
	printf("DATA E HORA DA ATUALIZACAO: ");
	aux = recebeCampo(&reg.dataHoraAtualiza, TRUE, TRUE);
	if(aux == 0) reg.tamanho += 4;
	else reg.tamanho += TAMANHO_FIXO;
	printf("TICKET: ");
	scanf("%d", &reg.ticket);
	printf("\n");

	reg.tamanho += 4 + reg.tamanhoDominio + TAMANHO_FIXO + 4 + reg.tamanhoNome + 4 + reg.tamanhoUF + 4 + reg.tamanhoCidade + 4;

	return reg;
}

boolean escreve(REGISTRO reg, FILE *arquivo, INDICE *indices, int n, int tipo){
	int pos, bo, end, tam;
	boolean reordena;

	bo = buscaIndice(reg.ticket, n, indices);
	if(bo != -1) return FALSE;

	pos = encontraPos(reg.tamanho, arquivo, TRUE, &end, &reordena);
	//printf("pos: %d\n", pos);

	if(pos != -1){
		fseek(arquivo, pos, SEEK_SET);
	}else{
		fseek(arquivo, 0, SEEK_END);
		pos = ftell(arquivo);
	}

	gravarArquivoComSeparador(arquivo, &reg);
	insereIndice(reg.ticket, pos, indices, n, tipo);
	if(reordena){
		fseek(arquivo, end+1, SEEK_SET);
		fread(&tam, sizeof(int), 1, arquivo);
		printf("tam %d\n", tam);

		ordenaListaRem(arquivo, tipo, end, tam);
	}

	fseek(arquivo, 0, SEEK_SET);
	fread(&pos, sizeof(int), 1, arquivo);
	//printf("pos 2: %d\n", pos);

	return TRUE;
}

void inserir(){
	REGISTRO reg;
	boolean b;
	FILE *best = fopen("saidas/saidaBestFit.bin", "r+");
	FILE *worst = fopen("saidas/saidaWorstFit.bin", "r+");
	FILE *first = fopen("saidas/saidaFirstFit.bin", "r+");
	FILE *bestIndice = fopen("indices/indiceBestFit.bin", "r+");
	FILE *worstIndice = fopen("indices/indiceWorstFit.bin", "r+");
	FILE *firstIndice = fopen("indices/indiceFirstFit.bin", "r+");
	int nBest, nWorst, nFirst;
	INDICE *indicesBest = lerIndice(bestIndice, &nBest);
	INDICE *indicesWorst = lerIndice(worstIndice, &nWorst);
	INDICE *indicesFirst = lerIndice(firstIndice, &nFirst);

	fclose(bestIndice);
	fclose(worstIndice);
	fclose(firstIndice);
	getchar();
	reg = recebeRegistro();
	imprimeRegistro(reg, TODOS);

	b = escreve(reg, best, indicesBest, nBest, BEST_FIT);
	fclose(best);
	if(!b) printf("Ja existe um registro com o ticket inserido no arquivo.\nA insercao falhou.\n");
	else{
		escreve(reg, worst, indicesWorst, nWorst, WORST_FIT);
		escreve(reg, first, indicesFirst, nFirst, FIRST_FIT);
		printf("Registro inserido com sucesso\n");
	}

	
	fclose(worst);
	fclose(first);
}