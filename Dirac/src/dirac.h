/* vi: set ts=4 expandtab shiftwidth=4: */
#ifndef _H_COM_DIAG_DIRAC_PRIVATE_
#define _H_COM_DIAG_DIRAC_PRIVATE_

/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA<BR>
 * Licensed under the terms in LICENSE.txt<BR>
 * Chip Overclock (mailto:coverclock@diag.com)<BR>
 * https://github.com/coverclock/com-diag-codex<BR>
 *
 * Defines the privae API for Dirac.
 */

#include "com/diag/diminuto/diminuto_containerof.h"

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

extern dirac_t * dirac_core_allocate(size_t rows, size_t columns);

extern dirac_t * dirac_core_free(dirac_t * that);

/*******************************************************************************
 * GETTORS
 ******************************************************************************/

static inline size_t dirac_core_rows_get(const dirac_t * that) {
    return that->data.head.rows;
}

static inline size_t dirac_core_cols_get(const dirac_t * that) {
    return that->data.head.columns;
}

static inline const dirac_complex_t * dirac_core_body_get(const dirac_t * that) {
    return &(that->data.body[0][0]);
}

static inline dirac_complex_t * dirac_core_body_mut(dirac_t * that) {
    return &(that->data.body[0][0]);
}

static inline const dirac_matrix_t * dirac_core_matrix_get(const dirac_t * that) {
    return (that != (const dirac_t *)0) ? (dirac_matrix_t *)dirac_core_body_get(that) : (const dirac_matrix_t *)0;
}

static inline dirac_matrix_t * dirac_core_matrix_mut(dirac_t * that) {
    return (that != (dirac_t *)0) ? (dirac_matrix_t *)dirac_core_body_mut(that) : (dirac_matrix_t *)0;
}

static inline const dirac_t * dirac_core_object_get(const dirac_matrix_t * them) {
    return (them != (const dirac_matrix_t *)0) ? diminuto_containerof(dirac_t, data.body[0][0], them) : (const dirac_t *)0;
}

static inline dirac_t * dirac_core_object_mut(dirac_matrix_t * them) {
    return (them != (dirac_matrix_t *)0) ? diminuto_containerof(dirac_t, data.body[0][0], them) : (dirac_t *)0;
}

/*******************************************************************************
 * ALLOCATORS
 ******************************************************************************/

extern dirac_t * dirac_core_dup(const dirac_t * thata);

extern dirac_t * dirac_core_trn(const dirac_t * thata);

extern dirac_t * dirac_core_sum(const dirac_t * thata, const dirac_t * thatb);

extern dirac_t * dirac_core_pro(const dirac_t * thata, const dirac_t * thatb);

extern dirac_t * dirac_core_kro(const dirac_t * thata, const dirac_t * thatb);

extern dirac_t * dirac_core_had(const dirac_t * thata, const dirac_t * thatb);

/*******************************************************************************
 * INDEXING AND POINTING
 ******************************************************************************/

static inline size_t dirac_core_index(const dirac_t * that, unsigned int row, unsigned int column) {
    return (row * dirac_core_cols_get(that)) + column;
}

static inline dirac_complex_t * dirac_core_point_fast(dirac_t * that, unsigned int row, unsigned int column) {
    return &((dirac_core_body_mut(that))[dirac_core_index(that, row, column)]);
}

extern dirac_complex_t * dirac_core_point_safe(dirac_t * that, unsigned int row, unsigned int column);

static inline dirac_complex_t * dirac_core_point(dirac_t * that, unsigned int row, unsigned int column) {
#if defined(DEBUG)
    return dirac_core_point_safe(that, row, column);
#else
    return dirac_core_point_fast(that, row, column);
#endif
}

/*******************************************************************************
 * DEBUGGING
 ******************************************************************************/

extern const dirac_t * dirac_core_print(FILE * fp, const dirac_t * that);

/*******************************************************************************
 * END
 ******************************************************************************/

#endif
