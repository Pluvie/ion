static inline char* io<string>_read (
    struct io* io,
    string* source,
    int amount
)
{
  if (likely(io->cursor < source->length)) {
    char* result = source->pointer + io->cursor;
    io->cursor += amount;
    return result;
  }

  return EMPTY_STRING;
}



static inline char* io<struct file>_read (
    struct io* io,
    struct file* source,
    int amount
)
{
  void* address = memory_alloc(io->buffer, amount);
  int result = file_read(source, address, amount);
  if (likely(result > 0)) {
    io->cursor += result;
    return address;
  }

  return EMPTY_STRING;
}



static inline char* io<struct pipe>_read (
    struct io* io,
    struct pipe* source,
    int amount
)
{
  void* address = memory_alloc(io->buffer, amount);
  int result = pipe_read(source, address, amount);
  if (likely(result > 0)) {
    io->cursor += result;
    return address;
  }

  return EMPTY_STRING;
}



static inline char* io<struct socket>_read (
    struct io* io,
    struct socket* source,
    int amount
)
{
  void* address = memory_alloc(io->buffer, amount);
  int result = socket_read(source, address, amount, io->read.flags);
  if (likely(result > 0)) {
    io->cursor += result;
    return address;
  }

  return EMPTY_STRING;
}



static inline char* io<struct stream>_read (
    struct io* io,
    struct stream* source,
    int amount
)
{
  void* address = memory_alloc(io->buffer, amount);
  int result = stream_read(source, address, amount);
  if (likely(result > 0)) {
    io->cursor += result;
    return address;
  }

  return EMPTY_STRING;
}
