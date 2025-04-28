/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA<BR>
 * Licensed under the terms in LICENSE.txt<BR>
 * Chip Overclock (mailto:coverclock@diag.com)<BR>
 * https://github.com/coverclock/com-diag-cdirac<BR>
 *
 * This is the implementation of the matrix-related portions of Dirac.
 */

/*
 * Matrix operations may allocate (new) from the cache, but if the do so,
 * the resulting dynamically allocated object must either be deallocated
 * (delete) or returned to the caller. The only objects they may deallocate
 * back to the cache are objects they themselves allocate; this allows the
 * use of statically allocated (i.e. on the C stack) objects in matrix
 * operations.
 */

/*******************************************************************************
 * PREREQUISITES
 ******************************************************************************/

#include "com/diag/dirac/dirac.h"
#include "com/diag/diminuto/diminuto_error.h"
#include <errno.h>
#include "dirac.h"

/*******************************************************************************
 * UTILITIES
 ******************************************************************************/

void dirac_matrix_print(FILE * fp, const dirac_t * that)
{
    if (that == (dirac_t *)0) {
        fprintf(fp, "dirac@%p\n", that);
    } else {
        size_t rows = dirac_rows_get(that);
        size_t cols = dirac_columns_get(that);
        fprintf(fp, "dirac@%p[%zu][%zu]\n", that, rows, cols);
        const dirac_complex_t * tt = dirac_body_get(that);
        int rr;
        int cc;
        int ii;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_index(that, rr, cc);
                fprintf(fp, " (%le%+lei)", creal((tt)[ii]), cimag((tt)[ii]));
            }
            fputc('\n', fp);
        }
    }
    fflush(fp);
}

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/

dirac_t * dirac_matrix_trn(const dirac_t * thata)
{
	dirac_t * that = dirac_new_trn(thata); 
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_trn");
    } else {
        const dirac_complex_t * aa = dirac_body_get(thata);
        dirac_complex_t * tt = dirac_body_mut(that);
        size_t rows = dirac_rows_get(thata);
        size_t cols = dirac_columns_get(thata);
        int rr;
        int cc;
        int ii;
        int jj;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_index(thata, rr, cc);
                jj = dirac_index(that, cc, rr);
                (tt)[jj] = (aa)[ii];
            }
        }
    } 
	return that;
}

dirac_t * dirac_matrix_add(const dirac_t * thata, const dirac_t * thatb)
{
	dirac_t * that = dirac_new_sum(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_add");
    } else {
        const dirac_complex_t * aa = dirac_body_get(thata);
        const dirac_complex_t * bb = dirac_body_get(thatb);
        dirac_complex_t * tt = dirac_body_mut(that);
        size_t rows = dirac_rows_get(that);
        size_t cols = dirac_columns_get(that);
        int rr;
        int cc;
        int ii;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_index(that, rr, cc);
                (tt)[ii] = (aa)[ii] + (bb)[ii];
            }
        }
    } 
	return that;
}

dirac_t * dirac_matrix_sub(const dirac_t * thata, const dirac_t * thatb)
{
	dirac_t * that = dirac_new_sum(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_sub");
    } else {
        const dirac_complex_t * aa = dirac_body_get(thata);
        const dirac_complex_t * bb = dirac_body_get(thatb);
        dirac_complex_t * tt = dirac_body_mut(that);
        size_t rows = dirac_rows_get(that);
        size_t cols = dirac_columns_get(that);
        int rr;
        int cc;
        int ii;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                ii = dirac_index(that, rr, cc);
                (tt)[ii] = (aa)[ii] - (bb)[ii];
            }
        }
    } 
	return that;
}

dirac_t * dirac_matrix_mul(const dirac_t * thata, const dirac_t * thatb)
{
	dirac_t * that = dirac_new_pro(thata, thatb);
    if (that == (dirac_t *)0) {
        diminuto_perror("dirac_matrix_mul");
    } else {
        const dirac_complex_t * aa = dirac_body_get(thata);
        const dirac_complex_t * bb = dirac_body_get(thatb);
        dirac_complex_t * tt = dirac_body_mut(that);
        size_t rows = dirac_rows_get(thata);
        size_t muls = dirac_rows_get(thatb);
        size_t cols = dirac_columns_get(thatb);
        int rr;
        int mm;
        int cc;
        int ii;
        int jj;
        int kk;
        for (rr = 0; rr < rows; ++rr) {
            for (mm = 0; mm < muls; ++rr) {
                for (cc = 0; cc < cols; ++cc) {
                    ii = dirac_index(thata, rr, mm);
                    jj = dirac_index(thatb, mm, cc);
                    kk = dirac_index(that, rr, cc);
                    (tt)[kk] = (aa)[ii] * (bb)[jj];
                }
            }
        }
    } 
	return that;
}

/*******************************************************************************
 * END
 ******************************************************************************/
