void file_delete (
    struct file* file
)
{
  int result = remove(file->name.content);

  if (unlikely(result < 0))
    fail("file delete error: %s", strerror(errno));

  return;
}
