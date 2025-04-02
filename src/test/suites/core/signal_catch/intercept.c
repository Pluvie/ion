test( signal_catch, intercept ) {

  given("a signal catcher");
    signal_catch(SIGUSR1);


  when("no signal is received");
    verify(signal_received(SIGUSR1) == false);


  calling("raise()");
    raise(SIGUSR1);


  must("catch the raised signal");
    verify(signal_received(SIGUSR1) == true);


  success();
}
