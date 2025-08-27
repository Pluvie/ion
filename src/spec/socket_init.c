spec( socket_init ) {

  argument(string uri);

  when("the uri is not of type `[tcp|udp]://`") {
    uri = s("abc://my/socket");

    struct socket sock = socket_init(uri);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("socket uri error: must start with [tcp|udp]://"));
    must("return an empty socket");
      verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
    success();
  } end();

  when("the uri is of type `[tcp|udp]://`") {
    when("the protocol is TCP") {
      when("the resource is empty") {
        uri = s("tcp://");

        struct socket sock = socket_init(uri);

        must("fail with a specific error");
          verify(failure.occurred == true);
          verify(failure_is("socket uri error: invalid"));
        must("return an empty socket");
          verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
        success();
      } end();

      when("the resource is an IPv4") {
        when("the resource does not have a port") {
          uri = s("tcp://127.0.0.1");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: missing port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has an invalid port") {
          uri = s("tcp://127.0.0.1:30a0");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: invalid port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has a valid IPv4 and port") {
          uri = s("tcp://127.0.0.1:3000");

          struct socket sock = socket_init(uri);

          must("not fail");
            verify(failure.occurred == false);
          must("initialize the protocol");
            verify(sock.protocol == SOCKET_TCP);
          must("initialize the type");
            verify(sock.type == SOCKET_IP_V4);
          must("initialize the port");
            verify(sock.port == 3000);
          must("initialize the ip");
            verify(eq(sock.ipv4, "127.0.0.1"));
          success();
        } end();
      } end();

      when("the resource is an IPv6") {
        when("the resource does not have a port") {
          uri = s("tcp://[::1]");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: missing port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has an invalid port") {
          uri = s("tcp://[::1]:30a0");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: invalid port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has a valid IPv6 and port") {
          uri = s("tcp://[::1]:3000");

          struct socket sock = socket_init(uri);

          must("not fail");
            verify(failure.occurred == false);
          must("initialize the protocol");
            verify(sock.protocol == SOCKET_TCP);
          must("initialize the type");
            verify(sock.type == SOCKET_IP_V6);
          must("initialize the port");
            verify(sock.port == 3000);
          must("initialize the ip");
            verify(eq(sock.ipv4, "::1"));
          success();
        } end();
      } end();

      when("the resource is a path") {
        uri = s("tcp://path/to/my/socket");

        struct socket sock = socket_init(uri);

        must("not fail");
          verify(failure.occurred == false);
        must("initialize the protocol");
          verify(sock.protocol == SOCKET_TCP);
        must("initialize the type");
          verify(sock.type == SOCKET_LOCAL);
        must("not initialize the port");
          verify(sock.port == 0);
        must("initialize the ip");
          verify(eq(sock.path, "path/to/my/socket"));
        success();
      } end();
    } end();


    when("the protocol is UDP") {
      when("the resource is empty") {
        uri = s("udp://");

        struct socket sock = socket_init(uri);

        must("fail with a specific error");
          verify(failure.occurred == true);
          verify(failure_is("socket uri error: invalid"));
        must("return an empty socket");
          verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
        success();
      } end();

      when("the resource is an IPv4") {
        when("the resource does not have a port") {
          uri = s("udp://127.0.0.1");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: missing port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has an invalid port") {
          uri = s("udp://127.0.0.1:30a0");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: invalid port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has a valid IPv4 and port") {
          uri = s("udp://127.0.0.1:3000");

          struct socket sock = socket_init(uri);

          must("not fail");
            verify(failure.occurred == false);
          must("initialize the protocol");
            verify(sock.protocol == SOCKET_UDP);
          must("initialize the type");
            verify(sock.type == SOCKET_IP_V4);
          must("initialize the port");
            verify(sock.port == 3000);
          must("initialize the ip");
            verify(eq(sock.ipv4, "127.0.0.1"));
          success();
        } end();
      } end();

      when("the resource is an IPv6") {
        when("the resource does not have a port") {
          uri = s("udp://[::1]");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: missing port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has an invalid port") {
          uri = s("udp://[::1]:30a0");

          struct socket sock = socket_init(uri);

          must("fail with a specific error");
            verify(failure.occurred == true);
            verify(failure_is("socket uri error: invalid port"));
          must("return an empty socket");
            verify(byte_eq(&sock, &(struct socket) { 0 }, sizeof(sock)));
          success();
        } end();

        when("the resource has a valid IPv6 and port") {
          uri = s("udp://[::1]:3000");

          struct socket sock = socket_init(uri);

          must("not fail");
            verify(failure.occurred == false);
          must("initialize the protocol");
            verify(sock.protocol == SOCKET_UDP);
          must("initialize the type");
            verify(sock.type == SOCKET_IP_V6);
          must("initialize the port");
            verify(sock.port == 3000);
          must("initialize the ip");
            verify(eq(sock.ipv4, "::1"));
          success();
        } end();
      } end();

      when("the resource is a path") {
        uri = s("udp://path/to/my/socket");

        struct socket sock = socket_init(uri);

        must("not fail");
          verify(failure.occurred == false);
        must("initialize the protocol");
          verify(sock.protocol == SOCKET_UDP);
        must("initialize the type");
          verify(sock.type == SOCKET_LOCAL);
        must("not initialize the port");
          verify(sock.port == 0);
        must("initialize the ip");
          verify(eq(sock.path, "path/to/my/socket"));
        success();
      } end();
    } end();
  } end();
}
