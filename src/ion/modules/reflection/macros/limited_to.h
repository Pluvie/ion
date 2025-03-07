/**
 * Used to define size limits in a reflection. */
#define limited_to(min_var, max_var)  \
  .size_limits = { .min = min_var, .max = max_var }
