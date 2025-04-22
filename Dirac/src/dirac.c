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
#include "com/diag/diminuto/diminuto_assert.h"
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
 * MEMORY MANAGEMENT
 ******************************************************************************/

dirac_t * dirac_alloc(size_t rows, size_t columns)
{
    size_t size = dirac_size(rows, columns);
    dirac_t * that = (dirac_t *)malloc(size);
    if (that == (dirac_t *)0) {
        perror("malloc");
    }
    return that;
}

dirac_t * dirac_init(dirac_t * that, size_t rows, size_t columns)
{
    memset(&(that->data.matrix), 0, dirac_length(rows, columns));
    that->data.rows = rows;
    that->data.columns = columns;
    return that;
}

static int compare(const diminuto_tree_t * a, const diminuto_tree_t * b)
{
    dirac_t * aa = (dirac_t *)a;
    dirac_t * bb = (dirac_t *)b;
    /*
     * Didn't use subtraction to insure result fits in an int.
     */
    if (aa->node.size < bb->node.size) {
        return -1;
    } else if (aa->node.size > bb->node.size) {
        return 1;
    } else {
        return 0;
    }
}

dirac_t * dirac_new(size_t rows, size_t columns)
{
    diminuto_tree_t me = DIMINUTO_TREE_NULLINIT;
    dirac_t * that = (dirac_t *)&me;
    that->node.size = dirac_count(rows, columns);
    int rc = 0;
    diminuto_tree_t * you = diminuto_tree_search(root, &me, compare, &rc);
    if ((that == (dirac_t *)0) || (rc != 0)) {
        that = dirac_alloc(rows, columns);
    } else if (you->data == (void *)0) {
        that = (dirac_t *)diminuto_tree_remove(you);
    } else {
        that = (dirac_t *)(you->data);
        you->data = ((diminuto_tree_t *)(you->data))->data;
    }
    return that;
}

dirac_t * dirac_delete(dirac_t * that)
{
    diminuto_tree_t * me = diminuto_tree_init(&(that->node.tree));
    that->node.size = dirac_count(that->data.rows, that->data.columns);
    diminuto_tree_t * you = diminuto_tree_search_insert_or_replace(&root, me, compare, !0);
    if (you != (diminuto_tree_t *)0) {
        that = (dirac_t *)0;
        if (you == me) {
            me->data = (void *)0;
        } else {
            me->data = (void *)you;
        }
    }
    return that;
}

/*******************************************************************************
 * AUDIT
 ******************************************************************************/

void dirac_audit(FILE * fp)
{
    diminuto_tree_root_t * rootp;
    diminuto_tree_t * nodep;
    diminuto_tree_t * prevp;
    dirac_t * that;
    for (rootp = &root, prevp = DIMINUTO_TREE_NULL, nodep = diminuto_tree_first(rootp); nodep != DIMINUTO_TREE_NULL; prevp = nodep, nodep = diminuto_tree_next(nodep)) {
        that = (dirac_t *)nodep;
        fprintf(fp, "dirac_audit: @%p[%zu]", that, that->node.size);
        while (that->node.tree.data != (void *)0) {
            that = (dirac_t *)(that->node.tree.data);
            fprintf(fp, " @%p[%zu]", that, that->node.size);
        }
        fputc('\n', fp);
        fflush(fp);
    }
}
