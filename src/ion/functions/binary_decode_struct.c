static inline void binary_decode_struct (
    struct protocol* decoder
)
{
  struct io* output = decoder->output;
  struct reflect* schema = decoder->schema;

  u64 output_initial_cursor = output->cursor;
  u64 struct_typesize = schema->bounds[0];
  u64 fields_count = schema->bounds[1];
  struct reflect* field = schema->child;

  for (u64 i = 0; i < fields_count; i++) {
    field->parent = schema;
    decoder->schema = field;
    output->cursor = output_initial_cursor + field->offset;
    binary_decode(decoder);
    field++;

    if (error.occurred)
      return;
  }

  output->cursor = output_initial_cursor + struct_typesize;
  decoder->schema = schema;
}
