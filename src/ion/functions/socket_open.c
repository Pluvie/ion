struct socket socket_open (
    string uri
)
{
#if platform(LINUX)
  struct socket sock = { .uri = uri };

  int family;
  int type;

  /*  */ if (strstart(uri, s("tcp://")) {
    family = AF_INET;
    type = SOCK_STREAM;
  } else if (strstart(uri, s("udp://")) {
    family = AF_INET;
    type = SOCK_DGRAM;
  } else if (strstart(uri, s("unix://")) {
    family = AF_UNIX;
    type = SOCK_STREAM;
  } else {
    fail("socket uri error: must start with [tcp|udp|unix]://");
    return sock;
  }

  sock.family = family;
  sock.type = type;
  sock.descriptor = socket(family, type, 0);
  if (sock.descriptor < 0) {
    fail("socket create error: %s", strerror(errno));
    return sock;
  }

  return sock;

#else
  #error "Unsupported platform."
#endif
}
