/* vi: set ts=4 expandtab shiftwidth=4: */
/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA<BR>
 * Licensed under the terms in LICENSE.txt<BR>
 * Chip Overclock (mailto:coverclock@diag.com)<BR>
 * https://github.com/coverclock/com-diag-cdirac<BR>
 *
 * See the README.md for a list of references.
 */

/*******************************************************************************
 * HEADERS
 ******************************************************************************/

#include "com/diag/dirac/dirac.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "dirac.h"

/*******************************************************************************
 * GLOBALS
 ******************************************************************************/

/*******************************************************************************
 * MEMORY MANAGEMENT
 ******************************************************************************/

dirac_t * dirac_matrix_alloc(size_t rows, size_t columns) {
    size_t size = dirac_matrix_size(rows, columns);
    dirac_t * that = (dirac_t *)malloc(size);
    if (that == (dirac_t *)0) {
        perror("malloc");
    }
    return that;
}

dirac_t * dirac_matrix_init(dirac_t * that, size_t rows, size_t columns) {
    memset(&(that->field.data.matrix), 0, dirac_matrix_payload(rows, columns));
    that->field.data.rows = rows;
    that->field.data.columns = columns;
    return that;
}

dirac_t * dirac_matrix_new(size_t rows, size_t columns) {
    size_t need = dirac_matrix_payload(rows, columns);
}

dirac_t * dirac_matrix_delete(dirac_t * that) {
    size_t need = dirac_matrix_payload(that->field.data.rows, that->field.data.columns);
    return (dirac_t *)0;
}
