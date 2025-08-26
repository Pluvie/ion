struct socket socket_open (
    string uri
)
{
  struct socket sock = socket_init(uri);
  if (unlikely(failure.occurred))
    return sock;

  sock.descriptor = socket(sock.family, sock.type, 0);
  if (unlikely(sock.descriptor) < 0)
    fail("socket open error: %s", strerror(errno));

  return sock;
}
