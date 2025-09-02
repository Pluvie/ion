void failure_add_io_info_direct (
    struct io_direct* io
)
{
  char* io_begin = io->data->pointer;
  char* io_end = io->end;
  char* io_cursor = io->cursor;

  #include "../procedures/failure_add_io_info.c"
}



void failure_add_io_info_buffered (
    struct io_buffered* io
)
{
  fail("to be implemented");
}
