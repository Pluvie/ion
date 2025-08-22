#if defined(__WIN32__)
  #error "Not implemented for Windows platform."

#elif defined(__APPLE__)
  #error "Not implemented for Apple platform."

#elif defined(__linux__)
  struct stream {
    void* stream;
  };
  check_sizeof(8, struct stream);

#else
  #error "Unsupported platform."
#endif
