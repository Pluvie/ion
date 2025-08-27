spec( socket_open ) {

  argument(string uri);

  when("the uri is not valid") {
    uri = s("abc://my/socket");

    struct socket sock = socket_open(uri);

    must("fail");
      verify(failure.occurred == true);
    must("return an empty socket");
      verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
    must("return an invalid descriptor");
      verify(sock.descriptor <= 0);

    success();
  } end();

  when("the uri valid") {
    uri = s("tcp://127.0.0.1:3000");

    struct socket sock = socket_open(uri);

    must("not fail");
      verify(failure.occurred == false);
    must("return a valid descriptor");
      verify(sock.descriptor > 0);

    success();
      socket_close(&sock);
  } end();
}
