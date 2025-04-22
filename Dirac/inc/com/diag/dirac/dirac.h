/* vi: set ts=4 expandtab shiftwidth=4: */
#ifndef _H_COM_DIAG_DIRAC_
#define _H_COM_DIAG_DIRAC_

/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * Licensed under the terms in LICENSE.txt.
 *
 * Defines the public API for Dirac.
 */

#include "com/diag/diminuto/diminuto_tree.h"
#include <stdlib.h>
#include <stdio.h>
#include <complex.h>

/*******************************************************************************
 * DATA STRUCTURES
 ******************************************************************************/

typedef struct DiracNode {
    diminuto_tree_t tree;
    size_t size;
} dirac_node_t;

typedef struct DiracData {
    size_t rows;
    size_t columns;
    complex double matrix[0];
} dirac_data_t;

typedef union Dirac {
    dirac_node_t node;
    dirac_data_t data;
} dirac_t;

/*******************************************************************************
 * MEMORY MANAGEMENT
 ******************************************************************************/

static inline size_t dirac_count(size_t rows, size_t columns) {
    return rows * columns;
}

static inline size_t dirac_length(size_t rows, size_t columns) {
    return dirac_count(rows, columns) * sizeof(complex double);
}

static inline size_t dirac_size(size_t rows, size_t columns) {
    return dirac_length(rows, columns) + sizeof(dirac_t);
}

extern dirac_t * dirac_init(dirac_t * that, size_t rows, size_t columns);

static inline dirac_t * dirac_fini(dirac_t * that) {
    return that;
}

extern dirac_t * dirac_new(size_t rows, size_t columns);

extern dirac_t * dirac_delete(dirac_t * that);

/*******************************************************************************
 * AUDITING
 ******************************************************************************/

extern void dirac_audit(FILE * fp);

/*******************************************************************************
 * INDEXING
 ******************************************************************************/

static inline double complex * dirac_index_fast(dirac_t * that, size_t row, size_t column) {
    return &(that->data.matrix[(row * that->data.columns) + column]);
}

static inline double complex * dirac_index_slow(dirac_t * that, size_t row, size_t column) {
    double complex * here = (double complex *)0;
    if (row >= that->data.rows) {
        /* Do nothing. */
    } else if (column >= that->data.columns) {
        /* Do nothing. */
    } else {
        here = dirac_index_fast(that, row, column);
    }
    return here;
}

static inline double complex * dirac_index(dirac_t * that, size_t row, size_t column) {
#if defined(DEBUG)
    return dirac_index_slow(that, row, column);
#else
    return dirac_index_fast(that, row, column);
#endif
}

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/

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

#endif
