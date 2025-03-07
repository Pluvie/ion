#ifdef ION_INCLUDED
static inline
#endif

i64 file_size (
    void* file
)
{
  if (unlikely(file == NULL))
    return 0;

  i64 initial_position = ftell(file);
  fseek(file, 0L, SEEK_END);

  i64 length = ftell(file);
  fseek(file, initial_position, SEEK_SET);

  return length;
}
