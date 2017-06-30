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

int main()
{
	REGISTRO *registro;///registro que será usado para armazenar os dados durante a gravação dos dados e escrita do arquivoSaida.
	REGISTRO *regsBusca;//Ponteiro de registro usado na busca de registros atraves de um campo
	CAMPOBUSCA campo;//Struct usada na busca a partir de um campo
	int opcao = 0, regNumber = 0, subop = 0, i;

    while(TRUE){
    	imprimeMenuPrincipal();

        opcao = leOp();


	    if(opcao == 6){
	    	break;
	    }

   		FILE *fp = fopen("./saidas/saidaTamanho.bin", "ab+");
    	switch(subop){
    		case 1:
    		registro = (REGISTRO*)malloc(sizeof(REGISTRO));
    		//Gera o arquivo de saida
    		leEntradaGeraSaida(ENTRADA, "./saidas/saidaTamanho.bin", registro, 1);///função que lê o arquivo de entrada e gera o arquivo saida dependendo da decisão do usuário.
    		//Libera a memoria usada
    		libera_campos(registro);
    		free(registro);
    		registro = NULL;
    		break;

    		case 2:
    		//Remover registros
    		break;

    		case 3:
    		//Inserir registro
    		break;

    		case 4:
    		//Estatisticas indices
			break;

			case 5:
			//Estatisticas registros removidos
			break;

			//Imprime o erro caso a opcao seja invalida
			default:
			printf("Opcao Invalida\n");
			break;
    	}
    	fclose(fp);

	}

	return 0;
}
