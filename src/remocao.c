#include <stdio.h>
#include <stdlib.h>

//realiza a busca do registro no arquivo de indice

FILE *indice1 = fopen("indices/indiceBestFit.bin", "w+");
FILE *indice2 = fopen("indices/indiceWorstFit.bin", "w+");
FILE *indice3 = fopen("indices/indiceFirstFit.bin", "w+");

int buscaBinaria (int x, int n, INDICE v[]) {
   int e, m, d;                              
   e = 0; d = n-1;                          
   while (e <= d) {                         
      m = (e + d)/2;                     
      if (v[m].ticket == x) return m;               
      if (v[m].ticket < x) e = m + 1;             
      else d = m - 1;                        
   }
   remocao();
   return -1;                               
}

int remocao (listaord *L, int posicao, elem *busca) 
{
	//abre os arquivos para remoção
	FILE *indice1 = fopen("indices/indiceBestFit.bin", "w+");
	FILE *indice2 = fopen("indices/indiceWorstFit.bin", "w+");
	FILE *indice3 = fopen("indices/indiceFirstFit.bin", "w+");
   // busca recebe o parametro encontrado
   // Retorna 0 se nada for encontrado caso contrário retorna 1
   fseek(indice1, (posicao+1)*sizeof(busca), SEEK_SET);
   fseek(indice2, (posicao+1)*sizeof(busca), SEEK_SET);
   fseek(indice3, (posicao+1)*sizeof(busca), SEEK_SET);
    int i;
   if ( (posicao > L->n)) || (posicao <= 0) ) return (0); 
   *busca = L->v[posicao-1];
      
   for (i=posicao; i<=(L->n)-1; i++)
	   L->v[i-1] = L->v[i];
	(L->n)--;
	
	elem *lixo;
	lixo = busca->prox;
	busca->prox = lixo->prox;
	//libera o indice
	free (lixo);
	
	fclose(indice1);
	fclose(indice2);
	fclose(indice3);
   return (1);
}