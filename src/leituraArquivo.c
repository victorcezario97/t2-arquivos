#include <stdlib.h>
#include <defines.h>
#include <stdio.h>
#include <string.h>
#include <escritaArquivo.h>
#include <free.h>
#include <indices.h>

//Funcao que le um registro de um arquivo passado
REGISTRO leRegistro(FILE *arquivo){
	REGISTRO registro;
	int tamanho, pos;

	//----------------------------CAMPOS FIXOS-------------------------//
	fread(registro.documento, sizeof(char), TAMANHO_FIXO, arquivo);

	///6 campo: dataHoraCadastro
    ///Faz a verificação se o campo não é null.
    pos = ftell(arquivo);
    fread(&tamanho, sizeof(int), 1, arquivo);
	if (tamanho != 0){
		fseek(arquivo, pos, SEEK_SET);
		registro.dataHoraCadastro = (char*)malloc(sizeof(char)*TAMANHO_FIXO);
		fread(registro.dataHoraCadastro, sizeof(char), TAMANHO_FIXO, arquivo);
	}else registro.dataHoraCadastro = NULL;

	///7 campo: dataHoraAtualiza
    ///Faz a verificação se o campo não é null.
    pos = ftell(arquivo);
	fread(&tamanho, sizeof(int), 1, arquivo);
	if (tamanho != 0){
		fseek(arquivo, pos, SEEK_SET);
		registro.dataHoraAtualiza = (char*)malloc(sizeof(char)*TAMANHO_FIXO);
		fread(registro.dataHoraAtualiza, sizeof(char), TAMANHO_FIXO, arquivo);
	}
	else registro.dataHoraAtualiza = NULL;

	///8 campo: ticket
	fread(&registro.ticket, sizeof(int), 1, arquivo);

	//--------------------------------------------------------------//

	//-----------------------------CAMPOS VARIAVEIS--------------------------//

	fread(&(registro.tamanhoDominio), sizeof(int), 1, arquivo);//tamanho do 1 campo
	registro.dominio = (char*)malloc(sizeof(char)*registro.tamanhoDominio);
	fread(registro.dominio, sizeof(char), registro.tamanhoDominio, arquivo);

	fread(&registro.tamanhoNome, sizeof(int), 1, arquivo);///tamanho do 3 campo
	registro.nome = (char*)malloc(sizeof(char)*registro.tamanhoNome);
	fread(registro.nome, sizeof(char), registro.tamanhoNome, arquivo);///3 campo: nome

	fread(&registro.tamanhoUF, sizeof(int), 1, arquivo);///tamanho do 4 campo
	registro.uf = (char*)malloc(sizeof(char)*registro.tamanhoUF);
	fread(registro.uf, sizeof(char), registro.tamanhoUF, arquivo);///4 campo: UF

    ///5 campo: cidade
    ///Se o campo for nulo o tamanho retornado sera 0, portando serao alocados e lidos 0 bytes
	pos = ftell(arquivo);
    fread(&registro.tamanhoCidade, sizeof(int), 1, arquivo);
    if(registro.tamanhoCidade != 0){
	    registro.cidade = (char*)malloc(sizeof(char)*registro.tamanhoCidade);
		fread(registro.cidade, sizeof(char), registro.tamanhoCidade, arquivo);
	}else registro.cidade = NULL;

	//------------------------------------------------------------------------//

	return registro;
}

///Função que lê caracter por caracter do arquivo até que se encontre um ';' ou a quebra de linha '\n' ou , em linux, o (EOF).
char *leCampoVariavel(FILE *arquivo, int *tamanho)
{
	char auxiliar;
	char *campo = NULL;
	int i = 0;

	//Verifica se o arquivo ainda tem conteudo
	auxiliar = fgetc(arquivo);
	if(auxiliar == EOF) return NULL;
	ungetc(auxiliar, arquivo);

	while ((auxiliar = fgetc(arquivo)) != ';' && auxiliar != '\n' && auxiliar != EOF)/// Lê até achar o ';' ou '\n' ou 'EOF'(para linux);
	{
		campo = (char*)realloc(campo, sizeof(char) * (i + 1));
		campo[i] = auxiliar;

		i++;
	}

	if (i == 0)
	{
		return NULL;
	}

	campo = (char*)realloc(campo, sizeof(char) * (i + 1));/// dá o realloc aqui para ter o tamanho para colocar o '\0';
	campo[i] = '\0';

	*tamanho = i + 1;/// tamanho da string lida que posteriormente será armazenado em alguma variavel(referente a string lida) dentro da struct.

	return campo;
}

///-------------------------------LEITURA DO ARQUIVO DE ENTRADA-------------------------///

///Função que Lê o arquivo de entrada e chama a função para gerar o arquivoSaida dependendo do modo que for pedido pelo usuario.
///modo(1): Arquivo com indicador de tamanho de registro.
///modo(2): Arquivo com delimitadores entre registros.
///modo(3): Arquivo com numero fixo de campos.
void leEntradaGeraSaida(char *entrada, REGISTRO *registro){
	int qtdRegistro = 0;
	FILE *arquivoEntrada = fopen(entrada, "r");
	FILE *arquivo1 = fopen("./saidas/saidaBestFit.bin", "wb+");
	FILE *arquivo2 = fopen("./saidas/saidaWorstFit.bin", "wb+");
	FILE *arquivo3 = fopen("./saidas/saidaFirstFit.bin", "wb+");

	///---------------LEITURA (POR "REGISTRO)-------------------
		///Dominio
	while((registro->dominio = leCampoVariavel(arquivoEntrada, &registro->tamanhoDominio)))
	{
		///Documento
		fread(registro->documento, sizeof(char), TAMANHO_FIXO, arquivoEntrada);
		registro->documento[TAMANHO_FIXO - 1] = '\0';

		///NOME
		registro->nome = leCampoVariavel(arquivoEntrada, &registro->tamanhoNome);

		///UF
		registro->uf = leCampoVariavel(arquivoEntrada, &registro->tamanhoUF);

		char nulo[5];

		fread(nulo, sizeof(char), 5, arquivoEntrada);
		nulo[4] = '\0';

		if (strcmp(nulo, "null") == 0)
		{
			registro->cidade = NULL;
			registro->tamanhoCidade = 0;
		}

		else
		{
			fseek(arquivoEntrada, -5, SEEK_CUR);

			registro->cidade = leCampoVariavel(arquivoEntrada, &registro->tamanhoCidade);
		}

		fread(nulo, sizeof(char), 5, arquivoEntrada);
		nulo[4] = '\0';

		if (strcmp(nulo, "null") == 0)
		{
			registro->dataHoraCadastro = NULL;
			registro->dataHoraCadastro = 0;
		}

		else
		{
			fseek(arquivoEntrada, -5, SEEK_CUR);

			registro->dataHoraCadastro = (char*)malloc(sizeof(char) * TAMANHO_FIXO);

			fread(registro->dataHoraCadastro, sizeof(char), TAMANHO_FIXO, arquivoEntrada);
			registro->dataHoraCadastro[19] = '\0';
		}

		///DATAHORAATUALIZA
		fread(nulo, sizeof(char), 5, arquivoEntrada);
		nulo[4] = '\0';

		if (strcmp(nulo, "null") == 0)
		{
			registro->dataHoraAtualiza = NULL;
			registro->dataHoraAtualiza = 0;
		}

		else
		{
			fseek(arquivoEntrada, -5, SEEK_CUR);

			registro->dataHoraAtualiza = (char*)malloc(sizeof(char) * TAMANHO_FIXO);

			fread(registro->dataHoraAtualiza, sizeof(char), TAMANHO_FIXO, arquivoEntrada);
			registro->dataHoraAtualiza[19] = '\0';
		}

		///TICKET
		fscanf(arquivoEntrada, "%d", &(registro->ticket));
		fseek(arquivoEntrada, +2, SEEK_CUR);

	///---------------------------------------GRAVAR ARQUIVO DE SAIDA--------------------------------------///

        gravarArquivoComSeparador(arquivo1, registro);
        gravarArquivoComSeparador(arquivo2, registro);
        gravarArquivoComSeparador(arquivo3, registro);

		qtdRegistro++;
		libera_campos(registro);
	}

	criaIndice(arquivo1, qtdRegistro);


	fclose(arquivoEntrada);
	fclose(arquivo1);
	fclose(arquivo2);
	fclose(arquivo3);

	printf("\nArquivos de saida gerados!\n");
}
