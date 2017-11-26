#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Matrix{
    int line;
    int column;
};

struct Base{
    int n_matrix;
    struct Matrix **matrix;
};

struct Base *mount_base_matrix(const int*);
void _test(struct Base *(*mount)(const int *), const int *);
struct Base *create_base(int n_matrix);
struct Matrix *create_matrix(int line, int column);
void print_matrix(struct Base *base);

int main(void) {

    printf("\n\nTEST 1: \n");
    int p[] = {4,15,5,10,20,25};
    _test(&mount_base_matrix,p);
    return 0;

}

void _test(struct Base *(*mount)(const int *), const int *arg){

    struct Base *base = mount(arg);
    print_matrix(base);
    

}

struct Base *mount_base_matrix(const int *p){

    int n_matrix = p[0];

    struct Base *base = create_base(n_matrix);
    for (int i = 1; i < base->n_matrix+1; ++i) base->matrix[i-1] = create_matrix(p[i], p[i+1]);
    return base;
}

struct Base *create_base(int n_matrix){

    struct Base *base =
            (struct Base *) malloc(sizeof(struct Base));
    base->n_matrix = n_matrix;
    base->matrix = (struct Matrix **) malloc(n_matrix * sizeof(struct Matrix));

    return base;
}

struct Matrix *create_matrix(int line, int column){

    struct Matrix *new_matrix = NULL;

    new_matrix = (struct Matrix *)malloc(sizeof(struct Matrix));
    new_matrix->line = line;
    new_matrix->column = column;

    return new_matrix;
}

void print_matrix(struct Base *base){

    struct Matrix *m = NULL;
    for (int i = 0; i < base->n_matrix; ++i) {
        m = base->matrix[i];
        printf("\nA%d: %d x %d",i+1,m->line,m->column);
    }
    m = NULL;

    printf("\n\n");
}



