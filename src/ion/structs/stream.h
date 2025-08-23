#if platform(LINUX)
  struct stream {
    void* pointer;
    const char* mode;
  };
  check_sizeof(8, struct stream);

#else
  #error "Unsupported platform."
#endif
