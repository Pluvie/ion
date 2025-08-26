struct socket socket_init (
    string uri
)
{
  struct socket sock = { .uri = uri };

  /*  */ if (strstart(uri, s("tcp://"))) {
    sock.type = SOCK_STREAM;
    goto internet_socket;

  } else if (strstart(uri, s("udp://"))) {
    sock.type = SOCK_DGRAM;
    goto internet_socket;

  } else if (strstart(uri, s("unix://"))) {
    sock.type = SOCK_STREAM;
    goto unix_socket;

  } else {
    fail("socket uri error: must start with [tcp|udp|unix]://");
    return sock;
  }

internet_socket:
  int ip_begin = stridx(sock.uri, s("://"));
  string ip_and_port = strsub(sock.uri, ip_begin + 3, -1);

  /* NOTE(Pluvie): The socket uri supports IPv4 and IPv6. IPv4 syntax is like
   * `tcp://127.0.0.1:3000`. IPv6 syntax is like `tcp://[::1]:3000`. The square
   * brackets are necessary in order to avoid confusion with the port, as specified
   * in [RFC 3986](https://datatracker.ietf.org/doc/html/rfc3986#section-3.2.2). */
  string port;
  int port_ipv6_begin = stridx(ip_and_port, s("]:"));
  int port_ipv4_begin = stridx(ip_and_port, s(":"));
  /*  */ if (port_ipv6_begin > 0) {
    sock.family = AF_INET6;
    string ip = strsub(ip_and_port, ip_begin + 4, port_ipv6_begin);
    snprintf(sock.ipv6, sizeof(sock.ipv6), "%s", ip.content);
    port = strsub(ip_and_port, port_ipv6_begin + 2, -1);

  } else if (port_ipv4_begin > 0) {
    sock.family = AF_INET;
    string ip = strsub(ip_and_port, ip_begin + 3, port_ipv4_begin);
    snprintf(sock.ipv4, sizeof(sock.ipv4), "%s", ip.content);
    port = strsub(ip_and_port, port_ipv4_begin + 1, -1);

  } else {
    fail("socket uri error: internet uri must be `[tcp|udp]://[ipv4|ipv6]:port`");
    return sock;
  }

  sock.port = string_to_int(port);
  if (unlikely(failure.occurred))
    return sock;

  if (likely(sock.port >= 0 && sock.port <= SOCKET_PORT_MAX))
    return sock;

  fail("socket uri error: invalid port");
  return sock;


unix_socket:
  sock.family = AF_UNIX;
  int path_begin = stridx(sock.uri, s("://"));
  string path = strsub(sock.uri, path_begin + 3, -1);
  snprintf(sock.path, sizeof(sock.path), "%s", path.content);

  return sock;
}
