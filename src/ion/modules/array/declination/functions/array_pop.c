t* array_pop(t) (
    array(t)* array
)
{
  if (unlikely(array->length == 0)) {
    fail("array at 0 length");
    return NULL;
  }

  array->length--;
  return array->elements + array->length;
}
