#ifndef _DEFINES_H_
#define _DEFINES_H_

//Tamanho dos campos fixos
#define TAMANHO_FIXO 20
//Nome do arquivo de entrada
#define ENTRADA "SCC0215012017projeto01turmaAdadosDominios.csv"
//Retorna se o campo é de tamanho fixo ou nao
#define fixo(i) (i == 1) || (i == 5) || (i == 6)

//Ordem dos campos
enum{
	DOMINIO,
	DOCUMENTO,
	NOME,
	UF,
	CIDADE,
	DHCADASTRO,
	DHATUALIZA,
	TICKET,
	TODOS
};

//Struct usada em buscas que envolvam um campo especifico
typedef struct campo{
	int numCampo;
	char *string;
	int ticket;
} CAMPOBUSCA;

//Registro
typedef struct reg
{
    int tamanhoDominio;
	char *dominio;
	char documento[TAMANHO_FIXO];
    int tamanhoNome;
	char *nome;
    int tamanhoUF;
	char *uf;
    int tamanhoCidade;
	char *cidade;
	char *dataHoraCadastro;///Campo fixo, porém como pode haver null no arquivo fica mais fácil verificar como um ponteiro depois....
	char *dataHoraAtualiza;///idem.
	int ticket;

} REGISTRO;



#endif