struct socket socket_init (
    string uri
)
{
  struct socket sock = { .uri = uri };

  /* NOTE(Pluvie): The socket uri supports IPv4 and IPv6. IPv4 syntax is like
   * `tcp://127.0.0.1:3000`. IPv6 syntax is like `tcp://[::1]:3000`. The square
   * brackets are necessary in order to avoid confusion with the port, as specified
   * in [RFC 3986](https://datatracker.ietf.org/doc/html/rfc3986#section-3.2.2). */

  string tcp = s("tcp://");
  string udp = s("udp://");
  int resource_begin = -1;

  if (string_starts(uri, tcp)) {
    sock.protocol = SOCKET_TCP;
    resource_begin = tcp.length;

  } else if (string_starts(uri, udp)) {
    sock.protocol = SOCKET_UDP;
    resource_begin = udp.length;

  } else {
    fail("socket uri error: must start with [tcp|udp]://");
    return sock;
  }

  /* If the user has given a string exactly equal to `tcp://` it is not valid.
   * Otherwise checks the first character to determine the resource. */
  if (unlikely(sock.uri.length <= resource_begin)) {
    fail("socket uri error: invalid");
    return sock;
  }

  string resource = substring(sock.uri, resource_begin, -1);
  switch (string_char_at(resource, 0)) {

  /* IPv6 socket. */
  case '[': {
    sock.type = SOCKET_IP_V6;
    int port_begin = string_index(resource, s("]:"));
    if (unlikely(port_begin < 0)) {
      fail("socket uri error: missing port");
      return sock;
    }

    string ip = substring(resource, 0, port_begin);
    string port = substring(resource, port_begin + 2, -1);
    snprintf(sock.ipv6, sizeof(sock.ipv6), "%s", (char*) ip.pointer);
    sock.port = string_to_int(port);

    if (unlikely(failure.occurred))
      return sock;

    if (likely(sock.port >= 0 && sock.port <= SOCKET_PORT_MAX))
      return sock;

    fail("socket uri error: invalid port");
    return sock;
  }

  /* IPv4 socket. */
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9': {
    sock.type = SOCKET_IP_V4;
    int port_begin = string_index(resource, s(":"));
    if (unlikely(port_begin < 0)) {
      fail("socket uri error: missing port");
      return sock;
    }

    string ip = substring(resource, 0, port_begin);
    string port = substring(resource, port_begin + 1, -1);
    snprintf(sock.ipv4, sizeof(sock.ipv4), "%s", (char*) ip.pointer);
    sock.port = string_to_int(port);

    if (unlikely(failure.occurred))
      return sock;

    if (likely(sock.port >= 0 && sock.port <= SOCKET_PORT_MAX))
      return sock;

    fail("socket uri error: invalid port");
    return sock;
  }

  /* Local socket, also known as UNIX domain socket. */
  default:
    sock.type = SOCKET_LOCAL;
    snprintf(sock.path, sizeof(sock.path), "%s", (char*) resource.pointer);
  }

  return sock;
}
