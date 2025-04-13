t* array_last(t) (
    array(t)* ary
)
{
  if (unlikely(ary->length == 0)) {
    fail("array at 0 length.");
    return NULL;
  }

  return ary->data + (ary->length - 1);
}
