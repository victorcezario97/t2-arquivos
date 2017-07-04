#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <escritaArquivo.h>
#include <leituraArquivo.h>
#include <free.h>
#include <impressao.h>
#include <busca.h>
#include <utils.h>
#include <menu.h>
#include <insercao.h>
#include <indices.h>
#include<remocao.h>

int main()
{
	LISTAREM *remBest = (LISTAREM*)malloc(sizeof(LISTAREM));
	remBest->n = 0;
	LISTAREM *remWorst = (LISTAREM*)malloc(sizeof(LISTAREM));
	remWorst->n = 0;
	LISTAREM *remFirst = (LISTAREM*)malloc(sizeof(LISTAREM));
	remFirst->n = 0;
	REGISTRO *registro;///registro que será usado para armazenar os dados durante a gravação dos dados e escrita do arquivoSaida.
	//REGISTRO *regsBusca;//Ponteiro de registro usado na busca de registros atraves de um campo
	//CAMPOBUSCA campo;//Struct usada na busca a partir de um campo
	int opcao = 0;// regNumber = 0;
	//char c; FILE *fp;
	int buscaremocao = 0;
    while(1){
    	imprimeMenuPrincipal();

        opcao = leOp();


	    if(opcao == 6){
	    	break;
	    }

   		//FILE *fp = fopen("./saidas/saidaTamanho.bin", "ab+");
    	switch(opcao){
    		case 1:
    		registro = (REGISTRO*)malloc(sizeof(REGISTRO));
    		//Gera o arquivo de saida
    		leEntradaGeraSaida(ENTRADA, registro);///função que lê o arquivo de entrada e gera o arquivo saida dependendo da decisão do usuário.
    		//Libera a memoria usada
    		/*libera_campos(registro);
    		free(registro);
    		registro = NULL;*/
    		break;

    		case 2:	
			printf("Digite o indice a ser removido: \n\n")
			scanf("%d",buscaremocao);
			buscaremocao(buscaremocao);
    		//Remover registros
    		break;

    		case 3:
    		inserir();
    		break;

    		case 4:
    		//Estatisticas indices
    		imprimirIndices();
			break;

			case 5:
			//Estatisticas registros removidos
			break;

			//Imprime o erro caso a opcao seja invalida
			default:
			printf("Opcao Invalida\n");
			break;
    	}

	}

	return 0;
}
