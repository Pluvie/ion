void io_close (
    struct io* io
)
{
  if (io->buffer != NULL) {
    memory_release(io->buffer);
    alloc_release(io->buffer);
  }
}
