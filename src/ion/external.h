/*
  This purpose of this file is to toggle the definition of the `int` type, to allow
  the inclusion of external libraries after <ion.h> is included.

  This is particularly useful when developing other libraries or application that
  need different system headers of the ones already specified in <ion/system.h>.
*/

#ifdef  int
#undef  int
#else
#define int   widest_int_t
#endif
