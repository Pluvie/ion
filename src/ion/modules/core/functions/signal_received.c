bool signal_received (
    i32 signum
)
{
  if (signals_received[signum]) {
    signals_received[signum] = false;
    return true;
  }

  return false;
}
