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

    {
        TEST();

        DIRAC_OBJECT_CONST(2, 3) those = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 0.0+0.0i, 0.0+1.0i, 0.0+2.0i, },
                { 1.0+0.0i, 1.0+1.0i, 1.0+2.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them)[2][3] = DIRAC_MATRIX_GET(those);

        dirac_print(stdout, them);

        ASSERT(dirac_rows_get(them) == 2);
        ASSERT(dirac_cols_get(them) == 3);

        dirac_complex_t (*that)[2][3] = dirac_matrix_dup(them);
        ASSERT(that != (dirac_complex_t (*)[2][3])0);

        dirac_print(stdout, that);

        ASSERT(dirac_rows_get(that) == 2);
        ASSERT(dirac_cols_get(that) == 3);

        int rr;
        int cc;
        for (rr = 0; rr < 2; ++rr) {
            for (cc = 0; cc < 3; ++cc) {
                ASSERT((*them)[rr][cc] == (*that)[rr][cc]);
            }
        }

        dirac_delete(that);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_CONST(2, 3) those = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 0.0+0.0i, 0.0+1.0i, 0.0+2.0i, },
                { 1.0+0.0i, 1.0+1.0i, 1.0+2.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them)[2][3] = DIRAC_MATRIX_GET(those);

        dirac_print(stdout, them);

        ASSERT(dirac_rows_get(them) == 2);
        ASSERT(dirac_cols_get(them) == 3);

        dirac_complex_t (*that)[3][2] = dirac_matrix_trn(them);
        ASSERT(that != (dirac_complex_t (*)[3][2])0);

        dirac_print(stdout, that);

        ASSERT(dirac_rows_get(that) == 3);
        ASSERT(dirac_cols_get(that) == 2);

        int rr;
        int cc;
        for (rr = 0; rr < 2; ++rr) {
            for (cc = 0; cc < 3; ++cc) {
                ASSERT((*them)[rr][cc] == (*that)[cc][rr]);
            }
        }

        dirac_delete(that);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_CONST(2, 3) those1 = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 0.0+0.0i, 0.0+1.0i, 0.0+2.0i, },
                { 1.0+0.0i, 1.0+1.0i, 1.0+2.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them1)[2][3] = DIRAC_MATRIX_GET(those1);

        dirac_print(stdout, them1);

        ASSERT(dirac_rows_get(them1) == 2);
        ASSERT(dirac_cols_get(them1) == 3);

        DIRAC_OBJECT_CONST(2, 3) those2 = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 2.0+4.0i, 2.0+5.0i, 2.0+6.0i, },
                { 3.0+4.0i, 3.0+5.0i, 3.0+6.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them2)[2][3] = DIRAC_MATRIX_GET(those2);

        dirac_print(stdout, them2);

        ASSERT(dirac_rows_get(them2) == 2);
        ASSERT(dirac_cols_get(them2) == 3);

        DIRAC_OBJECT_CONST(2, 3) those3 = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 2.0+4.0i, 2.0+6.0i, 2.0+8.0i, },
                { 4.0+4.0i, 4.0+6.0i, 4.0+8.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them3)[2][3] = DIRAC_MATRIX_GET(those3);

        dirac_print(stdout, them3);

        ASSERT(dirac_rows_get(them3) == 2);
        ASSERT(dirac_cols_get(them3) == 3);

        dirac_complex_t (*that)[2][3] = dirac_matrix_add(them1, them2);
        ASSERT(that != (dirac_complex_t (*)[2][3])0);

        dirac_print(stdout, that);

        ASSERT(dirac_rows_get(that) == 2);
        ASSERT(dirac_cols_get(that) == 3);

        int rr;
        int cc;
        for (rr = 0; rr < 2; ++rr) {
            for (cc = 0; cc < 3; ++cc) {
                ASSERT((*them3)[rr][cc] == (*that)[rr][cc]);
            }
        }

        dirac_delete(that);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_CONST(2, 3) those1 = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 3.0+6.0i, 5.0+9.0i, 7.0+12.0i, },
                { 10.0+12.0i, 12.0+15.0i, 14.0+18.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them1)[2][3] = DIRAC_MATRIX_GET(those1);

        dirac_print(stdout, them1);

        ASSERT(dirac_rows_get(them1) == 2);
        ASSERT(dirac_cols_get(them1) == 3);

        DIRAC_OBJECT_CONST(2, 3) those2 = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 0.0+0.0i, 0.0+1.0i, 0.0+2.0i, },
                { 1.0+0.0i, 1.0+1.0i, 1.0+2.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them2)[2][3] = DIRAC_MATRIX_GET(those2);

        dirac_print(stdout, them2);

        ASSERT(dirac_rows_get(them2) == 2);
        ASSERT(dirac_cols_get(them2) == 3);

        DIRAC_OBJECT_CONST(2, 3) those3 = 
            DIRAC_OBJECT_INIT_BEGIN(2, 3)
                { 3.0+6.0i, 5.0+8.0i, 7.0+10.0i, },
                { 9.0+12.0i, 11.0+14.0i, 13.0+16.0i, },
            DIRAC_OBJECT_INIT_END;
        const dirac_complex_t (*them3)[2][3] = DIRAC_MATRIX_GET(those3);

        dirac_print(stdout, them3);

        ASSERT(dirac_rows_get(them3) == 2);
        ASSERT(dirac_cols_get(them3) == 3);

        dirac_complex_t (*that)[2][3] = dirac_matrix_sub(them1, them2);
        ASSERT(that != (dirac_complex_t (*)[2][3])0);

        dirac_print(stdout, that);

        ASSERT(dirac_rows_get(that) == 2);
        ASSERT(dirac_cols_get(that) == 3);

        int rr;
        int cc;
        for (rr = 0; rr < 2; ++rr) {
            for (cc = 0; cc < 3; ++cc) {
                ASSERT((*them3)[rr][cc] == (*that)[rr][cc]);
            }
        }

        dirac_delete(that);

        STATUS();
    }

    {
        TEST();

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
