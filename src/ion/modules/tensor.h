#ifndef ION_CORE
#error ⚡️ION⚡️ CORE module is required. Include <ion/modules/core.h>.
#endif

#ifndef ION_ARRAY
#error ⚡️ION⚡️ ARRAY module is required. Include <ion/modules/array.h>.
#endif

/* Defines the `array(u64)` declination, if not already defined, used to hold the
 * tensor dimensions. */
#ifndef array__u64
  #define array_declination u64
  #include "ion/modules/array/declination.h"
#endif

#define ION_TENSOR

#include "tensor/macros.h"
