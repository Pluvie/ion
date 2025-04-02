/**
 * Global variable to track potential signals received by the program. */
static __thread bool signals_received[NSIG] = { 0 };
