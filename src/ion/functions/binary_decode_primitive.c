static inline void binary_decode_primitive (
    struct protocol* decoder
)
{
  struct io* input = decoder->input;
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;

  u32 type_size = type_sizes[schema->type];
  void* primitive_value = io_read(input, type_size);

  if (error.occurred)
    return protocol_failure(decoder);

  if (schema->type == BOOL) {
    // Special case for booleans: any value other than 0 is considered as `true`.
    if (*(u8*) primitive_value == 0)
      io_write(output, &(bool){ false }, type_size);
    else
      io_write(output, &(bool){ true }, type_size);
  } else {
    io_write(output, primitive_value, type_size);
  }

  if (error.occurred)
    return protocol_failure(decoder);
}
