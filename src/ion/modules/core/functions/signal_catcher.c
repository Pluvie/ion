void signal_catcher (
    i32 signum
)
{
  signals_received[signum] = true;
}
