static inline void binary_decode_primitive (
    struct protocol* decoder
)
{
  struct io* input = decoder->input;
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;

  u32 type_size = type_sizes[schema->type];
  void* primitive_value = io_read(input, type_size);

  if (primitive_value == NULL)
    return protocol_failure(decoder,
      "unable to read %i bytes from input: data length is %li bytes, but cursor "\
        "already at %li",
      type_size, input->length, input->cursor);

  u64 written_bytes;
  if (schema->type == BOOL) {
    // Special case for booleans: any value other than 0 is considered as `true`.
    if (*(u8*) primitive_value == 0)
      written_bytes = io_write(output, &(bool){ false }, type_size);
    else
      written_bytes = io_write(output, &(bool){ true }, type_size);
  } else {
    written_bytes = io_write(output, primitive_value, type_size);
  }

  if (written_bytes == 0)
    return protocol_failure(decoder,
      "unable to write %i bytes to output: data length is %li bytes, but cursor "\
      "already at %li",
      type_size, output->length, output->cursor);
}
