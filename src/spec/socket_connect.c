spec( socket_connect ) {

  argument(struct socket* sock);

  precondition("a valid opened socket");
  #define preconditions \
    sock = memory_alloc(spec_allocator, sizeof(struct socket)); \
    *sock = socket_open(uri);

  when("the uri has protocol tcp") {
    when("the uri does not contain a valid IPv4 address") {
      string uri = s("tcp://a.b.c.d:8080");
      apply(preconditions);

      socket_connect(sock);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(streq(failure.message, "socket connect error: Network is unreachable"));

      success();
        socket_close(sock);
    } end();

    when("the IPv4 address is greater than SOCKET_IPV4_MAXLEN") {
      string uri = s("tcp://1234.1234.1234.1234:7777");
      apply(preconditions);

      socket_connect(sock);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(streq(failure.message, "socket uri error: ip too long"));

      success();
        socket_close(sock);
    } end();

    when("the port is greater than SOCKET_PORT_MAXLEN") {
      string uri = s("tcp://123.123.123.123:777777");
      apply(preconditions);

      socket_connect(sock);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(streq(failure.message, "socket uri error: port too long"));

      success();
        socket_close(sock);
    } end();

    when("the uri does contains a valid IPv4 address but not a port") {
      string uri = s("tcp://127.0.0.1");
      apply(preconditions);

      socket_connect(sock);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(streq(failure.message, "socket uri error: missing port"));

      success();
        socket_close(sock);
    } end();

    when("the uri does contains a valid IPv4 address and a port") {
      string uri = s("tcp://127.0.0.1:3000");
      apply(preconditions);

      struct fiber(spec_socket_server) listener = fiber_init(
        spec_socket_server, { .uri = uri, .connector = NULL });
      fiber_spawn(listener);

      socket_connect(sock);

      must("not fail");
        failure_print();
        verify(failure.occurred == false);

      success();
        socket_close(sock);
    } end();
  } end();

  #undef preconditions
}
