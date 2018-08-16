#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define LINE_SIZE 120

typedef struct
{
	const char *name;
	const int age;
	const double height;
} Pessoa;

FILE *
_open(char *);

unsigned int
_count_lines(FILE *);

void
quick_sort(struct Pessoa **);

struct Pessoa **
populate(FILE *, unsigned int);

void
print_list(struct Pessoa **);

int
main(int argc, char *argv[])
{
	/*
	*  Try to read the file
	*/
	if (argc!=2)
	{
		printf("Syntax: main [file] \n");
		printf("No file specified. Closing program ... \n");
		exit(0);
	}

	FILE *filePointer;
	struct Pessoa **pessoas = NULL;
	unsigned int n_lines = 0;

	filePointer = _open(argv[1]);

	if (filePointer==NULL)
	{
		printf("Unexpected behavior: main.c 34 - Closing...");
		exit(1);
	}
	else
		printf("\nName file '%s' opened successfully.\n", argv[1]);

	n_lines = _count_lines(filePointer);
	pessoas = populate(filePointer, n_lines);

	quick_sort(pessoas);
	print_list(pessoas);

	return 0;
}

FILE *
_open(char *path)
{
	FILE *filePointer;

	if ((filePointer = fopen(path, "r"))==NULL)
	{
		printf("File not found.\n");
		exit(0);
	}

	/*
	 *  Checks if the file is empty
	 */
	fseek(filePointer, 0, SEEK_END);

	if (ftell(filePointer)==0)
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
	raw_line = (char *) malloc(LINE_SIZE*sizeof(char) + 1);

	/*
	 *  Count how many lines the file has
	 */
	while (fgets(raw_line, LINE_SIZE, filePtr)!=NULL)
		n_lines++;

	/*
	 *  Rewind file
	 */
	rewind(filePtr);

	free(raw_line);
	return n_lines;
}

struct Pessoa **
populate(FILE *filePointer, unsigned int n_lines)
{
	if (n_lines%3!=0)
	{
		printf("Number of lines in file is illegal - Closing...");
		exit(1);
	}

	unsigned int n_pessoas = n_lines/3;
	char *raw_line = NULL;
	struct Pessoa **pessoas = NULL;
	struct Pessoa * pessoa = NULL;

	pessoas = (struct Pessoa **) malloc(n_pessoas * sizeof(struct Pessoa*));
	raw_line = (char *) malloc(LINE_SIZE * sizeof(char) + 1);

	unsigned int l_num;
	for (l_num = 1; (fgets(raw_line, LINE_SIZE, filePointer) != NULL); ++l_num)
	{
		/*
		 *  It does the exchange of '\n' for '\0'
		 */
		if (strchr(raw_line, '\n') != NULL)
			*(strchr(raw_line, '\n')) = '\0';

		/*
		 *  Produces the Tokens using the line information
		 */
	}

}