static inline struct io io_open_file (
    int descriptor,
    int length,
    struct stat* stat
)
{
  if (length <= 0)
    length = stat->st_size;

  struct io io = {
    .channel = IO_FILE,
    .file = descriptor,
    .length = length
  };

  return io;
}
