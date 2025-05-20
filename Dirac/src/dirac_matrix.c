/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA<BR>
 * Licensed under the terms in LICENSE.txt<BR>
 * Chip Overclock (mailto:coverclock@diag.com)<BR>
 * https://github.com/coverclock/com-diag-cdirac<BR>
 * This is the implementation of the matrix-related portions of Dirac.
 */

/*******************************************************************************
 * PREREQUISITES
 ******************************************************************************/

#include "com/diag/dirac/dirac.h"
#include "com/diag/diminuto/diminuto_error.h"
#include <errno.h>
#include "dirac.h"

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/

/*
 * Matrix operations may allocate (new) from the cache, but if they do so,
 * the resulting dynamically allocated object must either be explicitly
 * deallocated (delete) or returned to the caller. The only objects they may
 * deallocate back to the cache are objects they themselves allocate; this
 * allows the use of statically allocated (C stack) objects in
 * matrix operations.
 */

dirac_matrix_t * dirac_matrix_dup(const dirac_matrix_t * thema)
{
    const dirac_t * thata = dirac_core_object_get(thema);
	dirac_t * that = dirac_core_dup(thata); 
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_dup");
    } else {
        const dirac_complex_t * aa = dirac_core_body_get(thata);
        dirac_complex_t * tt = dirac_core_body_mut(that);
        size_t rows = dirac_core_rows_get(thata);
        size_t cols = dirac_core_cols_get(thata);
        int rr;
        int cc;
        int ii;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_core_index(thata, rr, cc);
                (tt)[ii] = (aa)[ii];
            }
        }
    } 
	return dirac_core_matrix_mut(that);
}

dirac_matrix_t * dirac_matrix_trn(const dirac_matrix_t * thema)
{
    const dirac_t * thata = dirac_core_object_get(thema);
	dirac_t * that = dirac_core_trn(thata); 
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_trn");
    } else {
        const dirac_complex_t * aa = dirac_core_body_get(thata);
        dirac_complex_t * tt = dirac_core_body_mut(that);
        size_t rows = dirac_core_rows_get(thata);
        size_t cols = dirac_core_cols_get(thata);
        int rr;
        int cc;
        int ii;
        int jj;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_core_index(thata, rr, cc);
                jj = dirac_core_index(that, cc, rr);
                (tt)[jj] = (aa)[ii];
            }
        }
    } 
	return dirac_core_matrix_mut(that);
}

dirac_matrix_t * dirac_matrix_add(const dirac_matrix_t * thema, const dirac_matrix_t * themb)
{
    const dirac_t * thata = dirac_core_object_get(thema);
    const dirac_t * thatb = dirac_core_object_get(themb);
	dirac_t * that = dirac_core_sum(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_add");
    } else {
        const dirac_complex_t * aa = dirac_core_body_get(thata);
        const dirac_complex_t * bb = dirac_core_body_get(thatb);
        dirac_complex_t * tt = dirac_core_body_mut(that);
        size_t rows = dirac_core_rows_get(that);
        size_t cols = dirac_core_cols_get(that);
        int rr;
        int cc;
        int ii;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_core_index(that, rr, cc);
                (tt)[ii] = (aa)[ii] + (bb)[ii];
            }
        }
    } 
	return dirac_core_matrix_mut(that);
}

dirac_matrix_t * dirac_matrix_sub(const dirac_matrix_t * thema, const dirac_matrix_t * themb)
{
    const dirac_t * thata = dirac_core_object_get(thema);
    const dirac_t * thatb = dirac_core_object_get(themb);
	dirac_t * that = dirac_core_sum(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_sub");
    } else {
        const dirac_complex_t * aa = dirac_core_body_get(thata);
        const dirac_complex_t * bb = dirac_core_body_get(thatb);
        dirac_complex_t * tt = dirac_core_body_mut(that);
        size_t rows = dirac_core_rows_get(that);
        size_t cols = dirac_core_cols_get(that);
        int rr;
        int cc;
        int ii;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_core_index(that, rr, cc);
                (tt)[ii] = (aa)[ii] - (bb)[ii];
            }
        }
    } 
	return dirac_core_matrix_mut(that);
}

dirac_matrix_t * dirac_matrix_mul(const dirac_matrix_t * thema, const dirac_matrix_t * themb)
{
    const dirac_t * thata = dirac_core_object_get(thema);
    const dirac_t * thatb = dirac_core_object_get(themb);
	dirac_t * that = dirac_core_pro(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_mul");
    } else {
        const dirac_complex_t * aa = dirac_core_body_get(thata);
        const dirac_complex_t * bb = dirac_core_body_get(thatb);
        dirac_complex_t * tt = dirac_core_body_mut(that);
        size_t rows = dirac_core_rows_get(thata);
        size_t muls = dirac_core_rows_get(thatb);
        size_t cols = dirac_core_cols_get(thatb);
        int rr;
        int mm;
        int cc;
        int ii;
        int jj;
        int kk;
        for (rr = 0; rr < rows; ++rr) {
            for (mm = 0; mm < muls; ++rr) {
                for (cc = 0; cc < cols; ++cc) {
                    ii = dirac_core_index(thata, rr, mm);
                    jj = dirac_core_index(thatb, mm, cc);
                    kk = dirac_core_index(that, rr, cc);
                    (tt)[kk] = (aa)[ii] * (bb)[jj];
                }
            }
        }
    } 
	return dirac_core_matrix_mut(that);
}

dirac_matrix_t * dirac_matrix_kro(const dirac_matrix_t * thema, const dirac_matrix_t * themb)
{
    const dirac_t * thata = dirac_core_object_get(thema);
    const dirac_t * thatb = dirac_core_object_get(themb);
	dirac_t * that = dirac_core_kro(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_mul");
    } else {
        const dirac_complex_t * aa = dirac_core_body_get(thata);
        const dirac_complex_t * bb = dirac_core_body_get(thatb);
        dirac_complex_t * tt = dirac_core_body_mut(that);
        size_t rowsa = dirac_core_rows_get(thata);
        size_t colsa = dirac_core_cols_get(thata);
        size_t rowsb = dirac_core_rows_get(thatb);
        size_t colsb = dirac_core_cols_get(thatb);
        int ar;
        int ac;
        int br;
        int bc;
        int tr;
        int tc;
        int ai;
        int bi;
        int ti;
        for (ar = 0; ar < rowsa; ++ar) {
            for (ac = 0; ac < colsa; ++ac) {
                for (br = 0; br < rowsb; ++br) {
                    for (bc = 0; bc < colsb; ++bc) {
                        tr = (ar * rowsb) + br;
                        tc = (ac * colsb) + bc;
                        ai = dirac_core_index(thata, ar, ac);
                        bi = dirac_core_index(thatb, br, bc);
                        ti = dirac_core_index(that, tr, tc);
                        (tt)[ti] = (aa)[ai] * (bb)[bi];
                    }
                }
            }
        }
    }
    return dirac_core_matrix_mut(that);
}

dirac_matrix_t * dirac_matrix_had(const dirac_matrix_t * thema, const dirac_matrix_t * themb)
{
    const dirac_t * thata = dirac_core_object_get(thema);
    const dirac_t * thatb = dirac_core_object_get(themb);
	dirac_t * that = dirac_core_had(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_had");
    } else {
        const dirac_complex_t * aa = dirac_core_body_get(thata);
        const dirac_complex_t * bb = dirac_core_body_get(thatb);
        dirac_complex_t * tt = dirac_core_body_mut(that);
        size_t rows = dirac_core_rows_get(thata);
        size_t muls = dirac_core_rows_get(thatb);
        size_t cols = dirac_core_cols_get(thatb);
        int rr;
        int cc;
        int ii;
        for (rr = 0; ii < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_core_index(that, rr, cc);
                (tt)[ii] = (aa)[ii] * (bb)[ii];
            }
        }
    }
    return dirac_core_matrix_mut(that);
}

/*******************************************************************************
 * END
 ******************************************************************************/
