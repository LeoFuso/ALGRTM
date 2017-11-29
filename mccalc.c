/*
 * File:   mccalc.c
 * Author: lfuso
 * From: https://github.com/LeoFuso/mccalc
 *
 * Created on 2017-11-28
 */

#include "mccalc.h"

struct _base * _cbase(const uint64_t *p,size_t size);
uint64_t **_cstorage(size_t size);
void _run(uint64_t **storage, struct _base *base);

struct _matrix
{
    uint64_t line;
    uint64_t column;
};

struct _base
{
    size_t n_matrix;
    struct _matrix **matrix;
};

uint64_t ** mccalc(const uint64_t *p, size_t size)
{
    struct _base * base = _cbase(p, size);
    uint64_t ** storage = _cstorage(size);
    _run(storage,base);

    return storage;
}

void _run(uint64_t **storage, struct _base *base)
{
    double vfloor;

    uint64_t offset = 0;
    uint64_t _kvalue = 0;
    uint64_t result;
    uint64_t k;

    uint64_t j = 0;
    uint64_t i = 0;

    while(i < base->n_matrix)
    {
        if (i < j)
        {
            vfloor = INFINITY;

            for (k = i; k < j; ++k)
            {
                uint64_t a_1 = storage[i][k];
                uint64_t a_2 = storage[++k][j];

                uint64_t _m = base->matrix[i]->line;
                uint64_t _n = base->matrix[k]->column;
                uint64_t _p = base->matrix[j]->column;

                result = a_1 + a_2 + (_m * _n * _p);

                if (result <= vfloor){
                    vfloor = result;
                    _kvalue = k;
                }
            }
            storage[i][j] = (uint64_t)vfloor;
            storage[(base->n_matrix-1) - i][(base->n_matrix-1) - j] = _kvalue;
        }

        if(i < base->n_matrix - 1 && j < base->n_matrix - 1){
            j++;
            i++;
        }else if(i == base->n_matrix - 1 || j == base->n_matrix - 1){
            i = 0;
            j = ++offset;
        }

        if(j == base->n_matrix)
            break;
    }
}

struct _matrix * _cmatrix(uint64_t line, uint64_t column)
{
    struct _matrix *new_matrix = NULL;
    new_matrix = (struct _matrix *) malloc(sizeof(struct _matrix));
    new_matrix->line = line;
    new_matrix->column = column;

    return new_matrix;
}

struct _base * _cbase(const uint64_t *p,size_t size)
{
    struct _base *base =
            (struct _base *) malloc(sizeof(struct _base));
    base->n_matrix = size;
    base->matrix = (struct _matrix **) malloc(size * sizeof(struct _matrix));

    for (uint64_t i = 0; i < base->n_matrix; ++i)
        base->matrix[i] = _cmatrix(p[i], p[++i]);

    return base;
}

uint64_t **_cstorage(size_t size)
{
    uint64_t **storage = (uint64_t **) malloc(size * sizeof(uint64_t *));
    for (uint64_t row = 0; row < size; row++)
        storage[row] = (uint64_t *) malloc(size * sizeof(uint64_t));

    return storage;
}