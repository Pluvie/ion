static inline void binary_decode_array (
    struct protocol* decoder
)
{
  initialize(input, struct io*, decoder->input);
  initialize(output, struct io*, decoder->output);
  initialize(schema, struct reflect*, decoder->schema);
  initialize(element, struct reflect*, schema->child);
  initialize(array_typesize, u64, call(reflect_typesize, element));

read_length:
  initialize(array_length, u64*, io_read(input, sizeof(u64)));

  if (array_length == NULL)
    return protocol_failure(decoder, "unable to read array length from input "\
      "(%li bytes) : data length is %li bytes, but cursor already at %li",
      sizeof(u64), input->length, input->cursor);

check_minlength:
  u64 array_minlength = schema->bounds[0];
  if (array_minlength > 0 && *array_length < array_minlength)
    return protocol_failure(decoder, "array required minimum length of %li but found %li",
      array_minlength, *array_length);

check_maxlength:
  u64 array_maxlength = schema->bounds[1];
  if (array_maxlength > 0 && *array_length > array_maxlength)
    return protocol_failure(decoder, "array required maximum length of %li but found %li",
      array_maxlength, *array_length);

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
  }

  decoder->schema = schema;
  decoder->output = output;

write_output:
  u64 written_bytes = io_write(output, &array, sizeof(struct array));
  if (written_bytes == 0)
    return protocol_failure(decoder, "unable to write %li bytes to output: data length "\
      "is %li bytes, but cursor already at %li",
      sizeof(struct array), output->length, output->cursor);
}
