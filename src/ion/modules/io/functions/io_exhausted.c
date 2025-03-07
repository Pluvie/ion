#ifdef ION_INCLUDED
static inline
#endif

bool io_exhausted (
    struct io* io
)
{
  switch (io->channel) {
  case IO_CHANNEL_MEMORY:
    return io->cursor >= io->length;

  case IO_CHANNEL_FILE:
    return io->cursor >= io->length;

  case IO_CHANNEL_SOCKET:
    i32 recv_output = recv(io->socket, NULL, 1, MSG_PEEK);
    if (unlikely(recv_output < 0)) {
      fail("io: error while reading from socket: %s", strerror(errno));
      return false;
    }
    return recv_output > 0;

  default:
    fail("io: unsupported channel");
    return false;
  }
}
