t* array_set(t) (
    array(t)* array,
    u64 position,
    t* element
)
{
  if (unlikely(position >= array->length)) {
    fail("position %li out of bounds", position);
    return NULL;
  }

  t* address = array->elements + position;
  *address = *element;
  return element;
}
