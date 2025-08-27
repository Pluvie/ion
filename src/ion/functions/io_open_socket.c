struct io io_open_socket (
    struct socket* sock,
    int
)
{
  return (struct io) {
    .channel = IO_SOCKET,
    .socket = sock,
  };
}
