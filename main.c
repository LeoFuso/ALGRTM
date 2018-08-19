#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define LINE_SIZE 120

struct Pessoa
{
	char *name;
	int age;
	double height;
};
struct Lista
{
	unsigned int tamanho;
	struct Pessoa **pessoas;
};

FILE *
_open(char *);

int
comparator(const void *, const void *);

unsigned int
_count_lines(FILE *);

struct Lista *
populate(FILE *, unsigned int);

void
quick_sort(struct Lista *);
void
print_list(struct Lista *);

int
main(int argc, char *argv[])
{
	/*
	*  Try to read the file
	*/
	if (argc != 2)
	{
		printf("Syntax: main [file] \n");
		printf("No file specified. Closing program ... \n");
		exit(0);
	}

	FILE *filePointer;
	struct Lista *lista = NULL;

	unsigned int n_lines = 0;

	filePointer = _open(argv[1]);

	if (filePointer == NULL)
	{
		printf("Unexpected behavior: main.c 34 - Closing...");
		exit(1);
	}
	else
		printf("\nName file '%s' opened successfully.\n", argv[1]);

	n_lines = _count_lines(filePointer);
	lista = populate(filePointer, n_lines);

	printf("\nOriginal list: \n\n");
	/* Not sorted */
	print_list(lista);

	quick_sort(lista);

	/* Sorted */
	printf("\nSorted list: \n\n");
	print_list(lista);

	return 0;
}

FILE *
_open(char *path)
{
	FILE *filePointer;

	if ((filePointer = fopen(path, "r")) == NULL)
	{
		printf("File not found.\n");
		exit(0);
	}

	/*
	 *  Checks if the file is empty
	 */
	fseek(filePointer, 0, SEEK_END);

	if (ftell(filePointer) == 0)
	{
		printf("File is empty.\n");
		exit(0);
	}

	rewind(filePointer);
	return filePointer;
}

unsigned int
_count_lines(FILE *filePtr)
{
	unsigned int n_lines = 0;
	char *raw_line = NULL;

	/*
	 *  Allocates the memory space required for a program line
	 */
	raw_line = (char *) malloc(LINE_SIZE * sizeof(char) + 1);

	/*
	 *  Count how many lines the file has
	 */
	while (fgets(raw_line, LINE_SIZE, filePtr) != NULL)
		n_lines++;

	/*
	 *  Rewind file
	 */
	rewind(filePtr);

	free(raw_line);
	return n_lines;
}

struct Lista *
populate(FILE *filePointer, unsigned int n_lines)
{
	unsigned int n_pessoas = n_lines / 3;
	char *raw_line = NULL;

	struct Lista *lista = NULL;
	struct Pessoa **pessoas = NULL;
	struct Pessoa *pessoa = NULL;

	lista = (struct Lista *) malloc(sizeof(struct Lista));

	pessoas = (struct Pessoa **) malloc((n_pessoas + 1) * sizeof(struct Pessoa *));
	raw_line = (char *) malloc(LINE_SIZE * sizeof(char) + 1);

	unsigned int count;
	unsigned int l_num;
	for (l_num = 1, count = 0, n_pessoas = 0; (fgets(raw_line, LINE_SIZE, filePointer) != NULL); ++l_num)
	{
		/*
		 *  It does the exchange of '\n' for '\0'
		 */
		if (strchr(raw_line, '\n') != NULL)
			*(strchr(raw_line, '\n')) = '\0';

		/*
		 *  Produces the Pessoa struct using the line information
		 */
		switch (count)
		{
			case 0: pessoa = (struct Pessoa *) malloc(sizeof(struct Pessoa));
				pessoa->name = (char *) malloc(strlen(raw_line) * sizeof(char));
				strcpy(pessoa->name, raw_line);
				break;
			case 1: pessoa->age = (int) strtol(raw_line, (char **) NULL, 10);
				break;
			case 2: pessoa->height = (double) strtod(raw_line, (char **) NULL);
				break;
			default: printf("Unexpected behavior: main.c 152 - Closing...");
				exit(1);
		}

		if (count != 2)
			count++;
		else
		{
			pessoas[n_pessoas++] = pessoa;
			count = 0;
		}

	}
	lista->tamanho = n_pessoas;
	lista->pessoas = pessoas;
	return lista;
}

void
quick_sort(struct Lista *lista)
{
    /* unwrap for quick sort */
    struct Pessoa ** pessoas = lista->pessoas;
    unsigned int size = lista->tamanho;
	qsort(pessoas, size, sizeof(pessoas[0]), comparator);
}

void
print_list(struct Lista *lista)
{
	unsigned int i;
	for (i = 0; i < lista->tamanho; i++)
	{
		printf(" NOME: %s\n", lista->pessoas[i]->name);
		printf(" IDADE: %d\n", lista->pessoas[i]->age);
		printf(" ALTURA: %.2f\n", lista->pessoas[i]->height);
		printf("--------------------------\n\n");
	}
}

int
comparator(const void *p1, const void *p2)
{
	struct Pessoa * o1 = *(struct Pessoa **) p1;
	struct Pessoa * o2 = *(struct Pessoa **) p2;

	if (o1->height > o2->height)
		return 1;
	else if (o1->height  < o2->height)
		return -1;
	else
		return 0;
}
