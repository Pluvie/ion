struct socket {
  int descriptor;
  string uri;
  int32 family;
  int32 type;
  int32 port;
  union {
    char ipv4[SOCKET_IPV4_MAXLEN];
    char ipv6[SOCKET_IPV6_MAXLEN];
    char path[SOCKET_PATH_MAXLEN];
  };
};
check_sizeof(296, struct socket);
