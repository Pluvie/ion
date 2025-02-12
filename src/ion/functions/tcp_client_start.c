#ifdef ION_INCLUDED
static inline
#endif

void tcp_client_start (
    struct tcp_client* client
)
{
  /* Socket setup: TCP network, with reutilization of potentially previously bound
   * sockets. Should an error occur during this phase, the program shall abort. */
  struct sockaddr_in address = { 0 };
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(client->ip);
  address.sin_port = htons(client->port);

  i32 sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    fail("Socket failure: %s.", strerror(errno));
    return;
  }

  i32 connect_outcome = connect(sock, (struct sockaddr*) &address, sizeof(address));
  if (connect_outcome == -1) {
    fail("Socket connect failure: %s.", strerror(errno));
    return;
  }

  client->descriptor = sock;
  return;
}
