#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "mccalc.h"

void _pmatrix(uint64_t **storage, size_t size);


void _test(uint64_t **(*mount)(const uint64_t *, size_t size), const uint64_t *arg, size_t size);


int main(void) {


    printf("\n\nTEST 1: \n");
    uint64_t p0[] = {2, 5, 2, 10, 2, 10, 2};

    _test(&mccalc, p0, 6);

    printf("\n\nTEST 2: \n");
    uint64_t p1[] = {4,15,5,10,20,25};

    _test(&mccalc, p1, 5);

    return 0;

}


void _test(uint64_t **(*mount)(const uint64_t *, size_t size), const uint64_t *arg, size_t size) {

    uint64_t ** storage = mount(arg, size);

    printf("\nRESULT:\n");
    _pmatrix(storage,size);
}

void _pmatrix(uint64_t **storage, size_t size) {

    uint64_t num;
    uint64_t width;

    printf("\n");
    for (uint64_t k = 0; k < size; ++k) {
        printf("%d         ", (unsigned int)k);
    }
    printf("\n");
    printf("\n");

    for (uint64_t i = 0; i < size; i++) {
        for (uint64_t j = 0; j < size; j++) {
            num = storage[i][j];
            width = 10 - ((uint64_t) floor(log10(abs((unsigned int)num))) + 1);
            printf("%d%*.*s", (unsigned int)num, (unsigned int)width, (unsigned int)width, " ");
        }
        printf(" | %d", (unsigned int)i);
        printf("\n");
    }
}




