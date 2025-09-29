/*
  Defines the constant null pointer, when is compiled with C11 or C17 standard.
  `nullptr` is available by default in C23 and up.
*/
#if standard(<= C17)
#define nullptr ((void*) 0)
#endif
