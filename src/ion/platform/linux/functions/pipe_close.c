void pipe_close (
    struct pipe* pipes
)
{
  close(pipes->reader);
  close(pipes->writer);
}
