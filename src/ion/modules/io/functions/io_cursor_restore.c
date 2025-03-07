#ifdef ION_INCLUDED
static inline
#endif

void io_cursor_restore (
    struct io* io
)
{
  io_flag_remove(io, IO_FLAGS_BUFFER_RETAIN);
  io->cursor = io->saved_cursor;
}
