int stream_read (
    struct stream* stream,
    void* address,
    int length
)
{
  int result = fread(address, length, 1, stream->pointer);

  if (unlikely(result != 1)) {
    fail("error while reading from stream: %s", strerror(errno));
    return 0;
  }

  return length;
}
