#include <stdlib.h>
#include <defines.h>
#include <stdio.h>
#include <string.h>
#include <leituraArquivo.h>
#include <free.h>
#include <utils.h>

///--------------------------------------------------BUSCA DE REGISTROS--------------------------------------------------///

//Funcao que compara o campo especificado pela struct CAMPOBUSCA com o campo correspondente do registro
//Retorna TRUE ou FALSE dependendo da comparacao
boolean comparaRegistro(REGISTRO registro, CAMPOBUSCA campo){
	switch(campo.numCampo){
		case 0:
		if(strcmp(campo.string, registro.dominio) == 0) return TRUE;
		return FALSE;

		case 1:
		if(strcmp(campo.string, registro.documento) == 0) return TRUE;
		return FALSE;

		case 2:
		if(strcmp(campo.string, registro.nome) == 0) return TRUE;
		return FALSE;

		case 3:
		if(strcmp(campo.string, registro.uf) == 0) return TRUE;
		return FALSE;

		case 4:
		if(!registro.cidade) return FALSE;
		if(strcmp(campo.string, registro.cidade) == 0) return TRUE;
		return FALSE;

		case 5:
		if(!registro.dataHoraCadastro) return FALSE;
		if(strcmp(campo.string, registro.dataHoraCadastro) == 0) return TRUE;
		return FALSE;

		case 6:
		if(!registro.dataHoraAtualiza) return FALSE;
		if(strcmp(campo.string, registro.dataHoraAtualiza) == 0) return TRUE;
		return FALSE;

		case 7:
		if(campo.ticket == registro.ticket) return TRUE;
		return FALSE;

		default:
		return FALSE;
	}
}

//NUMERO FIXO DE CAMPOS//
//------------------------
//Busca dos registros com numero fixo de campos que possuem o campo como especificado
REGISTRO *buscaPorCampoNFC(CAMPOBUSCA campo, FILE *arquivo, int *n){
	REGISTRO *registros = (REGISTRO*)malloc(sizeof(REGISTRO));
	REGISTRO aux;
	(*n) = 0;
	char c;

	//Verifica se chegou em EOF
	c = fgetc(arquivo);
	while(c != EOF){
		ungetc(c, arquivo);
		//Funcao que le o registro
		aux = leRegistro(arquivo);
		//Se a funcao que compara o registro com o campo recebido retornar TRUE, insere ele na lista de registros
		if(comparaRegistro(aux, campo) == TRUE){
			registros = (REGISTRO*)realloc(registros, sizeof(REGISTRO)*((*n)+1));
			registros[(*n)++] = aux;
		}else libera_campos(&aux);

		c = fgetc(arquivo);
	}

	//Se nao ha registros com o campo especificado, libera a lista
	if((*n) == 0) free(registros);

	return registros;
}

//Busca de um registro com numero fixo de campos a partir do numero do registro
REGISTRO buscaRegistroNFC(int regNumber, FILE *arquivo){
	REGISTRO registro;
	int count = 0, ncampos, pos, tamanho;
	char c;

	//Verifica se chegou no registro esperado ou em EOF
	c = fgetc(arquivo);
	while(count < regNumber && c != EOF){
		ungetc(c, arquivo);

		for(ncampos = 0; ncampos < 8; ncampos++){
			//O oitavo campo eh um int
			if(ncampos == 7){
				//Avanca os quatro bytes do ticket
				fseek(arquivo, 4, SEEK_CUR);
			}else{
				//Armazena a posicao antes de fazer a verificacao de campo nulo
				pos = ftell(arquivo);
				fread(&tamanho, sizeof(int), 1, arquivo);

				if(tamanho != 0){
					//Caso o campo nao seja nulo, retorna para a posicao armazenada
					fseek(arquivo, pos, SEEK_SET);

					//verifica se eh um dos campos que tem tamanho fixo
					if(fixo(ncampos)) tamanho = 20;
					//Se tem tamanho variavel, le o tamanho antes.
					else fread(&tamanho, sizeof(int), 1, arquivo);

					//Avanca o tamanho do campo(pula o campo)
					fseek(arquivo, tamanho, SEEK_CUR);
				}
			}
		}
		count++;
		c = fgetc(arquivo);
	}
	ungetc(c, arquivo);

	//Caso tenha chegado ao final do arquivo, ou seja, nao encontrou o registro, seta ticket como -1
	if(c == EOF || count != regNumber){
		registro.ticket = -1;
		return registro;
	}

	//Se encontrou o registro armazena ele e retorna
	registro = leRegistro(arquivo);

	return registro;
}
//------------------------

//INDICADORES DE TAMANHO//
//------------------------
//Busca dos registros com indicadores de tamanho que possuem o campo como especificado
REGISTRO *buscaPorCampoTamanho(CAMPOBUSCA campo, FILE *arquivo, int *n){
	REGISTRO *registros = (REGISTRO*)malloc(sizeof(REGISTRO));
	REGISTRO aux;
	int tamanhoreg;

	(*n) = 0;

	//Enquanto conseguir ler o tamanho do proximo registro, ou seja, enquanto nao chega em EOF
	while(fread(&tamanhoreg, sizeof(int), 1, arquivo) == 1){
		//Funcao que le o registro
		aux = leRegistro(arquivo);
		//Se a funcao que compara o registro com o campo recebido retornar TRUE, insere ele na lista de registros
		if(comparaRegistro(aux, campo) == TRUE){
			registros = (REGISTRO*)realloc(registros, sizeof(REGISTRO)*((*n)+1));
			registros[(*n)++] = aux;
		}else libera_campos(&aux);
	}

	//Se nao ha registros com o campo especificado, libera a lista
	if((*n) == 0) free(registros);

	return registros;
}

//Busca de um registro com indicador de tamanho a partir do numero do registro
REGISTRO buscaRegistroTamanho(int regNumber, FILE *arquivo){
	REGISTRO registro;
	int count = 0, check, tamanho;

	//Verifica se chegou no registro esperado ou em EOF
	check = fread(&tamanho, sizeof(int), 1, arquivo);
	while(count < regNumber && check == 1){
		//Avanca no arquivo o tamanho do registro atual
		fseek(arquivo, tamanho, SEEK_CUR);
		count++;
		//Le o tamanho do proximo registro
		check = fread(&tamanho, sizeof(int), 1, arquivo);
	}

	//Caso tenha chegado ao final do arquivo, ou seja, nao encontrou o registro, seta ticket como -1
	if(check == 0 || count != regNumber){
		registro.ticket = -1;
		return registro;
	}

	//Se encontrou o registro armazena ele e retorna
	registro = leRegistro(arquivo);

	return registro;
}
//------------------------

//DELIMITADORES DE REGISTRO//
//------------------------
//Busca dos registros com delimitadores que possuem o campo como especificado
REGISTRO *buscaPorCampoDelimitador(CAMPOBUSCA campo, FILE *arquivo, int *n){
	REGISTRO *registros = (REGISTRO*)malloc(sizeof(REGISTRO));
	REGISTRO aux;
	int delim, pos = 0;

	(*n) = 0;
	//Enquanto conseguir ler o tamanho do proximo registro, ou seja, enquanto nao chega em EOF
	while(fread(&delim, sizeof(int), 1, arquivo) == 1){
		//Caso nao tenha o delimitador, volta para a posicao anterior
		if(delim != -1) fseek(arquivo, pos, SEEK_SET);

		//Funcao que le o registro
		aux = leRegistro(arquivo);

		//Se a funcao que compara o registro com o campo recebido retornar TRUE, insere ele na lista de registros
		if(comparaRegistro(aux, campo) == TRUE){
			registros = (REGISTRO*)realloc(registros, sizeof(REGISTRO)*((*n)+1));
			registros[(*n)++] = aux;
		}else libera_campos(&aux);

		//Armazena a posicao do ponteiro do arquivo
		pos = ftell(arquivo);
	}

	//Se nao ha registros com o campo especificado, libera a lista
	if((*n) == 0) free(registros);

	return registros;
}

//Busca de um registro com delimitador a partir do numero do registro
REGISTRO buscaRegistroDelimitador(int regNumber, FILE *arquivo){
	REGISTRO registro;
	int count = 0, check = 1, delim, pos = -1;

	//Verifica se chegou no registro esperado ou em EOF
	while(count < regNumber && check == 1){
		while(check == 1 && delim != -1){
			//Avanca no arquivo
			fseek(arquivo, pos+1, SEEK_SET);
			//Guarda a posicao atual e testa para EOF ou o delimitador
			pos = ftell(arquivo);
			check = fread(&delim, sizeof(int), 1, arquivo);
		}
		delim = 0;
		count++;
	}

	//Caso tenha chegado ao final do arquivo, ou seja, nao encontrou o registro, seta ticket como -1
	if(check == 0 || count != regNumber){
		registro.ticket = -1;
		return registro;
	}

	//Se encontrou o registro armazena ele e retorna
	registro = leRegistro(arquivo);

	return registro;
}