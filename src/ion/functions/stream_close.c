void stream_close (
    struct stream* stream
)
{
#if platform(LINUX)
  fclose(stream->pointer);

#else
  #error "Unsupported platform."
#endif
}
