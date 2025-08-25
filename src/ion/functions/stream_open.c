struct stream stream_open (
    char* name,
    const char* mode
)
{
#if platform(LINUX)
  struct stream stream = { .mode = mode };

  stream.pointer = fopen(name, "r");
  if (unlikely(stream.pointer == NULL))
    fail("error while opening stream: %s", strerror(errno));

  return stream;

#else
  #error "Unsupported platform."
#endif
}
