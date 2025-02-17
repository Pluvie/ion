static inline void binary_encode_sequence (
    struct object* source,
    struct io* target
)
{
  struct reflect* element_reflection = vector_get(source->reflection->child, 0);
  u64 sequence_length = source->reflection->bounds[0];
  u64 sequence_typesize = reflect_typesize(element_reflection);

  for (u64 i = 0; i < sequence_length; i++) {
    element_reflection->index = i;
    struct object element = {
      .reflection = element_reflection,
      .address = source->address + (i * sequence_typesize),
    };
    binary_encode(&element, target);
    if (error.occurred)
      return;
  }
}
