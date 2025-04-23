t* array_last(t) (
    array(t)* array
)
{
  if (unlikely(array->length == 0)) {
    fail("array at 0 length");
    return NULL;
  }

  return array->elements + (array->length - 1);
}
