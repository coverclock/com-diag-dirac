/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 * @copyright Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * @note Licensed under the terms in LICENSE.txt.
 * @brief This is a unit test of the Dirac matrix arithmetic and related.
 * @author Chip Overclock <mailto:coverclock@diag.com>
 * @see Diminuto <https://github.com/coverclock/com-diag-dirac>
 * @details
 * This is a unit test of the Dirac matri arithmetic and related.
 */

#include "com/diag/diminuto/diminuto_unittest.h"
#include "com/diag/dirac/dirac.h"

int main(void)
{
    SETLOGMASK();

    {
        TEST();

        DIRAC_OBJECT_DECL(2, 3) thing = DIRAC_OBJECT_INIT(2, 3);
        DIRAC_ARRAY_TYPE(thing2x3_t, 2, 3);
        thing2x3_t * that = DIRAC_ARRAY_POINTER(thing2x3_t, &thing);
        size_t rows = dirac_rows_get((dirac_t *)(&thing));
        size_t cols = dirac_columns_get((dirac_t *)(&thing));
        size_t rr;
        size_t cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*that)[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        dirac_matrix_print(stdout, (dirac_t *)(&thing));

        STATUS();

    }

    {
        TEST();

        DIRAC_OBJECT_DECL(2, 3) thing = DIRAC_OBJECT_INIT(2, 3);
        size_t rows = dirac_rows_get((dirac_t *)(&thing));
        size_t cols = dirac_columns_get((dirac_t *)(&thing));
        size_t rr;
        size_t cc;

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                thing.data.body[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        dirac_matrix_print(stdout, (dirac_t *)(&thing));

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
