/* Sets the `int` type based on the value of the INT_SIZE constant over which ⚡️ION⚡️
 * is compiled on.
 *
 * If the INT_SIZE constant is not provided, ⚡️ION⚡️ shall default to 64 bit sizes for
 * both integer and decimal numbers. */

#ifndef INT_SIZE
#define INT_SIZE  64
#endif

/* The base types `int64_t` and `int32_t` must be provided by the platform. Usually,
 * they are defined in the <stdint.h> header. */

#ifdef  int
#undef  int
#endif

#ifdef  int32
#undef  int32
#endif

#ifdef  int64
#undef  int64
#endif

#if   INT_SIZE == 64
  #define int32   int32_t
  #define int64   int64_t
  #define int     int64

  #define INT_MAXCHARS  19

#elif INT_SIZE == 32
  #define int32   int32_t
  #define int     int32

  #define INT_MAXCHARS  10

#else
  #error "⚡️ION⚡️: `int` type size must be 64 or 32."
#endif
