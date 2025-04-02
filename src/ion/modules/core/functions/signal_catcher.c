void signal_catcher (
    i32 signum
)
{
  signal_received = signum;
}
