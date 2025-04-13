/**
 * These macros are used to extract the key type and value type from the
 * `map_declination` directive. Example:
 *
 * ```c
 * #define map_declination i32, string
 * key_type(map_declination)    // Extracts `i32`
 * value_type(map_declination)  // Extracts `string`
 * ```
 *
 * The `__key_type` and `__value_type` macros are indirection layers: they are needed
 * because the preprocessor cannot handle the `i32, string` token as separate entities.
 * See more here: https://stackoverflow.com/a/57125670 */
#define key_type(...) __key_type(__VA_ARGS__)
#define value_type(...) __value_type(__VA_ARGS__)
#define __key_type(k, ...) k
#define __value_type(k, v, ...) v
#define kt  key_type(map_declination)
#define vt  value_type(map_declination)

/**
 * Includes all map functions, which are now declined on the `kt` and `vt` (key type
 * and value type) specified in the `map_declination` directive. */
#include "declination/structs.h"
#include "declination/functions.h"
#include "declination/functions/map_allocate.c"
#include "declination/functions/map_init.c"
#include "declination/functions/map_get.c"
#include "declination/functions/map_has.c"
#include "declination/functions/map_set.c"
#include "declination/functions/map_del.c"
#include "declination/functions/map_rehash.c"

/**
 * If the user does not define a custom comparer, then the default map comparer is
 * included. */
#ifndef map_use_comparer
  #include "declination/functions/map_comparer.c"
#else
  #undef map_use_comparer
#endif

/**
 * If the user does not define a custom hasher, then the default map hasher is
 * included. */
#ifndef map_use_hasher
  #include "declination/functions/map_hasher.c"
#else
  #undef map_use_hasher
#endif

/**
 * Undefines all macros used to extract the map declination key type and value type. */
#undef key_type
#undef value_type
#undef __key_type
#undef __value_type
#undef kt
#undef vt

/* Undefines the `map_declination` directive defined right outside this file. */
#undef map_declination
