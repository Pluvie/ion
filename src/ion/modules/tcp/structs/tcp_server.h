struct tcp_server;
/**
 * Explain the TCP server logic. */
struct tcp_server {
  i32 descriptor;
  u64 timeout_ms;
  const char* ip;
  u16 port;
  u32 connections_limit;
  void (*connector)(struct tcp_server*);
  char client_ip[INET_ADDRSTRLEN];
  padding(8);
};
check_sizeof(struct tcp_server, 64);
