#ifdef ION_INCLUDED
static inline
#endif

struct io file_read (
    const char* file_path,
    struct memory* allocator
)
{
  void* file = fopen(file_path, "r");
  if (file == NULL) {
    fail("error while opening file `%s`: %s", file_path, strerror(errno));
    return (struct io) { 0 };
  }

  u64 file_bytesize = file_size(file);
  void* file_content = memory_alloc(allocator, file_bytesize);
  i32 fread_output = fread(file_content, file_bytesize, 1, file);

  if (unlikely(fread_output != 1)) {
    fail("error while reading from file `%s`: %s", file_path, strerror(errno));
    return (struct io) { 0 };
  }

  fclose(file);
  return io_memory(file_content, file_bytesize);
}
