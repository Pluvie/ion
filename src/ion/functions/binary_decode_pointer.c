static inline void binary_decode_pointer (
    struct protocol* decoder
)
{
  struct io* input = decoder->input;
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;
  struct reflect* pointer = schema->child;

read_size:
  u64 pointer_size = 0;

  if (pointer->type == ARRAY) {
    /* Special case: a POINTER size of type ARRAY must be omitted. */
    pointer_size = sizeof(struct array);
    goto allocate_pointer;
  }

  u64* ptr_size = io_read(input, sizeof(u64));
  if (error.occurred)
    return protocol_failure(decoder);

  pointer_size = *ptr_size;

if (pointer->type == CHAR)
  goto check_string_size;
else
  goto check_type_size;

check_type_size:
  u32 pointer_typesize = reflect_typesize(pointer);

  if ((u64) pointer_typesize != pointer_size) {
    fail("pointer required size of %i (%s) but found %li",
      pointer_typesize, type_names[pointer->type], pointer_size);
    return protocol_failure(decoder);
  }

check_string_size:
  u64 pointer_maxsize = schema->bounds[0];

  if (pointer_maxsize > 0 && pointer_size > pointer_maxsize) {
    fail("pointer required maximum string size of %li but found %li",
      pointer_maxsize, pointer_size);
    return protocol_failure(decoder);
  }

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
