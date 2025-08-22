#if defined(__WIN32__)
  #error "Not implemented for Windows platform."

#elif defined(__APPLE__)
  #error "Not implemented for Apple platform."

#elif defined(__linux__)
  struct pipe {
    int32 reader;
    int32 writer;
  };
  check_sizeof(8, struct pipe);

#else
  #error "Unsupported platform."
#endif
