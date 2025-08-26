void* alloc (
    int amount
)
{
  void* result = malloc(amount);

  if (likely(result != NULL))
    return result;

  fatal("alloc failed: %s", strerror(errno));
  return NULL;
}
