static inline void binary_decode_pointer (
    struct protocol* decoder
)
{
  struct io* input = decoder->input;
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;
  struct reflect* pointer = vector_get(schema->child, 0);
  u64 pointer_size = reflect_typesize(pointer);

  /* Special case: a POINTER size of type CHAR must be explicitly sent, as its
   * length is not fixed and not known a priori. */
  if (pointer->type == CHAR)
    goto check_string_size;
  else
    goto allocate_pointer;

check_string_size:
  u64 string_max_size = schema->bounds[0];
  u64* string_size = io_read(input, sizeof(u64));
  if (error.occurred)
    return protocol_failure(decoder);

  if (string_max_size > 0 && *string_size > string_max_size) {
    fail("pointer required maximum string size of %li but found %li",
      string_max_size, pointer_size);
    return protocol_failure(decoder);
  }

  pointer_size = *string_size;

allocate_pointer:
  void* pointer_data = memory_alloc(decoder->allocator, pointer_size);
  struct io pointer_output = io_writer(pointer_data, pointer_size);

  pointer->parent = schema;
  decoder->schema = pointer;
  decoder->output = &pointer_output;

  if (pointer->type == CHAR) {
    /* Special case: a POINTER of type CHAR is intended to be a nul-terminated string. */
    for (u64 i = 0; i < pointer_size; i++) {
      binary_decode(decoder);
      if (error.occurred)
        return;
    }

  } else {
    binary_decode(decoder);
    if (error.occurred)
      return;
  }

  decoder->schema = schema;
  decoder->output = output;

write_output:
  u64 pointer_address = (u64) pointer_data;
  io_write(output, &pointer_address, sizeof(u64));
  if (error.occurred)
    return protocol_failure(decoder);
}
