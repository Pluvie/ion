#if platform(LINUX)
  struct socket {
    int descriptor;
    int type;
    struct sockaddr* address;
    int address_size;
  };
  check_sizeof(32, struct socket);

#else
  #error "Unsupported platform."
#endif
