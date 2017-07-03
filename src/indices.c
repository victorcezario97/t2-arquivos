#include <stdlib.h>
#include <stdio.h>
#include <defines.h>
#include <leituraArquivo.h>

void criaIndice (FILE *arquivo, int qtd)
{
    FILE *indice1 = fopen("indices/indiceBestFit.bin", "w+");
    FILE *indice2 = fopen("indices/indiceWorstFit.bin", "w+");
    FILE *indice3 = fopen("indices/indiceFirstFit.bin", "w+");
    INDICE *indices = (INDICE*)malloc(sizeof(INDICE) * (qtd));
	REGISTRO aux;
    LISTAIND *lista = (LISTAIND*)malloc(sizeof(LISTAIND));
    INDICE *ind;
	int delim, rnn = 0, n=0, pos = 0, i, k=0, t, r;

    fseek(arquivo, 0, SEEK_SET);
	//Enquanto conseguir ler o tamanho do proximo registro, ou seja, enquanto nao chega em EOF
    while(k < qtd-1){
        fread(&delim, sizeof(int), 1, arquivo);
        //Caso nao tenha o delimitador, volta para a posicao anterior
		if(delim != -1) fseek(arquivo, pos, SEEK_SET);
        else{
            k++;
            printf("k: %d\n", k);
        }
       // printf("%d\n", ftell(arquivo));

    //Armazena a posicao do ponteiro do arquivo
        pos = ftell(arquivo);

		//Funcao que le o registro
		aux = leRegistro(arquivo);
        /*printf("---------------\n");
        printf("ticket: %d\n", aux.ticket);
        printf("rrn: %d", rnn);
        printf("\n---------------\n");*/

		// inserir no vetor de maneira ordenada
		if (n==0){
            indices[n].ticket = aux.ticket;
            indices[n].rnn = rnn;
            n++;
		} else {
            for (i=0;i<n;i++){
                if ((indices[i].ticket) > (aux.ticket)){
                    break;
                }
            }
            for (int j=n;j>i;j--){
                indices[j+1].ticket = indices[j].ticket;
            }
            indices[i].ticket=aux.ticket;
            indices[i].rnn = rnn;
            n++;
		}
		rnn = pos;
    }

    /*printf("---------------\n");
    printf(" %d: ", qtd);
    printf("\n---------------\n");
    for (int i=0;i<qtd;i++){
        printf("%d: ", i);
        printf("ticket: %d - ", indices[n].ticket);
        printf("rnn: %d ", indices[n].rnn);
        printf("\n---------------\n");
    }*/

    // percorre todo o vetor e insere no arquivo de indice
     for (int i=0;i<qtd;i++){
        t = ind->ticket;
        r = ind->rnn;

        printf("a---->%d\n", t);
        fwrite(&t, sizeof(int), 1, indice1);
        fwrite(&r, sizeof(int), 1, indice1);
        fwrite(&t, sizeof(int), 1, indice2);
        fwrite(&r, sizeof(int), 1, indice2);
        fwrite(&t, sizeof(int), 1, indice3);
        fwrite(&r, sizeof(int), 1, indice3);
    }

    fclose(indice1);
    fclose(indice2);
    fclose(indice3);
}

INDICE *lerIndice(FILE *fp, int *n){
    INDICE *indices = (INDICE*)malloc(sizeof(INDICE));
    int a;
    *n = 0;

    while(fread(&a, sizeof(int), 1, fp) == 1){
        indices[*n].ticket = a;
        printf("n: %d\n", *n);
        printf("%d\n", indices[*n].ticket);
        fread(&indices[(*n)++].rnn, sizeof(int), 1, fp);
        indices = (INDICE*)malloc(sizeof(INDICE)*((*n)+1));
    }

    return indices;
}

void imprimirIndices(){
    FILE *indice1 = fopen("indices/indiceBestFit.bin", "r");
    FILE *indice2 = fopen("indices/indiceWorstFit.bin", "r");
    FILE *indice3 = fopen("indices/indiceFirstFit.bin", "r");
    int n;
    INDICE *ind = lerIndice(indice1, &n);

    //printf("INDICE BEST FIT\tINDICE WORST FIT\tINDICE FIRST FIT\n");
    //for(int i=0; i< n; i++){
    //    printf("-------------\nticket: %d\nRRN: %d\n--------------\n", ind[i].ticket, ind[i].rnn);
    //}
    return;
}