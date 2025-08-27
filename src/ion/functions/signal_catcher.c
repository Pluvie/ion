void signal_catcher (
    int signum
)
{
  __signal_received = signum;
}
