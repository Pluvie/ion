/*
  References the global variable for all translation units compiled separately from
  the main function.
*/
extern
#if standard(>= C11)
thread_local
#endif
struct failure failure;
