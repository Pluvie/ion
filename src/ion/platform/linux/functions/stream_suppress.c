void stream_suppress (
    struct stream* stream
)
{
  stream->pointer = fopen("/dev/null", "w");
}
