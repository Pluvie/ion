/*
void io_read (
    struct io* io,
    int amount
)
{
  if (io->buffer.enabled)
    return io_buffer_read(io, amount);

  if (io->channel == IO_MEMORY)
    return io_channel_read(io, amount, NULL);

  alloc_release(io->result.pointer);
  io->result.pointer = alloc_zero(amount);
  return io_channel_read(io, amount, io->result.pointer);
}
*/

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
    int amount,
    void* address
)
{
  int result = file_read(source, address, amount);
  if (likely(result > 0)) {
    io->cursor += amount;
    return address;
  }

  return EMPTY_STRING;
}
