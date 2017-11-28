#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Matrix {
    unsigned int line;
    unsigned int column;
};

struct Base {
    unsigned int n_matrix;
    struct Matrix **matrix;
};

struct Base *mount_base_matrix(const unsigned int *);
struct Base *create_base(unsigned int n_matrix);
struct Matrix *create_matrix(unsigned int line, unsigned int column);
void print_base(struct Base *base);
void print_matrix(unsigned int **m, unsigned int n_line, unsigned int n_column, unsigned int offset);
unsigned int **create_table(unsigned int n_line, unsigned int n_column);

/* logic */
void _test(struct Base *(*mount)(const unsigned int *), const unsigned int *);
void _fill_table(unsigned int **v_m, unsigned int **k_m, struct Base *b);

int main(void) {

    printf("\n\nTEST 1: \n");
    //unsigned int p[] = {4,15,5,10,20,25};
    unsigned int p[] = {6, 2, 5, 2, 10, 2, 10, 2};

    _test(&mount_base_matrix, p);
    return 0;

}

void _fill_table(unsigned int **v_m, unsigned int **k_m, struct Base *b) {


    unsigned int offset = 0;
    double floor_value;
    unsigned int _k_value = 0;
    unsigned int result;
    unsigned int k;

    unsigned int j = 0;
    unsigned int i = 0;

    while(i < b->n_matrix){


        if (i < j) {

            floor_value = INFINITY;

            for (k = i; k < j; ++k) {

                unsigned int a_1 = v_m[i][k];
                unsigned int a_2 = v_m[k + 1][j];

                unsigned int _m = b->matrix[i]->line;
                unsigned int _n = b->matrix[k]->column;
                unsigned int _p = b->matrix[j]->column;

                result = a_1 + a_2 + (_m * _n * _p);

                if (result <= floor_value) {
                    floor_value = result;
                    _k_value = k;
                }
            }

            v_m[i][j] = (unsigned int)floor_value;
            k_m[i][j] = _k_value;

        }


        if(i < b->n_matrix - 1 && j < b->n_matrix - 1){
            j++;
            i++;
        }else if(i == b->n_matrix - 1 || j == b->n_matrix - 1){
            i = 0;
            j = ++offset;
        }

        if(j == b->n_matrix)
            break;
    }
}

void _test(struct Base *(*mount)(const unsigned int *), const unsigned int *arg) {

    struct Base *base = mount(arg);
    print_base(base);

    unsigned int **v_matrix = create_table(base->n_matrix, base->n_matrix);
    unsigned int **k_matrix = create_table(base->n_matrix, base->n_matrix);
    _fill_table(v_matrix, k_matrix, base);
    printf("VALUE MATRIX:\n");
    print_matrix(v_matrix, base->n_matrix, base->n_matrix, 0);
    printf("K-INDEX MATRIX:\n");
    print_matrix(k_matrix, base->n_matrix, base->n_matrix, 1);


}

unsigned int **create_table(unsigned int n_line, unsigned int n_column) {

    // allocate Rows rows, each row is a pointer to unsigned int
    unsigned int **table = (unsigned int **) malloc(n_line * sizeof(unsigned int *));

    // for each row allocate Cols ints
    for (unsigned int row = 0; row < n_line; row++)
        table[row] = (unsigned int *) malloc(n_column * sizeof(unsigned int));

    return table;
}

struct Base *mount_base_matrix(const unsigned int *p) {

    unsigned int n_matrix = p[0];

    struct Base *base = create_base(n_matrix);
    for (unsigned int i = 1; i < base->n_matrix + 1; ++i)
        base->matrix[i - 1] = create_matrix(p[i], p[i + 1]);
    return base;
}

struct Base *create_base(unsigned int n_matrix) {

    struct Base *base =
            (struct Base *) malloc(sizeof(struct Base));
    base->n_matrix = n_matrix;
    base->matrix = (struct Matrix **) malloc(n_matrix * sizeof(struct Matrix));

    return base;
}

struct Matrix *create_matrix(unsigned int line, unsigned int column) {

    struct Matrix *new_matrix = NULL;

    new_matrix = (struct Matrix *) malloc(sizeof(struct Matrix));
    new_matrix->line = line;
    new_matrix->column = column;

    return new_matrix;
}

void print_matrix(unsigned int **m, unsigned int n_line, unsigned int n_column, unsigned int offset) {

    printf("\n");
    for (unsigned int k = 0; k < n_column; ++k) {
        printf("%d         ", k + 1);
    }
    printf("\n");
    printf("\n");
    for (unsigned int i = 0; i < n_column; i++) {
        for (unsigned int j = 0; j < n_line; j++) {

            if (i > j) {
                printf("          ");
            } else if (i == j) {
                printf("0         ");
            } else {
                unsigned int num = m[i][j] + offset;
                unsigned int width = (unsigned int) floor(log10(abs(num))) + 1;
                printf("%d%*.*s", num, 10 - width, 10 - width, " ");
            }

        }
        printf(" | %d", i + 1);
        printf("\n");
    }
}

void print_base(struct Base *base) {

    struct Matrix *m = NULL;
    for (unsigned int i = 0; i < base->n_matrix; ++i) {
        m = base->matrix[i];
        printf("\nA%d: %d x %d", i + 1, m->line, m->column);
    }
    m = NULL;

    printf("\n\n");
}



