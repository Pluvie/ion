#ifdef ION_INCLUDED
static inline
#endif

void tcp_server_start (
    struct tcp_server* server
)
{
  /* Socket setup: TCP network, with reutilization of potentially previously bound
   * sockets. Should an error occur during this phase, the program shall abort. */
  struct sockaddr_in address = { 0 };
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(server->ip);
  address.sin_port = htons(server->port);

  i32 sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    fail("Socket failure: %s.", strerror(errno));
    return;
  }

  const i32 reuse_socket = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse_socket, sizeof(i32));
  i32 bind_outcome = bind(sock, (struct sockaddr*) &address, sizeof(address));
  if (bind_outcome == -1) {
    fail("Socket binding failure: %s.", strerror(errno));
    return;
  }

  i32 listen_outcome = listen(sock, 10);
  if (listen_outcome == -1) {
    fail("Socket listen failure: %s.", strerror(errno));
    return;
  }

  /* Server setup: accepts incoming connection until the *connections_limit* is reached,
   * or accepts indefinitely if *connections_limit* is equal to `0`.
   *
   * The timeout for receiving data after a succesful connection is set by the server
   * *timeout_ms* field. */
  u32 socklen_size = sizeof(address);
  i32 timeout_outcome = -1;
  bool infinite_connections = (server->connections_limit == 0);
  i64 timeout_sec = server->timeout_ms / 1000;
  i64 timeout_usec = (server->timeout_ms * 1000) - timeout_sec;
  struct timeval receive_timeout = { .tv_sec = timeout_sec, .tv_usec = timeout_usec };

  /* Sets up an intercept function for SIGINT signals: they can be used to interrupt
   * the server block while accepting connections. */ 
  struct sigaction signal_action = {
    .sa_handler = tcp_server_sigint,
  };
  sigemptyset(&signal_action.sa_mask);
  if (sigaction(SIGINT, &signal_action, NULL) == -1) {
    fail("Could not set up an intercept for SIGINT: %s", strerror(errno));
    return;
  }

  /* Accepts incoming connection and waits up until 5 seconds to receive data. If no
   * data are received after this timeout, the connection shall be closed. */
  do {
    server->descriptor = accept(sock,
      (struct sockaddr*) &(address),
      (socklen_t*) &socklen_size);

    if (signal_received == SIGINT) {
      print("Interrupt received.");
      break;
    }

    if (server->descriptor == -1)
      continue;

    inet_ntop(AF_INET, &(address.sin_addr), server->client_ip, INET_ADDRSTRLEN);

    timeout_outcome = setsockopt(server->descriptor, SOL_SOCKET, SO_RCVTIMEO,
      (const char*) &receive_timeout, sizeof(receive_timeout));
    if (timeout_outcome == -1) {
      close(server->descriptor);
      continue;
    }

    /* Starts the request handling phase. The logical request handling must be done by
     * the provided *connector* function. */
    server->connector(server);
    server->connections_limit--;

  } while(infinite_connections || server->connections_limit > 0);

  if (server->descriptor > 0)
    close(server->descriptor);

  return;
}
