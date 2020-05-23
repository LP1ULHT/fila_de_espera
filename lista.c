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

typedef pessoa * FILA;

int Inserir (FILA *, pessoa);
void Apagar (FILA *);
void listar (FILA);

int main(int argc, char **argv)
{
	pessoa aux;
	FILA primeiro = NULL; // importante inicializar a lista a NULL
	FILE * fp = NULL;
	char input[DIM];
	char option;

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

		if (!Inserir(&primeiro, aux))
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
			Apagar(&primeiro);
			continue;

		case OPT_ADD:
			if (sscanf(input, " %c %s %d %[^\n]", &option, aux.nr, &aux.id, aux.nome) != 4)
				continue;
			Inserir(&primeiro, aux);

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

int Inserir (FILA * lista, pessoa p)
{
	pessoa * t;
	pessoa * aux = (pessoa *) malloc(sizeof(pessoa));
	if (aux == NULL)
		return 0;		// ERROR: out of memory
	strcpy(aux -> nome, p.nome);
	strcpy(aux -> nr, p.nr);
	aux -> id = p.id;
	aux -> next = NULL;

	if (*lista == NULL)
	{
		*lista = aux;
		return 1;
	}

	// percorrer a lista ate que o next seja NULL
	for (t = *lista ; t->next != NULL ; t = t -> next)
		; 

	t->next = aux;
	return 1;			// SUCCESS
}

void Apagar (FILA * lista)
{
	pessoa * aux;
	if (*lista == NULL)	// lista esta vazia
		return;

	aux = *lista;
	*lista = aux -> next; // alteramos o primeiro

	// libertamos a memoria que deixa de ser necessaria
	free(aux);
}

void listar(FILA lista)
{
	pessoa * t;

	for (t = lista ; t != NULL ; t = t -> next)
	{
		printf("%s %d %s\n", t->nr, t->id, t->nome);
	}
}