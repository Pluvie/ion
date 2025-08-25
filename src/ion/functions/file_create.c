struct file file_create (
    string name
)
{
#if platform(LINUX)
  struct file file = { .name = name };

  int flags = O_CREAT | O_RDWR;
  int permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

  file.descriptor = open(name.content, flags, permissions);
  if (unlikely(file.descriptor < 0)) {
    fail("file create error: %s", strerror(errno));
    return file;
  }

  return file;

#else
  #error "Unsupported platform."
#endif
}
