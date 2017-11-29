#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

struct Matrix {
    uint64_t line;
    uint64_t column;
};

struct Base {
    size_t n_matrix;
    struct Matrix **matrix;
};

struct Base *mount_base_matrix(const uint64_t *p, size_t size);
struct Base *create_base(size_t n_matrix);
struct Matrix *create_matrix(uint64_t line, uint64_t column);
void print_base(struct Base *base);
void print_matrix(uint64_t **m, uint64_t n_line, uint64_t n_column, uint64_t offset);
void print_matrix_2(uint64_t **m, uint64_t n_line, uint64_t n_column, uint64_t offset);
uint64_t **create_table(uint64_t n_line, uint64_t n_column);

/* logic */
void _test(struct Base *(*mount)(const uint64_t *, size_t size), const uint64_t *arg, size_t size);
void _fill_table(uint64_t **v_m, uint64_t **k_m, struct Base *b);

int main(void) {

    printf("\n\nTEST 1: \n");
    //uint64_t p[] = {4,15,5,10,20,25};
    uint64_t p[] = {2, 5, 2, 10, 2, 10, 2};

    _test(&mount_base_matrix, p, 6);
    return 0;

}

void _fill_table(uint64_t **v_m, uint64_t **k_m, struct Base *b) {


    uint64_t offset = 0;
    double floor_value;
    uint64_t _k_value = 0;
    uint64_t result;
    uint64_t k;

    uint64_t j = 0;
    uint64_t i = 0;

    while(i < b->n_matrix){


        if (i < j) {

            floor_value = INFINITY;

            for (k = i; k < j; ++k) {

                uint64_t a_1 = v_m[i][k];
                uint64_t a_2 = v_m[k + 1][j];

                uint64_t _m = b->matrix[i]->line;
                uint64_t _n = b->matrix[k]->column;
                uint64_t _p = b->matrix[j]->column;

                result = a_1 + a_2 + (_m * _n * _p);

                if (result <= floor_value) {
                    floor_value = result;
                    _k_value = k;
                }
            }

            v_m[i][j] = (uint64_t)floor_value;
            v_m[(b->n_matrix-1) - i][(b->n_matrix-1) - j] = _k_value+1;
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

void _test(struct Base *(*mount)(const uint64_t *, size_t size), const uint64_t *arg, size_t size) {

    struct Base *base = mount(arg, size);
    print_base(base);

    uint64_t **v_matrix = create_table(base->n_matrix, base->n_matrix);
    uint64_t **k_matrix = create_table(base->n_matrix, base->n_matrix);
    _fill_table(v_matrix, k_matrix, base);
    printf("VALUE MATRIX:\n");
    print_matrix_2(v_matrix, base->n_matrix, base->n_matrix, 0);
    printf("K-INDEX MATRIX:\n");
    print_matrix(k_matrix, base->n_matrix, base->n_matrix, 1);


}

uint64_t **create_table(uint64_t n_line, uint64_t n_column) {

    // allocate Rows rows, each row is a pointer to uint64_t
    uint64_t **table = (uint64_t **) malloc(n_line * sizeof(uint64_t *));

    // for each row allocate Cols ints
    for (uint64_t row = 0; row < n_line; row++)
        table[row] = (uint64_t *) malloc(n_column * sizeof(uint64_t));

    return table;
}

struct Base *mount_base_matrix(const uint64_t *p, size_t size) {

    size_t n_matrix = size;

    struct Base *base = create_base(n_matrix);
    for (uint64_t i = 0; i < base->n_matrix; ++i)
        base->matrix[i] = create_matrix(p[i], p[i + 1]);
    return base;
}

struct Base *create_base(size_t n_matrix) {

    struct Base *base =
            (struct Base *) malloc(sizeof(struct Base));
    base->n_matrix = n_matrix;
    base->matrix = (struct Matrix **) malloc(n_matrix * sizeof(struct Matrix));

    return base;
}

struct Matrix *create_matrix(uint64_t line, uint64_t column) {

    struct Matrix *new_matrix = NULL;

    new_matrix = (struct Matrix *) malloc(sizeof(struct Matrix));
    new_matrix->line = line;
    new_matrix->column = column;

    return new_matrix;
}

void print_matrix(uint64_t **m, uint64_t n_line, uint64_t n_column, uint64_t offset) {

    uint64_t num;
    uint64_t width;

    printf("\n");
    for (uint64_t k = 0; k < n_column; ++k) {
        printf("%d         ", k + 1);
    }
    printf("\n");
    printf("\n");
    for (uint64_t i = 0; i < n_column; i++) {
        for (uint64_t j = 0; j < n_line; j++) {

            if (i > j)
                printf("          ");
            else if (i == j)
                printf("0         ");
            else {
                num = m[i][j] + offset;
                width = 10 - ((uint64_t) floor(log10(abs(num))) + 1);
                printf("%d%*.*s", num, width,width, " ");
            }

        }
        printf(" | %d", i + 1);
        printf("\n");
    }
}

void print_matrix_2(uint64_t **m, uint64_t n_line, uint64_t n_column, uint64_t offset) {

    uint64_t num;
    uint64_t width;

    printf("\n");
    for (uint64_t k = 0; k < n_column; ++k) {
        printf("%d         ", k + 1);
    }
    printf("\n");
    printf("\n");
    for (uint64_t i = 0; i < n_column; i++) {
        for (uint64_t j = 0; j < n_line; j++) {
            num = m[i][j] + offset;
            width = 10 - ((uint64_t) floor(log10(abs(num))) + 1);
            printf("%d%*.*s", num, width, width, " ");
        }
        printf(" | %d", i + 1);
        printf("\n");
    }
}

void print_base(struct Base *base) {

    struct Matrix *m = NULL;
    for (size_t i = 0; i < base->n_matrix; ++i) {
        m = base->matrix[i];
        printf("\nA%d: %d x %d", (uint64_t)i + 1, m->line, m->column);
    }
    m = NULL;

    printf("\n\n");
}



