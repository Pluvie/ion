static inline void binary_encode_struct (
    struct protocol* encoder
)
{
  struct io* input = encoder->input;
  struct reflect* schema = encoder->schema;

  u64 input_initial_cursor = input->cursor;
  u32 struct_typesize = schema->bounds[0];

  for vector_each(schema->child, struct reflect*, field) {
    field->parent = schema;
    encoder->schema = field;
    input->cursor = input_initial_cursor + field->offset;
    binary_encode(encoder);
    if (error.occurred)
      return;
  }

  input->cursor = input_initial_cursor + struct_typesize;
  encoder->schema = schema;
}
