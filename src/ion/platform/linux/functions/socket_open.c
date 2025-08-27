struct socket socket_open (
    string uri
)
{
  struct socket sock = socket_init(uri);
  if (unlikely(failure.occurred))
    return sock;

  int linux_socket_family;
  int linux_socket_type;

  switch (sock.type) {
  case SOCKET_IP_V4:
    linux_socket_family = AF_INET;
    break;
  case SOCKET_IP_V6:
    linux_socket_family = AF_INET6;
    break;
  case SOCKET_LOCAL:
    linux_socket_family = AF_UNIX;
    break;
  default:
    fail("socket connect error: unsupported socket type");
    return (struct socket) { 0 };
  }

  switch (sock.protocol) {
  case SOCKET_TCP:
    linux_socket_type = SOCK_STREAM;
    break;
  case SOCKET_UDP:
    linux_socket_type = SOCK_DGRAM;
    break;
  default:
    fail("socket connect error: unsupported socket protocol");
    return (struct socket) { 0 };
  }

  sock.descriptor = socket(linux_socket_family, linux_socket_type, 0);
  if (unlikely(sock.descriptor) < 0)
    fail("socket open error: %s", strerror(errno));

  return sock;
}
