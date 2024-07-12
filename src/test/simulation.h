// Suppresses all prints to stderr.
FILE* tmp_stderr;
FILE* original_stderr;
FILE* suppressed_stderr;
#undef stderr
#define stderr suppressed_stderr

// Creates a custom `abort` symbol which is a simple macro that raises SIGABRT.
// This shall allow the test suite to intercept and handle the signal, which would
// have been impossible with the original `abort()` function.
#include <signal.h>
#undef abort
#define abort() raise(SIGABRT)
bool sigabrt_caught = false;
void sigabrt_catch(i32 signal) { sigabrt_caught = true; }


// -- Includes Ion code, so that it shall be compiled with simulations active.
//
#include <ion.c>
//
// -- Simulations are now injected into Ion code.
