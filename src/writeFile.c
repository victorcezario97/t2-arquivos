#include <stdio.h>
#include <stdlib.h>
#include <defines.h>

///-------------------------FUNCOES QUE GERAM OS ARQUIVOS DE SAIDA--------------------------///

///Função gravarArquivoComNumeroFixo que gera arquivoSaida com o registro váriavel, porém, com quantidade de campos fixos.
///- campos de tamanho fixo + campos de tamanho variável com indicador de tamanho + registros de tamanho variável com número fixo de campos
void gravarArquivoComNumeroFixo(FILE *arquivo, REGISTRO *registro)
{
	int campoNulo = 0;
	///----------------------------Campos FIXOS primeiro--------------------------------///
	fwrite(registro->documento, sizeof(char), TAMANHO_FIXO, arquivo);///1 campo: documento

	///2 campo: dataHoraCadastro
	///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->dataHoraCadastro)
	{
		fwrite(registro->dataHoraCadastro, sizeof(char), TAMANHO_FIXO, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}

	///3 campo: dataHoraAtualiza
	///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->dataHoraAtualiza)
	{
		fwrite(registro->dataHoraAtualiza, sizeof(char), TAMANHO_FIXO, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}

	///4 campo: ticket
	fwrite(&registro->ticket, sizeof(int), 1, arquivo);

	///----------------------------Campos FIXOS FIM--------------------------------///

	///----------------------------Campos VARIÁVEIS---------------------------------///
    fwrite(&registro->tamanhoDominio, sizeof(int), 1, arquivo);///tamanho do 5 campo
	fwrite(registro->dominio, sizeof(char), registro->tamanhoDominio, arquivo);///5 campo: dominio

	fwrite(&registro->tamanhoNome, sizeof(int), 1, arquivo);///tamanho do 6 campo
	fwrite(registro->nome, sizeof(char), registro->tamanhoNome, arquivo);///6 campo: nome

	fwrite(&registro->tamanhoUF, sizeof(int), 1, arquivo);///tamanho do 7 campo
	fwrite(registro->uf, sizeof(char), registro->tamanhoUF, arquivo);///7 campo: UF

    ///8 campo: cidade
    ///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->cidade)
	{
		fwrite(&registro->tamanhoCidade, sizeof(int), 1, arquivo);
		fwrite(registro->cidade, sizeof(char), registro->tamanhoCidade, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}
	///----------------------------Campos VARIÁVEIS FIM---------------------------------///   
}

///Função gravarArquivoComTamanho que gera arquivoSaida com o indicador de tamanho dos registros.
///"- campos de tamanho fixo + campos de tamanho variável com indicador de tamanho + registros de tamanho variável com indicador de tamanho "
void gravarArquivoComTamanho(FILE *arquivo, REGISTRO *registro)
{
	int campoNulo = 0;
	int tamanhoFixos = TAMANHO_FIXO;
	int indicadorTamanho = 4;

	if(registro->dataHoraCadastro)
	{
		tamanhoFixos += TAMANHO_FIXO;
	}

	else
	{
		tamanhoFixos += indicadorTamanho;
	}

	if (registro->dataHoraAtualiza)
	{
		tamanhoFixos += TAMANHO_FIXO;
	}
	else
	{
		tamanhoFixos += indicadorTamanho;
	}

    int tamanhoRegistro = tamanhoFixos + (indicadorTamanho * 4) + registro->tamanhoDominio + registro->tamanhoNome + registro->tamanhoCidade + registro->tamanhoUF + 4;

    ///----------------------Tamanho do registro-----------///
	fwrite(&tamanhoRegistro, sizeof(int), 1, arquivo);

	///----------------------------Campos FIXOS primeiro--------------------------------///
	fwrite(registro->documento, sizeof(char), TAMANHO_FIXO, arquivo);///1 campo: documento

	///2 campo: dataHoraCadastro
	///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->dataHoraCadastro)
	{
		fwrite(registro->dataHoraCadastro, sizeof(char), TAMANHO_FIXO, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}

	///3 campo: dataHoraAtualiza
	///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->dataHoraAtualiza)
	{
		fwrite(registro->dataHoraAtualiza, sizeof(char), TAMANHO_FIXO, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}

	///4 campo: ticket
	fwrite(&registro->ticket, sizeof(int), 1, arquivo);

	///---------------------------------------FIM dos Campos FIXOS----------------------------------------///

	///----------------------------------------CAMPOS VARIÁVEIS-------------------------------------------///
	fwrite(&registro->tamanhoDominio, sizeof(int), 1, arquivo);///tamanho do 5 campo
	fwrite(registro->dominio, sizeof(char), registro->tamanhoDominio, arquivo);///5 campo: dominio

	fwrite(&registro->tamanhoNome, sizeof(int), 1, arquivo);///tamanho do 6 campo
	fwrite(registro->nome, sizeof(char), registro->tamanhoNome, arquivo);///6 campo: nome

	fwrite(&registro->tamanhoUF, sizeof(int), 1, arquivo);///tamanho do 7 campo
	fwrite(registro->uf, sizeof(char), registro->tamanhoUF, arquivo);///7 campo: UF

    ///8 campo: cidade
    ///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->cidade)
	{
		fwrite(&registro->tamanhoCidade, sizeof(int), 1, arquivo);
		fwrite(registro->cidade, sizeof(char), registro->tamanhoCidade, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}
	///-----------------------------------FIM CAMPOS VARIÁVEIS--------------------------------------///
}

///Função gravarArquivoComSeparador  que gera o arquivo "arquivoSaida.bin" com Um indicador '#' para separador registradores e com números para dizer o tamanho do campo variável.
///"- campos de tamanho fixo + campos de tamanho variável com indicador de tamanho + registros de tamanho variável com delimitadores entre registros"
void gravarArquivoComSeparador(FILE *arquivo, REGISTRO *registro)
{
	int campoNulo = 0;
	int separadorDeRegistro = -1; 

	///--------------------------------------Campos FIXOS primeiro-----------------------------///
	fwrite(registro->documento, sizeof(char), TAMANHO_FIXO, arquivo);///1 campo: documento

	///2 campo: dataHoraCadastro
	///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->dataHoraCadastro)
	{
		fwrite(registro->dataHoraCadastro, sizeof(char), TAMANHO_FIXO, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}

	///3 campo: dataHoraAtualiza
	///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->dataHoraAtualiza)
	{
		fwrite(registro->dataHoraAtualiza, sizeof(char), TAMANHO_FIXO, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	} 

	///4 campo: ticket
	fwrite(&registro->ticket, sizeof(int), 1, arquivo);

	///--------------------------------------Campos VARIAVEIS -----------------------------------///
	fwrite(&registro->tamanhoDominio, sizeof(int), 1, arquivo);///tamanho do 5 campo
	fwrite(registro->dominio, sizeof(char), registro->tamanhoDominio, arquivo);///5 campo: dominio

	fwrite(&registro->tamanhoNome, sizeof(int), 1, arquivo);///tamanho do 6 campo
	fwrite(registro->nome, sizeof(char), registro->tamanhoNome, arquivo);///6 campo: nome

	fwrite(&registro->tamanhoUF, sizeof(int), 1, arquivo);///tamanho do 7 campo
	fwrite(registro->uf, sizeof(char), registro->tamanhoUF, arquivo);///7 campo: UF

    ///8 campo: cidade
    ///Faz a verificação se o campo não é null. Caso for, coloca numero inteiro 0, representando o NULL.
	if (registro->cidade)
	{
		fwrite(&registro->tamanhoCidade, sizeof(int), 1, arquivo);
		fwrite(registro->cidade, sizeof(char), registro->tamanhoCidade, arquivo);
	}

	else
	{
		fwrite(&campoNulo, sizeof(int), 1, arquivo);
	}
	///--------------------------------------Campos VARIAVEIS -----------------------------------///

	fwrite(&separadorDeRegistro, sizeof(int), 1, arquivo);///separador de registro.
}
