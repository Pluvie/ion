int stream_flush (
    struct stream* stream
)
{
  return fflush(stream->pointer);
}
