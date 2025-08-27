struct stream stream_duplicate (
    struct stream* stream
)
{
  struct stream dup = { 0 };

  int underlying_fd = fileno(stream->pointer);
  if (unlikely(underlying_fd < 0)) {
    fail("stream duplicate error: %s", strerror(errno));
    return dup;
  }

  dup.pointer = fdopen(underlying_fd, stream->mode);
  return dup;
}
