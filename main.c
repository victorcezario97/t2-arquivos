#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <writeFile.h>
#include <readFile.h>
#include <free.h>
#include <print.h>
#include <search.h>
#include <utils.h>
#include <menu.h>

int main()
{
	REGISTRO *registro;///registro que será usado para armazenar os dados durante a gravação dos dados e escrita do arquivoSaida.
	REGISTRO *regsBusca;//Ponteiro de registro usado na busca de registros atraves de um campo
	CAMPOBUSCA campo;//Struct usada na busca a partir de um campo
	int opcao = 0, regNumber = 0, subop = 0, i;

    while(1)
    {
    	printMainMenu();

        opcao = readOp();


        if(opcao == 4){
        	break;
        }

        //Menus das operacoes a serem realizadas sobre o tipo de arquivo selecionado
        subop = 0;
        while(subop != 6){
	   		printf("Digite a operacao desejada:\n");
	    	printf("1 - Gerar arquivo de saida\n");
	    	printf("2 - Imprimir arquivo de saida completo\n");
	    	printf("3 - Busca de registro por campo\n");
	    	printf("4 - Buscar registro por RRN\n");
	    	printf("5 - Busca de um campo especifico\n");
	    	printf("6 - Voltar\n");

	    	scanf("%d", &subop);

	        if(opcao == 1)///Arquivo com indicador de tamanho de registro
	        {
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
		        		ImprimeArquivoTamanho(fp);
		        		break;

		        		case 3:
		        		//Imprime as opcoes de campos
		        		printf("\nEscolha o campo que sera usado na pesquisa:\n");
		        		for(i = 0; i < 8; i++){
		        			printf("%d - ", i);
		        			imprimeNomeCampo(i);
		        			printf("\n");
		        		}
		        		printf("Campo: ");
		        		scanf("%d", &campo.numCampo);

		        		while(campo.numCampo > 7 || campo.numCampo < 0){
		        			printf("Campo selecionado invalido\n");
		        			printf("Campo: ");
		        			scanf("%d", &campo.numCampo);
		        		}

		        		fgetc(stdin); //Descartando o \n
		        		imprimeNomeCampo(campo.numCampo);
		        		printf(": ");
		        		//Le o valor do campo
		        		if(campo.numCampo == 7) scanf("%d", &campo.ticket);
		        		else campo.string = leString();

		        		//Realiza a busca e imprime os resultados
		        		regsBusca = buscaPorCampoTamanho(campo, fp, &regNumber);
		        		printf("\nRegistros encontrados: %d\n", regNumber);
		        		for(i=0; i<regNumber; i++){
		        			printf("Registro %d\n", i+1);
		        			imprimeRegistro(regsBusca[i], TODOS);
		        			libera_campos(&(regsBusca[i]));
		        			printf("Digite ENTER para continuar\n");
		        			fgetc(stdin);
		        		}

		        		//Libera a memoria utilizada
		        		if(regNumber != 0)free(regsBusca);
		        		if(campo.numCampo != 7) free(campo.string);
		        		break;


		        		case 4:
		        		registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		        		printf("\nInsira o numero do registro:\n");
		    			scanf("%d", &regNumber);
		    			fgetc(stdin);	//Descartando o \n
		    			(*registro) = buscaRegistroTamanho(regNumber, fp);

		    			if(registro->ticket == -1) printf("\nRegistro nao encontrado\n");
		    			else{
		    				printf("Registro %d\n", regNumber);
		    				imprimeRegistro(*registro, TODOS);
		    			}
		    			libera_campos(registro);
		    			free(registro);
		    			printf("\nDigite ENTER para voltar\n");
		    			fgetc(stdin);

		    			break;

		    			case 5:
		    			registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		    			//Le o RRN no registro
		    			printf("Digite o RRN do registro: ");
		    			scanf("%d", &regNumber);

		    			//Imprime os campos
		    			printf("\nEscolha o campo que deseja retornar:\n");
		        		for(i = 0; i < 8; i++){
		        			printf("%d - ", i);
		        			imprimeNomeCampo(i);
		        			printf("\n");
		        		}
		        		//Le o campo a ser retornado
		        		printf("Campo: ");
		        		scanf("%d", &campo.numCampo);

		        		while(campo.numCampo > 7 || campo.numCampo < 0){
		        			printf("Campo selecionado invalido\n");
		        			printf("Campo: ");
		        			scanf("%d", &campo.numCampo);
		        		}
		        		//Busca o registro com o RRN digitado
		        		(*registro) = buscaRegistroTamanho(regNumber, fp);

		        		//Imprime o campo do registro ou erro se o registro nao foi encontrado
		    			if(registro->ticket == -1) printf("\nRegistro nao encontrado\n");
		    			else{
		    				printf("\nRegistro %d\n", regNumber);
		    				imprimeRegistro(*registro, campo.numCampo);
		    			}

		    			//Libera a memoria utilizada
		    			libera_campos(registro);
		    			free(registro);
		    			break;

						case 6:
							
						break;

		    			//Imprime o erro caso a opcao seja invalida
		    			default:
		    			printf("Opcao Invalida\n");
		    			break;
		        	}
		        	fclose(fp);

	        }

	        if(opcao == 2)///Arquivo com delimitadores entre registros
	        {
	        		FILE *fp = fopen("saidas/saidaDelimitador.bin", "ab+");
		            switch(subop){
		        		case 1:
		        		registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		        		//Gera o arquivo de saida
		        		leEntradaGeraSaida(ENTRADA, "saidas/saidaDelimitador.bin", registro, 2);///função que lê o arquivo de entrada e gera o arquivo saida dependendo da decisão do usuário.
		        		//Libera a memoria usada
		        		libera_campos(registro);
		        		free(registro);
		        		registro = NULL;
		        		break;

		        		case 2:
		        		ImprimeArquivoDelimitador(fp);
		        		break;

		        		case 3:
		        		//Imprime as opcoes de campos
		        		printf("\nEscolha o campo que sera usado na pesquisa:\n");
		        		for(i = 0; i < 8; i++){
		        			printf("%d - ", i);
		        			imprimeNomeCampo(i);
		        			printf("\n");
		        		}
		        		printf("Campo: ");
		        		scanf("%d", &campo.numCampo);

		        		while(campo.numCampo > 7 || campo.numCampo < 0){
		        			printf("Campo selecionado invalido\n");
		        			printf("Campo: ");
		        			scanf("%d", &campo.numCampo);
		        		}

		        		fgetc(stdin); //Descartando o \n
		        		imprimeNomeCampo(campo.numCampo);
		        		printf(": ");
		        		//Le o valor do campo
		        		if(campo.numCampo == 7) scanf("%d", &campo.ticket);
		        		else campo.string = leString();
		        		//Realiza a busca e imprime os resultados
		        		regsBusca = buscaPorCampoDelimitador(campo, fp, &regNumber);

		        		printf("\nRegistros encontrados: %d\n", regNumber);
		        		for(i=0; i<regNumber; i++){
		        			printf("Registro %d\n", i+1);
		        			imprimeRegistro(regsBusca[i], TODOS);
		        			libera_campos(&(regsBusca[i]));
		        			printf("Digite ENTER para continuar\n");
		        			fgetc(stdin);
		        		}

		        		//Libera a memoria usada
		        		if(regNumber != 0)free(regsBusca);
		        		if(campo.numCampo != 7) free(campo.string);
		        		break;

		        		case 4:
		        		registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		        		//Le o RRN do registro
		        		printf("\nInsira o numero do registro:\n");
		    			scanf("%d", &regNumber);
		    			fgetc(stdin);	//Descartando o \n
		    			(*registro) = buscaRegistroDelimitador(regNumber, fp);

		    			//Imprime o registro ou o erro caso ele nao esteja no arquivo
		    			if(registro->ticket == -1) printf("\nRegistro nao encontrado\n");
		    			else{
		    				printf("Registro %d\n", regNumber);
		    				imprimeRegistro(*registro, TODOS);
		    			}

		    			//Libera a memoria usada
		    			libera_campos(registro);
		    			free(registro);

		    			printf("\nDigite ENTER para continuar\n");
		    			fgetc(stdin);

		    			break;

		    			case 5:
		    			registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		    			//Le o RRN do registro
		    			printf("Digite o RRN do registro: ");
		    			scanf("%d", &regNumber);

		    			//Imprime os campos
		    			printf("\nEscolha o campo que deseja retornar:\n");
		        		for(i = 0; i < 8; i++){
		        			printf("%d - ", i);
		        			imprimeNomeCampo(i);
		        			printf("\n");
		        		}
		        		printf("Campo: ");
		        		//Le o campo a ser impresso
		        		scanf("%d", &campo.numCampo);

		        		//Verificacao se a escolha eh valida
		        		while(campo.numCampo > 7 || campo.numCampo < 0){
		        			printf("Campo selecionado invalido\n");
		        			printf("Campo: ");
		        			scanf("%d", &campo.numCampo);
		        		}

		        		//Busca o registro
		        		(*registro) = buscaRegistroDelimitador(regNumber, fp);

		        		//Imprime o campo desejado ou o erro caso o registro nao esteja no arquivo
		    			if(registro->ticket == -1) printf("\nRegistro nao encontrado\n");
		    			else{
		    				printf("\nRegistro %d\n", regNumber);
		    				imprimeRegistro(*registro, campo.numCampo);
		    			}

		    			//Libera a memoria
		    			libera_campos(registro);
		    			free(registro);
		    			break;

						case 6:
							break;

		    			//Caso a opcao seja invalida, imprime o erro
		    			default:
		    			printf("Opcao invalida\n");
		    			break;
		        	}
		        	fclose(fp);


	        }

	        if(opcao == 3)///Arquivo com numero fixo de campos
	        {
	        		FILE *fp = fopen("saidas/saidaNumeroFixo.bin", "ab+");
		        	switch(subop){
		        		case 1:
		        		registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		        		leEntradaGeraSaida(ENTRADA, "saidas/saidaNumeroFixo.bin", registro, 3);///função que lê o arquivo de entrada e gera o arquivo saida dependendo da decisão do usuário.
		        		libera_campos(registro);
		        		free(registro);
		        		registro = NULL;
		        		break;

		        		case 2:
		        		imprimeArquivoFixo(fp);
		        		break;

		        		case 3:
		        		//Imprime as opcoes de campos
		        		printf("\nEscolha o campo que sera usado na pesquisa:\n");
		        		for(i = 0; i < 8; i++){
		        			printf("%d - ", i);
		        			imprimeNomeCampo(i);
		        			printf("\n");
		        		}
		        		printf("Campo: ");
		        		scanf("%d", &campo.numCampo);

		        		while(campo.numCampo > 7 || campo.numCampo < 0){
		        			printf("Campo selecionado invalido\n");
		        			printf("Campo: ");
		        			scanf("%d", &campo.numCampo);
		        		}

		        		fgetc(stdin); //Descartando o \n
		        		imprimeNomeCampo(campo.numCampo);
		        		printf(": ");
		        		//Le o valor do campo
		        		if(campo.numCampo == 7) scanf("%d", &campo.ticket);
		        		else campo.string = leString();

		        		//Realiza a busca e imprime os resultados
		        		regsBusca = buscaPorCampoNFC(campo, fp, &regNumber);
		        		printf("\nRegistros encontrados: %d\n", regNumber);
		        		for(i=0; i<regNumber; i++){
		        			printf("Registro %d\n", i+1);
		        			imprimeRegistro(regsBusca[i], TODOS);
		        			libera_campos(&(regsBusca[i]));
		        			printf("Digite ENTER para continuar\n");
		        			fgetc(stdin);
		        		}

		        		//Libera a memoria
		        		if(regNumber != 0)free(regsBusca);
		        		if(campo.numCampo != 7) free(campo.string);
		        		break;

		        		case 4:
		        		registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		        		//Le o RRN do registro
		        		printf("\nInsira o RRN do registro:\n");
		    			scanf("%d", &regNumber);
		    			fgetc(stdin);	//Descartando o \n
		    			(*registro) = buscaRegistroNFC(regNumber, fp);

		    			//Imprime o registro ou o erro caso ele nao seja encontrado
		    			if(registro->ticket == -1) printf("\nRegistro nao encontrado\n");
		    			else{
		    				printf("Registro %d\n", regNumber);
		    				imprimeRegistro(*registro, TODOS);
		    			}

		    			//Libera a memoria
		    			libera_campos(registro);
		    			free(registro);

		    			printf("\nDigite ENTER para continuar\n");
		    			fgetc(stdin);

		    			break;

		    			case 5:
		    			registro = (REGISTRO*)malloc(sizeof(REGISTRO));
		    			//Le o RRN do registro
		    			printf("Digite o RRN do registro: ");
		    			scanf("%d", &regNumber);

		    			//Imprime os campos
		    			printf("\nEscolha o campo que deseja retornar:\n");
		        		for(i = 0; i < 8; i++){
		        			printf("%d - ", i);
		        			imprimeNomeCampo(i);
		        			printf("\n");
		        		}
		        		printf("Campo: ");
		        		//Le o campo a ser impresso
		        		scanf("%d", &campo.numCampo);

		        		//Verifica se a opcao eh valida
		        		while(campo.numCampo > 7 || campo.numCampo < 0){
		        			printf("Campo selecionado invalido\n");
		        			printf("Campo: ");
		        			scanf("%d", &campo.numCampo);
		        		}

		        		//Realiza a busca
		        		(*registro) = buscaRegistroNFC(regNumber, fp);

		        		//Imprime o campo desejado ou o erro caso o registro nao esteja no arquivo
		    			if(registro->ticket == -1) printf("\nRegistro nao encontrado\n");
		    			else{
		    				printf("\nRegistro %d\n", regNumber);
		    				imprimeRegistro(*registro, campo.numCampo);
		    			}

		    			//Libera a memoria
		    			libera_campos(registro);
		    			free(registro);

		    			break;

		    			case 6:
		    			break;

		    			//Caso a opcao seja invalida, imprime o erro
		    			default:
		    			printf("Opcao invalida\n");
		    			break;
		        	}

		        	fclose(fp);
	        }

   		}

        opcao = 0;
    }

	return 0;
}
