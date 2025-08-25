void file_delete (
    struct file* file
)
{
#if platform(LINUX)
  int result = remove(file->name);

  if (unlikely(result < 0))
    fail("file delete error: %s", strerror(errno));

  return;

#else
  #error "Unsupported platform."
#endif
}
