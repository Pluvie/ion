/**
 * Determines if two decimal numbers are approximately equal. */
#define approx_eq(d1, d2) \
  (fabsl((d128) ((d1) - (d2))) < epsilon)
