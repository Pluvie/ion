void* array_push (
    struct array* ary,
    void* element
)
{
grow_check:
  if (likely(ary->length < ary->capacity))
    goto push;

grow:
  initialize(old_data, void*, ary->data);
  initialize(old_capacity, u64, ary->capacity);

  assign_to(ary->capacity, ary->capacity * 2);
  assign_to(ary->data,
    call(memory_alloc_zero,
      ary->allocator, ary->capacity * ary->typesize));

  call(memcpy,
    ary->data, old_data, old_capacity * ary->typesize);

push:
  initialize(address, void*,
    pointer_offset(ary->data,
      ary->length * ary->typesize));

  call(memcpy,
    address, element, ary->typesize);

  increment(ary->length);

  return address;
}
