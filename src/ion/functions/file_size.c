int file_size (
    struct file* file
)
{
#if platform(LINUX)
  struct stat stat;
  if (fstat(file->descriptor, &stat) != 0) {
    fail("file size error: %s", strerror(errno));
    return 0;
  }

  return stat.st_size;

#else
  #error "Unsupported platform."
#endif
}
