t* array_get(t) (
    array(t)* ary,
    u64 position
)
{
  if (unlikely(position >= ary->length)) {
    fail("position %li out of bounds", position);
    return NULL;
  }

  return ary->data + position;
}
