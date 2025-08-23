void pipe_close (
    struct pipe* pipes
)
{
#if platform(LINUX)
  close(pipes->reader);
  close(pipes->writer);

#else
  #error "Unsupported platform."
#endif
}
