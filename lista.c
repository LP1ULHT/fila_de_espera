#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NR_DIM 10
#define NOME_DIM 128
#define DIM 256

#define OPT_REM 'R'
#define OPT_ADD 'N'
#define OPT_LIST 'L'
#define OPT_QUIT 'Q'

typedef struct s_pessoa {
	char nr[NR_DIM];
	char nome[NOME_DIM];
	int id;
	struct s_pessoa * next;
} pessoa;


int Inserir (pessoa **, pessoa **, pessoa);
void Apagar (pessoa **, pessoa **);
void listar (pessoa *);

int main(int argc, char **argv)
{
	pessoa aux;
	pessoa * primeiro = NULL;
	pessoa * ultimo = NULL;
	FILE * fp = NULL;
	char input[DIM];
	char option;
	int i = 0;

	for (i = 0 ; i < argc ; i++)
	{
		printf("Argumento %d = %s\n", i, argv[i]);
	}

	if (argc < 2)
	{
		puts("error: invalid arguments");
		exit(1);
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		puts("error: could not open file");
		exit(1);
	}

	// podemos, e devemos, fazer uma funcao para a leitura do ficheiro
	while (!feof(fp))
	{
		if (fscanf(fp, "%s %d %[^\n]", aux.nr, &aux.id, aux.nome) != 3)
			continue;

		if (!Inserir(&primeiro, &ultimo, aux))
		{
			puts("Error: out of memory!");
			exit(1);
		}
	}

	listar(primeiro);


	while(1)
	{
		putchar('>');
		fgets(input, DIM, stdin);

		if (sscanf(input, " %c ", &option) != 1)
			continue;

		switch(toupper(option))
		{
		case OPT_REM:
			Apagar(&primeiro, &ultimo);
			continue;

		case OPT_ADD:
			if (sscanf(input, " %c %s %d %[^\n]", &option, aux.nr, &aux.id, aux.nome) != 4)
				continue;
			Inserir(&primeiro, &ultimo, aux);
			break;

		case OPT_LIST:
			listar(primeiro);
			continue;

		case OPT_QUIT:
			exit(0);

		default:
			puts("unknown option");

		}
	}

	exit(0);
}

int Inserir (pessoa ** primeiro, pessoa ** ultimo, pessoa p)
{
	pessoa * aux = (pessoa *) malloc(sizeof(pessoa));
	if (aux == NULL)
		return 0;		// ERROR: out of memory
	
	*aux = p; /* copiar informacao para a memoria dinamica */

	if (*ultimo != NULL) /* a lista nao esta vazia */
	{
		(*ultimo) -> next = aux;
		*ultimo = aux;
		return 1;
	}
	*primeiro = aux;
	*ultimo = aux;

	return 1;
}

void Apagar (pessoa ** primeiro, pessoa ** ultimo)
{
	pessoa * aux;
	if (*primeiro == NULL)	/* lista esta vazia */
		return;

	aux = *primeiro;
	*primeiro = aux -> next; /* alteramos o primeiro */

	if (*primeiro == NULL) /* se a lista ficou vazia, actualizamos também o ultimo */
		*ultimo = NULL;

	/* libertamos a memoria que deixa de ser necessaria */
	free(aux);
}

void listar(pessoa * primeiro)
{
	pessoa * t;

	for (t = primeiro ; t != NULL ; t = t -> next)
	{
		printf("%s %d %s\n", t->nr, t->id, t->nome);
	}
}