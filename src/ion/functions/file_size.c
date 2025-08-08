int file_size (
    void* file
)
{
  if (unlikely(file == NULL))
    return 0;

  int initial_position = ftell(file);
  fseek(file, 0L, SEEK_END);

  int length = ftell(file);
  fseek(file, initial_position, SEEK_SET);

  return length;
}
