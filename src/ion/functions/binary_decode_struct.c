static inline void binary_decode_struct (
    struct protocol* decoder
)
{
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;

  u64 output_initial_cursor = output->cursor;
  u32 struct_typesize = schema->bounds[0];

  for vector_each(schema->child, struct reflect*, field) {
    field->parent = schema;
    decoder->schema = field;
    output->cursor = output_initial_cursor + field->offset;
    binary_decode(decoder);
    if (error.occurred)
      return;
  }

  output->cursor = output_initial_cursor + struct_typesize;
  decoder->schema = schema;
}
