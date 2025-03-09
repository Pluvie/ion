void tcp_server_sigint(
    i32 signum
)
{
  signal_received = SIGINT;
}
