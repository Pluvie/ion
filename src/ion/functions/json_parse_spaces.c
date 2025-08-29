void json<T>_parse_spaces (
    struct io* io,
    T* source
)
{
read_space:
  char* data = io_read(io, source, sizeof(char));

  if (isspace(*data))
    goto read_space;

  if (likely(*data != 0))
    io->cursor--;
}
