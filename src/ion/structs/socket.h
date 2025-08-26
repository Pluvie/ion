#if platform(LINUX)
  struct socket {
    int descriptor;
    int32 family;
    int32 type;
    string uri;
  };
  check_sizeof(32, struct socket);

#else
  #error "Unsupported platform."
#endif
