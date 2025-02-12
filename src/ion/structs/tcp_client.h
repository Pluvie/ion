struct tcp_client;
/**
 * Explain the TCP client logic. */
struct tcp_client {
  i32 descriptor;
  const char* ip;
  u16 port;
  padding(8);
};
check_sizeof(struct tcp_client, 32);
