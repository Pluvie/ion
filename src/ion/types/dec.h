/*
  Defines the `dec` ⚡️ION⚡️ types.

  This type represent decimal numbers. Using the DEC_BIT_WIDTH compile time directive,
  ⚡️ION⚡️ can be compiled with a fixed precision on decimal numbers. Allowed values for
  DEC_BIT_WIDTH are 32 or 64, respectively representing `float` and `double` types.

  Using ⚡️ION⚡️ it is not possible to have both precisions running on the same program.
  Not by using the `dec` type anyway. This is a design choice in order to simplify
  software complexity, especially when dealing with data seralization.

  You must choose which decimal precision is necessary for your program and stick with
  it. If not defined, the DEC_BIT_WIDTH directive assumes a 64 bit value, thus
  converting to the `double` type.
*/

#ifndef DEC_BIT_WIDTH
#define DEC_BIT_WIDTH 64
#endif

#ifdef  dec
#undef  dec
#endif

#if   DEC_BIT_WIDTH == 64
  #define dec   double
  #define DEC_EXP_MAX       308
  #define DEC_EXP_MAXCHARS  3

#elif DEC_BIT_WIDTH == 32
  #define dec   float
  #define DEC_EXP_MAX       38
  #define DEC_EXP_MAXCHARS  2

#else
  #error "⚡️ION⚡️: `dec` type bit width must be 64 or 32."
#endif
