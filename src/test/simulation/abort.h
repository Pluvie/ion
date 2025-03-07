/**
 * Creates a custom `abort` symbol which is a simple macro that raises SIGABRT.
 *
 * This shall allow the test suite to intercept and handle the signal, which would
 * have been impossible with the original `abort()` function. */




#include <signal.h>

#undef abort
#define abort() raise(SIGABRT)

bool sigabrt_caught = false;
void sigabrt_catch(i32 signal) { sigabrt_caught = true; }
