t* array_push(t) (
    array(t)* ary,
    t* element
)
{
  if (likely(ary->allocator != NULL))
    goto grow_check;

  fail("cannot push on a stack allocated array");
  return NULL;

grow_check:
  if (likely(ary->length < ary->capacity))
    goto push;

grow:
  t* old_data = ary->data;
  u64 old_capacity = ary->capacity;

  ary->capacity *= 2;
  ary->data = memory_alloc_zero(ary->allocator, ary->capacity * sizeof(t));
  memcpy(ary->data, old_data, old_capacity * sizeof(t));

push:
  t* address = ary->data + ary->length;
  *address = *element;
  ary->length++;

  return element;
}
