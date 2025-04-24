/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 * @copyright Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * @note Licensed under the terms in LICENSE.txt.
 * @brief This is a unit test of the Tree feature.
 * @author Chip Overclock <mailto:coverclock@diag.com>
 * @see Diminuto <https://github.com/coverclock/com-diag-dirac>
 * @details
 * This is a unit test of the Dirac memory management>
 */

#include "com/diag/diminuto/diminuto_unittest.h"
#include "com/diag/diminuto/diminuto_countof.h"
#include "com/diag/diminuto/diminuto_log.h"
#include "com/diag/dirac/dirac.h"

int main(void)
{
    SETLOGMASK();

    {
        TEST();

        fprintf(stderr, "sizeof(dirac_complex_t)=%zu\n", sizeof(dirac_complex_t));
        ASSERT(sizeof(complex double) == sizeof(dirac_complex_t));
        fprintf(stderr, "sizeof(dirac_data_t)=%zu\n", sizeof(dirac_data_t));
        fprintf(stderr, "sizeof(dirac_node_t)=%zu\n", sizeof(dirac_node_t));
        ASSERT(sizeof(dirac_node_t) > sizeof(dirac_data_t));
        fprintf(stderr, "sizeof(dirac_t)=%zu\n", sizeof(dirac_t));
        ASSERT(sizeof(dirac_t) == sizeof(dirac_node_t));

        STATUS();
    }

    {
        TEST();

        dirac_t that;
        size_t rows;
        size_t columns;
        dirac_complex_t * matrix;

        that.data.rows = 5;
        that.data.columns = 7;

        rows = dirac_rows_get(&that);
        ASSERT(rows == that.data.rows);

        columns = dirac_columns_get(&that);
        ASSERT(columns == that.data.columns);

        matrix = dirac_matrix_get(&that);
        ASSERT(matrix == &(that.data.matrix[0]));

        STATUS();
    }

    {
        TEST();

        dirac_free();
        dirac_dump(stderr);

        dirac_t * new1 = dirac_new(0, 0);
        ASSERT(new1 != (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * new2 = dirac_new(2, 3);
        ASSERT(new2 != (dirac_t *)0);
        ASSERT(new2 != new1);
        dirac_dump(stderr);

        dirac_t * new3 = dirac_new(3, 2);
        ASSERT(new3 != (dirac_t *)0);
        ASSERT(new3 != new1);
        ASSERT(new3 != new2);
        dirac_dump(stderr);

        dirac_t * new4 = dirac_new(4, 4);
        ASSERT(new4 != (dirac_t *)0);
        ASSERT(new4 != new1);
        ASSERT(new4 != new2);
        ASSERT(new4 != new3);
        dirac_dump(stderr);

        dirac_t * delete3 = dirac_delete(new3);
        ASSERT(delete3 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * delete1 = dirac_delete(new1);
        ASSERT(delete1 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * delete4 = dirac_delete(new4);
        ASSERT(delete4 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * delete2 = dirac_delete(new2);
        ASSERT(delete2 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * new5 = dirac_new(0, 0);
        ASSERT(new5 != (dirac_t *)0);
        ASSERT(new5 == new1);
        dirac_dump(stderr);

        dirac_t * new6 = dirac_new(2, 3);
        ASSERT(new6 != (dirac_t *)0);
        ASSERT(new6 == new3);
        dirac_dump(stderr);

        dirac_t * new7 = dirac_new(3, 2);
        ASSERT(new7 != (dirac_t *)0);
        ASSERT(new7 == new2);
        ASSERT(new7 != new6);
        dirac_dump(stderr);

        dirac_t * new8 = dirac_new(4, 4);
        ASSERT(new8 != (dirac_t *)0);
        ASSERT(new8 == new4);
        dirac_dump(stderr);

        dirac_t * delete7 = dirac_delete(new7);
        ASSERT(delete7 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * delete5 = dirac_delete(new5);
        ASSERT(delete5 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * delete8 = dirac_delete(new8);
        ASSERT(delete8 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * delete6 = dirac_delete(new6);
        ASSERT(delete6 == (dirac_t *)0);
        dirac_dump(stderr);

        dirac_free();
        dirac_dump(stderr);

        STATUS();
    }

    {
        TEST();

        static const size_t ROWS = 3;
        static const size_t COLS = 4;
        dirac_t * that;
        typedef dirac_complex_t (array_t)[ROWS][COLS];
        array_t * here;
        dirac_complex_t * aa;
        dirac_complex_t * bb;
        unsigned int rr, cc, ii;

        that = dirac_new(ROWS, COLS);
        ASSERT(that != (dirac_t *)0);
        ASSERT(that->data.rows == ROWS);
        ASSERT(that->data.columns == COLS);

        ASSERT(dirac_point_fast(that, 0, 0) != (dirac_complex_t *)0);
        ASSERT(dirac_point_fast(that, ROWS - 1, COLS - 1) != (dirac_complex_t *)0);
        ASSERT(dirac_point_fast(that, ROWS, COLS - 1) != (dirac_complex_t *)0);
        ASSERT(dirac_point_fast(that, ROWS - 1, COLS) != (dirac_complex_t *)0);
        ASSERT(dirac_point_fast(that, ROWS, COLS) != (dirac_complex_t *)0);

        ASSERT(dirac_point_safe(that, 0, 0) != (dirac_complex_t *)0);
        ASSERT(dirac_point_safe(that, ROWS - 1, COLS - 1) != (dirac_complex_t *)0);
        ASSERT(dirac_point_safe(that, ROWS, COLS - 1) == (dirac_complex_t *)0);
        ASSERT(dirac_point_safe(that, ROWS - 1, COLS) == (dirac_complex_t *)0);
        ASSERT(dirac_point_safe(that, ROWS, COLS) == (dirac_complex_t *)0);

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                aa = dirac_point(that, rr, cc);
                fprintf(stderr, "node(%u,%u)@%p\n", rr, cc, aa);
                ASSERT(*aa == CMPLX(0, 0));
            }
        }

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                ii = dirac_index(that, rr, cc);
                aa = &(that->data.matrix[ii]);
                fprintf(stderr, "matrix(%u,%u)[%u]@%p\n", rr, cc, ii, aa);
                ASSERT(*aa == CMPLX(0, 0));
            }
        }

        here = (array_t *)(&(that->data.matrix));

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                bb = &((*here)[rr][cc]);
                fprintf(stderr, "array[%u][%u]@%p\n", rr, cc, bb);
                ASSERT((*here)[rr][cc] == CMPLX(0, 0));
            }
        }

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                aa = dirac_point(that, rr, cc);
                bb = &((*here)[rr][cc]);
                ASSERT(aa == bb);
            }
        }

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                (*here)[rr][cc] = CMPLX(rr, cc);
            }
        }

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                dirac_complex_t value = (double)rr + ((double)cc * I);
                fprintf(stderr, "value %lf%+lfi\n", creal(value), cimag(value));
                ASSERT(value == CMPLX(rr, cc));
                ASSERT((*here)[rr][cc] == value);
                ASSERT(((unsigned int)creal((*here)[rr][cc])) == rr);
                ASSERT(((unsigned int)cimag((*here)[rr][cc])) == cc);
            }
        }

        dirac_delete(that);

        dirac_free();

        STATUS();
    }

    {
        TEST();

        static const size_t ROWS = 3;
        static const size_t COLS = 4;
        dirac_t * that;
        DIRAC_ARRAY_TYPE(array3x4_t, ROWS, COLS);
        array3x4_t * array3x4p;
        dirac_complex_t * aa;
        dirac_complex_t * bb;
        dirac_complex_t * cc;
        unsigned int row, col;

        that = dirac_new(ROWS, COLS);
        array3x4p = DIRAC_ARRAY_POINTER(array3x4_t, that);

        for (row = 0; row < ROWS; ++row) {
            for (col = 0; col < COLS; ++col) {
                ASSERT((*array3x4p)[row][col] == (0+(0*I)));
                (*array3x4p)[row][col] = CMPLX(row, col);
                aa = dirac_point(that, row, col);
                bb = &((*array3x4p)[row][col]);
                cc = &(that->data.matrix[dirac_index(that, row, col)]);
                ASSERT(aa == bb);
                ASSERT(bb == cc);
                ASSERT(aa == cc);
                ASSERT((unsigned int)creal(*aa) == row);
                ASSERT((unsigned int)cimag(*aa) == col);
                ASSERT((unsigned int)creal(*bb) == row);
                ASSERT((unsigned int)cimag(*bb) == col);
                ASSERT((unsigned int)creal(*cc) == row);
                ASSERT((unsigned int)cimag(*cc) == col);
            }
        }

        dirac_delete(that);

        dirac_free();

        STATUS();
    }

    {
        TEST();

#define ROWS 5
#define COLS 7

        /*
         * 5 * 7 * sizeof(dirac_complex_t) = 560
         * 560 + sizeof(dirac_data_t) = 576
         * sizeof(dirac_t) - sizeof(dirac_data_t) = 40
         * 40 / sizeof(direc_complex_t) = 2.5
         * floor(2.5) * sizeof(direc_complex_t) = 32
         * 576 - 32 = 544
         * 544 + 40 = 584
         */

        DIRAC_STATIC_DECL(ROWS, COLS) thing = DIRAC_STATIC_INIT(ROWS, COLS);
        dirac_t * that = DIRAC_STATIC_POINTER(thing);
        DIRAC_ARRAY_TYPE(array3x4_t, ROWS, COLS);
        array3x4_t * array3x4p;
        dirac_complex_t * aa;
        dirac_complex_t * bb;
        dirac_complex_t * cc;
        dirac_complex_t * dd;
        unsigned int row, col;

        ASSERT(that->data.rows == ROWS);
        ASSERT(that->data.columns == COLS);

        fprintf(stderr, "sizeof(thing)=%zu\n", sizeof(thing));
        fprintf(stderr, "sizeof(thing.head)=%zu\n", sizeof(thing.head));
        fprintf(stderr, "sizeof(thing.head.node)=%zu\n", sizeof(thing.head.node));
        fprintf(stderr, "sizeof(thing.head.data)=%zu\n", sizeof(thing.head.data));
        fprintf(stderr, "sizeof(thing.body)=%zu\n", sizeof(thing.body));
        ASSERT(sizeof(thing.head) == sizeof(dirac_t));

        aa = &(thing.head.data.matrix[0]);
        bb = &(thing.head.data.matrix[(ROWS * COLS) - 1]);
        cc = &(thing.body[0]);
        dd = &(thing.body[countof(thing.body) - 1]);
        fprintf(stderr, "&matrix[%u]=%p\n", 0, aa);
        fprintf(stderr, "&matrix[%zu]=%p\n", (ROWS * COLS) - 1, bb);
        fprintf(stderr, "&body[%u]=%p\n", 0, cc);
        fprintf(stderr, "&body[%zu]=%p\n", countof(thing.body) - 1, dd);

        array3x4p = DIRAC_ARRAY_POINTER(array3x4_t, that);

        for (row = 0; row < ROWS; ++row) {
            for (col = 0; col < COLS; ++col) {
                ASSERT((*array3x4p)[row][col] == (0+(0*I)));
                (*array3x4p)[row][col] = CMPLX(row, col);
                aa = dirac_point(that, row, col);
                bb = &((*array3x4p)[row][col]);
                cc = &(that->data.matrix[dirac_index(that, row, col)]);
                ASSERT(aa == bb);
                ASSERT(bb == cc);
                ASSERT(aa == cc);
                ASSERT((unsigned int)creal(*aa) == row);
                ASSERT((unsigned int)cimag(*aa) == col);
                ASSERT((unsigned int)creal(*bb) == row);
                ASSERT((unsigned int)cimag(*bb) == col);
                ASSERT((unsigned int)creal(*cc) == row);
                ASSERT((unsigned int)cimag(*cc) == col);
            }
        }

#undef COLS
#undef ROWS

        STATUS();
    }

    EXIT();
}
