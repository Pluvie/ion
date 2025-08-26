void stream_close (
    struct stream* stream
)
{
  fclose(stream->pointer);
}
