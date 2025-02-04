static inline void binary_decode_struct (
    struct io* source,
    struct object* target
)
{
  for vector_each(target->schema->child, struct reflect*, field) {
    struct object field_object = {
      .name = field->name,
      .schema = field,
      .address = target->address + field->offset,
      .allocator = target->allocator
    };

    binary_decode(source, &field_object);
    if (error.occurred)
      return;
  }

  reflect_validate(target->schema, target->address);
  if (error.occurred)
    return reflect_failure(target->schema);
}
