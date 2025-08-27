void signal_send (
    int signum
)
{
  raise(signum);
}
