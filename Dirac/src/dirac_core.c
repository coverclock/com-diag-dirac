/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA<BR>
 * Licensed under the terms in LICENSE.txt<BR>
 * Chip Overclock (mailto:coverclock@diag.com)<BR>
 * https://github.com/coverclock/com-diag-cdirac<BR>
 *
 * This is the implementation of the cache-related portions of Dirac.
 */

/*******************************************************************************
 * PREREQUISITES
 ******************************************************************************/

#include "com/diag/dirac/dirac.h"
#include "com/diag/diminuto/diminuto_criticalsection.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "dirac.h"

/*******************************************************************************
 * GLOBALS
 ******************************************************************************/

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static diminuto_tree_root_t cache = DIMINUTO_TREE_EMPTY;

/*******************************************************************************
 * HELPERS
 ******************************************************************************/

static inline size_t count(size_t rows, size_t columns) {
    return rows * columns;
}

static inline size_t length(size_t rows, size_t columns) {
    return count(rows, columns) * sizeof(dirac_complex_t);
}

static inline size_t size(size_t rows, size_t columns) {
    size_t bytes = length(rows, columns) + sizeof(dirac_data_t);
    if (bytes < sizeof(dirac_node_t)) { bytes = sizeof(dirac_node_t); }
    return bytes;
}

static dirac_t * construct(dirac_t * that, size_t rows, size_t columns)
{
    if (that != (dirac_t *)0) {
        memset(dirac_body_mut(that), 0, length(rows, columns));
        that->data.head.rows = rows;
        that->data.head.columns = columns;
    }
    return that;
}

static int compare(const diminuto_tree_t * a, const diminuto_tree_t * b)
{
    dirac_t * aa = (dirac_t *)a;
    dirac_t * bb = (dirac_t *)b;
    /* Didn't use subtraction so as to insure result fits in an int. */
    if (aa->node.size < bb->node.size) {
        return -1;
    } else if (aa->node.size > bb->node.size) {
        return 1;
    } else {
        return 0;
    }
}

static inline dirac_t * allocate(size_t rows, size_t columns)
{
    return (dirac_t *)malloc(size(rows, columns));
}

/*******************************************************************************
 * MEMORY MANAGEMENT
 ******************************************************************************/

dirac_t * dirac_new(size_t rows, size_t columns)
{
    diminuto_tree_t me = DIMINUTO_TREE_NULLINIT;
    dirac_t * that = (dirac_t *)&me;
    that->node.size = size(rows, columns);
    int rc = 0;
    DIMINUTO_CRITICAL_SECTION_BEGIN(&mutex);
        diminuto_tree_t * you = diminuto_tree_search(cache, &me, compare, &rc);
        if (you == (diminuto_tree_t *)0) {
            that = allocate(rows, columns);
        } else if (rc != 0) {
            that = allocate(rows, columns);
        } else if (you->data == (void *)0) {
            that = (dirac_t *)diminuto_tree_remove(you);
        } else {
            that = (dirac_t *)(you->data);
            you->data = ((diminuto_tree_t *)(you->data))->data;
        }
    DIMINUTO_CRITICAL_SECTION_END;
    return construct(that, rows, columns);
}

dirac_t * dirac_delete(dirac_t * that)
{
    size_t bytes = size(dirac_rows_get(that), dirac_columns_get(that));
    diminuto_tree_t * me = diminuto_tree_init(&(that->node.tree));
    that->node.size = bytes;
    DIMINUTO_CRITICAL_SECTION_BEGIN(&mutex);
        diminuto_tree_t * you = diminuto_tree_search_insert_or_replace(&cache, me, compare, !0);
        if (you == (diminuto_tree_t *)0) {
            /* Do  nothing. */
        } else if (you == me) {
            me->data = (void *)0;
            that = (dirac_t *)0;
        } else {
            me->data = (void *)you;
            that = (dirac_t *)0;
        }
    DIMINUTO_CRITICAL_SECTION_END;
    return that;
}

void dirac_free(void)
{
    diminuto_tree_t * nodep = (diminuto_tree_t *)0;
    diminuto_tree_t * nextp = (diminuto_tree_t *)0;
    diminuto_tree_t * peerp = (diminuto_tree_t *)0;
    diminuto_tree_t * linkp = (diminuto_tree_t *)0;
    DIMINUTO_CRITICAL_SECTION_BEGIN(&mutex);
        nodep = diminuto_tree_first(&cache);
        while (nodep != DIMINUTO_TREE_NULL) {
            nextp = diminuto_tree_next(nodep);
            (void)diminuto_tree_remove(nodep);
            peerp = nodep->data;
            while (peerp != DIMINUTO_TREE_NULL) {
                linkp = peerp->data;
                free(peerp);
                peerp = linkp;
            }
            free(nodep);
            nodep = nextp;
        }
    DIMINUTO_CRITICAL_SECTION_END;
}

/*******************************************************************************
 * INITIALIZATION
 ******************************************************************************/

dirac_t * dirac_init(dirac_t * that, size_t rows, size_t columns)
{
    return construct(that, rows, columns);
}

/*******************************************************************************
 * ADDRESSING AND INDEXING
 ******************************************************************************/

dirac_complex_t * dirac_point_safe(dirac_t * that, unsigned int row, unsigned int column) {
    dirac_complex_t * here = (dirac_complex_t *)0;
    if (row >= dirac_rows_get(that)) {
        /* Do nothing. */
    } else if (column >= dirac_columns_get(that)) {
        /* Do nothing. */
    } else {
        here = dirac_point_fast(that, row, column);
    }
    return here;
}


/*******************************************************************************
 * DEBUGGING
 ******************************************************************************/

dirac_t * dirac_audit(void)
{
    return (dirac_t *)diminuto_tree_audit(&cache);
}

ssize_t dirac_dump(FILE * fp)
{
    ssize_t total = 0;
    diminuto_tree_root_t * rootp = (diminuto_tree_root_t *)0;
    diminuto_tree_t * nodep = (diminuto_tree_t *)0;
    diminuto_tree_t * nextp = (diminuto_tree_t *)0;
    dirac_t * that = (dirac_t *)0;
    DIMINUTO_CRITICAL_SECTION_BEGIN(&mutex);
        that = dirac_audit();
        if (that == (dirac_t *)0) {
            if (fp != (FILE *)0) { fprintf(fp, "dirac_dump: begin\n"); }
            for (rootp = &cache, nodep = diminuto_tree_first(rootp); nodep != DIMINUTO_TREE_NULL; nodep = diminuto_tree_next(nodep)) {
                that = (dirac_t *)nodep;
                total += that->node.size;
                if (fp != (FILE *)0) { fprintf(fp, "dirac_dump: @%p[%zu]", that, that->node.size); }
                nextp = nodep->data;
                while (nextp != (void *)0) {
                    that = (dirac_t *)nextp;
                    if (fp != (FILE *)0) { fprintf(fp, " @%p[%zu]", that, that->node.size); }
                    nextp = nextp->data;
                }
                if (fp != (FILE *)0) { fputc('\n', fp); }
            }
            if (fp != (FILE *)0) { fprintf(fp, "dirac_dump: end [%zd]\n", total); }
        } else {
            if (fp != (FILE *)0) { fprintf(fp, "dirac_dump: @%p[%zu] FAILED!\n", that, that->node.size); }
            total = -1;
        }
    DIMINUTO_CRITICAL_SECTION_END;
    fflush(fp);
    return total;
}

const dirac_t * dirac_print(FILE * fp, const dirac_t * that)
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
                fprintf(fp, " (%7.4le%+7.4lei)", creal((tt)[ii]), cimag((tt)[ii]));
            }
            fputc('\n', fp);
        }
    }
    fflush(fp);
    return that;
}

/*******************************************************************************
 * END
 ******************************************************************************/
