#include <stdlib.h>
#include <defines.h>
#include <utils.h>
#include <impressao.h>
#include <stdio.h>
#include <string.h>
#include <escritaArquivo.h>

enum{
	BEST_FIT,
	WORST_FIT,
	FIRST_FIT
};

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
	int n = 0;

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
	reg.tamanho = recebeCampo(&reg.dataHoraCadastro, TRUE, TRUE);
	printf("DATA E HORA DA ATUALIZACAO: ");
	reg.tamanho += recebeCampo(&reg.dataHoraAtualiza, TRUE, TRUE);
	printf("TICKET: ");
	scanf("%d", &reg.ticket);
	printf("\n");

	reg.tamanho += reg.tamanhoDominio + TAMANHO_FIXO + reg.tamanhoNome + reg.tamanhoUF + reg.tamanhoCidade;

	return reg;
}

REMOVIDOS *encontraPos(int n, LISTAREM *lista){
	REMOVIDOS *rem = lista->topo, *prev;

	while(rem && n > rem->tamanho){
		prev = rem;
		rem = rem->prox;
	}

	if(rem){
		prev->prox = rem->prox;
	}

	return rem;
}

void removeIndice(){

}

void insereIndice(){}

void escreve(REGISTRO reg, LISTAREM *lista, FILE *arquivo){
	REMOVIDOS *rem;
	int pos, n;
	char c = '*';

	rem = encontraPos(reg.tamanho, lista);
	if(rem){
		fseek(arquivo, rem->rrn, SEEK_SET);
		gravarArquivoComSeparador(arquivo, &reg);
		removeIndice(rem->rrn);
		if(rem->tamanho > reg.tamanho){
			pos = ftell(arquivo);
			fwrite(&c, 1, 1, arquivo);
			n = rem->tamanho - reg.tamanho;
			fwrite(&n, 4, 1, arquivo);
			insereIndice(n, pos);
		}
	}else{
		fseek(arquivo, 0, SEEK_END);
		gravarArquivoComSeparador(arquivo, &reg);
	}
}

void inserir(LISTAREM *lBest, LISTAREM *lWorst, LISTAREM *lFirst){
	REGISTRO reg;
	FILE *best = fopen("saidas/saidaBestFit.bin", "a");
	FILE *worst = fopen("saidas/saidaWorstFit.bin", "a");
	FILE *first = fopen("saidas/saidaFirstFit.bin", "a");	

	reg = recebeRegistro();

	escreve(reg, lBest, best);
	escreve(reg, lWorst, worst);
	escreve(reg, lFirst, first);
}