struct stream stream_open (
    string name,
    const char* mode
)
{
  struct stream stream = { .name = name, .mode = mode };

  stream.pointer = fopen(name.pointer, mode);
  if (unlikely(stream.pointer == NULL))
    fail("error while opening stream: %s", strerror(errno));

  return stream;
}
