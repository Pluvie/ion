static inline void binary_decode_sequence (
    struct protocol* decoder
)
{
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;

  u64 output_initial_cursor = output->cursor;
  u64 sequence_length = schema->bounds[0];

  struct reflect* sequence = vector_get(schema->child, 0);
  sequence->parent = schema;
  decoder->schema = sequence;

  for (u64 i = 0; i < sequence_length; i++) {
    sequence->index = i;
    binary_decode(decoder);
    if (error.occurred)
      return;
  }

  decoder->schema = schema;

  reflect_validate(schema, output->data + output_initial_cursor);
  if (error.occurred)
    return protocol_failure(decoder);
}
