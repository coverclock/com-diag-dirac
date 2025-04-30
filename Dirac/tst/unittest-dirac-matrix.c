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

    DIRAC_OBJECT_DECL(2, 3) thing2x3a = DIRAC_OBJECT_INIT(2, 3);
    DIRAC_ARRAY_TYPE(thing2x3_t, 2, 3);
    thing2x3_t * matrix2x3a = DIRAC_ARRAY_POINTER(thing2x3_t, &thing2x3a);

    DIRAC_OBJECT_DECL(2, 3) thing2x3b = DIRAC_OBJECT_INIT(2, 3);
    thing2x3_t * matrix2x3b = DIRAC_ARRAY_POINTER(thing2x3_t, &thing2x3b);

    DIRAC_OBJECT_DECL(3, 2) thing3x2c = DIRAC_OBJECT_INIT(3, 2);
    DIRAC_ARRAY_TYPE(thing3x2_t, 3, 2);
    thing3x2_t * matrix3x2c = DIRAC_ARRAY_POINTER(thing3x2_t, &thing3x2c);

    DIRAC_OBJECT_DECL(5, 7) thing5x7d = DIRAC_OBJECT_INIT(5, 7);
    DIRAC_ARRAY_TYPE(thing5x7_t, 5, 7);
    thing5x7_t * matrix5x7d = DIRAC_ARRAY_POINTER(thing5x7_t, &thing5x7d);

    {
        TEST();

        STATUS();
    }

    EXIT();
}
