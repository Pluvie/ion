t* array_push(t) (
    array(t)* array,
    t* element
)
{
  if (likely(array->allocator != NULL))
    goto grow_check;

  fail("cannot push on a stack allocated array");
  return NULL;

grow_check:
  if (likely(array->length < array->capacity))
    goto push;

grow:
  t* old_elements = array->elements;
  u64 old_capacity = array->capacity;

  array->capacity *= 2;
  array->elements = memory_alloc_zero(array->allocator, array->capacity * sizeof(t));
  memcpy(array->elements, old_elements, old_capacity * sizeof(t));

push:
  t* address = array->elements + array->length;
  *address = *element;
  array->length++;

  return element;
}
