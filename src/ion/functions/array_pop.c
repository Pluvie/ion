void* array_pop (
    struct array* ary
)
{
length_check:
  if (likely(ary->length > 0))
    goto pop;

abort:
  fprintf(stderr,
    "fatal: popping at 0 length [%p]\n",
    ary);

  abort();

pop:
  void* address = ary->data + (ary->length * ary->typesize);
  ary->length--;
  return address;
}
