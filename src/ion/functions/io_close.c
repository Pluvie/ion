void io_close (
    struct io* io
)
{
  switch (io->type) {
  case IO_DIRECT:
    return;
  case IO_BUFFERED:
    /* To be implemented. */
  default:
    fail("json decode: unrecognized io type");
  }
}
