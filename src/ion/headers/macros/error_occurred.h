/**
 * Checks if an error has occurred.
 *
 * If so, resets its occurence and evaluates to `true`.
 * Otherwise, evaluates to `false`. */
#define error_occurred \
  (error.occurred ? error.occurred = false, true : false)
