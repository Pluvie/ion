#ifdef ION_INCLUDED
static inline
#endif

void io_close (
    struct io* io
)
{
  switch (io->channel) {
  case IO_CHANNEL_MEMORY:
    return;
  case IO_CHANNEL_FILE:
  case IO_CHANNEL_SOCKET:
    buffer_release(&(io->buffer.allocator));
    return;
  }
}
