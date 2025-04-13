/**
 * These macros are used to extract the element type from the `tensor_declination`
 * directive. Example:
 *
 * ```c
 * #define tensor_declination i32
 * element_type(tensor_declination)    // Extracts `i32`
 * ```
 *
 * The `__element_type` macro is an indirection layer: it is needed because the
 * preprocessor cannot handle the `i32` token as separate entities.
 * See more here: https://stackoverflow.com/a/57125670 */
#define element_type(...) __element_type(__VA_ARGS__)
#define __element_type(e, ...) e
#define t  element_type(tensor_declination)

/**
 * Includes all tensor functions, which are now declined on the `t` elment type
 * specified in the `tensor_declination` directive. */
#include "declination/structs.h"
#include "declination/functions.h"
#include "declination/functions/tensor_allocate.c"
#include "declination/functions/tensor_init.c"
#include "declination/functions/tensor_at.c"

/**
 * Undefines all macros used to extract the tensor declination element type. */
#undef element_type
#undef __element_type
#undef t

/* Undefines the `tensor_declination` directive defined right outside this file. */
#undef tensor_declination
