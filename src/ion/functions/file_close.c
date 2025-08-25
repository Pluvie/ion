void file_close (
    struct file* file
)
{
#if platform(LINUX)
  int result = close(file->descriptor);
  if (result < 0)
    fail("file close error: %s", strerror(errno));

  return;

#else
  #error "Unsupported platform."
#endif
}
