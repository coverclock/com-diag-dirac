/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA<BR>
 * Licensed under the terms in LICENSE.txt<BR>
 * Chip Overclock (mailto:coverclock@diag.com)<BR>
 * https://github.com/coverclock/com-diag-cdirac<BR>
 *
 * Defines the implementation for Dirac.
 */

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "com/diag/dirac/dirac.h"
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "dirac.h"

/*******************************************************************************
 * GLOBALS
 ******************************************************************************/

static diminuto_tree_root_t root = DIMINUTO_TREE_EMPTY;

/*******************************************************************************
 * HELPERS
 ******************************************************************************/

static inline size_t count(size_t rows, size_t columns) {
    return rows * columns;
}

static inline size_t length(size_t rows, size_t columns) {
    return count(rows, columns) * sizeof(complex double);
}

static inline size_t size(size_t rows, size_t columns) {
    return length(rows, columns) + sizeof(dirac_t);
}

static dirac_t * construct(dirac_t * that, size_t rows, size_t columns)
{
    if (that != (dirac_t *)0) {
        memset(&(that->data.matrix), 0, length(rows, columns));
        that->data.rows = rows;
        that->data.columns = columns;
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
    diminuto_tree_t * you = diminuto_tree_search(root, &me, compare, &rc);
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
    return construct(that, rows, columns);;
}

dirac_t * dirac_delete(dirac_t * that)
{
    diminuto_tree_t * me = diminuto_tree_init(&(that->node.tree));
    that->node.size = size(that->data.rows, that->data.columns);
    diminuto_tree_t * you = diminuto_tree_search_insert_or_replace(&root, me, compare, !0);
    if (you == (diminuto_tree_t *)0) {
        /* Do  nothing. */
    } else if (you == me) {
        me->data = (void *)0;
        that = (dirac_t *)0;
    } else {
        me->data = (void *)you;
        that = (dirac_t *)0;
    }
    return that;
}

void dirac_free(void)
{
    diminuto_tree_t * nodep;
    diminuto_tree_t * nextp;
    diminuto_tree_t * peerp;
    diminuto_tree_t * linkp;
    nodep = diminuto_tree_first(&root);
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
}

/*******************************************************************************
 * DUMPING
 ******************************************************************************/

void dirac_dump(FILE * fp)
{
    diminuto_tree_root_t * rootp;
    diminuto_tree_t * nodep;
    diminuto_tree_t * nextp;
    dirac_t * that;
    fprintf(fp, "dirac_dump: begin\n");
    for (rootp = &root, nodep = diminuto_tree_first(rootp); nodep != DIMINUTO_TREE_NULL; nodep = diminuto_tree_next(nodep)) {
        that = (dirac_t *)nodep;
        fprintf(fp, "dirac_dump: @%p[%zu]", that, that->node.size);
        nextp = nodep->data;
        while (nextp != (void *)0) {
            that = (dirac_t *)nextp;
            fprintf(fp, " @%p[%zu]", that, that->node.size);
            nextp = nextp->data;
        }
        fputc('\n', fp);
    }
    fprintf(fp, "dirac_dump: end\n");
    fflush(fp);
}

/*******************************************************************************
 * OPERATIONS
 ******************************************************************************/
