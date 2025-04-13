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
  t* old_elements = ary->elements;
  u64 old_capacity = ary->capacity;

  ary->capacity *= 2;
  ary->elements = memory_alloc_zero(ary->allocator, ary->capacity * sizeof(t));
  memcpy(ary->elements, old_elements, old_capacity * sizeof(t));

push:
  t* address = ary->elements + ary->length;
  *address = *element;
  ary->length++;

  return element;
}
