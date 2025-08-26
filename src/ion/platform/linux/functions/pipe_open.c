struct pipe pipe_open (
    void
)
{
  struct pipe pipes = { 0 }; 

  int result = pipe((int32*) &pipes);
  if (unlikely(result == -1))
    fail("unable to open pipe: %s", strerror(errno));

  return pipes;
}
