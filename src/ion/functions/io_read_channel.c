slice io_read_channel (
    struct io* io,
    int amount,
    void* storage
)
{
  slice result = { 0 };
  int read_bytes = 0;

  switch (io->channel) {
  case IO_FILE:
    if (unlikely(storage == NULL)) {
      fail("cannot read from file with empty storage");
      return result;
    }

    read_bytes = read(io->file, storage, amount);

    if (read_bytes < 0) {
      fail("file read error: %s", strerror(errno));
      return result;
    }

    result.data = storage;
    result.length = read_bytes;
    io_cursor_advance(io, result.length);
    return result;

  case IO_MEMORY:
    result.data = io->memory + io->cursor;
    result.length = amount;

    if (io->cursor + amount > io->length)
      result.length = io->length - io->cursor;

    if (unlikely(result.length <= 0)) {
      result.length = 0;
      result.data = NULL;
      return result;
    }

    if (storage != NULL) {
      memcpy(storage, result.data, result.length);
      result.data = storage;
    }

    io_cursor_advance(io, result.length);
    return result;

  case IO_PIPE:
    if (unlikely(storage == NULL)) {
      fail("cannot read from pipe with empty storage");
      return result;
    }

    read_bytes = read(io->pipe, storage, amount);

    if (read_bytes < 0) {
      fail("pipe read error: %s", strerror(errno));
      return result;
    }

    result.data = storage;
    result.length = read_bytes;
    io_cursor_advance(io, result.length);
    return result;

  case IO_SOCKET:
    if (unlikely(storage == NULL)) {
      fail("cannot read from socket with empty storage");
      return result;
    }

    read_bytes = recv(io->socket, storage, amount, io->read.flags);

    if (read_bytes < 0) {
      fail("socket read error: %s", strerror(errno));
      return result;
    }

    result.data = storage;
    result.length = read_bytes;
    io_cursor_advance(io, result.length);
    return result;

  case IO_STREAM:
    return (slice) { 0 };

  default:
    return (slice) { 0 };
  }
}
