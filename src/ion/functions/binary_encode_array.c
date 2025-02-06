static inline void binary_encode_array (
    struct object* source,
    struct io* target
)
{
  struct array* array = (struct array*) source->address;

check_minlength:
  u64 array_minlength = source->reflection->bounds[0];
  if (array_minlength > 0 && array->length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, array->length);
    return reflect_failure(source->reflection);
  }

check_maxlength:
  u64 array_maxlength = source->reflection->bounds[1];
  if (array_maxlength > 0 && array->length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, array->length);
    return reflect_failure(source->reflection);
  }

encode_length:
  io_write(target, &(array->length), sizeof(array->length));
  if (error.occurred)
    return reflect_failure(source->reflection);

encode_array:
  struct reflect* element_reflection = vector_get(source->reflection->child, 0);

  for (u64 i = 0; i < array->length; i++) {
    element_reflection->index = i;
    struct object element = {
      .reflection = element_reflection,
      .address = array->data + (i * array->typesize),
    };
    binary_encode(&element, target);
    if (error.occurred)
      return;
  }
}
