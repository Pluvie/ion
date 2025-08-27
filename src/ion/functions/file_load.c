void file_load (
    string file_name,
    void* address
)
{
  struct stream file = stream_open(file_name, "r");
  if (unlikely(failure.occurred))
    return;

  stream_read(&file, address, stream_size(&file));
  if (unlikely(failure.occurred))
    return;

  stream_close(&file);
}
