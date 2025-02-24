static inline void binary_encode_vector (
    struct object* source,
    struct io* target
)
{
  struct vector* vector = (struct vector*) source->address;

check_minlength:
  u64 vector_minlength = source->reflection->bounds[0];
  if (vector_minlength > 0 && vector->length < vector_minlength) {
    fail("vector required minimum length of %li but found %li",
      vector_minlength, vector->length);
    return error_add_reflection_path(source->reflection);
  }

check_maxlength:
  u64 vector_maxlength = source->reflection->bounds[1];
  if (vector_maxlength > 0 && vector->length > vector_maxlength) {
    fail("vector required maximum length of %li but found %li",
      vector_maxlength, vector->length);
    return error_add_reflection_path(source->reflection);
  }

encode_length:
  io_write(target, &(vector->length), sizeof(vector->length));
  if (error.occurred)
    return error_add_reflection_path(source->reflection);

encode_vector:
  struct reflect* element_reflection = vector_get(source->reflection->child, 0);

  for (u64 i = 0; i < vector->length; i++) {
    element_reflection->index = i;
    struct object element = {
      .reflection = element_reflection,
      .address = vector->data + (i * vector->typesize),
    };
    binary_encode(&element, target);
    if (error.occurred)
      return;
  }
}
