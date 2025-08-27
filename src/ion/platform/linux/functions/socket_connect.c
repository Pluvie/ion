void socket_connect (
    struct socket* sock
)
{
  switch (sock->type) {
  case SOCKET_IP_V4: {
    struct sockaddr_in address = { 0 };
    address.sin_family = AF_INET;
    address.sin_port = htons(sock->port);
    int valid_address = inet_pton(AF_INET, sock->ipv4, (void*) &(address.sin_addr));
    if (unlikely(valid_address != 1)) {
      fail("socket connect error: invalid IPv4 address `%s`", sock->ipv4);
      return;
    }

    int result = connect(sock->descriptor, (struct sockaddr*) &address, sizeof(address));
    if (result == -1)
      fail("socket connect error: %s", strerror(errno));

    return;
  }

  case SOCKET_IP_V6: {
    struct sockaddr_in6 address = { 0 };
    address.sin6_family = AF_INET6;
    address.sin6_port = htons(sock->port);
    int valid_address = inet_pton(AF_INET, sock->ipv6, (void*) &(address.sin6_addr));
    if (unlikely(valid_address != 1)) {
      fail("socket connect error: invalid IPv6 address `%s`", sock->ipv6);
      return;
    }

    int result = connect(sock->descriptor, (struct sockaddr*) &address, sizeof(address));
    if (result == -1)
      fail("socket connect error: %s", strerror(errno));

    return;
  }

  case SOCKET_LOCAL: {
    struct sockaddr_un address = { 0 };
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, sock->path, sizeof(address.sun_path) - 1);

    int result = connect(sock->descriptor, (struct sockaddr*) &address, sizeof(address));
    if (result == -1)
      fail("socket connect error: %s", strerror(errno));
  }

  default:
    fail("socket connect error: unsupported socket type");
  }

  return;
}
