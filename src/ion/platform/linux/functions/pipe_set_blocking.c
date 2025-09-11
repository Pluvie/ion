void pipe_set_blocking (
    struct pipe* pipes,
    bool blocking
)
{
  int existing_flags = fcntl(pipes->reader, F_GETFL);
  if (unlikely(existing_flags < 0)) {
    fail("unable to get flags: %s", strerror(errno));
    return;
  }

  int new_flags = existing_flags;
  if (blocking)
    new_flags &= ~O_NONBLOCK;
  else
    new_flags |= O_NONBLOCK;

  int result = fcntl(pipes->reader, F_SETFL, new_flags);
  if (unlikely(result < 0)) {
    fail("unable to set flags: %s", strerror(errno));
    return;
  }

  return;
}
