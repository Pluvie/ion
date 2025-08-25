static inline struct io io_open_file (
    struct file* file,
    int length
)
{
  if (length <= 0)
    length = file_size(file);

  struct io io = {
    .channel = IO_FILE,
    .file = file,
    .length = length
  };

  return io;
}
