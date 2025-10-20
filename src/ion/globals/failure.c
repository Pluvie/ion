/*
 Global error that can be set using the `fail` macro.
 
 Useful to check if another code (usually a function call) has encountered an
 error while running.
 
 When ⚡️ION⚡️ is compiled as a shared library the global variable is declared `static` 
 in order to be correctly addressed by the linker.
 
 Additionally, on C11 standard and later, the failure global variable has thread
 local storage in order to be safe to use in multi-threaded applications. ⚡️ION⚡️
 supports threading only for C11 standard and later due to the introduction on
 ISO C threads.
*/
#ifdef ION_SHARED_LIB
static
#endif
#if standard(>= C11)
thread_local
#endif
struct failure failure = { 0 };
