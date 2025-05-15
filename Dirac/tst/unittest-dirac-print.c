/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 * @copyright Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * @note Licensed under the terms in LICENSE.txt.
 * @brief This is a unit test of the Dirac print function and related.
 * @author Chip Overclock <mailto:coverclock@diag.com>
 * @see Diminuto <https://github.com/coverclock/com-diag-dirac>
 * @details
 * This is a unit test of the Dirac print function and related. It's also an
 * excuse to try different coding patterns to use either dynamic or static Dirac
 * objects.
 */

#include "com/diag/diminuto/diminuto_unittest.h"
#include "com/diag/dirac/dirac.h"

int main(void)
{
    SETLOGMASK();

#if 0

    /*
     * Dynamic objects allocated from the heap.
     */

    {
        TEST();

        dirac_t * that = dirac_new(2, 3);
        DIRAC_ARRAY_TYPE(thing2x3_t, 2, 3);
        thing2x3_t * matrix = DIRAC_ARRAY_POINTER(thing2x3_t, that);
        size_t rows = dirac_rows_get(that);
        size_t cols = dirac_columns_get(that);
        int rr;
        int cc;

        ASSERT(rows == 2);
        ASSERT(cols == 3);

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*matrix)[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        (void)dirac_print(stdout, that);

        dirac_delete(that);

        STATUS();
    }

    {
        TEST();

        typedef DIRAC_OBJECT_DECL(2, 3) thing2x3_t;
        thing2x3_t * that = (thing2x3_t *)dirac_new(2, 3);
        size_t rows = dirac_rows_get((dirac_t *)that);
        size_t cols = dirac_columns_get((dirac_t *)that);
        int rr;
        int cc;

        ASSERT(rows == 2);
        ASSERT(cols == 3);

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                that->data.body[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        (void)dirac_print(stdout, (dirac_t *)that);

        dirac_delete((dirac_t *)that);

        STATUS();
    }

    /*
     * Static objects allocated on the stack.
     */

    {
        TEST();

        DIRAC_OBJECT_DECL(2, 3) thing = DIRAC_OBJECT_INIT(2, 3);
        DIRAC_ARRAY_TYPE(thing2x3_t, 2, 3);
        thing2x3_t * matrix = DIRAC_ARRAY_POINTER(thing2x3_t, &thing);
        size_t rows = dirac_rows_get((dirac_t *)(&thing));
        size_t cols = dirac_columns_get((dirac_t *)(&thing));
        int rr;
        int cc;

        ASSERT(rows == 2);
        ASSERT(cols == 3);

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*matrix)[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        (void)dirac_print(stdout, (dirac_t *)(&thing));

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(2, 3) thing = DIRAC_OBJECT_INIT(2, 3);
        size_t rows = dirac_rows_get((dirac_t *)(&thing));
        size_t cols = dirac_columns_get((dirac_t *)(&thing));
        int rr;
        int cc;

        ASSERT(rows == 2);
        ASSERT(cols == 3);

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                thing.data.body[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        (void)dirac_print(stdout, (dirac_t *)(&thing));

        STATUS();
    }

    /*
     * Variable Length Array (VLA) objects allocated on the stack.
     */

    {
        TEST();

        const size_t ROWS = 2;
        const size_t COLS = 3;
        DIRAC_OBJECT_DECL(ROWS, COLS) thing;
        DIRAC_ARRAY_TYPE(thing2x3_t, ROWS, COLS);
        thing2x3_t * matrix = DIRAC_ARRAY_POINTER(thing2x3_t, &thing);
        int rr;
        int cc;

        dirac_t * that = dirac_init((dirac_t *)&thing, ROWS, COLS);
        ASSERT(that == (dirac_t *)&thing);

        size_t rows = dirac_rows_get(that);
        size_t cols = dirac_columns_get(that);
        ASSERT(rows == ROWS);
        ASSERT(cols == COLS);

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*matrix)[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        (void)dirac_print(stdout, (dirac_t *)(&thing));

        STATUS();
    }

    {
        TEST();

        const size_t ROWS = 2;
        const size_t COLS = 3;
        DIRAC_OBJECT_DECL(ROWS, COLS) thing;
        int rr;
        int cc;

        dirac_t * that = dirac_init((dirac_t *)&thing, ROWS, COLS);
        ASSERT(that == (dirac_t *)&thing);

        size_t rows = dirac_rows_get(that);
        size_t cols = dirac_columns_get(that);
        ASSERT(rows == ROWS);
        ASSERT(cols == COLS);

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                thing.data.body[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        (void)dirac_print(stdout, (dirac_t *)(&thing));

        STATUS();
    }

    /*
     * Stack code generator.
     */

    {
        TEST();

        DIRAC_STACK_CODE(thing, 2, 3);
        size_t rows = dirac_rows_get(thing_p);
        size_t cols = dirac_columns_get(thing_p);
        int rr;
        int cc;

        ASSERT(rows == 2);
        ASSERT(cols == 3);

        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*thing_m)[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }

        (void)dirac_print(stdout, thing_p);

        STATUS();
    }

    /*
     * End.
     */

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

#endif

    EXIT();
}
