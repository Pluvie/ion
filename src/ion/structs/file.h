#if platform(LINUX)
  struct file {
    int descriptor;
    char* name;
  };
  check_sizeof(16, struct file);

#else
  #error "Unsupported platform."
#endif
