static inline struct io io_open_socket (
    int descriptor
)
{
  return (struct io) {
    .channel = IO_SOCKET,
    .socket = descriptor,
  };
}
