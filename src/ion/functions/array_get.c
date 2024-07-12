void* array_get (
    struct array* ary,
    u64 position
)
{
position_check:
  if (likely(position < ary->length))
    goto get;

abort:
  fprintf(stderr, "fatal: position %li out of bounds [%p]\n", position, ary);
  abort();

get:
  return ary->data + (position * ary->typesize);
}
