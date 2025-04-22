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
#include "com/diag/diminuto/diminuto_log.h"
#include "com/diag/dirac/dirac.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int main(void)
{
    SETLOGMASK();

    {
        TEST();

        dirac_dump(stderr);

        dirac_t * new1 = dirac_new(0, 0);
        ASSERT(new1 != (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * new2 = dirac_new(2, 3);
        ASSERT(new2 != (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * new3 = dirac_new(3, 2);
        ASSERT(new3 != (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * new4 = dirac_new(4, 4);
        ASSERT(new4 != (dirac_t *)0);
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
        dirac_dump(stderr);

        dirac_t * new6 = dirac_new(2, 3);
        ASSERT(new6 != (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * new7 = dirac_new(3, 2);
        ASSERT(new7 != (dirac_t *)0);
        dirac_dump(stderr);

        dirac_t * new8 = dirac_new(4, 4);
        ASSERT(new8 != (dirac_t *)0);
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

    EXIT();
}
