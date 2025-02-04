static inline void binary_decode_sequence (
    struct io* source,
    struct object* target
)
{
  struct reflect* element = vector_get(target->schema->child, 0);
  u64 sequence_length = target->schema->bounds[0];
  u64 sequence_typesize = reflect_typesize(element);

  for (u64 i = 0; i < sequence_length; i++) {
    element->index = i;
    struct object element_object = {
      .schema = element,
      .address = target->address + (i * sequence_typesize),
      .allocator = target->allocator
    };
    binary_decode(source, &element_object);
    if (error.occurred)
      return;
  }

  reflect_validate(target->schema, target->address);
  if (error.occurred)
    return reflect_failure(target->schema);
}
