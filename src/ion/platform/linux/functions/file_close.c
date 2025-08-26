void file_close (
    struct file* file
)
{
  int result = close(file->descriptor);
  if (result < 0)
    fail("file close error: %s", strerror(errno));
}
