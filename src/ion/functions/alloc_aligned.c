void* alloc_aligned (
    int amount,
    int alignment
)
{
#if platform(LINUX)
  void* address;
  int result = posix_memalign(&address, alignment, amount);

  if (likely(result == 0))
    return address;

  fatal("aligned alloc failed: %s", strerror(errno));
  return NULL;

#else
  #error "Unsupported platform."
#endif
}
