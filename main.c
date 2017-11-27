#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Matrix {
    int line;
    int column;
};

struct Base {
    int n_matrix;
    struct Matrix **matrix;
};

struct Base *mount_base_matrix(const int *);
struct Base *create_base(int n_matrix);
struct Matrix *create_matrix(int line, int column);
void print_base(struct Base *base);
void print_matrix(int **m, int n_line, int n_column, int offset);
int **create_table(int n_line, int n_column);

/* logic */
void _test(struct Base *(*mount)(const int *), const int *);
void _fill_table(int **v_m, int **k_m, struct Base *b);

int main(void) {

    printf("\n\nTEST 1: \n");
    //int p[] = {4,15,5,10,20,25};
    int p[] = {6, 2, 5, 2, 10, 2, 10, 2};

    _test(&mount_base_matrix, p);
    return 0;

}

void _fill_table(int **v_m, int **k_m, struct Base *b) {
    int i = 0;
    int sum = 0;
    for (int j = 0; j < b->n_matrix; ++j) {

        if (i != j) {

            int floor = INFINITY;
            int k_index;
            int result;
            int k;
            for (k = j; k < i; ++k) {

                int a_1 = v_m[j][k];
                int a_2 = v_m[k + 1][i];

                int _m = b->matrix[j]->line;
                int _n = b->matrix[k]->column;
                int _p = b->matrix[i]->column;

                result = a_1 + a_2 + (_m * _n * _p);

                if (result <= floor) {
                    floor = result;
                    k_index = k;
                }
            }

            v_m[j][i] = floor;
            k_m[j][i] = k_index;

        }

        if (j == b->n_matrix - 1 || i == b->n_matrix - 1) {
            j = -1;
            sum++;
            i = sum;
        } else {
            i++;
        }

        if (i == b->n_matrix)
            break;
    }
}

void _test(struct Base *(*mount)(const int *), const int *arg) {

    struct Base *base = mount(arg);
    print_base(base);

    int **v_matrix = create_table(base->n_matrix, base->n_matrix);
    int **k_matrix = create_table(base->n_matrix, base->n_matrix);
    _fill_table(v_matrix, k_matrix, base);
    printf("VALUE MATRIX:\n");
    print_matrix(v_matrix, base->n_matrix, base->n_matrix, 0);
    printf("K-INDEX MATRIX:\n");
    print_matrix(k_matrix, base->n_matrix, base->n_matrix, 1);


}

int **create_table(int n_line, int n_column) {

    // allocate Rows rows, each row is a pointer to int
    int **table = (int **) malloc(n_line * sizeof(int *));

    // for each row allocate Cols ints
    for (int row = 0; row < n_line; row++)
        table[row] = (int *) malloc(n_column * sizeof(int));

    return table;
}

struct Base *mount_base_matrix(const int *p) {

    int n_matrix = p[0];

    struct Base *base = create_base(n_matrix);
    for (int i = 1; i < base->n_matrix + 1; ++i)
        base->matrix[i - 1] = create_matrix(p[i], p[i + 1]);
    return base;
}

struct Base *create_base(int n_matrix) {

    struct Base *base =
            (struct Base *) malloc(sizeof(struct Base));
    base->n_matrix = n_matrix;
    base->matrix = (struct Matrix **) malloc(n_matrix * sizeof(struct Matrix));

    return base;
}

struct Matrix *create_matrix(int line, int column) {

    struct Matrix *new_matrix = NULL;

    new_matrix = (struct Matrix *) malloc(sizeof(struct Matrix));
    new_matrix->line = line;
    new_matrix->column = column;

    return new_matrix;
}

void print_matrix(int **m, int n_line, int n_column, int offset) {

    printf("\n");
    for (int k = 0; k < n_column; ++k) {
        printf("%d         ", k + 1);
    }
    printf("\n");
    printf("\n");
    for (int i = 0; i < n_column; i++) {
        for (int j = 0; j < n_line; j++) {

            if (i > j) {
                printf("          ");
            } else if (i == j) {
                printf("0         ");
            } else {
                int num = m[i][j] + offset;
                int width = (int) floor(log10(abs(num))) + 1;
                printf("%d%*.*s", num, 10 - width, 10 - width, " ");
            }

        }
        printf(" | %d", i + 1);
        printf("\n");
    }
}

void print_base(struct Base *base) {

    struct Matrix *m = NULL;
    for (int i = 0; i < base->n_matrix; ++i) {
        m = base->matrix[i];
        printf("\nA%d: %d x %d", i + 1, m->line, m->column);
    }
    m = NULL;

    printf("\n\n");
}



