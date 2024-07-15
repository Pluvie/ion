static inline void* io_read_file (
    struct io* reader,
    u64 amount
)
{
  fprintf(stderr, "not implemented: io read for type IO_TYPE_FILE\n");
  abort();
  return NULL;
}
