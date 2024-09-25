void* array_pop (
    struct array* ary
)
{
length_check:
  if (likely(ary->length > 0))
    goto pop;

abort:
  call(fprintf,
    stderr,
    "fatal: popping at 0 length [%p]\n",
    ary);

  abort();

pop:
  initialize(address, void*,
    pointer_offset(ary->data,
      ary->length * ary->typesize));

  decrement(ary->length);

  return address;
}
