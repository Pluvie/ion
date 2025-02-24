static inline void binary_decode_sequence (
    struct io* source,
    struct object* target
)
{
  struct reflect* element_reflection = vector_get(target->reflection->child, 0);
  u64 sequence_length = target->reflection->bounds[0];
  u64 sequence_typesize = reflect_typesize(element_reflection);

  for (u64 i = 0; i < sequence_length; i++) {
    element_reflection->index = i;
    struct object element = {
      .reflection = element_reflection,
      .address = target->address + (i * sequence_typesize),
      .allocator = target->allocator
    };
    binary_decode(source, &element);
    if (error.occurred)
      return;
  }

  reflect_validate(target->reflection, target->address);
  if (error.occurred)
    return error_add_reflection_path(target->reflection);
}
