void socket_accept (
    struct socket* sock,
    void (*connector)(struct socket*),
    int max_accepts,
    int timeout_ms
)
{
  struct sockaddr* sockaddr;
  int sockaddr_len;

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

    sockaddr = (struct sockaddr*) &address;
    sockaddr_len = sizeof(address);
    break;
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

    sockaddr = (struct sockaddr*) &address;
    sockaddr_len = sizeof(address);
    break;
  }

  case SOCKET_LOCAL: {
    struct sockaddr_un address = { 0 };
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, sock->path, sizeof(address.sun_path) - 1);

    sockaddr = (struct sockaddr*) &address;
    sockaddr_len = sizeof(address);
    break;
  }

  default:
    fail("socket connect error: unsupported socket type");
  }

  setsockopt(sock->descriptor, SOL_SOCKET, SO_REUSEADDR, &(int32) { 1 }, sizeof(int32));

  int bind_outcome = bind(sock->descriptor, sockaddr, sockaddr_len);
  if (bind_outcome == -1) {
    fail("socket binding failure: %s", strerror(errno));
    return;
  }

  int listen_outcome = listen(sock->descriptor, 10);
  if (listen_outcome == -1) {
    fail("socket listen failure: %s", strerror(errno));
    return;
  }

  bool infinite_connections = (max_accepts == 0);
  int timeout_sec = timeout_ms / 1000;
  int timeout_usec = (timeout_ms * 1000) - timeout_sec;
  struct timeval receive_timeout = { .tv_sec = timeout_sec, .tv_usec = timeout_usec };
  struct socket client = { 0 };

  /* Accepts incoming connection and waits up until 5 seconds to receive data. If no
   * data are received after this timeout, the connection shall be closed. */
  do {
    client.descriptor = accept(sock->descriptor, sockaddr, (socklen_t*) &sockaddr_len);
    if (client.descriptor == -1)
      continue;

    int timeout_outcome = setsockopt(client.descriptor, SOL_SOCKET, SO_RCVTIMEO,
      (const char*) &receive_timeout, sizeof(receive_timeout));
    if (timeout_outcome == -1) {
      close(client.descriptor);
      continue;
    }

    if (connector != NULL)
      connector(&client);

    max_accepts--;

  } while(infinite_connections || max_accepts > 0);

  return;
}
