t* array_get(t) (
    array(t)* array,
    u64 position
)
{
  if (unlikely(position >= array->length)) {
    fail("position %li out of bounds", position);
    return NULL;
  }

  return array->elements + position;
}
