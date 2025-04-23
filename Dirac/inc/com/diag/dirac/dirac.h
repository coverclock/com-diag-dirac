/* vi: set ts=4 expandtab shiftwidth=4: */
#ifndef _H_COM_DIAG_DIRAC_
#define _H_COM_DIAG_DIRAC_

/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * Licensed under the terms in LICENSE.txt.
 *
 * Defines the public API for Dirac, a library that supports matrix
 * arithmetic using complex numbers.
 *
 * Any rational person would have written this in Python. But I wanted to
 * be able to incorporate some of this into the real-time/embedded systems
 * I develop in C. It also gave me an excuse to develop the object caching
 * code, which may eventually find its way mainstreamed into the Diminuto
 * systems programming library on which this depends.
 *
 * REFERENCES
 *
 * This work was inspired by the course "Quantum Computing for Curious
 * Minds" [Mark Siemens, Physics and Astronomy, University of Denver]
 * which I took in April 2025.
 *
 * NOTES
 *
 * From the "complex" (7) man page:
 *
 *  Given z = a+b*i and w = c+d*i then
 *
 *      z+w = (a+c) + (b+d)*i
 *
 *      z*w = (a*c - b*d) + (a*d + b*c)*i
 *
 *      z/w = ((a*c + b*d)/(c*c + d*d)) + ((b*c - a*d)/(c*c + d*d))*i
 */

/*******************************************************************************
 * PREREQUISITES
 ******************************************************************************/

#include "com/diag/diminuto/diminuto_tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <complex.h>

/*******************************************************************************
 * TYPES
 ******************************************************************************/

typedef complex double dirac_complex_t;

typedef struct DiracNode {
    diminuto_tree_t tree;
    size_t size;
} dirac_node_t;

typedef struct DiracData {
    size_t rows;
    size_t columns;
    dirac_complex_t matrix[0];
} dirac_data_t;

typedef union Dirac {
    dirac_node_t node;
    dirac_data_t data;
} dirac_t;

/*******************************************************************************
 * MACROS
 ******************************************************************************/

#define DIRAC_ARRAY_TYPE(_TYPE_, _ROWS_, _COLS_) typedef dirac_complex_t (_TYPE_)[_ROWS_][_COLS_]

#define DIRAC_ARRAY_POINTER(_TYPE_, _THAT_) ((_TYPE_ *)(&((_THAT_)->data.matrix)))

/*******************************************************************************
 * MEMORY MANAGEMENT
 ******************************************************************************/

extern dirac_t * dirac_new(size_t rows, size_t columns);

extern dirac_t * dirac_delete(dirac_t * that);

extern void dirac_free(void);

/*******************************************************************************
 * INDEXING
 ******************************************************************************/

static inline size_t dirac_index(dirac_t * that, unsigned int row, unsigned int column) {
    return (row * that->data.columns) + column;
}

static inline dirac_complex_t * dirac_point_fast(dirac_t * that, unsigned int row, unsigned int column) {
    return &(that->data.matrix[dirac_index(that, row, column)]);
}

extern dirac_complex_t * dirac_point_slow(dirac_t * that, unsigned int row, unsigned int column);

static inline dirac_complex_t * dirac_point(dirac_t * that, unsigned int row, unsigned int column) {
#if defined(DEBUG)
    return dirac_point_slow(that, row, column);
#else
    return dirac_point_fast(that, row, column);
#endif
}

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/

/*******************************************************************************
 * AUDITING
 ******************************************************************************/

extern dirac_t * dirac_audit(void);

extern void dirac_dump(FILE * fp);

#endif
