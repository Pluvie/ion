void io_close (
    struct io* io
)
{
  switch (io->type) {
  case IO_DIRECT:
    return;
  case IO_BUFFERED:
    alloc_release(io->buffered->buffer.data);
    return;
  default:
    fail("io close: unrecognized io type");
  }
}
