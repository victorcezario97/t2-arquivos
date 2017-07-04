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
#include <listaRem.h>
#include <remocao.h>

int main()
{
	FILE *arquivo; 
	REGISTRO *registro;///registro que será usado para armazenar os dados durante a gravação dos dados e escrita do arquivoSaida.
	//REGISTRO *regsBusca;//Ponteiro de registro usado na busca de registros atraves de um campo
	//CAMPOBUSCA campo;//Struct usada na busca a partir de um campo
	int opcao = 0;// regNumber = 0;
	int a;
	//char c; FILE *fp;
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
    		//Remover registros
			remover();
    		break;

    		case 3:
    		arquivo = fopen("./indices/indiceBestFit.bin", "r");
    		fread(&a, sizeof(int), 1, arquivo);
    		printf("%d\n", a);
			fclose(arquivo);
    		inserir();

    		break;

    		case 4:
    		//Estatisticas indices
    		imprimirIndices();
    		arquivo = fopen("./saidas/saidaBestFit.bin", "r");
    		imprimeArquivoDelimitador(arquivo);
			fclose(arquivo);
			break;

			case 5:
			//Estatisticas registros removidos
			arquivo = fopen("./saidas/saidaBestFit.bin", "r");
			imprimeListaRem(arquivo);
			fclose(arquivo);

			arquivo = fopen("./saidas/saidaWorstFit.bin", "r");
			imprimeListaRem(arquivo);
			fclose(arquivo);

			arquivo = fopen("./saidas/saidaFirstFit.bin", "r");
			imprimeListaRem(arquivo);
			fclose(arquivo);
			break;

			//Imprime o erro caso a opcao seja invalida
			default:
			printf("Opcao Invalida\n");
			break;
    	}

	}

	return 0;
}
