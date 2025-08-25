struct socket socket_open (
    int type,
    void* address,
    int address_size
)
{
#if platform(LINUX)
  struct socket sock = { 0 };
  struct sockaddr* sockaddr = address;

  sock.type = type;
  sock.descriptor = socket(sockaddr->sa_family, sock.type, 0);
  if (sock.descriptor < 0) {
    fail("socket create error: %s", strerror(errno));
    return sock;
  }

  int bind_result = bind(sock.descriptor, sockaddr, address_size);
  if (bind_result < 0) {
    fail("socket bind error: %s", strerror(errno));
    return sock;
  }

  return sock;

#else
  #error "Unsupported platform."
#endif
}
