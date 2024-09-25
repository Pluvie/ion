void* array_last (
    struct array* ary
)
{
length_check:
  if (likely(ary->length > 0))
    goto last;

abort:
  call(fprintf,
    stderr,
    "fatal: getting last at 0 length [%p]\n",
    ary);

  abort();

last:
  return pointer_offset(ary->data,
    (ary->length - 1) * ary->typesize);
}
