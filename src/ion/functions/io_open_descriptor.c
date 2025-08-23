static inline struct io io_open_descriptor (
    int descriptor,
    int length
)
{
#if platform(LINUX)
  struct io io = { 0 };

  struct stat stat;
  if (fstat(descriptor, &stat) != 0) {
    fail("error while calling `fstat` for descriptor %li: %s", descriptor, strerror(errno));
    return io;
  }

  if (S_ISSOCK(stat.st_mode))
    return io_open_socket(descriptor);
  
  if (S_ISREG(stat.st_mode))
    return io_open_file(descriptor, length, &stat);

  fail("cannot determine descriptor %li type: neither socket nor file", descriptor);
  return io;

#else
  #error "Unsupported platform."
#endif
}
