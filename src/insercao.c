#include <stdlib.h>
#include <defines.h>
#include <utils.h>

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
			if(n == TAMANHO_FIXO) break;

			printf("Tamanho invalido para o campo\n");
			if(n != 0) free((*campo));
			n = 0;
			continue;
		}else if(nulo == TRUE && fixo == FALSE){
			break;
		}else if(nulo == TRUE && fixo == TRUE){
			if(n == 0 || n == TAMANHO_FIXO) break;

			printf("Tamanho invalido para o campo\n");
			free((*campo));
			n = 0;
			continue;
		}else{
			if(n != 0) break;

			printf("Tamanho invalido para o campo\n");
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
	printf("\nDOCUMENTO: ");
	recebeCampo(&reg.documento, TRUE, FALSE);
	printf("\nNOME: ");
	reg.tamanhoNome = recebeCampo(&reg.nome, FALSE, FALSE);
	printf("\nUF: ");
	reg.tamanhoUF = recebeCampo(&reg.uf, FALSE, FALSE);;
	printf("\nCIDADE: ");
	reg.tamanhoCidade = recebeCampo(&reg.cidade, FALSE, TRUE);;
	printf("\nDATA E HORA DO CADASTRO: ");
	recebeCampo(&reg.dataHoraCadastro, TRUE, TRUE);
	printf("\nDATA E HORA DA ATUALIZACAO: ");
	recebeCampo(&reg.dataHoraAtualizacao, TRUE, TRUE);
	printf("\nTICKET: ");
	scanf("%d", &reg.ticket);
	printf("\n");

	return reg;
}

int inserir(){
	int pos;
	REGISTRO reg;

	reg = recebeRegistro();


	return pos;
}