#include <stdlib.h>
#include <stdio.h>
#include <defines.h>
#include <utils.h>

void removeLista(int bo, FILE *arquivo){
	int pos, prev = 0, prox;

	rewind(arquivo);
	fread(&pos, sizeof(int), 1, arquivo);
	fseek(arquivo, pos+5, SEEK_SET);
	fread(&prox, sizeof(int), 1, arquivo);

	if(pos == -1) return;
	while(pos != bo){
		prev = pos;
		pos = prox;
		fseek(arquivo, prox+5, SEEK_SET);
		fread(&prox, sizeof(int), 1, arquivo);
	}
	if(prev != 0) prev += 5;
	fseek(arquivo, prev, SEEK_SET);
	fwrite(&prox, sizeof(int), 1, arquivo);

	return;
}

int encontraPos(int n, FILE *arquivo, boolean op, int *end, boolean *reordena){
	int rrn, prox, tam = 0;

	*reordena = FALSE;

	fseek(arquivo, 0, SEEK_SET);

	//Le o topo da lista de registros removidos
	fread(&rrn, sizeof(int), 1, arquivo);	
	//printf("rrn %d\n", n);

	//Caso nao tenha nenhum removido, retorna -1
	if(rrn == -1) return rrn;

	//fread(&tamanho, sizeof(int), 1, arquivo);

	prox = rrn;
	//Verifica se o tamanho eh suficiente e cabem os bytes para indicar o registro removido
	while(n == tam || n + 9 > tam){
		rrn = prox;
		//Chegou ao fim da lista e nao encontrou espaco
		if(prox == -1) return -2; 
		//Vai ate a posicao do registro removido
		fseek(arquivo, prox, SEEK_SET);
		//Le o byte que representa um registro removido 
		fgetc(arquivo);
		//Le o tamanho do espaco e o rrn do proximo registro
		fread(&tam, sizeof(int), 1, arquivo);
		fread(&prox, sizeof(int), 1, arquivo);
	}

	//printf("--->%c %d\n",c, tam );

	if(op && tam > n){
		*reordena = TRUE;
		*end = rrn;
		tam = tam - n;
		fseek(arquivo, rrn+1, SEEK_SET);
		fwrite(&tam, sizeof(int), 1, arquivo);
		fwrite(&prox, sizeof(int), 1, arquivo);
		removeLista(rrn, arquivo);
	}
	//printf("rrn:%d tam: %d n:%d\n", rrn, tam, n);
	return rrn + tam;
}

void ordenaBest(FILE *arquivo, int rrn, int tam, int pos){
	int n = 0, prox, prev;

	fseek(arquivo, pos, SEEK_SET);
	fgetc(arquivo);
	fread(&n, sizeof(int), 1, arquivo);
	fread(&prox, sizeof(int), 1, arquivo);

	if(n > tam){
		fseek(arquivo, 0, SEEK_SET);
		fwrite(&rrn, sizeof(int), 1, arquivo);

		fseek(arquivo, rrn+5, SEEK_SET);
		fwrite(&pos, sizeof(int), 1, arquivo);

		return;
	}

	while(n < tam){
		if(prox == -1){
			fseek(arquivo, pos+5, SEEK_SET);
			fwrite(&rrn, sizeof(int), 1, arquivo);

			fseek(arquivo, rrn+5, SEEK_SET);
			pos = -1;
			fwrite(&pos, sizeof(int), 1, arquivo);
			return;
		}

		prev = pos;
		pos = prox;
		fseek(arquivo, prox, SEEK_SET);
		fgetc(arquivo);
		fread(&n, sizeof(int), 1, arquivo);
		fread(&prox, sizeof(int), 1, arquivo);		
	}

	fseek(arquivo, prev+5, SEEK_SET);
	fwrite(&rrn, sizeof(int), 1, arquivo);

	fseek(arquivo, rrn+5, SEEK_SET);
	fwrite(&pos, sizeof(int), 1, arquivo);
}

void ordenaWorst(FILE *arquivo, int rrn, int tam, int pos){
	int n = 0, prox, prev;

	fseek(arquivo, pos, SEEK_SET);
	fgetc(arquivo);
	fread(&n, sizeof(int), 1, arquivo);
	fread(&prox, sizeof(int), 1, arquivo);

	if(n < tam){
		fseek(arquivo, 0, SEEK_SET);
		fwrite(&rrn, sizeof(int), 1, arquivo);

		fseek(arquivo, rrn+5, SEEK_SET);
		fwrite(&pos, sizeof(int), 1, arquivo);

		return;
	}

	while(n > tam){
		if(prox == -1){
			fseek(arquivo, pos+5, SEEK_SET);
			fwrite(&rrn, sizeof(int), 1, arquivo);

			fseek(arquivo, rrn+5, SEEK_SET);
			pos = -1;
			fwrite(&pos, sizeof(int), 1, arquivo);
			return;
		}

		prev = pos;
		pos = prox;
		fseek(arquivo, prox, SEEK_SET);
		fgetc(arquivo);
		fread(&n, sizeof(int), 1, arquivo);
		fread(&prox, sizeof(int), 1, arquivo);		
	}

	fseek(arquivo, prev+5, SEEK_SET);
	fwrite(&rrn, sizeof(int), 1, arquivo);

	fseek(arquivo, rrn+5, SEEK_SET);
	fwrite(&pos, sizeof(int), 1, arquivo);
}

void ordenaFirst(FILE *arquivo, int rrn, int pos){
	int prox, prev;

	

	if(rrn < pos){
		fseek(arquivo, 0, SEEK_SET);
		fwrite(&rrn, sizeof(int), 1, arquivo);

		fseek(arquivo, rrn+5, SEEK_SET);
		fwrite(&pos, sizeof(int), 1, arquivo);

		return;
	}

	fseek(arquivo, pos+5, SEEK_SET);
	fread(&prox, sizeof(int), 1, arquivo);

	while(rrn > pos){
		if(prox == -1){
			fseek(arquivo, pos+5, SEEK_SET);
			fwrite(&rrn, sizeof(int), 1, arquivo);

			fseek(arquivo, rrn+5, SEEK_SET);
			pos = -1;
			fwrite(&pos, sizeof(int), 1, arquivo);
			return;
		}

		prev = pos;
		pos = prox;
		fseek(arquivo, prox+5, SEEK_SET);
		fread(&prox, sizeof(int), 1, arquivo);		
	}

	fseek(arquivo, prev+5, SEEK_SET);
	fwrite(&rrn, sizeof(int), 1, arquivo);

	fseek(arquivo, rrn+5, SEEK_SET);
	fwrite(&pos, sizeof(int), 1, arquivo);
}

void ordenaListaRem(FILE *arquivo, int tipo, int rrn, int tam){
	int pos;
	fseek(arquivo, 0, SEEK_SET);
	fread(&pos, sizeof(int), 1, arquivo);
	//pos = encontraPos(tam, arquivo, FALSE);
	//printf("---->>%d %d\n", rrn, tam);

	//fseek(arquivo, pos, SEEK_SET);
	//fread(&c, sizeof(char), 1, arquivo);
	//printf("%c\n", c);
	//Caso a lista ainda nao tenha remocoes, nao altera nada
	if(pos == -1){
		rewind(arquivo);
		fwrite(&rrn, sizeof(int), 1, arquivo);
		return;
	}
	//Caso o registro recebido seja o ultimo
	if(pos == -2){
		fseek(arquivo, 0, SEEK_SET);
		fwrite(&rrn, sizeof(int), 1, arquivo);
		return;
	}

	switch(tipo){
		case BEST_FIT:
		ordenaBest(arquivo, rrn, tam, pos);
		break;

		case WORST_FIT:
		ordenaWorst(arquivo, rrn, tam, pos);
		break;

		case FIRST_FIT:
		ordenaFirst(arquivo, rrn, pos);
		break;

		default:
		printf("Falha ao ordenar a lista de registros removidos.\n");
		break;
	}
}

void imprimeListaRem(FILE *arquivo){
	int rrn, prev, tam;

	fseek(arquivo, 0, SEEK_SET);
	fread(&rrn, sizeof(int), 1, arquivo);
	printf("TOPO DA LISTA: %d\n", rrn);

	//fseek(arquivo, rrn, SEEK_SET);
	//c = fgetc(arquivo);
	//printf("%c\n", c);


	while(rrn != -1){
		prev = rrn;
		fseek(arquivo, rrn+1, SEEK_SET);
		fread(&tam, sizeof(int), 1, arquivo);
		fread(&rrn, sizeof(int), 1, arquivo);

		printf("TAMANHO: %d RRN: %d -----> ", tam, prev);
	}

	printf("FIM DA LISTA\n\n");

}
