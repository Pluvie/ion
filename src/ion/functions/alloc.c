void* alloc (
    int amount,
    int alignment
)
{
#if defined(__WIN32__)
  #error "Not implemented for Windows platform."

#elif defined(__APPLE__)
  #error "Not implemented for Apple platform."

#elif defined(__linux__)
  void* address;
  int result = posix_memalign(&address, alignment, amount);

  if (likely(result == 0))
    return address;

  fail("memory allocation failed: %s", strerror(errno));
  return NULL;

#else
  #error "Unsupported platform."
#endif
}
