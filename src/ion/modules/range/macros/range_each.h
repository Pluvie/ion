/**
 * Loops through the values of a range. A specific name for the index can be
 * provided as optional third argument. */
#define range_each(range_var, ...)                                                \
  (range_var.at = range_var.min; range_var.at <= range_var.max; range_var.at++)   \
    __VA_OPT__(for(i64 __VA_ARGS__ = range_var.at - range_var.min; __VA_ARGS__ >= 0; __VA_ARGS__ = -1))
