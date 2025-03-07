#ifdef ION_INCLUDED
static inline
#endif

void io_cursor_save (
    struct io* io
)
{
  io_flag_add(io, IO_FLAGS_BUFFER_RETAIN);
  io->saved_cursor = io->cursor;
}
