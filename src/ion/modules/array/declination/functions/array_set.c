t* array_(set, t) (
    array(t)* ary,
    u64 position,
    t* element
)
{
  if (unlikely(position >= ary->length)) {
    fail("position %li out of bounds.", position);
    return NULL;
  }

  t* address = ary->data + position;
  *address = *element;
  return element;
}
