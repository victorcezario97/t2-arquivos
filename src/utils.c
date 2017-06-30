#include <stdlib.h>
#include <stdio.h>

//Funcao que le e retorna uma string da entrada padrao ate que encontre um '\n' ou EOF
char *leString(){
	char *string = (char*)malloc(sizeof(char));
	char c;
	int count = 0;

	c = fgetc(stdin);
	while(c != '\n' && c != EOF){
		string[count++] = c;
		string = (char*)realloc(string, sizeof(char)*(count+1));
		c = fgetc(stdin);
	}

	string[count] = '\0';

	return string;
}