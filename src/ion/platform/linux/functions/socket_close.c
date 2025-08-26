void socket_close (
    struct socket* sock
)
{
  int result = close(sock->descriptor);
  if (result < 0)
    fail("socket close error: %s", strerror(errno));
}
