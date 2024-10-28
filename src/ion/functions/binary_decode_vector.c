static inline void binary_decode_vector (
    struct protocol* decoder
)
{
  struct io* input = decoder->input;
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;
  struct reflect* element = vector_get(schema->child, 0);
  u64 vector_typesize = reflect_typesize(element);

read_length:
  u64* vector_length = io_read(input, sizeof(u64));
  if (error.occurred)
    return protocol_failure(decoder);

check_minlength:
  u64 vector_minlength = schema->bounds[0];
  if (vector_minlength > 0 && *vector_length < vector_minlength) {
    fail("vector required minimum length of %li but found %li",
      vector_minlength, *vector_length);
    return protocol_failure(decoder);
  }

check_maxlength:
  u64 vector_maxlength = schema->bounds[1];
  if (vector_maxlength > 0 && *vector_length > vector_maxlength) {
    fail("vector required maximum length of %li but found %li",
      vector_maxlength, *vector_length);
    return protocol_failure(decoder);
  }

allocate_vector:
  struct vector vector = vector_init(vector_typesize, *vector_length, decoder->allocator);

decode_vector:
  struct io vector_output = io_writer(vector.data, vector.typesize * vector.length);
  element->parent = schema;
  decoder->schema = element;
  decoder->output = &vector_output;

  for (u64 i = 0; i < vector.length; i++) {
    element->index = i;
    binary_decode(decoder);
    if (error.occurred)
      return;
  }

  decoder->schema = schema;
  decoder->output = output;

validate_vector:
  reflect_validate(schema, &vector);
  if (error.occurred)
    return protocol_failure(decoder);

write_output:
  io_write(output, &vector, sizeof(struct vector));
  if (error.occurred)
    return protocol_failure(decoder);
}
