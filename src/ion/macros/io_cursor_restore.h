/**
 * Macro to restore the previous value of an I/O cursor. */
#define io_cursor_restore(io, prev) \
  (io)->cursor = prev
