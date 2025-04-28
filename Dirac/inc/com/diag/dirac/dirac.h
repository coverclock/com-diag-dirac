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
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <complex.h>

/*******************************************************************************
 * CODE GENERATORS
 ******************************************************************************/

#define DIRAC_ARRAY_TYPE(_TYPE_, _ROWS_, _COLS_) typedef dirac_complex_t (_TYPE_)[_ROWS_][_COLS_]

#define DIRAC_ARRAY_POINTER(_TYPE_, _THAT_) ((_TYPE_ *)(&((_THAT_)->data.body)))

#define DIRAC_OBJECT_DECL(_ROWS_, _COLS_) \
    union { \
        struct { \
            dirac_data_t head; \
            dirac_complex_t body[(_ROWS_) * (_COLS_)]; \
        } data; \
        dirac_node_t node; \
    }

#define DIRAC_OBJECT_INIT(_ROWS_, _COLS_) \
    { { { _ROWS_, _COLS_ } } }

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
} dirac_data_t;

typedef DIRAC_OBJECT_DECL(0, 0) dirac_t;

/*******************************************************************************
 * GETTORS AND MUTATORS
 ******************************************************************************/

static inline size_t dirac_rows_get(const dirac_t * that) {
    return that->data.head.rows;
}

static inline size_t dirac_columns_get(const dirac_t * that) {
    return that->data.head.columns;
}

static inline const dirac_complex_t * dirac_body_get(const dirac_t * that) {
    return &(that->data.body[0]);
}

static inline dirac_complex_t * dirac_body_mut(dirac_t * that) {
    return &(that->data.body[0]);
}

/*******************************************************************************
 * MEMORY MANAGEMENT
 ******************************************************************************/

extern dirac_t * dirac_new(size_t rows, size_t columns);

extern dirac_t * dirac_delete(dirac_t * that);

extern void dirac_free(void);

/*******************************************************************************
 * INDEXING AND POINTING
 ******************************************************************************/

static inline size_t dirac_index(const dirac_t * that, unsigned int row, unsigned int column) {
    return (row * dirac_columns_get(that)) + column;
}

static inline dirac_complex_t * dirac_point_fast(dirac_t * that, unsigned int row, unsigned int column) {
    return &(that->data.body[dirac_index(that, row, column)]);
}

extern dirac_complex_t * dirac_point_safe(dirac_t * that, unsigned int row, unsigned int column);

static inline dirac_complex_t * dirac_point(dirac_t * that, unsigned int row, unsigned int column) {
#if defined(DEBUG)
    return dirac_point_safe(that, row, column);
#else
    return dirac_point_fast(that, row, column);
#endif
}

/*******************************************************************************
 * AUDITING
 ******************************************************************************/

extern dirac_t * dirac_audit(void);

extern ssize_t dirac_dump(FILE * fp);

/*******************************************************************************
 * HELPERS
 ******************************************************************************/

static inline dirac_t * dirac_new_dup(const dirac_t * thata) {
    return dirac_new(dirac_rows_get(thata), dirac_columns_get(thata));
}

static inline dirac_t * dirac_new_trn(const dirac_t * thata) {
    return dirac_new(dirac_columns_get(thata), dirac_rows_get(thata));
}

static inline dirac_t * dirac_new_sum(const dirac_t * thata, const dirac_t * thatb) {
    dirac_t * that = (dirac_t *)0;
    if (dirac_rows_get(thata) != dirac_rows_get(thatb)) {
        errno = EINVAL;
    } else if (dirac_columns_get(thata) != dirac_columns_get(thatb)) {
        errno = EINVAL;
    } else {
        that = dirac_new(dirac_rows_get(thata), dirac_columns_get(thatb));
    }
    return that;
}

static inline dirac_t * dirac_new_pro(const dirac_t * thata, const dirac_t * thatb) {
    dirac_t * that = (dirac_t *)0;
    if (dirac_columns_get(thata) != dirac_rows_get(thatb)) {
        errno = EINVAL;
    } else {
        that = dirac_new(dirac_columns_get(thata), dirac_rows_get(thatb));
    }
    return that;
}

/* Kronecker product */
static inline dirac_t * dirac_new_kro(const dirac_t * thata, const dirac_t * thatb) {
    return dirac_new(dirac_rows_get(thata) * dirac_rows_get(thatb), dirac_columns_get(thata) * dirac_columns_get(thatb));
}

/* Hadamard product */
static inline dirac_t * dirac_new_had(const dirac_t * thata, const dirac_t * thatb) {
    dirac_t * that = (dirac_t *)0;
    if (dirac_rows_get(thata) != dirac_rows_get(thatb)) {
        errno = EINVAL;
    } else if (dirac_columns_get(thata) != dirac_columns_get(thatb)) {
        errno = EINVAL;
    } else {
        that = dirac_new(dirac_rows_get(thata), dirac_columns_get(thatb));
    }
    return that;
}

/*******************************************************************************
 * UTILITIES
 ******************************************************************************/

extern void dirac_matrix_print(FILE * fp, const dirac_t * that);

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/

extern dirac_t * dirac_matrix_trn(const dirac_t * thata);

extern dirac_t * dirac_matrix_add(const dirac_t * thata, const dirac_t * thatb);

extern dirac_t * dirac_matrix_sub(const dirac_t * thata, const dirac_t * thatb);

extern dirac_t * dirac_matrix_mul(const dirac_t * thata, const dirac_t * thatb);

/*******************************************************************************
 * END
 ******************************************************************************/

#endif
