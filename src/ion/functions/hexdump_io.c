void hexdump_io (
    struct io* io
)
{
  void* hexdata = io_read(io, 1024);
  io->cursor -= 1024;
  hexdump(hexdata, io->read_amount);
}
