/**
 * These macros are used to extract the element type from the * `set_declination`
 * directive. Example:
 *
 * ```c
 * #define set_declination string
 * element_type(set_declination)  // Extracts `strin`
 * ```
 *
 * The `__element_type` macro are indirection layers: they are needed
 * because the preprocessor cannot handle the `string` token as separate entities.
 * See more here: https://stackoverflow.com/a/57125670 */
#define element_type(...) __element_type(__VA_ARGS__)
#define __element_type(e, ...) e
#define t  element_type(set_declination)

/**
 * Includes all set functions, which are now declined on the `t` elment type
 * specified in the `set_declination` directive. */
#include "declination/structs.h"
#include "declination/functions.h"
#include "declination/functions/set_allocate.c"
#include "declination/functions/set_init.c"
#include "declination/functions/set_add.c"
#include "declination/functions/set_has.c"
#include "declination/functions/set_del.c"
#include "declination/functions/set_rehash.c"

/**
 * If the user does not define a custom comparer, then the default set comparer is
 * included. */
#ifndef set_use_comparer
  #include "declination/functions/set_comparer.c"
#else
  #undef set_use_comparer
#endif

/**
 * If the user does not define a custom hasher, then the default set hasher is
 * included. */
#ifndef set_use_hasher
  #include "declination/functions/set_hasher.c"
#else
  #undef set_use_hasher
#endif

/**
 * Undefines all macros used to extract the set declination element type. */
#undef element_type
#undef __element_type
#undef t

/* Undefines the `set_declination` directive defined right outside this file. */
#undef set_declination
