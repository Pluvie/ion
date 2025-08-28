struct file file_open (
    string name
)
{
  struct file file = { .name = name };

  int flags = O_RDWR;

  file.descriptor = open(name.pointer, flags, 0);
  if (unlikely(file.descriptor < 0)) {
    fail("file open error: %s", strerror(errno));
    return file;
  }

  return file;
}
