/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 * @copyright Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * @note Licensed under the terms in LICENSE.txt.
 * @brief This is a unit test of the Dirac matrix funcsions and related.
 * @author Chip Overclock <mailto:coverclock@diag.com>
 * @see Diminuto <https://github.com/coverclock/com-diag-dirac>
 * @details
 * This is a unit test of the Dirac matrix funcsions and related.
 */

#include "com/diag/diminuto/diminuto_unittest.h"
#include "com/diag/dirac/dirac.h"
#include "unittest-dirac-primes.h"

int main(void)
{
    SETLOGMASK();

    int ii = 0;

    dirac_complex_t (*that2x3a)[2][3] = dirac_new(2, 3);

    {
        TEST();

        int rows = dirac_rows_get(that2x3a);
        int cols = dirac_cols_get(that2x3a);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*that2x3a)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        dirac_print(stdout, that2x3a);

        STATUS();
    }

    dirac_complex_t (*that2x3b)[2][3] = dirac_new(2, 3);

    {
        TEST();

        int rows = dirac_rows_get(that2x3b);
        int cols = dirac_cols_get(that2x3b);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*that2x3b)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        dirac_print(stdout, that2x3b);

        STATUS();
    }

    dirac_complex_t (*that3x2c)[3][2] = dirac_new(3, 2);

    {
        TEST();

        int rows = dirac_rows_get(that3x2c);
        int cols = dirac_cols_get(that3x2c);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*that3x2c)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        dirac_print(stdout, that3x2c);

        STATUS();
    }

    dirac_complex_t (*that5x7d)[5][7] = dirac_new(5, 7);

    {
        TEST();

        int rows = dirac_rows_get(that5x7d);
        int cols = dirac_cols_get(that5x7d);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*that5x7d)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        dirac_print(stdout, that5x7d);

        STATUS();
    }

    {
        TEST();

        dirac_complex_t (*that)[7][5] = dirac_matrix_trn(that5x7d);
        ASSERT(that != (dirac_complex_t (*)[7][5])0);
        dirac_print(stdout, that);
        dirac_delete(that);

        STATUS();
    }

    {
        TEST();

        dirac_complex_t (*that)[2][3] = dirac_matrix_add(that2x3a, that2x3b);
        ASSERT(that != (dirac_complex_t (*)[2][3])0);
        dirac_print(stdout, that);
        dirac_delete(that);

        STATUS();
    }

    {
        TEST();

        dirac_delete(that2x3a);
        dirac_delete(that2x3b);
        dirac_delete(that3x2c);
        dirac_delete(that5x7d);

        dirac_t * that = dirac_audit();
        ASSERT(that == (dirac_t *)0);

        ssize_t total;

        total = dirac_dump(stderr);
        fprintf(stderr, "cache[%zd]\n", total);
        ASSERT(total >= 0);

        dirac_free();

        total = dirac_dump((FILE *)0);
        fprintf(stderr, "cache[%zd]\n", total);
        ASSERT(total == 0);

        STATUS();
    }

    EXIT();
}
