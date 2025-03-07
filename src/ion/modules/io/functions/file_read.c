#ifdef ION_INCLUDED
static inline
#endif

struct io file_read (
    char* file_name,
    struct memory* allocator
)
{
  void* file_stream = fopen(file_name, "r");
  if (unlikely(file_stream == NULL)) {
    fail("io: error while opening file: %s", strerror(errno));
    goto error;
  }

  i64 file_bytesize = file_size(file_stream);
  void* file_data = memory_alloc(allocator, file_bytesize);

  i32 fread_output = fread(file_data, file_bytesize, 1, file_stream);
  if (unlikely(fread_output != 1)) {
    fail("io: error while reading from file: %s", strerror(errno));
    goto error;
  }

  struct io file_in_memory = io_open_memory(file_data, file_bytesize);
  fclose(file_stream);
  return file_in_memory;

error:
  if (file_stream != NULL)
    fclose(file_stream);

  return (struct io) { 0 };
}
