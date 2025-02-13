static inline void binary_encode_struct (
    struct object* source,
    struct io* target
)
{
  for vector_each(source->reflection->child, struct reflect*, field_reflection) {
    struct object field = {
      .name = field_reflection->name,
      .reflection = field_reflection,
      .address = source->address + field_reflection->offset
    };
    binary_encode(&field, target);
    if (error.occurred)
      return;
  }
}
