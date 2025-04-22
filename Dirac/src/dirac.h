/* vi: set ts=4 expandtab shiftwidth=4: */
#ifndef _H_COM_DIAG_DIRAC_PRIVATE_
#define _H_COM_DIAG_DIRAC_PRIVATE_

/**
 * @file
 *
 * Copyright 2025 Digital Aggregates Corporation, Colorado, USA<BR>
 * Licensed under the terms in LICENSE.txt<BR>
 * Chip Overclock (mailto:coverclock@diag.com)<BR>
 * https://github.com/coverclock/com-diag-codex<BR>
 *
 * Defines the privae API for Dirac.
 */

extern dirac_t * dirac_alloc(size_t rows, size_t columns);

static inline void dirac_free(dirac_t * that) {
    free(that);
}

#endif
