int socket_read (
    int sockfd,
    void* address,
    int amount,
    int32 flags
)
{
#if platform(LINUX)
  int read_bytes = recv(sockfd, address, amount, flags);
  if (unlikely(read_bytes < 0)) {
    fail("socket read error: %s", strerror(errno));
    return 0;
  }

  return read_bytes;

#else
  #error "Unsupported platform."
#endif
}
