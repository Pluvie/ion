void socket_connect (
    struct socket* sock
)
{
#if platform(LINUX)
  if (unlikely(sock->uri.length >= 256)) {
    fail("socket uri error: too long");
    return;
  }

  switch (sock->family) {
  case AF_INET: {
    int ip_begin = stridx(sock->uri, s("://"));
    if (unlikely(ip_begin < 0)) {
      fail("socket uri error: must start with [tcp|udp|unix]://");
      return;
    }

    /* NOTE(Pluvie): We should add support for IPv6 by checking the ip format.
     * The code below is assuming a IPv4 syntax like `tcp://127.0.0.1:3000`.
     * The equivalent IPv6 format would be `tcp://[::1]:3000`. The square brackets are
     * necessary in order to avoid confusion with the port, as specified in [RFC 3986]
     * (https://datatracker.ietf.org/doc/html/rfc3986#section-3.2.2). */
    string ip_and_port = strsub(sock->uri, ip_begin + 3, -1);
    int port_begin = stridx(ip_and_port, s(":"));
    if (unlikely(port_begin < 0)) {
      fail("socket uri error: missing port");
      return;
    }

    string ip = strsub(ip_and_port, ip_begin + 3, port_begin);
    string port = strsub(ip_and_port, port_begin + 1, -1);

    char ip0[256] = { 0 };
    snprintf(ip0, ip.length, "%s", ip.content);

    int port_number = string_to_int(port);
    if (unlikely(failure.occurred))
      return;

    struct sockaddr_in address = { 0 };
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip0);
    address.sin_port = htons(port_number);

    int result = connect(sock->descriptor, (struct sockaddr*) &address, sizeof(address));
    if (result == -1)
      fail("socket connect error: %s", strerror(errno));

    return;
  }

  case AF_UNIX: {
    int path_begin = stridx(sock->uri, s("://"));
    if (unlikely(path_begin < 0)) {
      fail("socket uri error: must start with [tcp|udp|unix]://");
      return;
    }

    string path = strsub(sock->uri, path_begin + 3, -1);

    struct sockaddr_un address = { 0 };
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, path.content, sizeof(address.sun_path) - 1);

    int result = connect(sock->descriptor, (struct sockaddr*) &address, sizeof(address));
    if (result == -1)
      fail("socket connect error: %s", strerror(errno));

    return;
  }

  default:
    fail("socket connect error: unsupported socket family");
    return;
  }

#else
  #error "Unsupported platform."
#endif
}
