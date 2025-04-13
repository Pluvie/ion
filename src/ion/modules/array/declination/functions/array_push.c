t* array_push(t) (
    array(t)* ary,
    t* element
)
{
grow_check:
  if (likely(ary->length < ary->capacity))
    goto push;

grow:
  t* old_data = ary->data;
  u64 old_capacity = ary->capacity;

  ary->capacity *= 2;
  ary->data = memory_alloc_zero(ary->allocator, ary->capacity);
  memcpy(ary->data, old_data, old_capacity);

push:
  t* address = ary->data + ary->length;
  *address = *element;
  ary->length++;

  return element;
}
