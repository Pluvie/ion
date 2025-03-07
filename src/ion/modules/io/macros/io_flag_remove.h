/**
 * Removes a flag to the io. */
#define io_flag_remove(io, flag)  \
  (io)->flags &= ~(flag)
