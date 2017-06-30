#include <stdlib.h>
#include <defines.h>

//Funcao que libera os campos de um registro que estao alocados
void libera_campos(REGISTRO *registro){
	if(registro->dominio){
		free(registro->dominio);
		registro->dominio = NULL;
	}

	if(registro->nome){
		free(registro->nome);
		registro->nome = NULL;
	}

	if(registro->uf){
		free(registro->uf);
		registro->uf = NULL;
	}

	if(registro->cidade){
		free(registro->cidade);
		registro->cidade = NULL;
	}

	if(registro->dataHoraCadastro){
		free(registro->dataHoraCadastro);
		registro->dataHoraCadastro = NULL;
	}

	if(registro->dataHoraAtualiza){
		free(registro->dataHoraAtualiza);
		registro->dataHoraAtualiza = NULL;
	}
}
