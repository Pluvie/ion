static inline void binary_decode_array (
    struct protocol* decoder
)
{
  struct io* input = decoder->input;
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;
  struct reflect* element = vector_get(schema->child, 0);
  u64 array_typesize = reflect_typesize(element);

read_length:
  u64* array_length = io_read(input, sizeof(u64));
  if (error.occurred)
    return protocol_failure(decoder);

check_minlength:
  u64 array_minlength = schema->bounds[0];
  if (array_minlength > 0 && *array_length < array_minlength) {
    fail("array required minimum length of %li but found %li",
      array_minlength, *array_length);
    return protocol_failure(decoder);
  }

check_maxlength:
  u64 array_maxlength = schema->bounds[1];
  if (array_maxlength > 0 && *array_length > array_maxlength) {
    fail("array required maximum length of %li but found %li",
      array_maxlength, *array_length);
    return protocol_failure(decoder);
  }

allocate_array:
  struct array array = array_init(array_typesize, *array_length, decoder->allocator);
  array.length = *array_length;

decode_array:
  struct io array_output = io_writer(array.data, array.typesize * array.capacity);
  element->parent = schema;
  decoder->schema = element;
  decoder->output = &array_output;

  for (u64 i = 0; i < array.length; i++) {
    element->index = i;
    binary_decode(decoder);
    if (error.occurred)
      return;
  }

  decoder->schema = schema;
  decoder->output = output;

validate_array:
  reflect_validate(schema, &array);
  if (error.occurred)
    return protocol_failure(decoder);

write_output:
  io_write(output, &array, sizeof(struct array));
  if (error.occurred)
    return protocol_failure(decoder);
}
