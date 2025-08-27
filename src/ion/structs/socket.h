struct socket {
  int descriptor;
  int port;
  string uri;
  enum socket_protocols protocol;
  enum socket_ip_versions ip_version;
  union {
    char ipv4[SOCKET_IPV4_MAXLEN];
    char ipv6[SOCKET_IPV6_MAXLEN];
    char path[SOCKET_PATH_MAXLEN];
  };
};
check_sizeof(296, struct socket);
