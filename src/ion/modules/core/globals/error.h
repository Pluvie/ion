/**
 * Error that can be set using the `fail` macro.
 *
 * Useful to check if another code (usually a function call) has encountered an
 * error while running.
 *
 * The error global variable is thread local in order to be used seamlessly also
 * with fibers. */
__thread struct failure error = { 0 };
