spec( socket_connect ) {

  argument(struct socket* sock);

  precondition("a valid opened socket");
  #define preconditions \
    sock = memory_alloc(spec_allocator, sizeof(struct socket)); \
    *sock = socket_open(uri);

  when("uri points to a socket accepting connections") {
    string uri = s("tcp://127.0.0.1:3000");

    struct fiber(spec_socket_server) listener = fiber_init(
      spec_socket_server, { .uri = uri, .connector = NULL });
    fiber_spawn(listener);

    apply(preconditions);
    sleep_ms(10);
    socket_connect(sock);

    must("not fail");
      verify(failure.occurred == false);

    success();
      fiber_wait(listener);
      socket_close(sock);
  } end();

  #undef preconditions
}
