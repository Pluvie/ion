void signal_catch (
    int signum
)
{
  struct sigaction signal_action = { .sa_handler = (void (*)(int32)) signal_catcher };
  sigemptyset(&signal_action.sa_mask);
  if (sigaction(signum, &signal_action, NULL) != -1)
    return;

  fail("signal `%s` catch error: %s", strsignal(signum), strerror(errno));
  return;
}
