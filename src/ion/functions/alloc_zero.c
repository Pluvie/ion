void* alloc_zero (
    int amount
)
{
#if platform(LINUX)
  void* result = calloc(1, amount);

  if (likely(result != NULL))
    return result;

  fatal("alloc zero failed: %s", strerror(errno));
  return NULL;

#else
  #error "Unsupported platform."
#endif
}
