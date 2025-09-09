/* Sets the `int` type based on the value of the DEC_SIZE constant over which ⚡️ION⚡️
 * is compiled on.
 *
 * If the DEC_SIZE constant is not provided, ⚡️ION⚡️ shall default to 64 bit sizes for
 * both integer and decimal numbers. */

#ifndef DEC_SIZE
#define DEC_SIZE  64
#endif

/* The base types `float` and `double` must be provided by the platform. */

#ifdef  dec
#undef  dec
#endif

#if   DEC_SIZE == 64
  #define dec   double

#elif DEC_SIZE == 32
  #define dec   float

#else
  #error "⚡️ION⚡️: `dec` type size must be 64 or 32."
#endif
