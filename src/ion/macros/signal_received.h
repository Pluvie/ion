/**
 * Checks whether the process has received the specified signal. */
#define signal_received(signum) \
  (__signal_received == signum && (__signal_received = 0))
