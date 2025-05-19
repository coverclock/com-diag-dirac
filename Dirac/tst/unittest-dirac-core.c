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
#include "dirac.h"

int main(void)
{
    SETLOGMASK();

    {
        TEST();

        fprintf(stderr, "sizeof(double)=%zu\n", sizeof(double));
        fprintf(stderr, "sizeof(complex double)=%zu\n", sizeof(complex double));
        fprintf(stderr, "sizeof(dirac_complex_t)=%zu\n", sizeof(dirac_complex_t));
        fprintf(stderr, "sizeof(dirac_matrix_t)=%zu\n", sizeof(dirac_matrix_t));
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

        dirac_t object;

        object.data.head.rows = 5;
        object.data.head.columns = 7;

        dirac_matrix_t * them = dirac_core_matrix_mut(&object);
        ASSERT(them == &(object.data.body[0][0]));

        const dirac_matrix_t * them2 = dirac_core_matrix_get(&object);
        ASSERT(them2 == &(object.data.body[0][0]));

        size_t rows;
        size_t columns;

        rows = dirac_rows_get(them);
        ASSERT(rows == 5);

        columns = dirac_cols_get(them);
        ASSERT(columns == 7);

        dirac_t * that = dirac_core_object_mut(them);
        ASSERT(that == &object);

        const dirac_t * that2 = dirac_core_object_get(them2);
        ASSERT(that == &object);

        rows = dirac_core_rows_get(that2);
        ASSERT(rows == 5);

        columns = dirac_core_cols_get(that2);
        ASSERT(columns == 7);

        dirac_complex_t * body = dirac_core_body_mut(that);
        ASSERT(body == &(object.data.body[0][0]));

        const dirac_complex_t * body2 = dirac_core_body_get(that2);
        ASSERT(body2 == &(object.data.body[0][0]));

        STATUS();
    }

    {
        TEST();

        dirac_t * new1 = dirac_core_allocate(0, 0);
        fprintf(stderr, "new1=%p\n", new1);
        dirac_core_print(stderr, new1);
        ASSERT(new1 != (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new2 = dirac_core_allocate(2, 3);
        fprintf(stderr, "new2=%p\n", new2);
        dirac_core_print(stderr, new2);
        ASSERT(new2 != (dirac_t *)0);
        ASSERT(new2 != new1);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new3 = dirac_core_allocate(3, 2);
        fprintf(stderr, "new3=%p\n", new3);
        dirac_core_print(stderr, new3);
        ASSERT(new3 != (dirac_t *)0);
        ASSERT(new3 != new1);
        ASSERT(new3 != new2);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new4 = dirac_core_allocate(4, 4);
        fprintf(stderr, "new4=%p\n", new4);
        dirac_core_print(stderr, new4);
        ASSERT(new4 != (dirac_t *)0);
        ASSERT(new4 != new1);
        ASSERT(new4 != new2);
        ASSERT(new4 != new3);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete3 = dirac_core_free(new3);
        ASSERT(delete3 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete1 = dirac_core_free(new1);
        ASSERT(delete1 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete4 = dirac_core_free(new4);
        ASSERT(delete4 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete2 = dirac_core_free(new2);
        ASSERT(delete2 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new5 = dirac_core_allocate(0, 0);
        fprintf(stderr, "new5=%p\n", new5);
        dirac_core_print(stderr, new5);
        ASSERT(new5 != (dirac_t *)0);
        ASSERT(new5 == new1);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new6 = dirac_core_allocate(2, 3);
        fprintf(stderr, "new6=%p\n", new6);
        dirac_core_print(stderr, new6);
        ASSERT(new6 != (dirac_t *)0);
        ASSERT(new6 == new3);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new7 = dirac_core_allocate(3, 2);
        fprintf(stderr, "new7=%p\n", new7);
        dirac_core_print(stderr, new7);
        ASSERT(new7 != (dirac_t *)0);
        ASSERT(new7 == new2);
        ASSERT(new7 != new6);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * new8 = dirac_core_allocate(4, 4);
        fprintf(stderr, "new8=%p\n", new8);
        dirac_core_print(stderr, new8);
        ASSERT(new8 != (dirac_t *)0);
        ASSERT(new8 == new4);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete7 = dirac_core_free(new7);
        ASSERT(delete7 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete5 = dirac_core_free(new5);
        ASSERT(delete5 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete8 = dirac_core_free(new8);
        ASSERT(delete8 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        dirac_t * delete6 = dirac_core_free(new6);
        ASSERT(delete6 == (dirac_t *)0);
        ASSERT(dirac_dump(stderr) >= 0);

        STATUS();
    }


    {
        TEST();

        dirac_matrix_t * them = dirac_new(0, 0);
        ASSERT(them != (dirac_matrix_t *)0);
        dirac_print(stdout, them);
        dirac_delete(them);

        STATUS();
    }

    {
        TEST();

        dirac_dump(stdout);

        dirac_complex_t (*them)[2][3] = dirac_new(2, 3);
        ASSERT((void *)them != (void *)0);

        dirac_print(stdout, them);

        size_t rows = dirac_rows_get(them);
        size_t cols = dirac_cols_get(them);
        ASSERT(rows == 2);
        ASSERT(cols == 3);

        int rr;
        int cc;
        for (rr = 0; rr < rows; ++rr) {
            for (cc = 0; cc < cols; ++cc) {
                (*them)[rr][cc] = CMPLX((double)rr, (double)cc);
            }
        }
        dirac_print(stdout, them);

        dirac_delete(them);

        dirac_dump(stdout);

        dirac_free();

        dirac_dump(stdout);

        STATUS();
    }

    {
        TEST();

        dirac_t * that0 = dirac_core_allocate(11, 17);
        ASSERT(that0 != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that0) == 11);
        ASSERT(dirac_core_cols_get(that0) == 17);

        dirac_t * that1 = dirac_core_dup(that0);
        ASSERT(that1 != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that1) == 11);
        ASSERT(dirac_core_cols_get(that1) == 17);

        that1 = dirac_core_free(that1);
        ASSERT(that1 == (dirac_t *)0);

        that0 = dirac_core_free(that0);
        ASSERT(that0 == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        dirac_t * that0 = dirac_core_allocate(11, 17);
        ASSERT(that0 != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that0) == 11);
        ASSERT(dirac_core_cols_get(that0) == 17);

        dirac_t * that1 = dirac_core_trn(that0);
        ASSERT(that1 != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that1) == 17);
        ASSERT(dirac_core_cols_get(that1) == 11);

        that1 = dirac_core_free(that1);
        ASSERT(that1 == (dirac_t *)0);

        that0 = dirac_core_free(that0);
        ASSERT(that0 == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        dirac_t * that1 = dirac_core_allocate(2, 3);
        ASSERT(that1 != (dirac_t *)0);

        dirac_t * that2 = dirac_core_allocate(2, 4);
        ASSERT(that2 != (dirac_t *)0);

        dirac_t * that3 = dirac_core_allocate(4, 3);
        ASSERT(that3 != (dirac_t *)0);

        dirac_t * that4 = dirac_core_allocate(2, 3);
        ASSERT(that4 != (dirac_t *)0);

        dirac_t * that;

        that = dirac_core_sum(that1, that2);
        ASSERT(that == (dirac_t *)0);

        that = dirac_core_sum(that1, that3);
        ASSERT(that == (dirac_t *)0);

        that = dirac_core_sum(that1, that4);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that) == 2);
        ASSERT(dirac_core_cols_get(that) == 3);

        that = dirac_core_free(that);
        ASSERT(that == (dirac_t *)0);

        that4 = dirac_core_free(that4);
        ASSERT(that4 == (dirac_t *)0);

        that3 = dirac_core_free(that3);
        ASSERT(that3 == (dirac_t *)0);

        that2 = dirac_core_free(that2);
        ASSERT(that2 == (dirac_t *)0);

        that1 = dirac_core_free(that1);
        ASSERT(that1 == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        dirac_t * that1 = dirac_core_allocate(3, 5);
        ASSERT(that1 != (dirac_t *)0);

        dirac_t * that2 = dirac_core_allocate(9, 3);
        ASSERT(that2 != (dirac_t *)0);

        dirac_t * that3 = dirac_core_allocate(5, 7);
        ASSERT(that3 != (dirac_t *)0);

        dirac_t * that;

        that = dirac_core_pro(that1, that2);
        ASSERT(that == (dirac_t *)0);

        that = dirac_core_pro(that1, that3);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that) == 5);
        ASSERT(dirac_core_cols_get(that) == 5);

        that = dirac_core_free(that);
        ASSERT(that == (dirac_t *)0);

        that2 = dirac_core_free(that2);
        ASSERT(that2 == (dirac_t *)0);

        that1 = dirac_core_free(that1);
        ASSERT(that1 == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        dirac_t * that1 = dirac_core_allocate(3, 5);
        ASSERT(that1 != (dirac_t *)0);

        dirac_t * that2 = dirac_core_allocate(7, 11);
        ASSERT(that2 != (dirac_t *)0);

        dirac_t * that = dirac_core_kro(that1, that2);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that) == (3 * 7));
        ASSERT(dirac_core_cols_get(that) == (5 * 11));

        that = dirac_core_free(that);
        ASSERT(that == (dirac_t *)0);

        that2 = dirac_core_free(that2);
        ASSERT(that2 == (dirac_t *)0);

        that1 = dirac_core_free(that1);
        ASSERT(that1 == (dirac_t *)0);

        STATUS();
    }

    {
        TEST();

        dirac_t * that1 = dirac_core_allocate(3, 5);
        ASSERT(that1 != (dirac_t *)0);

        dirac_t * that2 = dirac_core_allocate(5, 3);
        ASSERT(that2 != (dirac_t *)0);

        dirac_t * that3 = dirac_core_allocate(7, 11);
        ASSERT(that3 != (dirac_t *)0);

        dirac_t * that4 = dirac_core_allocate(3, 5);
        ASSERT(that4 != (dirac_t *)0);

        dirac_t * that;

        that = dirac_core_had(that1, that2);
        ASSERT(that == (dirac_t *)0);

        that = dirac_core_had(that1, that3);
        ASSERT(that == (dirac_t *)0);

        that = dirac_core_had(that1, that4);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that) == 3);
        ASSERT(dirac_core_cols_get(that) == 5);

        that = dirac_core_free(that);
        ASSERT(that == (dirac_t *)0);

        that4 = dirac_core_free(that4);
        ASSERT(that4 == (dirac_t *)0);

        that3 = dirac_core_free(that3);
        ASSERT(that3 == (dirac_t *)0);

        that2 = dirac_core_free(that2);
        ASSERT(that2 == (dirac_t *)0);

        that1 = dirac_core_free(that1);
        ASSERT(that1 == (dirac_t *)0);

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

        that = dirac_core_allocate(ROWS, COLS);
        ASSERT(that != (dirac_t *)0);
        ASSERT(dirac_core_rows_get(that) == ROWS);
        ASSERT(dirac_core_cols_get(that) == COLS);

        ASSERT(dirac_core_point_fast(that, 0, 0) != (dirac_complex_t *)0);
        ASSERT(dirac_core_point_fast(that, ROWS - 1, COLS - 1) != (dirac_complex_t *)0);
        ASSERT(dirac_core_point_fast(that, ROWS, COLS - 1) != (dirac_complex_t *)0);
        ASSERT(dirac_core_point_fast(that, ROWS - 1, COLS) != (dirac_complex_t *)0);
        ASSERT(dirac_core_point_fast(that, ROWS, COLS) != (dirac_complex_t *)0);

        ASSERT(dirac_core_point_safe(that, 0, 0) != (dirac_complex_t *)0);
        ASSERT(dirac_core_point_safe(that, ROWS - 1, COLS - 1) != (dirac_complex_t *)0);
        ASSERT(dirac_core_point_safe(that, ROWS, COLS - 1) == (dirac_complex_t *)0);
        ASSERT(dirac_core_point_safe(that, ROWS - 1, COLS) == (dirac_complex_t *)0);
        ASSERT(dirac_core_point_safe(that, ROWS, COLS) == (dirac_complex_t *)0);

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                aa = dirac_core_point(that, rr, cc);
                fprintf(stderr, "node(%u,%u)@%p\n", rr, cc, aa);
                ASSERT(*aa == CMPLX(0, 0));
            }
        }

        for (rr = 0; rr < ROWS; ++rr) {
            for (cc = 0; cc < COLS; ++cc) {
                ii = dirac_core_index(that, rr, cc);
                aa = &((dirac_core_body_mut(that))[ii]);
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
                aa = dirac_core_point(that, rr, cc);
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

        dirac_core_free(that);

        STATUS();
    }

    {
        TEST();

        static const size_t ROWS = 3;
        static const size_t COLS = 4;

        dirac_complex_t (*them)[ROWS][COLS] = dirac_new(ROWS, COLS);
        dirac_t * that = dirac_core_object_mut(them);

        dirac_complex_t * aa;
        dirac_complex_t * bb;
        dirac_complex_t * cc;
        unsigned int row, col;

        ASSERT(dirac_rows_get(them) == ROWS);
        ASSERT(dirac_cols_get(them) == COLS);

        ASSERT(dirac_core_rows_get(that) == ROWS);
        ASSERT(dirac_core_cols_get(that) == COLS);

        for (row = 0; row < ROWS; ++row) {
            for (col = 0; col < COLS; ++col) {
                ASSERT((*them)[row][col] == (0+(0*I)));
                (*them)[row][col] = CMPLX(row, col);
                aa = dirac_core_point(that, row, col);
                bb = &((*them)[row][col]);
                cc = &(dirac_core_body_mut(that)[dirac_core_index(that, row, col)]);
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

        dirac_delete(them);

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
