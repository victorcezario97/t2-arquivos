#include <stdlib.h>
#include <stdio.h>
#include <utils.h>

void printMainMenu(){
	//Menu do tipo de arquivo a ser manipulado
   		printf ("Escolha a opcao desejada:\n");
        printf ("1 - Ler registros e gerar arquivos de saida\n");
        printf ("2 - Remover registro\n");
        printf ("3 - Inserir registro\n");
        printf ("4 - Visualizar estatisticas sobre os arquivos de indice\n");
        printf ("5 - Visualizar estatisticas sobre as listas de registros removidos\n");
        printf ("6 - Sair\n");
}

int readOp(){
	int opcao;

	do
        {
            printf ("Opcao: ");
            scanf("%d", &opcao);
            printf("%d\n", opcao);

            if(opcao > 6 || opcao < 1)
            {
                printf("Opcao invalida. Digite Novamente(numero de 1 a 6).\n");
            }

        }while(opcao > 6 || opcao < 1);

        return opcao;
}
