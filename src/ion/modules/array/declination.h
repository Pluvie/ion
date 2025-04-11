/**
 * These macros are used to extract the element type from the `array_declination`
 * directive. Example:
 *
 * ```c
 * #define array_declination i32
 * element_type(array_declination)    // Extracts `i32`
 * ```
 *
 * The `__element_type` macro is an indirection layer: it is needed because the
 * preprocessor cannot handle the `i32` token as separate entities.
 * See more here: https://stackoverflow.com/a/57125670 */
#define element_type(...) __element_type(__VA_ARGS__)
#define __element_type(e, ...) e
#define t  element_type(array_declination)

/**
 * Includes all array functions, which are now declined on the `t` elment type
 * specified in the `array_declination` directive. */
#include "declination/structs.h"
#include "declination/functions.h"
#include "declination/functions/array_allocate.c"
#include "declination/functions/array_init.c"
#include "declination/functions/array_get.c"
#include "declination/functions/array_set.c"
#include "declination/functions/array_last.c"
#include "declination/functions/array_pop.c"
#include "declination/functions/array_push.c"

/**
 * Undefines all macros used to extract the array declination element type. */
#undef element_type
#undef __element_type
#undef t

/* Undefines the `array_declination` directive defined right outside this file. */
#undef array_declination
