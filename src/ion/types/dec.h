/* Defines the `dec` ⚡️ION⚡️ types.

  This type represent decimal numbers. Using the DEC_BITSIZE compile time directive,
  ⚡️ION⚡️ can be compiled with a fixed precision on decimal numbers. Allowed values for
  DEC_BITSIZE are 32 or 64, respectively representing `float` and `double` types.

  Using ⚡️ION⚡️ it is not possible to have both precisions running on the same program.
  Not by using the `dec` type anyway. This is a design choice in order to reduce
  software complexity, especially when dealing with data seralization.

  You must choose which decimal precision is necessary for your program and stick with
  it. If not defined, the DEC_BITSIZE directive assumes a 64 bit value, thus
  referring to the `double` type. */

#ifdef  dec
#undef  dec
#endif

#ifndef DEC_BITSIZE
#define DEC_BITSIZE 64
#endif

#if   DEC_BITSIZE == 64
  #define dec   double
  #define DEC_EXP_MAX       308
  #define DEC_EXP_MAXCHARS  3

#elif DEC_BITSIZE == 32
  #define dec   float
  #define DEC_EXP_MAX       38
  #define DEC_EXP_MAXCHARS  2

#else
  #error "ION supports only IEEE 754 decimals in 64-bit or 32-bit."
#endif
