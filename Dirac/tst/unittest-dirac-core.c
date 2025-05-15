/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 * @copyright Copyright 2025 Digital Aggregates Corporation, Colorado, USA.
 * @note Licensed under the terms in LICENSE.txt.
 * @brief This is a unit test of the Dirac memory management and related.
 * @author Chip Overclock <mailto:coverclock@diag.com>
 * @see Diminuto <https://github.com/coverclock/com-diag-dirac>
 * @details
 * This is a unit test of the Dirac memory management and related.
 */

#include "com/diag/diminuto/diminuto_unittest.h"
#include "com/diag/diminuto/diminuto_countof.h"
#include "com/diag/diminuto/diminuto_dump.h"
#include "com/diag/diminuto/diminuto_log.h"
#include "com/diag/dirac/dirac.h"

int main(void)
{
    SETLOGMASK();

    {
        TEST();

        dirac_dump(stdout);

        dirac_complex_t (* matrix)[2][3];

        matrix = dirac_new_matrix(2, 3);
        ASSERT((void *)matrix != (void *)0);
        dirac_matrix_print(stdout, matrix);

        dirac_free_matrix(matrix);

        dirac_dump(stdout);

        dirac_free();

        dirac_dump(stdout);

        STATUS();
    }

#if 0

    {
        TEST();

        fprintf(stderr, "sizeof(double)=%zu\n", sizeof(double));
        fprintf(stderr, "sizeof(complex double)=%zu\n", sizeof(complex double));
        fprintf(stderr, "sizeof(dirac_complex_t)=%zu\n", sizeof(dirac_complex_t));
        ASSERT(sizeof(complex double) == sizeof(dirac_complex_t));

        static const double thirteen = 13.0;
        fprintf(stderr, "sizeof(thirteen)=%zu\n", sizeof(thirteen));
        fprintf(stderr, "thirteen=%lf\n", thirteen);
        diminuto_dump(stderr, &thirteen, sizeof(thirteen));

        static const double seventeen = 17.0;
        fprintf(stderr, "sizeof(seventeen)=%zu\n", sizeof(seventeen));
        fprintf(stderr, "seventeen=%lf\n", seventeen);
        diminuto_dump(stderr, &seventeen, sizeof(seventeen));

        dirac_complex_t value13plus17i = 13 + (17*I);
        fprintf(stderr, "value13plus17i=%lf%+lfi\n", creal(value13plus17i), cimag(value13plus17i));
        diminuto_dump(stderr, &value13plus17i, sizeof(value13plus17i));

        fprintf(stderr, "sizeof(I)=%zu\n", sizeof(I));
        fprintf(stderr, "I=%lf%+lfi\n", creal(I), cimag(I));

        dirac_complex_t i = I;
        fprintf(stderr, "i=%lf%+lfi\n", creal(i), cimag(i));
        diminuto_dump(stderr, &i, sizeof(i));
        fprintf(stderr, "i^2=%lf%+lfi\n", creal(i*i), cimag(i*i));

        dirac_complex_t j = -I;
        fprintf(stderr, "j=%lf%+lfi\n", creal(j), cimag(j));
        diminuto_dump(stderr, &j, sizeof(j));
        fprintf(stderr, "j^2=%lf%+lfi\n", creal(j*j), cimag(j*j));

        dirac_complex_t k = 0 + (-1*I);
        fprintf(stderr, "k=%lf%+lfi\n", creal(k), cimag(k));
        diminuto_dump(stderr, &k, sizeof(k));
        fprintf(stderr, "k^2=%lf%+lfi\n", creal(k*k), cimag(k*k));

        STATUS();
    }

    {
        TEST();

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
        const dirac_complex_t * matrix;

        that.data.head.rows = 5;
        that.data.head.columns = 7;

        rows = dirac_rows_get(&that);
        ASSERT(rows == 5);

        columns = dirac_columns_get(&that);
        ASSERT(columns == 7);

        matrix = dirac_body_get(&that);
        ASSERT(matrix == &(that.data.body[0][0]));

        STATUS();
    }

    {
        TEST();

        dirac_t * new1 = dirac_new(0, 0);
        ASSERT(new1 != (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new2 = dirac_new(2, 3);
        ASSERT(new2 != (dirac_t *)0);
        ASSERT(new2 != new1);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new3 = dirac_new(3, 2);
        ASSERT(new3 != (dirac_t *)0);
        ASSERT(new3 != new1);
        ASSERT(new3 != new2);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new4 = dirac_new(4, 4);
        ASSERT(new4 != (dirac_t *)0);
        ASSERT(new4 != new1);
        ASSERT(new4 != new2);
        ASSERT(new4 != new3);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete3 = dirac_delete(new3);
        ASSERT(delete3 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete1 = dirac_delete(new1);
        ASSERT(delete1 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete4 = dirac_delete(new4);
        ASSERT(delete4 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete2 = dirac_delete(new2);
        ASSERT(delete2 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new5 = dirac_new(0, 0);
        ASSERT(new5 != (dirac_t *)0);
        ASSERT(new5 == new1);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new6 = dirac_new(2, 3);
        ASSERT(new6 != (dirac_t *)0);
        ASSERT(new6 == new3);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new7 = dirac_new(3, 2);
        ASSERT(new7 != (dirac_t *)0);
        ASSERT(new7 == new2);
        ASSERT(new7 != new6);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new8 = dirac_new(4, 4);
        ASSERT(new8 != (dirac_t *)0);
        ASSERT(new8 == new4);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete7 = dirac_delete(new7);
        ASSERT(delete7 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete5 = dirac_delete(new5);
        ASSERT(delete5 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete8 = dirac_delete(new8);
        ASSERT(delete8 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete6 = dirac_delete(new6);
        ASSERT(delete6 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        STATUS();
    }

    {
        TEST();

        ASSERT(sizeof(dirac_t) == sizeof(dirac_node_t));

        DIRAC_OBJECT_DECL(0, 0) thing1 = DIRAC_OBJECT_INIT(0, 0);
        ASSERT(sizeof(thing1) == sizeof(dirac_node_t));

        DIRAC_OBJECT_DECL(1, 1) thing2 = DIRAC_OBJECT_INIT(1, 1);
        ASSERT(sizeof(thing2) == sizeof(dirac_node_t));

        DIRAC_OBJECT_DECL(1, 2) thing3 = DIRAC_OBJECT_INIT(1, 2);
        ASSERT(sizeof(thing3) == sizeof(dirac_node_t));

        DIRAC_OBJECT_DECL(1, 3) thing4 = DIRAC_OBJECT_INIT(1, 3);
        ASSERT(sizeof(thing4) > sizeof(dirac_node_t));

        dirac_t * that = dirac_new(0, 0);
        ASSERT(sizeof(*that) == sizeof(dirac_node_t));
        that = dirac_delete(that);
        ASSERT(that == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(11, 17) thing = DIRAC_OBJECT_INIT(11, 17);

        dirac_t * that = dirac_new_dup((dirac_t *)&thing);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_rows_get(that) == 11);
        ASSERT(dirac_columns_get(that) == 17);

        that = dirac_delete(that);
        ASSERT(that == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(19, 23) thing = DIRAC_OBJECT_INIT(19, 23);

        dirac_t * that = dirac_new_trn((dirac_t *)&thing);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_rows_get(that) == 23);
        ASSERT(dirac_columns_get(that) == 19);

        that = dirac_delete(that);
        ASSERT(that == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(2, 3) thing1 = DIRAC_OBJECT_INIT(2, 3);
        DIRAC_OBJECT_DECL(2, 4) thing2 = DIRAC_OBJECT_INIT(2, 4);
        DIRAC_OBJECT_DECL(3, 3) thing3 = DIRAC_OBJECT_INIT(3, 3);
        DIRAC_OBJECT_DECL(2, 3) thing4 = DIRAC_OBJECT_INIT(2, 3);

        dirac_t * that;

        that = dirac_new_sum((dirac_t *)&thing1, (dirac_t *)&thing2);
        ASSERT(that == (dirac_t *)0);

        that = dirac_new_sum((dirac_t *)&thing1, (dirac_t *)&thing3);
        ASSERT(that == (dirac_t *)0);

        that = dirac_new_sum((dirac_t *)&thing1, (dirac_t *)&thing4);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_rows_get((dirac_t *)that) == 2);
        ASSERT(dirac_columns_get((dirac_t *)that) == 3);

        that = dirac_delete(that);
        ASSERT(that == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(3, 5) thing1 = DIRAC_OBJECT_INIT(3, 5);
        DIRAC_OBJECT_DECL(3, 5) thing2 = DIRAC_OBJECT_INIT(3, 5);
        DIRAC_OBJECT_DECL(5, 7) thing3 = DIRAC_OBJECT_INIT(5, 7);

        dirac_t * that;

        that = dirac_new_pro((dirac_t *)&thing1, (dirac_t *)&thing2);
        ASSERT(that == (dirac_t *)0);

        that = dirac_new_pro((dirac_t *)&thing1, (dirac_t *)&thing3);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_rows_get(that) == 5);
        ASSERT(dirac_columns_get(that) == 5);

        that = dirac_delete(that);
        ASSERT(that == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(3, 5) thing1 = DIRAC_OBJECT_INIT(3, 5);
        DIRAC_OBJECT_DECL(7, 11) thing2 = DIRAC_OBJECT_INIT(7, 11);

        dirac_t * that;

        that = dirac_new_kro((dirac_t *)&thing1, (dirac_t *)&thing2);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_rows_get((dirac_t *)that) == (3 * 7));
        ASSERT(dirac_columns_get((dirac_t *)that) == (5 * 11));

        that = dirac_delete(that);
        ASSERT(that == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(3, 5) thing1 = DIRAC_OBJECT_INIT(3, 5);
        DIRAC_OBJECT_DECL(3, 11) thing2 = DIRAC_OBJECT_INIT(7, 11);
        DIRAC_OBJECT_DECL(7, 5) thing3 = DIRAC_OBJECT_INIT(7, 11);
        DIRAC_OBJECT_DECL(3, 5) thing4 = DIRAC_OBJECT_INIT(3, 5);

        dirac_t * that;

        that = dirac_new_had((dirac_t *)&thing1, (dirac_t *)&thing2);
        ASSERT(that == (dirac_t *)0);

        that = dirac_new_had((dirac_t *)&thing1, (dirac_t *)&thing3);
        ASSERT(that == (dirac_t *)0);

        that = dirac_new_had((dirac_t *)&thing1, (dirac_t *)&thing4);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_rows_get((dirac_t *)that) == 3);
        ASSERT(dirac_columns_get((dirac_t *)that) == 5);

        that = dirac_delete(that);
        ASSERT(that == (dirac_t *)0);

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
        ASSERT(dirac_rows_get(that) == ROWS);
        ASSERT(dirac_columns_get(that) == COLS);

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
                aa = &((dirac_body_mut(that))[ii]);
                fprintf(stderr, "body(%u,%u)[%u]@%p\n", rr, cc, ii, aa);
                ASSERT(*aa == CMPLX(0, 0));
            }
        }

        here = (array_t *)(&(that->data.body[0][0]));

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
                fprintf(stderr, "value=%lf%+lfi\n", creal(value), cimag(value));
                ASSERT(value == CMPLX(rr, cc));
                ASSERT((*here)[rr][cc] == value);
                ASSERT(((unsigned int)creal((*here)[rr][cc])) == rr);
                ASSERT(((unsigned int)cimag((*here)[rr][cc])) == cc);
            }
        }

        dirac_delete(that);

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
                cc = &(dirac_body_mut(that)[dirac_index(that, row, col)]);
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

        STATUS();
    }

    {
        TEST();

        DIRAC_OBJECT_DECL(0, 0) thing = DIRAC_OBJECT_INIT(0, 0);
        dirac_t * that = (dirac_t *)&thing;

        ASSERT(dirac_rows_get(that) == 0);
        ASSERT(dirac_columns_get(that) == 0);

        ASSERT(sizeof(thing) == sizeof(*that));

        STATUS();
    }

    {
        TEST();

#define ROWS 5
#define COLS 7

        DIRAC_OBJECT_DECL(ROWS, COLS) thing = DIRAC_OBJECT_INIT(ROWS, COLS);
        dirac_t * that = (dirac_t *)&thing;
        DIRAC_ARRAY_TYPE(array3x4_t, ROWS, COLS);
        array3x4_t * array3x4p;
        dirac_complex_t * aa;
        dirac_complex_t * bb;
        dirac_complex_t * cc;
        dirac_complex_t * dd;
        unsigned int row, col;

        ASSERT(dirac_rows_get(that) == ROWS);
        ASSERT(dirac_columns_get(that) == COLS);

        ASSERT(sizeof(thing) > sizeof(*that));

        fprintf(stderr, "sizeof(thing)=%zu\n", sizeof(thing));
        fprintf(stderr, "sizeof(thing.data)=%zu\n", sizeof(thing.data));
        fprintf(stderr, "sizeof(thing.data.head)=%zu\n", sizeof(thing.data.head));
        fprintf(stderr, "sizeof(thing.data.body)=%zu\n", sizeof(thing.data.body));
        fprintf(stderr, "sizeof(thing.node)=%zu\n", sizeof(thing.node));

        aa = &((dirac_body_mut(that))[0]);
        bb = &((dirac_body_mut(that))[(ROWS * COLS) - 1]);
        cc = &(thing.data.body[0][0]);
        dd = &(thing.data.body[ROWS - 1][COLS - 1]);
        fprintf(stderr, "that[%u]=%p\n", 0, aa);
        fprintf(stderr, "that[%zu]=%p\n", (ROWS * COLS) - 1, bb);
        fprintf(stderr, "thing[%u]=%p\n", 0, cc);
        fprintf(stderr, "thing[%zu]=%p\n", countof(thing.data.body) - 1, dd);
        ASSERT(aa == cc);
        ASSERT(bb == dd);

        array3x4p = DIRAC_ARRAY_POINTER(array3x4_t, that);

        for (row = 0; row < ROWS; ++row) {
            for (col = 0; col < COLS; ++col) {
                ASSERT((*array3x4p)[row][col] == (0+(0*I)));
                (*array3x4p)[row][col] = CMPLX(row, col);
                aa = dirac_point(that, row, col);
                bb = &((*array3x4p)[row][col]);
                cc = &(dirac_body_mut(that)[dirac_index(that, row, col)]);
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

    {
        TEST();

        const size_t ROWS = 5;
        const size_t COLS = 7;

        DIRAC_OBJECT_DECL(ROWS, COLS) thing;
        DIRAC_ARRAY_TYPE(array3x4_t, ROWS, COLS);
        array3x4_t * array3x4p;
        dirac_complex_t * aa;
        dirac_complex_t * bb;
        dirac_complex_t * cc;
        dirac_complex_t * dd;
        unsigned int row, col;

        dirac_t * that = dirac_init((dirac_t *)&thing, ROWS, COLS);
        ASSERT(that == (dirac_t *)&thing);

        ASSERT(dirac_rows_get(that) == ROWS);
        ASSERT(dirac_columns_get(that) == COLS);

        ASSERT(sizeof(thing) > sizeof(*that));

        fprintf(stderr, "sizeof(thing)=%zu\n", sizeof(thing));
        fprintf(stderr, "sizeof(thing.data)=%zu\n", sizeof(thing.data));
        fprintf(stderr, "sizeof(thing.data.head)=%zu\n", sizeof(thing.data.head));
        fprintf(stderr, "sizeof(thing.data.body)=%zu\n", sizeof(thing.data.body));
        fprintf(stderr, "sizeof(thing.node)=%zu\n", sizeof(thing.node));

        aa = &((dirac_body_mut(that))[0]);
        bb = &((dirac_body_mut(that))[(ROWS * COLS) - 1]);
        cc = &(thing.data.body[0][0]);
        dd = &(thing.data.body[ROWS - 1][COLS - 1]);
        fprintf(stderr, "that[%u]=%p\n", 0, aa);
        fprintf(stderr, "that[%zu]=%p\n", (ROWS * COLS) - 1, bb);
        fprintf(stderr, "thing[%u]=%p\n", 0, cc);
        fprintf(stderr, "thing[%zu]=%p\n", countof(thing.data.body) - 1, dd);
        ASSERT(aa == cc);
        ASSERT(bb == dd);

        array3x4p = DIRAC_ARRAY_POINTER(array3x4_t, that);

        for (row = 0; row < ROWS; ++row) {
            for (col = 0; col < COLS; ++col) {
                ASSERT((*array3x4p)[row][col] == (0+(0*I)));
                (*array3x4p)[row][col] = CMPLX(row, col);
                aa = dirac_point(that, row, col);
                bb = &((*array3x4p)[row][col]);
                cc = &(dirac_body_mut(that)[dirac_index(that, row, col)]);
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

#endif

    EXIT();
}
