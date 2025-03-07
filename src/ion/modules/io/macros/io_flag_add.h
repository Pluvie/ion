/**
 * Adds a flag to the io. */
#define io_flag_add(io, flag)  \
  (io)->flags &= flag
