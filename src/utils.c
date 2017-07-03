#include <stdlib.h>
#include <stdio.h>

//Funcao que le e retorna uma string da entrada padrao ate que encontre um '\n' ou EOF
char *leString(int *count){
	char *string = (char*)malloc(sizeof(char));
	char c;
	*count = 0;

	c = fgetc(stdin);
	while(c != '\n' && c != EOF){
		string[(*count)++] = c;
		string = (char*)realloc(string, sizeof(char)*((*count)+1));
		c = fgetc(stdin);
	}

	if((*count) == 0) {
		free(string);
		return NULL;
	}
	string[(*count)] = '\0';

	return string;
}