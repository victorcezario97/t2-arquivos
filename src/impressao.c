#include <stdlib.h>
#include <stdio.h>
#include <defines.h>

///--------------------------------------------------IMPRESSAO DOS REGISTROS---------------------------------------------///

//Funcao auxiliar que imprime o nome do campo de acordo com seu numero correspondente(0..7)
void imprimeNomeCampo(int n){
	char nome[8][27] = {"DOMINIO", "DOCUMENTO", "NOME SOCIAL", "UF", "CIDADE", "DATA E HORA DO CADASTRO", "DATA E HORA DA ATUALIZACAO", "TICKET"};

	printf("%s", nome[n]);
}

//Funcao que recebe um registro e imprime seus campos
void imprimeRegistro(REGISTRO registro, int quais){

	printf("**************************************************\n");

	if(quais == TODOS || quais == DOMINIO){
		imprimeNomeCampo(DOMINIO);
		printf(": %s\n", registro.dominio);
	}

	if(quais == TODOS || quais == DOCUMENTO){
		imprimeNomeCampo(DOCUMENTO);
		printf(": %s\n", registro.documento);
	}

	if(quais == TODOS || quais == NOME){
		imprimeNomeCampo(NOME);
		printf(": %s\n", registro.nome);
	}
	if(quais == TODOS || quais == UF){
		imprimeNomeCampo(UF);
		printf(": %s\n", registro.uf);
	}
	if(quais == TODOS || quais == CIDADE){
		imprimeNomeCampo(CIDADE);
		if(registro.cidade)
			printf(": %s\n", registro.cidade);
		else printf(":\n");
	}
	if(quais == TODOS || quais == DHCADASTRO){
		imprimeNomeCampo(DHCADASTRO);
		if(registro.dataHoraCadastro)
			printf(": %s\n", registro.dataHoraCadastro);
		else printf(":\n");
	}
	if(quais == TODOS || quais == DHATUALIZA){
		imprimeNomeCampo(DHATUALIZA);
		if(registro.dataHoraAtualiza)
			printf(": %s\n", registro.dataHoraAtualiza);
		else printf(":\n");
	}
	if(quais == TODOS || quais == TICKET){
		imprimeNomeCampo(TICKET);
		printf(": %d\n", registro.ticket);
	}
	printf("**************************************************\n");
}

//Funcao que imprime todos os registros de um arquivo com registros com campos de tamanho fixo.
void imprimeArquivoFixo(FILE *arquivo){
	char c;
	int ncampos = 0, numero, tamanho, nregistro = 1, pos;

	fgetc(stdin);	//Descartando o \n digitado da opcao

	//Enquanto nao chega no final do arquivo
	c = fgetc(arquivo);
	while(c != EOF){

		ungetc(c, arquivo);
		for(ncampos = 0; ncampos < 8; ncampos++){
			if(ncampos == 0) printf("\nRegistro %d\n*********************\n", nregistro++);
			imprimeNomeCampo(ncampos);
			printf(": ");

			//O oitavo campo eh um int
			if(ncampos == 7){
				fread(&numero, sizeof(int), 1, arquivo);
				printf("%d", numero);
			}else{
				pos = ftell(arquivo);
				fread(&tamanho, sizeof(int), 1, arquivo);

				if(tamanho != 0){
					fseek(arquivo, pos, SEEK_SET);

					//verifica se eh um dos campos que tem tamanho fixo
					if(fixo(ncampos)) tamanho = 20;
					//Se tem tamanho variavel, le o tamanho antes.
					else fread(&tamanho, sizeof(int), 1, arquivo);

					for(int i=0; i<tamanho; i++){
						c = fgetc(arquivo);
						printf("%c", c);
					}
				}
			}

			printf("\n");
			//Se ja leu os 8 campos, zera o contador e imprime o final do registro
			if(ncampos == 7){
				printf("********************\n");
				//ncampos = 0;

				printf("Digite ENTER para continuar ou ESC para sair\n");
				c = fgetc(stdin);
				if(c == 27) return;
			}
		}

		c = fgetc(arquivo);
	}

	printf("//-------------FIM DO ARQUIVO-------------//\n\n");

}

//Funcao que imprime todos os registros de um arquivo com registros separados por delimitadores.
//Delimitador = -1(int).
void imprimeArquivoDelimitador(FILE *arquivo){
	char c;
	int ncampos = 0, numero, tamanho, nregistro = 1;
    int i, pos, delimitador = -1;

	fgetc(stdin);	//Descartando o \n digitado da opcao
	fread(&numero, sizeof(int), 1, arquivo);

	c = fgetc(arquivo);

	while(c != EOF){
		//Caso o caracter nao seja EOF e o registro atual tenha terminado, devolve ele para o arquivo.
		if(delimitador == -1) ungetc(c, arquivo);
		//Se for o primeiro campo, imprime o inicio do registro
		if(ncampos == 0)
            printf("\nRegistro %d\n*********************\n", nregistro);

        imprimeNomeCampo(ncampos);
        printf(": ");
		//O oitavo campo eh um int
		if(ncampos == 3){
			fread(&numero, sizeof(int), 1, arquivo);
			printf("%d", numero);
		}else{
			pos = ftell(arquivo);
			fread(&tamanho, sizeof(int), 1, arquivo);
			printf("--------------------->%d\n", tamanho);

			if(tamanho != 0){
				fseek(arquivo, pos, SEEK_SET);
				//Lendo o tamanho do campo
				//Se for de tamanho fixo
				if(ncampos < 4)	tamanho = 20;
				//Caso contrario, le o tamanho
				else fread(&tamanho, sizeof(int), 1, arquivo);

				for(i = 0; i < tamanho; i++){
					c = fgetc(arquivo);
					printf("%c", c);
				}
			}
		}
		printf("\n");
		ncampos++;

		pos = ftell(arquivo);
		fread(&delimitador, sizeof(int), 1, arquivo);
		//Se encontrar o delimitador, zera o contador de campos e imprime o final do registro
		if(delimitador == -1){
			printf("********************\n");
			printf("Digite ENTER para continuar ou ESC para sair\n");

			ncampos = 0;
			nregistro++;
			c = fgetc(stdin);
			if(c == 27) return;
			c = fgetc(arquivo);

		}else fseek(arquivo, pos, SEEK_SET);

	}

	printf("//-------------FIM DO ARQUIVO-------------//\n\n");

}

//Funcao que imprime todos os registros de um arquivo com registros com indicadores de tamanho
void imprimeArquivoTamanho(FILE *arquivo){
	char c;
	int ncampos = 0, numero, tamanho, nregistro = 1;
    int i, pos, tamanhoreg, count = 0, indicadorTamanho = 4;

	fgetc(stdin);	//Descartando o \n digitado da opcao

	c = fgetc(arquivo);

	while(c != EOF){
		//Caso o caracter nao seja EOF, devolve ele para o arquivo.
		ungetc(c, arquivo);

		//Le o tamanho do registro
		fread(&tamanhoreg, sizeof(int), 1, arquivo);
		count = 0;
	    printf("\nRegistro %d\n*********************\n", nregistro);

		//Percorre o registro de acordo com seu tamanho
		while(count < tamanhoreg){
			imprimeNomeCampo(ncampos);
			printf(": ");
			//O oitavo campo eh um int
			if(ncampos == 7){
				count += 4 + indicadorTamanho;
				fread(&numero, sizeof(int), 1, arquivo);
				printf("%d", numero);
			}else{
				pos = ftell(arquivo);
				fread(&tamanho, sizeof(int), 1, arquivo);

				if(tamanho != 0){
					fseek(arquivo, pos, SEEK_SET);
					//Lendo o tamanho do campo
					//Se for de tamanho fixo
					if(fixo(ncampos)) tamanho = 20;
					//Caso contrario, le o tamanho
					else{
						fread(&tamanho, sizeof(int), 1, arquivo);
						count += indicadorTamanho;
					}

					for(i = 0; i < tamanho; i++){
						c = fgetc(arquivo);
						printf("%c", c);
					}
					count += tamanho;
				}else count += indicadorTamanho;
			}
			printf("\n");
			ncampos++;

		}


		//Se o total lido ja eh igual ao tamanho do registro, zera o contador e imprime o final do registro
		printf("********************\n");
		ncampos = 0;
		nregistro++;
		printf("Digite ENTER para continuar ou ESC para sair\n");
		c = fgetc(stdin);
		if(c == 27) return;

		//Le o proximo caracter para verificar se eh EOF
		c = fgetc(arquivo);
	}

	printf("//-------------FIM DO ARQUIVO-------------//\n\n");
}