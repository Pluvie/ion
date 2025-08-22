/**
 * Global error that can be set using the `fail` macro.
 *
 * Useful to check if another code (usually a function call) has encountered an
 * error while running.
 *
 * The failure global variable is declared thread local with `__thread` in order to be
 * safe to use in multi-threaded applications.
 *
 * Additionally, the global variable is declared `static` in order to be correctly
 * addressed by the linker when ⚡️ION⚡️ is used as a shared library. */
static __thread struct error failure = { 0 };
