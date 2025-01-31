static inline void binary_encode_primitive (
    struct protocol* encoder
)
{
  struct io* input = encoder->input;
  struct io* output = encoder->output;
  struct reflect* schema = encoder->schema;

  u32 type_size = type_sizes[schema->type];
  void* primitive_value = io_read(input, type_size);
  if (error.occurred)
    return protocol_failure(encoder);

  io_write(output, primitive_value, type_size);
  if (error.occurred)
    return protocol_failure(encoder);
}
