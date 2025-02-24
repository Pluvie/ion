static inline void binary_decode_struct (
    struct io* source,
    struct object* target
)
{
  for vector_each(target->reflection->child, struct reflect*, field_reflection) {
    struct object field = {
      .name = field_reflection->name,
      .reflection = field_reflection,
      .address = target->address + field_reflection->offset,
      .allocator = target->allocator
    };

    binary_decode(source, &field);
    if (error.occurred)
      return;
  }

  reflect_validate(target->reflection, target->address);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);
}
