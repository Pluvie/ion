test( signal_catch, intercept ) {

  given("a signal catcher");
    struct sigaction signal_action = {
      .sa_handler = signal_catch,
    };
    sigemptyset(&signal_action.sa_mask);
    sigaction(SIGUSR1, &signal_action, NULL);


  when("no signal is received");
    verify(signal_received == 0);


  calling("raise()");
    raise(SIGUSR1);


  must("catch the raised signal");
    verify(signal_received == SIGUSR1);


  success();
    signal_received = 0;
}
