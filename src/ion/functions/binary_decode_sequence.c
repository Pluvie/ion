static inline void binary_decode_sequence (
    struct protocol* decoder
)
{
  struct reflect* schema = decoder->schema;
  u64 sequence_length = schema->bounds[0];

  struct reflect* sequence = schema->child;
  sequence->parent = schema;
  decoder->schema = sequence;

  for (u64 i = 0; i < sequence_length; i++) {
    sequence->index = i;
    binary_decode(decoder);
  }

  decoder->schema = schema;
}
