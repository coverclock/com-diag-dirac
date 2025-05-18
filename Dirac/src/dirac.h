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

static inline size_t dirac_rows_get(const dirac_matrix_t * them) {
    return dirac_object_get(them)->data.head.rows;
}

static inline size_t dirac_cols_get(const dirac_matrix_t * them) {
    return dirac_object_get(them)->data.head.columns;
}

/*******************************************************************************
 * HELPERS
 ******************************************************************************/

static inline dirac_t * dirac_new_dup(const dirac_t * thata) {
    return dirac_new(dirac_rows_get(thata), dirac_cols_get(thata));
}

static inline dirac_t * dirac_new_trn(const dirac_t * thata) {
    return dirac_new(dirac_cols_get(thata), dirac_rows_get(thata));
}

static inline dirac_t * dirac_new_sum(const dirac_t * thata, const dirac_t * thatb) {
    dirac_t * that = (dirac_t *)0;
    if (dirac_rows_get(thata) != dirac_rows_get(thatb)) {
        errno = EINVAL;
    } else if (dirac_cols_get(thata) != dirac_cols_get(thatb)) {
        errno = EINVAL;
    } else {
        that = dirac_new(dirac_rows_get(thata), dirac_cols_get(thatb));
    }
    return that;
}

static inline dirac_t * dirac_new_pro(const dirac_t * thata, const dirac_t * thatb) {
    dirac_t * that = (dirac_t *)0;
    if (dirac_cols_get(thata) != dirac_rows_get(thatb)) {
        errno = EINVAL;
    } else {
        that = dirac_new(dirac_cols_get(thata), dirac_rows_get(thatb));
    }
    return that;
}

/* Kronecker product */
static inline dirac_t * dirac_new_kro(const dirac_t * thata, const dirac_t * thatb) {
    return dirac_new(dirac_rows_get(thata) * dirac_rows_get(thatb), dirac_cols_get(thata) * dirac_cols_get(thatb));
}

/* Hadamard product */
static inline dirac_t * dirac_new_had(const dirac_t * thata, const dirac_t * thatb) {
    dirac_t * that = (dirac_t *)0;
    if (dirac_rows_get(thata) != dirac_rows_get(thatb)) {
        errno = EINVAL;
    } else if (dirac_cols_get(thata) != dirac_cols_get(thatb)) {
        errno = EINVAL;
    } else {
        that = dirac_new(dirac_rows_get(thata), dirac_cols_get(thatb));
    }
    return that;
}

/*******************************************************************************
 * INDEXING AND POINTING
 ******************************************************************************/

static inline size_t dirac_index(const dirac_t * that, unsigned int row, unsigned int column) {
    return (row * dirac_cols_get(that)) + column;
}

static inline dirac_complex_t * dirac_point_fast(dirac_t * that, unsigned int row, unsigned int column) {
    return &((dirac_body_mut(that))[dirac_index(that, row, column)]);
}

extern dirac_complex_t * dirac_point_safe(dirac_t * that, unsigned int row, unsigned int column);

static inline dirac_complex_t * dirac_point(dirac_t * that, unsigned int row, unsigned int column) {
#if defined(DEBUG)
    return dirac_point_safe(that, row, column);
#else
    return dirac_point_fast(that, row, column);
#endif
}

#endif
