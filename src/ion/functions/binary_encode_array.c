static inline void binary_encode_array (
    struct protocol* encoder
)
{
  struct io* input = encoder->input;
  struct io* output = encoder->output;
  struct reflect* schema = encoder->schema;

  struct array* array = io_read(input, sizeof(struct array));
  if (error.occurred)
    return protocol_failure(encoder);

check_minlength:
  u64 array_minlength = schema->bounds[0];
  if (array_minlength > 0 && array->length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, array->length);
    return protocol_failure(encoder);
  }

check_maxlength:
  u64 array_maxlength = schema->bounds[1];
  if (array_maxlength > 0 && array->length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, array->length);
    return protocol_failure(encoder);
  }

encode_length:
  io_write(output, &(array->length), sizeof(array->length));
  if (error.occurred)
    return protocol_failure(encoder);

encode_array:
  struct io array_input = io_reader(array->data, array->typesize * array->length);
  struct reflect* element = vector_get(schema->child, 0);
  element->parent = schema;
  encoder->schema = element;
  encoder->input = &array_input;

  for (u64 i = 0; i < array->length; i++) {
    element->index = i;
    binary_encode(encoder);
    if (error.occurred)
      return;
  }

  encoder->schema = schema;
  encoder->input = input;
}
