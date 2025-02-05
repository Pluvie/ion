static inline void binary_encode_array (
    struct object* source,
    struct io* target
)
{
  struct array* array = (struct array*) source->address;

check_minlength:
  u64 array_minlength = source->schema->bounds[0];
  if (array_minlength > 0 && array->length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, array->length);
    return reflect_failure(source->schema);
  }

check_maxlength:
  u64 array_maxlength = source->schema->bounds[1];
  if (array_maxlength > 0 && array->length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, array->length);
    return reflect_failure(source->schema);
  }

encode_length:
  io_write(target, &(array->length), sizeof(array->length));
  if (error.occurred)
    return reflect_failure(source->schema);

encode_array:
  struct reflect* element = vector_get(source->schema->child, 0);

  for (u64 i = 0; i < array->length; i++) {
    element->index = i;
    struct object element_object = {
      .schema = element,
      .address = array->data + (i * array->typesize),
    };
    binary_encode(&element_object, target);
    if (error.occurred)
      return;
  }
}
