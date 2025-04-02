void signal_catch (
    i32 signum
)
{
  struct sigaction signal_action = { .sa_handler = signal_catcher };
  sigemptyset(&signal_action.sa_mask);
  if (sigaction(signum, &signal_action, NULL) != -1)
    return;

  fail("could not set up an intercept for `%s`: %s", strsignal(signum), strerror(errno));
  return;
}
