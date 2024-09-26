#ifdef ION_INCLUDED
static inline
#endif

void* array_push (
    struct array* ary,
    void* element
)
{
grow_check:
  if (likely(ary->length < ary->capacity))
    goto push;

grow:
  void* old_data = ary->data;
  u64 old_capacity = ary->capacity;

  ary->capacity *= 2;
  ary->data = memory_alloc_zero(ary->allocator, ary->capacity * ary->typesize);
  memcpy(ary->data, old_data, old_capacity * ary->typesize);

push:
  void* address = ary->data + (ary->length * ary->typesize);
  memcpy(address, element, ary->typesize);
  ary->length++;

  return address;
}
