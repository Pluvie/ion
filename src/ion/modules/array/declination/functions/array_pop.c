t* array_pop(t) (
    array(t)* ary
)
{
  if (unlikely(ary->length == 0)) {
    fail("array at 0 length");
    return NULL;
  }

  ary->length--;
  return ary->elements + ary->length;
}
