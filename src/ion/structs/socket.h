#if platform(LINUX)
  struct socket {
    int descriptor;
    int family;
    int type;
    string uri;
  };
  check_sizeof(32, struct socket);

#else
  #error "Unsupported platform."
#endif
