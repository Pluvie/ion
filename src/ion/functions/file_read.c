#ifdef ION_INCLUDED
static inline
#endif

struct io file_read (
    void* file,
    struct memory* allocator
)
{
  u64 filesize = file_size(file);
  void* file_content = memory_alloc(allocator, filesize);
  i32 fread_output = fread(file_content, filesize, 1, file);

  if (unlikely(fread_output != 1)) {
    fail("error while reading from file: %s", strerror(errno));
    return (struct io) { 0 };
  }

  struct io reader = {
    .file = file_content,
    .length = filesize,
    .channel = IO_CHANNEL_MEM,
    .mode = IO_MODE_READ,
  };

  return reader;
}
