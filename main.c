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
void _do_stuff(int ** v_m, int ** k_m, struct Base * b);
struct Base *create_base(int n_matrix);
struct Matrix *create_matrix(int line, int column);
void print_base(struct Base *base);
void print_matrix(int **m, int n_line, int n_column);
int** create_table(int n_line, int n_column);

int main(void) {

    printf("\n\nTEST 1: \n");
    int p[] = {4,15,5,10,20,25};
    _test(&mount_base_matrix,p);
    return 0;

}

void _test(struct Base *(*mount)(const int *), const int *arg){

    struct Base *base = mount(arg);
    print_base(base);

    int** v_matrix = create_table(base->n_matrix, base->n_matrix);
    int** k_matrix = create_table(base->n_matrix, base->n_matrix);
    _do_stuff(v_matrix,k_matrix,base);
    print_matrix(v_matrix, base->n_matrix, base->n_matrix);


}

void _do_stuff(int ** v_m, int ** k_m, struct Base * b){
    int i = 0;
    int sum = 0;
    for (int j = 0; j < b->n_matrix; ++j) {
        if(i == j)
            v_m[j][i] = 0;
        else
            v_m[j][i] = 2;
        if(j == b->n_matrix-1 || i == b->n_matrix-1){
            j = -1;
            sum++;
            i = sum;
        }else{
            i++;
        }
        if(i == b->n_matrix)
            break;
    }
}

int** create_table(int n_line, int n_column){

    // allocate Rows rows, each row is a pointer to int
    int **table = (int **)malloc(n_line * sizeof(int *));

    // for each row allocate Cols ints
    for (int row = 0; row < n_line; row++)
        table[row] = (int *)malloc(n_column * sizeof(int));

    return table;
}

struct Base *mount_base_matrix(const int *p){

    int n_matrix = p[0];

    struct Base *base = create_base(n_matrix);
    for (int i = 1; i < base->n_matrix+1; ++i)
        base->matrix[i-1] = create_matrix(p[i], p[i+1]);
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

void print_matrix(int **m, int n_line, int n_column){
    for (int k = 0; k < n_column; ++k) {
            printf("%d ", k+1);
    }
    printf("\n");
    printf("\n");
    for (int i = 0; i < n_column; i++) {
        for (int j = 0; j < n_line; j++) {
            printf("%d ", m[i][j]);
        }
        printf("  %d ", i+1);
        printf("\n");
    }
}
void print_base(struct Base *base){

    struct Matrix *m = NULL;
    for (int i = 0; i < base->n_matrix; ++i) {
        m = base->matrix[i];
        printf("\nA%d: %d x %d",i+1,m->line,m->column);
    }
    m = NULL;

    printf("\n\n");
}



