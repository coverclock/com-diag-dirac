/* vi: set ts=4 expandtab shiftwidth=4: */
#ifndef _H_COM_DIAG_DIRAC_
#define _H_COM_DIAG_DIRAC_

/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * Licensed under the terms in LICENSE.txt.
 */

#include "com/diag/diminuto/diminuto_tree.h"
#include <stdlib.h>
#include <complex.h>

/*
 * From complex (7) man page:
 * 
 * Given z = a+b*i and w = c+d*i then
 *
 * z+w = (a+c) + (b+d)*i
 *
 * z*w = (a*c - b*d) + (a*d + b*c)*i
 *
 * z/w = ((a*c + b*d)/(c*c + d*d)) + ((b*c - a*d)/(c*c + d*d))*i
 */

/*******************************************************************************
 * DATA STRUCTURES
 ******************************************************************************/

typedef struct Dirac {
    union DiracField {
        struct DiracNode {
            diminuto_tree_t tree;
            size_t size;
        } node;
        struct DiracData {
            size_t rows;
            size_t columns;
            complex double matrix[0];
        } data;
    } field;
} dirac_t;

/*******************************************************************************
 * MEMORY MANAGEMENT
 ******************************************************************************/

static inline size_t dirac_matrix_payload(size_t rows, size_t columns) {
    return rows * columns * sizeof(complex double);
}

static inline size_t dirac_matrix_size(size_t rows, size_t columns) {
    return sizeof(dirac_t) + dirac_matrix_payload(rows, columns);
}

extern dirac_t * dirac_matrix_alloc(size_t rows, size_t columns);

static inline void dirac_matrix_free(dirac_t * that) {
    free(that);
}

extern dirac_t * dirac_matrix_init(dirac_t * that, size_t rows, size_t columns);

static inline dirac_t * dirac_matrix_fini(dirac_t * that) {
    return that;
}

extern dirac_t * dirac_matrix_new(size_t rows, size_t columns);

extern dirac_t * dirac_matrix_delete(dirac_t * that);

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/

#endif
