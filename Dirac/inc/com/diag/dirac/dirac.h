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
 * REFERENCES
 *
 * S. Boyd, L. Vandenberghe, INTRODUCTION TO APPLIED LINEAR ALGEBRA,
 * Cambridge University Press, 2018
 *
 * J. Kun, A PROGRAMMER"S INTRODUCTION TO MATHEMATICS, pimbook.org, 2020
 *
 * M. Siemens, "Quantum Computing for Curious Minds", University of
 * Denver, 2025-04
 *
 * Wikipedia, "Matrix (mathematics)", 2025-04-19
 *
 * Wikipedia, "Matrix multiplication", 2025-04-25
 *
 * Wikipedia, "Hadamard product (matrices)", 2025-04-25
 *
 * Wikipedia, "Kronecker product", 2025-04-23
 *
 * T. Wong, INTRODUCTION TO CLASSICAL AND QUANTUM COMPUTING, Rooted Grove,
 * 2022
 *
 * DISCLAIMER
 *
 * Any rational person would have written this in Python. But I wanted to
 * be able to incorporate some of this into the real-time/embedded systems
 * I develop in C. It also gave me an excuse to develop the object caching
 * code, which may eventually find its way mainstreamed into the Diminuto
 * systems programming library on which this depends.
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
#include "com/diag/diminuto/diminuto_containerof.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <complex.h>

/*******************************************************************************
 * TYPES
 ******************************************************************************/

typedef complex double dirac_complex_t;

typedef void dirac_matrix_t;

typedef struct DiracNode {
    diminuto_tree_t tree;
    size_t size;
} dirac_node_t;

typedef struct DiracData {
    size_t rows;
    size_t columns;
} dirac_data_t;

typedef union Dirac {
    struct {
        dirac_data_t head;
        dirac_complex_t body[0][0];
    } data;
    dirac_node_t node;
} dirac_t;

/*******************************************************************************
 * GETTORS
 ******************************************************************************/

static inline const dirac_complex_t * dirac_body_get(const dirac_t * that) {
    return &(that->data.body[0][0]);
}

static inline dirac_complex_t * dirac_body_mut(dirac_t * that) {
    return &(that->data.body[0][0]);
}

static inline const dirac_matrix_t * dirac_matrix_get(const dirac_t * that) {
    return (that != (const dirac_t *)0) ? (dirac_matrix_t *)dirac_body_get(that) : (const dirac_matrix_t *)0;
}

static inline dirac_matrix_t * dirac_matrix_mut(dirac_t * that) {
    return (that != (dirac_t *)0) ? (dirac_matrix_t *)dirac_body_mut(that) : (dirac_matrix_t *)0;
}

static inline const dirac_t * dirac_object_get(const dirac_matrix_t * them) {
    return (them != (const dirac_matrix_t *)0) ? diminuto_containerof(dirac_t, data.body[0][0], them) : (const dirac_t *)0;
}

static inline dirac_t * dirac_object_mut(dirac_matrix_t * them) {
    return (them != (dirac_matrix_t *)0) ? diminuto_containerof(dirac_t, data.body[0][0], them) : (dirac_t *)0;
}

static inline size_t dirac_rows_get(const dirac_matrix_t * them) {
    return dirac_object_get(them)->data.head.rows;
}

static inline size_t dirac_cols_get(const dirac_matrix_t * them) {
    return dirac_object_get(them)->data.head.columns;
}

/*******************************************************************************
 * INITIALIZERS AND FINALIZERS
 ******************************************************************************/

extern dirac_t * dirac_core_init(dirac_t * that, size_t rows, size_t columns);

static inline dirac_t * dirac_core_fini(dirac_t * that) {
    return that;
}

/*******************************************************************************
 * MEMORY MANAGEMENT
 ******************************************************************************/

extern dirac_t * dirac_object_allocate(size_t rows, size_t columns);

extern dirac_t * dirac_object_free(dirac_t * that);

static inline dirac_matrix_t * dirac_new_base(size_t rows, size_t columns) {
    return dirac_matrix_mut(dirac_core_allocate(rows, columns));
}

static inline void dirac_delete(dirac_matrix_t * them) {
    dirac_object_free(dirac_object_mut(them));
}

extern void dirac_free(void);

/*******************************************************************************
 * CODE GENERATORS
 ******************************************************************************/

#define dirac_new(_ROWS_, _COLS_) \
    ((dirac_complex_t (*)[_ROWS_][_COLS_])dirac_new_base(_ROWS_, _COLS_))

/*******************************************************************************
 * DEBUGGING
 ******************************************************************************/

extern dirac_t * dirac_audit(void);

extern ssize_t dirac_dump(FILE * fp);

extern const dirac_t * dirac_core_print(FILE * fp, const dirac_t * that);

static inline const dirac_t * dirac_print(FILE * fp, const dirac_matrix_t * them) {
    return dirac_core_print(fp, (them != (dirac_matrix_t)0) ? diminuto_containerof(dirac_t, data.body[0][0], them) : (dirac_t *)0);
}

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/

extern dirac_matrix_t * dirac_matrix_trn(const dirac_matrix_t * thema);

extern dirac_matrix_t * dirac_matrix_add(const dirac_matrix_t * thema, const dirac_matrix_t * themb);

extern dirac_matrix_t * dirac_matrix_sub(const dirac_matrix_t * thema, const dirac_matrix_t * themb);

extern dirac_matrix_t * dirac_matrix_mul(const dirac_matrix_t * thema, const dirac_matrix_t * themb);

extern dirac_matrix_t * dirac_matrix_had(const dirac_matrix_t * thema, const dirac_matrix_t * themb);

extern dirac_matrix_t * dirac_matrix_kro(const dirac_matrix_t * thema, const dirac_matrix_t * themb);

/*******************************************************************************
 * END
 ******************************************************************************/

#endif
