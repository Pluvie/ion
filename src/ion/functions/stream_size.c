int stream_size (
    struct stream* stream
)
{
#if platform(LINUX)
  int initial_position = ftell(stream->pointer);
  fseek(stream->pointer, 0L, SEEK_END);

  int length = ftell(stream->pointer);
  fseek(stream->pointer, initial_position, SEEK_SET);

  return length;
#else
  #error "Unsupported platform."
#endif
}
