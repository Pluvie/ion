spec( socket_init ) {

  argument(string uri);

  when("the uri is not of the type `[tcp|udp|unix]://`") {
    uri = s("abc://my/socket");

    struct socket sock = socket_init(uri);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("socket uri error: must start with [tcp|udp|unix]://"));
    must("return an invalid descriptor");
      verify(sock.descriptor == 0);

    success();
  } end();

  when("the uri is of the type `[tcp|udp|unix]://`") {
    when("the uri protocol is tcp") {
      uri = s("tcp://127.0.0.1:3000");

      struct socket sock = socket_init(uri);

      must("not fail");
        verify(failure.occurred == false);
      must("initialize the ");
        verify(sock.descriptor > 0);

      success();
        socket_close(&sock);
    } end();

    when("the uri protocol is udp") {
      uri = s("udp://127.0.0.1:3000");

      struct socket sock = socket_init(uri);

      must("not fail");
        verify(failure.occurred == false);
      must("return a valid descriptor");
        verify(sock.descriptor > 0);

      success();
        socket_close(&sock);
    } end();

    when("the uri protocol is unix") {
      uri = s("unix:///tmp/my.sock");

      struct socket sock = socket_init(uri);

      must("not fail");
        verify(failure.occurred == false);
      must("return a valid descriptor");
        verify(sock.descriptor > 0);

      success();
        socket_close(&sock);
    } end();
  } end();
}
