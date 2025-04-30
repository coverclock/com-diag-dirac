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

    DIRAC_OBJECT_DECL(2, 3) thing2x3a = DIRAC_OBJECT_INIT(2, 3);
    DIRAC_ARRAY_TYPE(thing2x3_t, 2, 3);
    thing2x3_t * matrix2x3a = DIRAC_ARRAY_POINTER(thing2x3_t, &thing2x3a);

    {
        TEST();

        int rr;
        int cc;

        for (rr = 0; rr < dirac_rows_get((dirac_t *)&thing2x3a); ++rr) {
            for (cc = 0; cc < dirac_columns_get((dirac_t *)&thing2x3a); ++cc) {
                (*matrix2x3a)[rr][cc] = CMPLX((double)PRIMES[ii++], (double)PRIMES[ii++]);
            }
        }
        dirac_matrix_print(stdout, (dirac_t *)&thing2x3a);

        STATUS();
    }

    DIRAC_OBJECT_DECL(2, 3) thing2x3b = DIRAC_OBJECT_INIT(2, 3);
    thing2x3_t * matrix2x3b = DIRAC_ARRAY_POINTER(thing2x3_t, &thing2x3b);

    {
        TEST();

        int rr;
        int cc;

        for (rr = 0; rr < dirac_rows_get((dirac_t *)&thing2x3b); ++rr) {
            for (cc = 0; cc < dirac_columns_get((dirac_t *)&thing2x3b); ++cc) {
                (*matrix2x3b)[rr][cc] = CMPLX((double)PRIMES[ii++], (double)PRIMES[ii++]);
            }
        }
        dirac_matrix_print(stdout, (dirac_t *)&thing2x3b);

        STATUS();
    }

    DIRAC_OBJECT_DECL(3, 2) thing3x2c = DIRAC_OBJECT_INIT(3, 2);
    DIRAC_ARRAY_TYPE(thing3x2_t, 3, 2);
    thing3x2_t * matrix3x2c = DIRAC_ARRAY_POINTER(thing3x2_t, &thing3x2c);

    {
        TEST();

        int rr;
        int cc;

        for (rr = 0; rr < dirac_rows_get((dirac_t *)&thing3x2c); ++rr) {
            for (cc = 0; cc < dirac_columns_get((dirac_t *)&thing3x2c); ++cc) {
                (*matrix3x2c)[rr][cc] = CMPLX((double)PRIMES[ii++], (double)PRIMES[ii++]);
            }
        }
        dirac_matrix_print(stdout, (dirac_t *)&thing3x2c);

        STATUS();
    }

    DIRAC_OBJECT_DECL(5, 7) thing5x7d = DIRAC_OBJECT_INIT(5, 7);
    DIRAC_ARRAY_TYPE(thing5x7_t, 5, 7);
    thing5x7_t * matrix5x7d = DIRAC_ARRAY_POINTER(thing5x7_t, &thing5x7d);

    {
        TEST();

        int rr;
        int cc;

        for (rr = 0; rr < dirac_rows_get((dirac_t *)&thing5x7d); ++rr) {
            for (cc = 0; cc < dirac_columns_get((dirac_t *)&thing5x7d); ++cc) {
                (*matrix5x7d)[rr][cc] = CMPLX((double)PRIMES[ii++], (double)PRIMES[ii++]);
            }
        }
        dirac_matrix_print(stdout, (dirac_t *)&thing5x7d);

        STATUS();
    }

    {
        TEST();

        STATUS();
    }

    EXIT();
}
