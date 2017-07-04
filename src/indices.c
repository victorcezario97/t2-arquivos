#include <stdlib.h>
#include <stdio.h>
#include <defines.h>
#include <leituraArquivo.h>
#include <utils.h>
#include <impressao.h>

void quick(INDICE *vetor, int inicio, int fim){
   
   int pivo, auxt, auxr, i, j, meio;
   
   i = inicio;
   j = fim;
   
   meio = (int) ((i + j) / 2);
   pivo = vetor[meio].ticket;
   
   do{
      while (vetor[i].ticket < pivo) i = i + 1;
      while (vetor[j].ticket > pivo) j = j - 1;
      
      if(i <= j){
         auxt = vetor[i].ticket;
         auxr = vetor[i].rnn;
         vetor[i].ticket = vetor[j].ticket;
         vetor[i].rnn = vetor[j].rnn;
         vetor[j].ticket = auxt;
         vetor[j].rnn = auxr;
         i = i + 1;
         j = j - 1;
      }
   }while(j > i);
   
   if(inicio < j) quick(vetor, inicio, j);
   if(i < fim) quick(vetor, i, fim);   

}

void escreveIndice(INDICE *indices, int n, int tipo){
    FILE *arquivo;
    int a;

    switch(tipo){
        case BEST_FIT:
        arquivo = fopen("indices/indiceBestFit.bin", "r+");
        break;

        case WORST_FIT:
        arquivo = fopen("indices/indiceWorstFit.bin", "r+");
        break;

        case FIRST_FIT:
        arquivo = fopen("indices/indiceFirstFit.bin", "r+");
        break;
    }
    rewind(arquivo);
    fwrite(&n, sizeof(int), 1, arquivo);

    quick(indices, 0, n-1);

    for(int i=0; i<n; i++){
        fwrite(&(indices[i].ticket), sizeof(int), 1, arquivo);
        fwrite(&(indices[i].rnn), sizeof(int), 1, arquivo);
    }

    fclose(arquivo);
}

void criaIndice (FILE *arquivo, int qtd)
{
    FILE *indice1 = fopen("indices/indiceBestFit.bin", "w+");
    FILE *indice2 = fopen("indices/indiceWorstFit.bin", "w+");
    FILE *indice3 = fopen("indices/indiceFirstFit.bin", "w+");
    INDICE *indices = (INDICE*)malloc(sizeof(INDICE) * (qtd));
    REGISTRO aux;
    int delim, pos = 0, i, k=0, t, r;
    char c;

    fseek(arquivo, 4, SEEK_SET);
    //c = fgetc(arquivo);
    //Enquanto conseguir ler o tamanho do proximo registro, ou seja, enquanto nao chega em EOF
    while(k < qtd){
        /*if(c == '*'){
            fread(&t, sizeof(int), 1, arquivo);
            pos = ftell(arquivo);
            fseek(arquivo, pos + (t-5), SEEK_SET);
            continue;
        }*/

        pos = ftell(arquivo);
        fread(&delim, sizeof(int), 1, arquivo);
        //Caso nao tenha o delimitador, volta para a posicao anterior
        if(delim != -1) fseek(arquivo, pos, SEEK_SET);
        else{
            k++;
           // printf("k: %d\n", k);
        }

        //Armazena a posicao do ponteiro do arquivo
        pos = ftell(arquivo);

        //Funcao que le o registro
        aux = leRegistro(arquivo);
        //imprimeRegistro(aux, TODOS);

        indices[k].ticket = aux.ticket;
        indices[k].rnn = pos;  
    }

    quick(indices, 0, qtd-1);
    
    /*printf("---------------\n");
    printf(" %d ", qtd);
    printf("\n---------------\n");
    for (i=0;i<qtd;i++){
        printf("%d: ", i);
        printf("ticket: %d - ", indices[i].ticket);
        printf("rnn: %d ", indices[i].rnn);
        printf("\n---------------\n");
    }*/
    
    fwrite(&qtd, sizeof(int), 1, indice1);
    fwrite(&qtd, sizeof(int), 1, indice2);
    fwrite(&qtd, sizeof(int), 1, indice3);
    
    // percorre todo o vetor e insere no arquivo de indice
     for (i=0;i<qtd;i++){
        t = indices[i].ticket;
        r = indices[i].rnn;

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

INDICE *lerIndice(FILE *arquivo, int *n){
    INDICE *indices;
    int a;

    fseek(arquivo, 0, SEEK_SET);

    fread(n, sizeof(int), 1, arquivo);
    printf("----------->%d\n", *n);
    indices = (INDICE*)malloc(sizeof(INDICE)*(*n));

    for(int i=0; i < *n; i++){
        fread(&a, sizeof(int), 1, arquivo);
        indices[i].ticket = a;
        fread(&indices[i].rnn, sizeof(int), 1, arquivo);
    }

    return indices;
}

void imprimirIndices(){
    FILE *indice1 = fopen("indices/indiceBestFit.bin", "r");
    FILE *indice2 = fopen("indices/indiceWorstFit.bin", "r");
    FILE *indice3 = fopen("indices/indiceFirstFit.bin", "r");
    int n1, n2, n3;
    INDICE *ind1 = lerIndice(indice1, &n1);
    INDICE *ind2 = lerIndice(indice2, &n2);
    INDICE *ind3 = lerIndice(indice3, &n3);
    int max = MAX3(n1, n2, n3);
    printf("%d\n", n1);
    //return;
    boolean todos = FALSE;
    char c;

    getchar();
    printf("Impressao dos indices.\nPressione ENTER para imprimir o proximo ou ESPACO seguido de ENTER para imprimir o restante.\n");
    printf("INDICE BEST FIT(%d) \tINDICE WORST FIT(%d)\tINDICE FIRST FIT(%d)\n", n1, n2, n3);
    for(int i=0; i< max; i++){
        printf("Indice %d:\n", i);
        printf("--------------------------------------------------------------------\n");
        if(n1 > i) printf("TICKET: %8d\t", ind1[i].ticket);
        else printf("%16s\t", "");

        if(n2 > i) printf("TICKET: %8d\t", ind2[i].ticket);
        else printf("%16s\t", "");

        if(n3 > i) printf("TICKET: %8d\n", ind3[i].ticket);
        else printf("%16s\n", "");

        if(n1 > i) printf("   RRN: %8d\t", ind1[i].rnn);
        else printf("%16s\t", "");

        if(n2 > i) printf("   RRN: %8d\t", ind2[i].rnn);
        else printf("%16s\t", "");

        if(n3 > i) printf("   RRN: %8d\n", ind3[i].rnn);
        else printf("%16s\n", "");
        printf("--------------------------------------------------------------------\n");


        if(todos == FALSE){
            c = getchar();
            if(c == ' ') todos = TRUE; 
        }
    }

    fclose(indice1);
    fclose(indice2);
    fclose(indice3);
    return;
}

int buscaIndice(int x, int n, INDICE *v) {
   int e, m, d;                              
   e = 0; d = n-1;                          
   while (e <= d) {                         
      m = (e + d)/2;                     
      if (v[m].ticket == x) return m;               
      if (v[m].ticket < x) e = m + 1;             
      else d = m - 1;                        
   }                                        
   return -1;                               
}

void removeIndice(int ticket, INDICE *indices, int n, int tipo){
    int pos = buscaIndice(ticket, n indices);
    
    indices[pos] = indices[n-1];
    indices = (INDICE*)realloc(indices, sizeof(INDICE)*(n-1));
    escreveIndice(indices, n-1, tipo);
}

void insereIndice(int ticket, int bo, INDICE *indices, int n, int tipo){
    INDICE ind;

    ind.ticket = ticket;
    ind.rnn = bo;
    indices = (INDICE*)realloc(indices, sizeof(INDICE)*(n+1));
    indices[n] = ind;

    escreveIndice(indices, n+1, tipo);
}