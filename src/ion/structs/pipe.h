#if platform(LINUX)
  struct pipe {
    int32 reader;
    int32 writer;
  };
  check_sizeof(8, struct pipe);

#else
  #error "Unsupported platform."
#endif
