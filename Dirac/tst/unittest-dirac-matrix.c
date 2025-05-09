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

    DIRAC_STACK_CODE(thing2x3a, 2, 3);

    {
        TEST();

        int rows = dirac_rows_get(thing2x3a_p);
        int cols = dirac_columns_get(thing2x3a_p);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*thing2x3a_m)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        ASSERT(dirac_print(stdout, thing2x3a_p) == (dirac_t *)&thing2x3a);

        STATUS();
    }

    DIRAC_STACK_CODE(thing2x3b, 2, 3);

    {
        TEST();

        int rows = dirac_rows_get(thing2x3b_p);
        int cols = dirac_columns_get(thing2x3b_p);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*thing2x3b_m)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        ASSERT(dirac_print(stdout, thing2x3b_p) == (dirac_t *)&thing2x3b);

        STATUS();
    }

    DIRAC_STACK_CODE(thing3x2c, 3, 2);

    {
        TEST();

        int rows = dirac_rows_get(thing3x2c_p);
        int cols = dirac_columns_get(thing3x2c_p);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*thing3x2c_m)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        ASSERT(dirac_print(stdout, thing3x2c_p) == (dirac_t *)&thing3x2c);

        STATUS();
    }

    DIRAC_STACK_CODE(thing5x7d, 5, 7);

    {
        TEST();

        int rows = dirac_rows_get(thing5x7d_p);
        int cols = dirac_columns_get(thing5x7d_p);
        int rr;
        int cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*thing5x7d_m)[rr][cc] = CMPLX((double)PRIMES[ii++], 0.0);
            }
        }

        ASSERT(dirac_print(stdout, thing5x7d_p) == (dirac_t *)&thing5x7d);

        STATUS();
    }

    {
        TEST();

        dirac_t * that = dirac_matrix_add(thing2x3a_p, thing2x3b_p);
        ASSERT(dirac_print(stdout, that) == that);
        ASSERT(dirac_delete(that) == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        dirac_t * that = dirac_audit();
        ASSERT(that == (dirac_t *)0);

        ssize_t total = dirac_dump(stderr);
        fprintf(stderr, "cache[%zd]\n", total);
        ASSERT(total >= 0);

        dirac_free();
        total = dirac_dump((FILE *)0);
        ASSERT(total == 0);

        STATUS();
    }

    EXIT();
}
